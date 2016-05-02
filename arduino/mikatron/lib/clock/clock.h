#ifndef MIKATRON_CLOCK_H
#define MIKATRON_CLOCK_H

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
};

#endif //MIKATRON_CLOCK_H
