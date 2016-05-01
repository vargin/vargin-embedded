#ifndef MIKATRON_CLOCK_H
#define MIKATRON_CLOCK_H

class Clock {
public:
  static void setTime(uint8_t bcdHour, uint8_t bcdMinute, uint8_t bcdSecond);
};

#endif //MIKATRON_CLOCK_H
