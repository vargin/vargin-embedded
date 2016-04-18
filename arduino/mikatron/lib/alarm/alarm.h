#ifndef MIKATRON_ALARM_H
#define MIKATRON_ALARM_H

class Alarm {
public:
  static void play();

private:
  static void tone(unsigned char divisor, unsigned char octave, unsigned long duration);
  static void delay_ms(unsigned long delay);
};

#endif //MIKATRON_ALARM_H
