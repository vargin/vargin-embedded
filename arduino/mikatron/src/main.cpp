#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "softuart.h"

volatile uint8_t analogLow = 0;
volatile uint8_t analogHigh = 0;
volatile uint8_t analogResultChanged = 0;

void
startConversion() {
  ADCSRA |= 1 << ADSC;
}

ISR(ADC_vect) {
  analogLow = ADCL;
  analogHigh = ADCH;
  analogResultChanged = 1;
}

void
setHigh(uint8_t pin) {
  PORTB |= 1 << pin;
}

void
setLow(uint8_t pin) {
  PORTB &= ~(1 << pin);
}

void
initADC() {
  // Choose Vcc as reference voltage and right value adjustment.
  //ADMUX &= ~((1 << REFS1) | (1 << REFS0) | (1 << ADLAR));

  // Choose ADC0.
  //ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3));

  // Choose free running mode.
  //ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2));

  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

  // Turn off Digital input on PB5;
  DIDR0 |= ADC0D;

  // Enable ADC and interruptions.
  ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADATE);
}

int main(void) {
  // Set PB2 to be output.
  DDRB |= 1 << DDB2;
  // Set PB5 as the input.
  DDRB &= ~(1 << DDB5);

  softuart_init();
  softuart_turn_rx_off();
  initADC();

  sei();

  // Start first conversion.
  startConversion();

  while (1) {
    if (analogResultChanged) {
      analogResultChanged = 0;

      softuart_puts("-L: ");
      char str[5];
      itoa(analogLow, str, 10);
      softuart_puts(str);

      softuart_puts(", H: ");
      itoa(analogHigh, str, 10);
      softuart_puts(str);

      softuart_puts(", F: ");
      itoa((analogHigh << 8) | analogLow, str, 10);
      softuart_puts(str);
      softuart_putchar('-');
    }

    setHigh(PB2);
    _delay_ms(500);

    setLow(PB2);
    _delay_ms(500);

    softuart_putchar('+');
  }
}