#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "softuart.h"

volatile uint8_t analogLow = 0;
volatile uint8_t analogHigh = 0;
volatile uint8_t analogResultChanged = 0;
volatile uint8_t pinChanged = 0;
volatile uint16_t previousAction = 0;
volatile uint32_t actionTime = 0;

void
startConversion() {
  ADCSRA |= 1 << ADSC;
}

ISR(ADC_vect) {
  analogLow = ADCL;
  analogHigh = ADCH;
  analogResultChanged = 1;
}

/*ISR(PCINT0_vect) {
  pinChanged = 1;
}*/


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
  ADMUX &= ~((1 << REFS1) | (1 << REFS0) | (1 << ADLAR));

  // Choose ADC2.
  ADMUX |= 1 << MUX1;

  // Choose free running mode.
  //ADCSRB |= (1 << ADTS2) | (1 << ADTS1);
  ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2));

  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

  // Turn off Digital input on PB4;
  DIDR0 |= ADC2D;

  // Enable ADC and interruptions.
  ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADATE);
}

void
printAction(uint16_t action) {
  softuart_putchar('-');
  char str[2];
  itoa(action, str, 10);
  softuart_puts(str);
  softuart_putchar('-');
  startConversion();
}

int main(void) {
  // Set PB2 to be output.
  DDRB |= 1 << DDB2;
  // Set PB4 as the input.
  DDRB &= ~(1 << DDB4);

 /* PCMSK |= 1 << PCINT4;
  GIMSK |= 1 << PCIE;*/

  softuart_init();
  softuart_turn_rx_off();
  initADC();

  sei();

  // Start first conversion.
  startConversion();

  while (1) {
    if (!analogResultChanged) {
      continue;
    }

    analogResultChanged = 0;

    uint16_t analogResult = (analogHigh << 8) | analogLow;
    uint8_t action = 0;

    if (analogResult < 150) {
      action = 1;
    } else if (analogResult < 350) {
      action = 2;
    } else if (analogResult < 500) {
      action = 3;
    } else if (analogResult < 1000) {
      action = 4;
    } else {
      action = 0;
    }

    // Long press actions.
    if (actionTime >= 1500) {
      switch(action) {
        case 1:
          action = 5;
          break;
        case 2:
          action = 6;
          break;
        case 3:
          action = 7;
          break;
        case 4:
          action = 8;
          break;
        default:
          break;
      }

      if (previousAction != action && action > 0) {
        setHigh(PB2);
        _delay_ms(30);
        setLow(PB2);
      }
    }

    if (action != previousAction) {
      // We display action only once button is unpressed.
      if (action == 0) {
        printAction(previousAction);
        actionTime = 0;
      }

      previousAction = action;
    } else if (action > 0 && action < 5) {
      // Increment only when we are still not sure if it's long press.
      actionTime += 200;
      _delay_ms(200);
    }

   /* if (pinChanged) {
      pinChanged = 0;
      softuart_putchar('Z');
    }*/

    //setHigh(PB2);
    //_delay_ms(500);

    //setLow(PB2);
    //_delay_ms(500);

    //softuart_putchar('+');
  }
}