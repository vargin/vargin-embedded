#include <PLL.h>
#include <sys/_stdint.h>
#include <SysTick.h>
#include "ports.h"

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

// GPIO Analog Mode Select (GPIOAMSEL) (spec, p. 687).
// #define GPIO_PORTE_AMSEL_R      (*((volatile uint32_t *)0x40024528))

// GPIO Port Control (GPIOPCTL) (spec, p. 688).
// #define GPIO_PORTE_PCTL_R       (*((volatile uint32_t *)0x4002452C))

// GPIO Alternate Function Select (GPIOAFSEL) (spec, p. 671).
// #define GPIO_PORTE_AFSEL_R      (*((volatile uint32_t *)0x40024420))

// The GPIODIR register is the data direction register (spec, p. 663).
// #define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))

// GPIO Digital Enable (GPIODEN) (spec, p. 682).
// #define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))

// The GPIODATA register is the data register (spec, p. 662).
// #define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))

// 0x4002 4000 + 0x0040
/*
#define PORTE_PIN4_DATA         (*((volatile uint32_t *)0x40024040))
#define PORTE_PIN3_DATA         (*((volatile uint32_t *)0x40024020))
#define PORTE_PIN2_DATA         (*((volatile uint32_t *)0x40024010))
#define PORTE_PIN1_DATA         (*((volatile uint32_t *)0x40024008))
#define PORTE_PIN0_DATA         (*((volatile uint32_t *)0x40024004))
*/

typedef struct
{
  /**
   * Output signal for the state.
   */
  uint32_t Out;

  /**
   * Minimum delay for the state to be on.
   */
  uint32_t Delay;

  /**
   * Possible next states, depending on input. Index equals to the input.
   */
  uint32_t Next[4];
} TrafficLightState;

TrafficLightState States[4] = {
    {
    },
    { },
    { },
    { }
};

void
initPortE(GPIOPortAdresses port)
{
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
  //GPIO_PORTE_AMSEL_R = 0x00;
  (*port.AMSEL) = 0x00;

  /**
   * Disable analog on all pins of port E.
   */
  (*port.PCTL) = 0x00000000;

  /**
   * Clear the bits in the Alternate Function Select register (AFSEL).
   * Pins on the TM4C123 can be configured as GPIO pins or as an alternate
   * function (eg: serial interface). We want them to be GPIO pins, so make sure
   * to clear this register. All pins are GPIO.
   */
  // GPIO_PORTE_AFSEL_R = 0x00;
  (*port.AFSEL) = 0x00;

  /**
   * Configure each pin as an input or output in the DIR register. PE2-0 -
   * input, PE3-4 - output.
   * xxx1 1000
   */
  (*port.DIR) |= 0x18;
  (*port.DIR) &= ~0x07;

  /*
   * Enable digital I/O on PE4-0, 0x1F is 0001 1111.
   */
  (*port.DEN) |= 0x1F;
}

unsigned char isAlarmSystemOn = 0;
unsigned char isAlarmSystemBusy = 0;

char
checkMainSwitch(GPIOPortAdresses port)
{
  unsigned char powerIsPressed = (*port.PINS[2]) == 0x04;//PORTE_PIN2_DATA == 0x04;

  if (powerIsPressed && !isAlarmSystemBusy) {
    isAlarmSystemBusy = 1;
  } else if (!powerIsPressed && isAlarmSystemBusy) {
    isAlarmSystemOn = !isAlarmSystemOn;
    isAlarmSystemBusy = 0;
  }

  // Enable power on LED.
  (*port.PINS[3]) = isAlarmSystemOn ? 0x08 : 0x00;

  return isAlarmSystemOn;
}

void
checkAlarmState(GPIOPortAdresses port)
{
  if ((*port.PINS[0]) == 0x01 || (*port.PINS[1]) == 0x02) {
    (*port.PINS[4]) ^= 0x10;
    SysTickDelay(2500);
  } else {
    (*port.PINS[4]) = 0x00;
  }
}

int
main(void)
{
  GPIOPortAdresses portE = GetPort(PortE);

  PLLInitialize(4);

  // Use 1ms gradation.
  SysTickInitialize(1000UL);

  initPortE(portE);

  while (1) {
    if (!checkMainSwitch(portE)) {
      continue;
    }

    checkAlarmState(portE);
  }

  return 0;
}
