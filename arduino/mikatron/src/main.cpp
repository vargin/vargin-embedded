#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

volatile uint8_t analogLow = 0;
volatile uint8_t analogHigh = 0;
volatile uint8_t analogResultChanged = 0;
volatile uint8_t pinChanged = 0;
volatile uint16_t previousAction = 0;
volatile uint32_t actionTime = 0;

volatile uint8_t currentScheduleIndex = 0;
volatile uint16_t currentSchedule[8];

#define MAX_SCHEDULES_COUNT 8
volatile uint32_t schedules[8];
volatile uint16_t scheduleIndex = 0;

void
startConversion() {
  ADCSRA |= 1 << ADSC;
}

ISR(ADC_vect) {
  // Read low bit first as suggested in the datasheet, to make sure we read low and high bits of
  // the same number.
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
uart_puts(const char* str) {
  while (*str) {
    TxByte(*str++);
  }
}

void uart_putchar(const char byte) {
  TxByte(byte);
}

void
printAction(uint16_t action) {
  uart_putchar('-');
  char str[2];
  itoa(action, str, 10);
  uart_puts(str);
  uart_putchar('-');
  startConversion();
}

uint32_t flushCurrentSchedule(uint16_t action) {
  uint32_t numberOfSeconds = 0;
  for (uint8_t i = 0; i < currentScheduleIndex; i++) {
    uint32_t multiplier = 1;
    uint8_t power = currentScheduleIndex - i - 1;
    if (power > 0) {
      for (uint8_t multiplierIndex = 0; multiplierIndex < power; multiplierIndex++) {
        multiplier *= 10;
      }
    }

    numberOfSeconds += currentSchedule[i] * multiplier;
  }

  switch(action) {
    // Minutes.
    case 6:
      numberOfSeconds *= 60;
      break;
      // Hours.
    case 7:
      numberOfSeconds *= 60 * 60;
      break;
    default:
      break;
  }

  currentScheduleIndex = 0;

  return numberOfSeconds;
}

/**
 * Pinout:
 * PB0 (pin 5) - UART Rx;
 * PB1 (pin 6) - UART Tx;
 * PB2 (pin 7) - LED;
 * PB3 (pin 2) - DAC (speaker);
 * PB4 (pin 3) - ADC (buttons).
 */

int main(void) {
  // Set PB2 to be output.
  DDRB |= (1 << DDB2);
  // Set PB4 as the input.
  DDRB &= ~(1 << DDB4);

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
    } else if (analogResult < 250) {
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
        //playTune();
      }
    }

    if (action != previousAction) {
      // We display action only once button is unpressed.
      if (action == 0) {
        if (previousAction < 5) {
          if (currentScheduleIndex >= 7) {
            currentScheduleIndex = 0;
          }

          currentSchedule[currentScheduleIndex++] = previousAction;
        } else {
          if (scheduleIndex == MAX_SCHEDULES_COUNT - 1) {
            scheduleIndex = 0;
          }

          schedules[scheduleIndex++] = flushCurrentSchedule(previousAction);

          uart_putchar('|');
          char str[8];
          itoa(schedules[scheduleIndex - 1], str, 10);
          uart_puts(str);
          uart_putchar('|');
        }

        printAction(previousAction);
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