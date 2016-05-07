#include <avr/io.h>
#include <util/delay.h>
#include "clock.h"
#include "TinyWireM.h"

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

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(RTC_STATUS_ADDRESS);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 1);
  uint8_t status = bcd2bin(TinyWireM.read());

  status &= ~_BV(A1F);

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(RTC_STATUS_ADDRESS);
  TinyWireM.write(status);
  TinyWireM.endTransmission();

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

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(RTC_CONTROL_ADDRESS);
  TinyWireM.endTransmission();

  // Enable interrupt generation once alarm fires.
  TinyWireM.requestFrom(RTC_ADDRESS, 1);
  uint8_t control = bcd2bin(TinyWireM.read());

  control |= _BV(CONTROL_INTCN) | _BV(CONTROL_A1IE);

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(RTC_CONTROL_ADDRESS);
  TinyWireM.write(control);
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
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(RTC_CONTROL_ADDRESS);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 1);
  uint8_t control = bcd2bin(TinyWireM.read());

  // Reset frequency to default.
  control &= ~(_BV(CONTROL_RS1) | _BV(CONTROL_RS2));

  if (frequency == SquareWaveFrequency::NO_WAVE) {
    control |= _BV(CONTROL_INTCN);
  } else {
    control &= ~_BV(CONTROL_INTCN);
    control |= frequency;
  }

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(RTC_CONTROL_ADDRESS);
  TinyWireM.write(control);
  TinyWireM.endTransmission();
}
