#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "alarm.h"
#include "scheduler.h"

volatile uint16_t analogResult = 0;
volatile uint16_t previousAction = 0;
volatile uint32_t actionTime = 0;

const uint16_t LONG_PRESS_DURATION = 1500;

void
startConversion() {
  ADCSRA |= 1 << ADSC;
}

ISR(ADC_vect) {
  // Read low bit first as suggested in the datasheet, to make sure we read low and high bits of
  // the same number.
  uint8_t analogLow = ADCL;
  analogResult = (ADCH << 8) | analogLow;
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
uart_puts(const char *str) {
  while (*str) {
    TxByte(*str++);
  }
}

void uart_putchar(const char byte) {
  TxByte(byte);
}

void printNumber(uint32_t number) {
  uart_putchar('-');
  char str[8];
  itoa(number, str, 10);
  uart_puts(str);
  uart_putchar('-');
}

/**
 * GPIO ports:
 * PB0 (pin 5) - Vacant;
 * PB1 (pin 6) - PWM (speaker);
 * PB2 (pin 7) - LED;
 * PB3 (pin 2) - UART Rx/Tx;
 * PB4 (pin 3) - ADC (buttons);
 * PB5 (pin 1) - Vacant (reset).
 *
 * UART Rx/Tx:
 *            D1
 * AVR ----+--|>|-----+----- Tx
 *         |      10K $ R1
 *         +--------(/^\)--- Rx
 *              NPN E   C
 */

int main(void) {
  // Set PB2 to be output.
  DDRB |= (1 << DDB1) | (1 << DDB2);
  // Set PB4 as the input.
  DDRB &= ~(1 << DDB4);

  initADC();
  sei();

  Scheduler *scheduler = new Scheduler(100, 10);

  // Start first conversion.
  startConversion();

  while (1) {
    if (analogResult == 0) {
      continue;
    }

    uint8_t action = 0;

    if (analogResult < 200) {
      action = 1;
    } else if (analogResult < 400) {
      action = 2;
    } else if (analogResult < 600) {
      action = 3;
    } else if (analogResult < 1000) {
      action = 4;
    } else {
      action = 0;
    }

    analogResult = 0;

    // Long press actions.
    if (actionTime >= LONG_PRESS_DURATION) {
      switch (action) {
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
        _delay_ms(100);
        setLow(PB2);
        Alarm::play();
      }
    }

    if (action != previousAction) {
      // We display action only once button is unpressed.
      if (action == 0) {
        if (previousAction < 5) {
          scheduler->push(previousAction);
        } else {
          uint32_t numberOfMs = scheduler->commit((CommitType) (previousAction - 4));
          printNumber(numberOfMs);
        }

        printNumber(previousAction);

        _delay_ms(100);

        startConversion();
        actionTime = 0;
      }

      previousAction = action;
    } else if (action > 0 && action < 5) {
      // Increment only when we are still not sure if it's long press.
      actionTime += 200;
      _delay_ms(200);
    }
  }
}