#include <avr/io.h>
#include <util/delay.h>
#include "clock.h"
#include "TinyWireM.h"

#define RTC_ADDRESS  0x68

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