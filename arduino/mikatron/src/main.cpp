#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "speaker.h"
#include "scheduler.h"
#include "TinyWireM.h"

volatile uint16_t analogResult = 0;
uint16_t previousAction = 10;
uint32_t actionTime = 0;

const uint16_t LONG_PRESS_DURATION = 1200;
const uint16_t COMMIT_DURATION = 2400;
char numberString[10];

#define RTC_ADDRESS  0x68

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
  // DIDR0 |= ADC2D;

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
  ltoa(number, numberString, 10);
  uart_puts(numberString);
}

/**
 * GPIO ports:
 * PB0 (pin 5) - SDA;
 * PB1 (pin 6) - PWM (speaker);
 * PB2 (pin 7) - SCL;
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

/*
void debug(Scheduler *scheduler) {
  uart_puts("[D:");

  uart_puts("[AR:");
  printNumber(analogResult);
  uart_putchar(']');

  uart_puts("[PA:");
  printNumber(previousAction);
  uart_putchar(']');

  uart_puts("[AT:");
  printNumber(actionTime);
  uart_putchar(']');

  const uint8_t bufferLength = scheduler->getBufferLength();
  uart_puts("[BFL:");
  printNumber(bufferLength);
  uart_putchar(']');
  if (bufferLength > 0) {
    uart_puts("[BF:");
    const uint8_t *buffer = scheduler->getBuffer();
    for (uint8_t i = 0; i < bufferLength; i++) {
      printNumber(buffer[i]);
    }
    uart_putchar(']');
  }
  uart_putchar(']');
}
*/

/**
 * Converts binary coded decimal to decimal, e.g. 0101 0100/0x54/54: 0x54 - 6 * (0x54 >> 4) =
 * 0x54 - 0x1e = 0x36/54.
 * @param val
 * @return
 */
static uint8_t bcd2bin (uint8_t val) {
  return val - 6 * (val >> 4);
}

void readTime() {
  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(0);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 7);
  uint8_t ss = bcd2bin(TinyWireM.read() & 0x7F);
  uint8_t mm = bcd2bin(TinyWireM.read());
  uint8_t hh = bcd2bin(TinyWireM.read());
  /*TinyWireM.read();
  uint8_t d = bcd2bin(TinyWireM.read());
  uint8_t m = bcd2bin(TinyWireM.read());
  uint16_t y = bcd2bin(TinyWireM.read()) + 2000;*/

  uart_puts("[SECONDS:");
  printNumber(ss);
  uart_putchar(']');

  uart_puts("[MINUTES:");
  printNumber(mm);
  uart_putchar(']');

  uart_puts("[HOUR:");
  printNumber(hh);
  uart_putchar(']');
}

int main(void) {
  // Set PB2 to be output.
  DDRB |= (1 << DDB1);// | (1 << DDB2);
  // Set PB4 as the input.
  DDRB &= ~(1 << DDB4);

  initADC();
  sei();

  TinyWireM.begin();

  TinyWireM.beginTransmission(RTC_ADDRESS);
  TinyWireM.write(0);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(RTC_ADDRESS, 1);

  if (TinyWireM.read() >> 7) {
    uart_puts("[NO TIME]");
    return 1;
  } else {
    uart_puts("[WE HAVE TIME]");
    readTime();
  }

  Scheduler *scheduler = new Scheduler(20, 10);

  // Start first conversion.
  startConversion();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  while (1) {
    if (analogResult == 0) {
      continue;
    }

    uint8_t action = 10;

    if (analogResult < 200) {
      action = 1;
    } else if (analogResult < 400) {
      action = 2;
    } else if (analogResult < 600) {
      action = 3;
    } else if (analogResult < 800) {
      action = 4;
    } else if (analogResult < 1000) {
      action = 5;
    }

    analogResult = 0;

    // Long press actions.
    if (actionTime >= LONG_PRESS_DURATION && actionTime < COMMIT_DURATION) {
      switch (action) {
        case 1:
          action = 6;
          break;
        case 2:
          action = 7;
          break;
        case 3:
          action = 8;
          break;
        case 4:
          action = 9;
          break;
        case 5:
          action = 0;
          break;
        default:
          break;
      }

      if (previousAction != action && action < 10) {
        Speaker::doubleBeep();
      }
    } else if (actionTime >= COMMIT_DURATION) {
      if (previousAction != action && action < 10) {
        Speaker::melody();
      }
    }

    if (action != previousAction) {
      // We display action only once button is unpressed.
      if (action == 10) {
        if (actionTime < COMMIT_DURATION) {
          scheduler->push(previousAction);
          if (actionTime < LONG_PRESS_DURATION) {
            Speaker::beep();
          }

          uart_puts("[ACTION:");
          printNumber(previousAction);
          uart_putchar(']');

          //readTime();
        } else {
          uint32_t numberOfSeconds = scheduler->commit((CommitType)previousAction);
          uart_puts("[SCHEDULED:");
          printNumber(numberOfSeconds);
          uart_putchar(']');
        }

        actionTime = 0;

        startConversion();
      }

      previousAction = action;
    } else if (action < 10 && actionTime < COMMIT_DURATION) {
      // Increment only when we are still not sure if it's long press.
      actionTime += 200;
    }

    _delay_ms(200);
  }
#pragma clang diagnostic pop
}