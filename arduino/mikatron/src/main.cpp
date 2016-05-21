#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "speaker.h"
#include "scheduler.h"
#include "clock.h"
#include "TinyWireM.h"

enum ModeType {
  NoMode = 0,
  Schedule,
  GetTime,
  SetTime,
  SetAlarm,
  GetAlarm
};

ModeType mode = NoMode;

volatile uint16_t analogResult = 0;
uint16_t previousAction = 10;
uint32_t actionTime = 0;
Scheduler *scheduler;

uint8_t dateParts[3];
uint8_t datePartDigitIndex = 0;

const uint16_t LONG_PRESS_DURATION = 1200;
const uint16_t COMMIT_DURATION = 2400;
char numberString[10];

volatile bool interrupt = false;

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

ISR(PCINT0_vect) {
  interrupt = true;
}

void
listenForAlarm() {
  DDRB &= ~_BV(DDB1);

  PCMSK |= _BV(PCINT1);
  GIMSK |= _BV(PCIE);
}

void
dontListenForAlarm() {
  DDRB |= _BV(DDB1);

  GIMSK &= ~_BV(PCIE);
  PCMSK &= ~_BV(PCINT1);
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

void processGetTimeMode() {
  ClockTime time = Clock::getTime();

  uart_puts("[TIME:");
  printNumber(time.hour());
  uart_putchar(':');
  printNumber(time.minute());
  uart_putchar(':');
  printNumber(time.second());
  uart_putchar(']');

  mode = NoMode;
}

void processGetAlarmMode() {
  ClockTime time = Clock::getAlarm();

  uart_puts("[ALARM:");
  printNumber(time.hour());
  uart_putchar(':');
  printNumber(time.minute());
  uart_putchar(':');
  printNumber(time.second());
  uart_putchar(']');
  mode = NoMode;
}

void processSetTimeMode(uint8_t action) {
  // Long press actions.
  if (actionTime >= LONG_PRESS_DURATION) {
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
      Speaker::play(MELODY_DOUBLE_BEEP);
    }
  }

  if (action != previousAction) {
    // We display action only once button is unpressed.
    if (action == 10) {
      dateParts[datePartDigitIndex / 2] = datePartDigitIndex % 2 == 0 ?
                                          previousAction * 10 :
                                          dateParts[datePartDigitIndex / 2] + previousAction;
      if (actionTime < LONG_PRESS_DURATION) {
        Speaker::play(MELODY_BEEP);
      }

      uart_puts("[DIGIT:");
      printNumber(previousAction);
      uart_putchar(':');
      printNumber(dateParts[datePartDigitIndex / 2]);
      uart_putchar(']');

      if (datePartDigitIndex == 5) {
        uart_puts("[TIME SET:");
        printNumber(dateParts[0]);
        uart_putchar(':');
        printNumber(dateParts[1]);
        uart_putchar(':');
        printNumber(dateParts[2]);
        uart_putchar(']');

        Clock::setTime(
            ClockTime(dateParts[0], dateParts[1], dateParts[2])
        );

        datePartDigitIndex = 0;
        Speaker::play(MELODY_ALARM);
        mode = NoMode;
      } else {
        datePartDigitIndex++;
      }

      actionTime = 0;

      startConversion();
    }

    previousAction = action;
  } else if (action < 10 && actionTime < LONG_PRESS_DURATION) {
    // Increment only when we are still not sure if it's long press.
    actionTime += 200;
  }

  _delay_ms(200);
}

