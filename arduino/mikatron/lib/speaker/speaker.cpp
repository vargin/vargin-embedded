#include <avr/io.h>
#include <util/delay.h>
#include "speaker.h"

// Taken from http://www.technoblogy.com/show?KVO.

// Example for Note C:
// Frequency for note C4 is 261.63 Hz (see http://www.phy.mtu.edu/~suits/notefreqs.html),
// Divisor for this note will be = 1000000 (1 Mhz clock) / 261.63 = 3822.19.
// However, the divider for the counter must fit into 8 bits, so the maximum number we can
// represent is 255. The solution is to set the prescaler to divide the clock by 2^4, or 16.
// Then we get: divisor = 1000000 / 16 / 261.63 = 238.89 which rounds to 239.
const int Note_C = 239;
const int Note_CS = 225;
const int Note_D = 213;
const int Note_DS = 201;
const int Note_E = 190;
const int Note_F = 179;
const int Note_FS = 169;
const int Note_G = 159;
const int Note_GS = 150;
const int Note_A = 142;
const int Note_AS = 134;
const int Note_B = 127;

void Speaker::delay_ms(unsigned long delay) {
  for (unsigned long i = 0; i < delay; i++) {
    _delay_ms(1);
  }
}

void Speaker::tone(unsigned char divisor, unsigned char octave, unsigned long duration) {
  // For 1MHz clock.
  // 1. Timer/Counter1 is reset to $00 in the CPU clock cycle after a compare match with
  // OCR1A register;
  // 2. Output pin action following a compare match with compare register A in Timer/Counter1 will
  // be: "Toggle the OC1A output line.".
  TCCR1 = (1 << CTC1) | (1 << COM1A0) | (8 - octave);

  // for 8MHz clock
  // TCCR1 = (1 << CTC1) | (1 << COM1A0) | (11-octave);

  // Set the OCR.
  OCR1C = divisor - 1;

  Speaker::delay_ms(duration);

  // Stop the counter.
  TCCR1 = (1 << CTC1) | (1 << COM1A0);
}

void Speaker::melody() {
  Speaker::tone(Note_C, 4, 50);
  Speaker::tone(Note_D, 4, 50);
  Speaker::tone(Note_E, 4, 50);
  Speaker::tone(Note_F, 4, 50);
  Speaker::tone(Note_G, 4, 50);
  Speaker::tone(Note_A, 4, 50);
  Speaker::tone(Note_B, 4, 50);
  Speaker::tone(Note_C, 5, 50);
}

void Speaker::modeMelody() {
  Speaker::tone(Note_C, 4, 50);
  Speaker::tone(Note_D, 4, 50);
  Speaker::tone(Note_E, 4, 50);
  Speaker::tone(Note_C, 4, 50);
  Speaker::tone(Note_D, 4, 50);
  Speaker::tone(Note_E, 4, 50);
}

void Speaker::beep() {
  Speaker::tone(Note_C, 4, 150);
}

void Speaker::doubleBeep() {
  Speaker::tone(Note_C, 4, 150);
  Speaker::tone(Note_D, 4, 150);
}