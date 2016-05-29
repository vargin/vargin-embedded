#include <avr/io.h>
#include <stdlib.h>
#include "clock.h"

const uint8_t MAX_ALARM_COUNT = 20;

ClockTime alarms[MAX_ALARM_COUNT];
uint8_t alarmCount = 0;

static int clockTimeSorter(const void *pLhs, const void *pRhs) {
  const ClockTime *lhs = (const ClockTime *)pLhs;
  const ClockTime *rhs = (const ClockTime *)pRhs;

  if (lhs->hour() != rhs->hour()) {
    return lhs->hour() - rhs->hour();
  }

  if (lhs->minute() != rhs->minute()) {
    return lhs->minute() - rhs->minute();
  }

  return lhs->second() - rhs->second();
}

/**
 * Converts binary coded decimal to decimal, e.g. 0101 0100/0x54/54: 0x54 - 6 * (0x54 >> 4) =
 * 0x54 - 0x1e = 0x36/54.
 * @param val
 * @return
 */
static uint8_t bcd2bin(uint8_t val) {
  return val - 6 * (val >> 4);
}

static uint8_t bin2bcd(uint8_t val) {
  return val + 6 * (val / 10);
}

ClockTime::ClockTime(uint8_t hour, uint8_t min, uint8_t sec) {
  hh = hour;
  mm = min;
  ss = sec;
}

bool ClockTime::operator==(const ClockTime &other) {
  return this->hour() == other.hour() &&
          this->minute() == other.minute() &&
          this->second() == other.second();
}

bool ClockTime::operator<(const ClockTime &other) {
  return this->hour() <= other.hour() &&
         this->minute() <= other.minute() &&
         this->second() < other.second();
}

void Clock::setTime(const ClockTime& time) {
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(0);
  TinyWireM.write(bin2bcd(time.second()));
  TinyWireM.write(bin2bcd(time.minute()));
  TinyWireM.write(bin2bcd(time.hour()));
  TinyWireM.endTransmission();
}

ClockTime Clock::getTime() {
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(0);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 3);
  uint8_t ss = bcd2bin(TinyWireM.read() & 0x7F);
  uint8_t mm = bcd2bin(TinyWireM.read());
  uint8_t hh = bcd2bin(TinyWireM.read());

  return ClockTime(hh, mm, ss);
}

void Clock::setAlarm(Alarm1Type type, const ClockTime& time) {
  Clock::setSquareWave(SquareWaveFrequency::NO_WAVE);
  Clock::writeByte(
      RTC_STATUS_ADDRESS,
      Clock::readByte(RTC_STATUS_ADDRESS) & ~_BV(A1F)
  );

  uint8_t seconds = bin2bcd(time.second());
  uint8_t minutes = bin2bcd(time.minute());
  uint8_t hours = bin2bcd(time.hour());
  uint8_t date = 0;

  if (type == Alarm1Type::EVERY_SECOND) {
    seconds |= _BV(A1M1);
  } else {
    seconds &= ~_BV(A1M1);
  }

  if (type == Alarm1Type::EVERY_SECOND || type == Alarm1Type::MATCH_SECONDS) {
    minutes |= _BV(A1M2);
  } else {
    minutes &= ~_BV(A1M2);
  }

  if (type == Alarm1Type::EVERY_SECOND || type == Alarm1Type::MATCH_SECONDS ||
      type == Alarm1Type::MATCH_MINUTES) {
    hours |= _BV(A1M3);
  } else {
    hours &= ~_BV(A1M3);
  }

  date |= _BV(A1M4);

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(ALARM1_SECONDS_ADDRESS);
  TinyWireM.write(seconds);
  TinyWireM.write(minutes);
  TinyWireM.write(hours);
  TinyWireM.write(date);
  TinyWireM.endTransmission();

  Clock::writeByte(
      RTC_CONTROL_ADDRESS,
      Clock::readByte(RTC_CONTROL_ADDRESS) | _BV(CONTROL_INTCN) | _BV(CONTROL_A1IE)
  );
}

