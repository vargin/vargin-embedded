#ifndef MIKATRON_CLOCK_H
#define MIKATRON_CLOCK_H

#define RTC_ADDRESS  0x68

#define ALARM1_SECONDS_ADDRESS 0x07
#define ALARM1_MINUTES_ADDRESS 0x08
#define ALARM1_HOURS_ADDRESS 0x09

// Alarm 1 mask bits. Inspired by https://github.com/JChristensen/DS3232RTC.
#define A1M1 7
#define A1M2 7
#define A1M3 7
#define A1M4 7

#define RTC_CONTROL_ADDRESS 0x0E

#define CONTROL_A1IE  0
#define CONTROL_INTCN 2
#define CONTROL_RS1   3
#define CONTROL_RS2   4

enum Alarm1Type {
  // Fire alarm every second.
  EVERY_SECOND = 0x0F,
  // Fire alarm when seconds match.
  MATCH_SECONDS = 0x0E,
  // Fire alarm when minutes and seconds match.
  MATCH_MINUTES = 0x0C,
  // Fire alarm when hours and minutes and seconds match.
  MATCH_HOURS = 0x08
};

enum SquareWaveFrequency {
  SQWAVE_1_HZ    = 0x00,
  SQWAVE_1024_HZ = 0x08,
  SQWAVE_4096_HZ = 0x10,
  SQWAVE_8192_HZ = 0x18
};

class ClockTime {
public:
  ClockTime(uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
  uint8_t hour() const        { return hh; }
  uint8_t minute() const      { return mm; }
  uint8_t second() const      { return ss; }
protected:
  uint8_t hh, mm, ss;
};

class Clock {
public:
  static void setTime(const ClockTime& time);
  static ClockTime getTime();
  static void setAlarm(Alarm1Type type, const ClockTime& time);
  static ClockTime getAlarm();
  static void enableSquareWave(SquareWaveFrequency frequency);
};

#endif //MIKATRON_CLOCK_H
