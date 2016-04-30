#ifndef MIKATRON_SPEAKER_H
#define MIKATRON_SPEAKER_H

class Speaker {
public:
  static void melody();
  static void beep();
  static void doubleBeep();
  static void modeMelody();

private:
  static void tone(unsigned char divisor, unsigned char octave, unsigned long duration);
  static void delay_ms(unsigned long delay);
};

#endif //MIKATRON_SPEAKER_H
