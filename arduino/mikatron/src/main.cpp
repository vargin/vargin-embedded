#include <avr/io.h>
#include <util/delay.h>


int main(void) {
  // set PB0 to be output
  DDRB = 0b00000001;
  while (1) {

    // flash# 1:
    // set PB0 high
    PORTB = 0b00000001;
    _delay_ms(20);
    // set PB0 low
    PORTB = 0b00000000;
    _delay_ms(20);

    // flash# 2:
    // set PB0 high
    PORTB = 0b00000001;
    _delay_ms(200);
    // set PB0 low
    PORTB = 0b00000000;
    _delay_ms(200);
  }
}