void Clock::resetAlarm() {
  Clock::writeByte(
    RTC_STATUS_ADDRESS,
    Clock::readByte(RTC_STATUS_ADDRESS) & ~_BV(A1F)
  );

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(ALARM1_SECONDS_ADDRESS);
  TinyWireM.write(0);
  TinyWireM.write(0);
  TinyWireM.write(0);
  TinyWireM.write(0);
  TinyWireM.endTransmission();
}

ClockTime Clock::getAlarm() {
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(ALARM1_SECONDS_ADDRESS);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 3);
  uint8_t ss = bcd2bin(TinyWireM.read() & 0x7F);
  uint8_t mm = bcd2bin(TinyWireM.read() & 0x7F);
  uint8_t hh = bcd2bin(TinyWireM.read() & 0x7F);

  return ClockTime(hh, mm, ss);
}

void Clock::setSquareWave(SquareWaveFrequency frequency) {
  // Reset frequency to default.
  uint8_t control = Clock::readByte(RTC_CONTROL_ADDRESS) & ~(_BV(CONTROL_RS1) | _BV(CONTROL_RS2));

  if (frequency == SquareWaveFrequency::NO_WAVE) {
    control |= _BV(CONTROL_INTCN);
  } else {
    control &= ~_BV(CONTROL_INTCN);
    control |= frequency;
  }

  Clock::writeByte(RTC_CONTROL_ADDRESS, control);
}

uint8_t Clock::readByte(uint8_t address) {
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(address);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 1);
  return TinyWireM.read();
}

void Clock::writeByte(uint8_t address, uint8_t data) {
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(address);
  TinyWireM.write(data);
  TinyWireM.endTransmission();
}

void Clock::toggle32K(bool toggle) {
  uint8_t status = Clock::readByte(RTC_STATUS_ADDRESS);
  const bool is32KEnabled = status & _BV(EN32kHz);
  if (is32KEnabled != toggle) {
    Clock::writeByte(
      RTC_STATUS_ADDRESS,
      toggle ? (status | _BV(EN32kHz)) : (status & ~_BV(EN32kHz))
    );
  }
}

ClockTime Clock::getNextAlarm() {
  Clock::refreshAlarms();

  ClockTime currentTime = Clock::getTime();

  for (uint8_t i = 0; i < alarmCount; i++) {
    ClockTime alarm = alarms[i];

    if (currentTime < alarm) {
      return alarm;
    }
  }

  return alarmCount > 0 ? alarms[0] : NULL;
}

void Clock::addAlarm(const ClockTime &time) {
  if (Clock::hasAlarm(time)) {
    return;
  }

  alarms[alarmCount++] = time;

  // Order all alarms.
  qsort(alarms, alarmCount, sizeof(ClockTime), clockTimeSorter);

  // Add new alarm to the end of the list.
  Storage::write(alarmCount * 3 - 2, bin2bcd(time.hour()));
  Storage::write(alarmCount * 3 - 1, bin2bcd(time.minute()));
  Storage::write(alarmCount * 3, bin2bcd(time.second()));

  // Write new length.
  Storage::write(0, alarmCount);

  ClockTime nextAlarm = Clock::getNextAlarm();

  // If next alarm should be the new one, let's set it.
  if (nextAlarm == time) {
    Clock::setAlarm(Alarm1Type::MATCH_HOURS, time);
  }
}
bool Clock::hasAlarm(const ClockTime &time) {
  Clock::refreshAlarms();

  for (uint8_t i = 0; i < alarmCount; i++) {
    ClockTime alarm = alarms[i];

    if (alarms[i] == time) {
      return true;
    }
  }

  return false;
}

void Clock::clearAlarms() {
  for (uint8_t i = 0; i < alarmCount; i++) {
    alarms[i] = NULL;
  }

  alarmCount = 0;

  Storage::write(0, alarmCount);
}

void Clock::refreshAlarms() {
  if (alarmCount != 0) {
    return;
  }

  // If we don't have any alarms let's check if just haven't loaded them yet.
  alarmCount = Storage::read(0);

  for (uint8_t i = 0; i < alarmCount; i++) {
    alarms[i] = ClockTime(
      bcd2bin(Storage::read(i * 3 + 1)),
      bcd2bin(Storage::read(i * 3 + 2)),
      bcd2bin(Storage::read(i * 3 + 3))
    );
  }
}