#include <stdint.h>
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

GPIOPortRegisters portB;
GPIOPortRegisters portE;

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
initPorts(void)
{
  portB = GetPort(PortB);
  portE = GetPort(PortE);

  /**
   * Enable the Port’s Clock in RCGCGPIO. You are required to enable the clock
   * prior to accessing any of the peripherals registers.  If you don’t enable
   * the peripheral’s clock, your application will end up in the fault handler.
   * Here we enabled clock only for Port B and E (1st and 4th bits):
   * OR ----0001.0010.
   * Specification, page 340.
   */
  SYSCTL_RCGCGPIO_R |= 0x00000012;

  uint32_t inputPins = PORT_PIN_0 | PORT_PIN_1;
  uint32_t outputPins = PORT_PIN_0 |
                        PORT_PIN_1 |
                        PORT_PIN_2 |
                        PORT_PIN_3 |
                        PORT_PIN_4 |
                        PORT_PIN_5;

   // Disable analog on all pins.
  (*portE.AMSEL) &= ~inputPins;
  (*portB.AMSEL) &= ~outputPins;

  (*portE.PCTL) &= ~inputPins;
  (*portB.PCTL) &= ~outputPins;

  // Clear the bits in the Alternate Function Select register (AFSEL).
  (*portE.AFSEL) &= ~inputPins;
  (*portB.AFSEL) &= ~outputPins;

  // Configure each pin as an input or output in the DIR register.
  (*portE.DIR) &= ~inputPins;
  (*portB.DIR) |= outputPins;

  // Enable digital I/O on all required pins.
  (*portE.DEN) |= inputPins;
  (*portB.DEN) |= outputPins;
}

void
checkAlarmState(void)
{
  if ((*portE.PINS[0]) == PORT_PIN_0 || (*portE.PINS[1]) == PORT_PIN_1) {
    (*portB.PINS[0]) ^= PORT_PIN_0;
    SysTickDelay(2500);
  } else {
    (*portB.PINS[0]) = 0x00;
  }
}

int
main(void)
{
  initPorts();

  PLLInitialize(4);

  // Use 1ms gradation.
  SysTickInitialize(1000UL);

  while (1) {
    checkAlarmState();
  }

  return 0;
}
