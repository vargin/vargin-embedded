#include <stdint.h>
#include "SysTick.h"
#include "PLL.h";

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

// GPIO Analog Mode Select (GPIOAMSEL) (spec, p. 687).
#define GPIO_PORTE_AMSEL_R      (*((volatile uint32_t *)0x40024528))

// GPIO Port Control (GPIOPCTL) (spec, p. 688).
#define GPIO_PORTE_PCTL_R       (*((volatile uint32_t *)0x4002452C))

// GPIO Alternate Function Select (GPIOAFSEL) (spec, p. 671).
#define GPIO_PORTE_AFSEL_R      (*((volatile uint32_t *)0x40024420))

// The GPIODIR register is the data direction register (spec, p. 663).
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))

// GPIO Digital Enable (GPIODEN) (spec, p. 682).
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))

// The GPIODATA register is the data register (spec, p. 662).
#define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))

// 0x4002 4000 + 0x0040
#define PORTE_PIN4_DATA         (*((volatile uint32_t *)0x40024040))
#define PORTE_PIN3_DATA         (*((volatile uint32_t *)0x40024020))
#define PORTE_PIN2_DATA         (*((volatile uint32_t *)0x40024010))
#define PORTE_PIN1_DATA         (*((volatile uint32_t *)0x40024008))
#define PORTE_PIN0_DATA         (*((volatile uint32_t *)0x40024004))

void initPortE(void) {
  /**
   * Enable the Port’s Clock in RCGCGPIO. You are required to enable the clock
   * prior to accessing any of the peripherals registers.  If you don’t enable
   * the peripheral’s clock, your application will end up in the fault handler.
   * Here we enabled clock only for Port F and E (5th and 4th bits):
   * OR ----0011.0000.
   * Specification, page 340.
   */
  SYSCTL_RCGCGPIO_R |= 0x00000030;

  /**
   * Disable analog on all pins of port E.
   */
  GPIO_PORTE_AMSEL_R = 0x00;

  /**
   * Disable analog on all pins of port E.
   */
  GPIO_PORTE_PCTL_R = 0x00000000;

  /**
   * Clear the bits in the Alternate Function Select register (AFSEL).
   * Pins on the TM4C123 can be configured as GPIO pins or as an alternate
   * function (eg: serial interface). We want them to be GPIO pins, so make sure
   * to clear this register. All pins are GPIO.
   */
  GPIO_PORTE_AFSEL_R = 0x00;

  /**
   * Configure each pin as an input or output in the DIR register. PE2-0 -
   * input, PE3-4 - output.
   * xxx1 1000
   */
  GPIO_PORTE_DIR_R |= 0x18;
  GPIO_PORTE_DIR_R &= ~0x07;

  /*
   * Enable digital I/O on PE4-0, 0x1F is 0001 1111.
   */
  GPIO_PORTE_DEN_R |= 0x1F;
}

unsigned char isAlarmSystemOn = 0;
unsigned char isAlarmSystemBusy = 0;

char checkMainSwitch() {
  unsigned char powerIsPressed = PORTE_PIN2_DATA == 0x04;

  if (powerIsPressed && !isAlarmSystemBusy) {
    isAlarmSystemBusy = 1;
  } else if (!powerIsPressed && isAlarmSystemBusy) {
    isAlarmSystemOn = !isAlarmSystemOn;
    isAlarmSystemBusy = 0;
  }

  // Enable power on LED.
  PORTE_PIN3_DATA = isAlarmSystemOn ? 0x08 : 0x00;

  return isAlarmSystemOn;
}

void checkAlarmState(void) {
  if (PORTE_PIN0_DATA == 0x01 || PORTE_PIN1_DATA == 0x02) {
    PORTE_PIN4_DATA ^= 0x10;
    SysTickDelay(2500);
  } else {
    PORTE_PIN4_DATA = 0x00;
  }
}

int main(void) {
  PLLInitialize(4);

  // Use 1ms gradation.
  SysTickInitialize(1000UL);

  initPortE();

  while(1) {
    if (!checkMainSwitch()) {
      continue;
    }

    checkAlarmState();
  }

  return 0;
}