void processSetAlarmMode(uint8_t action) {
  // Long press actions.
  if (actionTime >= LONG_PRESS_DURATION) {
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
      Speaker::play(MELODY_DOUBLE_BEEP);
    }
  }

  if (action != previousAction) {
    // We display action only once button is unpressed.
    if (action == 10) {
      dateParts[datePartDigitIndex / 2] = datePartDigitIndex % 2 == 0 ?
                                          previousAction * 10 :
                                          dateParts[datePartDigitIndex / 2] + previousAction;
      if (actionTime < LONG_PRESS_DURATION) {
        Speaker::play(MELODY_BEEP);
      }

      uart_puts("[DIGIT:");
      printNumber(previousAction);
      uart_putchar(':');
      printNumber(dateParts[datePartDigitIndex / 2]);
      uart_putchar(']');

      if (datePartDigitIndex == 5) {
        uart_puts("[ALARM SET:");
        printNumber(dateParts[0]);
        uart_putchar(':');
        printNumber(dateParts[1]);
        uart_putchar(':');
        printNumber(dateParts[2]);
        uart_putchar(']');

        Clock::setAlarm(
            Alarm1Type::MATCH_HOURS,
            ClockTime(dateParts[0], dateParts[1], dateParts[2])
        );

        datePartDigitIndex = 0;
        Speaker::play(MELODY_ALARM);
        mode = NoMode;
      } else {
        datePartDigitIndex++;
      }

      actionTime = 0;

      startConversion();
    }

    previousAction = action;
  } else if (action < 10 && actionTime < LONG_PRESS_DURATION) {
    // Increment only when we are still not sure if it's long press.
    actionTime += 200;
  }

  _delay_ms(200);
}

void processScheduleMode(uint8_t action) {
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
      Speaker::play(MELODY_DOUBLE_BEEP);
    }
  } else if (actionTime >= COMMIT_DURATION) {
    if (previousAction != action && action < 10) {
      Speaker::play(MELODY_ALARM);
    }
  }

  if (action != previousAction) {
    // We display action only once button is unpressed.
    if (action == 10) {
      if (actionTime < COMMIT_DURATION) {
        scheduler->push(previousAction);
        if (actionTime < LONG_PRESS_DURATION) {
          Speaker::play(MELODY_BEEP);
        }

        uart_puts("[ACTION:");
        printNumber(previousAction);
        uart_putchar(']');

        //readTime();
      } else {
        uint32_t numberOfSeconds = scheduler->commit((CommitType) previousAction);
        uart_puts("[SCHEDULED:");
        printNumber(numberOfSeconds);
        uart_putchar(']');
        mode = NoMode;
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

void processNoMode(uint8_t action) {
  if (action == 10 && actionTime >= LONG_PRESS_DURATION) {
    mode = (ModeType) previousAction;

    actionTime = 0;
    previousAction = action;

    uart_puts("[MODE:");
    switch (mode) {
      case GetTime:
        uart_puts("GET TIME");
        break;
      case SetTime:
        uart_puts("SET TIME");
        break;
      case Schedule:
        uart_puts("SET SCHEDULE");
        break;
      case SetAlarm:
        uart_puts("SET ALARM");
        break;
      case GetAlarm:
        uart_puts("GET ALARM");
        break;
      default:
        uart_puts("UNKNOWN");
        break;
    }
    uart_putchar(']');
  } else if (action != 10 && actionTime < LONG_PRESS_DURATION) {
    previousAction = action;
    actionTime += 200;
  }

  if (actionTime >= LONG_PRESS_DURATION && (actionTime - 200) < LONG_PRESS_DURATION) {
    Speaker::play(MELODY_MODE);
  }

  _delay_ms(200);
}

int main(void) {
  // Set PB1 to be output.
  //DDRB |= (1 << DDB1);

  // Set PB4 as the input.
  DDRB &= ~(1 << DDB4);

  listenForAlarm();
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
  }

  scheduler = new Scheduler(20, 10);

  // Start first conversion.
  startConversion();

  while (1) {
    if (interrupt) {
      uart_puts("INTERRUPT");
      interrupt = false;
      Clock::resetAlarm();
    }

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

    switch (mode) {
      case NoMode:
        processNoMode(action);
        break;
      case GetTime:
        processGetTimeMode();
        break;
      case SetTime:
        processSetTimeMode(action);
        break;
      case SetAlarm:
        processSetAlarmMode(action);
        break;
      case GetAlarm:
        processGetAlarmMode();
        break;
      case Schedule:
        processScheduleMode(action);
        break;
    }
  }
}