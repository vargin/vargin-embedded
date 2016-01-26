#include <PLL.h>
#include <sys/_stdint.h>
#include <SysTick.h>
#include "ports.h"

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

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
  (*port.AMSEL) = 0x0UL;

  /**
   * Disable analog on all pins of port E.
   */
  (*port.PCTL) = 0x0UL;

  /**
   * Clear the bits in the Alternate Function Select register (AFSEL).
   * Pins on the TM4C123 can be configured as GPIO pins or as an alternate
   * function (e.g. serial interface). We want them to be GPIO pins, so make
   * sure to clear this register. All pins are GPIO.
   */
  (*port.AFSEL) = 0x0UL;

  /**
   * Configure each pin as an input or output in the DIR register.
   */
  (*port.DIR) |= PORT_PIN_3 | PORT_PIN_4;
  (*port.DIR) &= ~(PORT_PIN_0 | PORT_PIN_1 | PORT_PIN_2);

  /*
   * Enable digital I/O on PE4-0, 0x1F is 0001 1111.
   */
  (*port.DEN) |= PORT_PIN_0 | PORT_PIN_1 | PORT_PIN_2 | PORT_PIN_3 | PORT_PIN_4;
}

unsigned char isAlarmSystemOn = 0;
unsigned char isAlarmSystemBusy = 0;

char
checkMainSwitch(GPIOPortAdresses port)
{
  unsigned char powerIsPressed = (*port.PINS[2]) == PORT_PIN_2;

  if (powerIsPressed && !isAlarmSystemBusy) {
    isAlarmSystemBusy = 1;
  } else if (!powerIsPressed && isAlarmSystemBusy) {
    isAlarmSystemOn = !isAlarmSystemOn;
    isAlarmSystemBusy = 0;
  }

  // Enable power on LED.
  (*port.PINS[3]) = isAlarmSystemOn ? PORT_PIN_3 : 0x00;

  return isAlarmSystemOn;
}

void
checkAlarmState(GPIOPortAdresses port)
{
  if ((*port.PINS[0]) == PORT_PIN_0 || (*port.PINS[1]) == PORT_PIN_1) {
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
