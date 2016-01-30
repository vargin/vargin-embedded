#include <stdint.h>
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

static const uint8_t GoNorth = 0;
static const uint8_t WaitNorth = 1;
static const uint8_t GoWest = 2;
static const uint8_t WaitWest = 3;

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
  uint8_t Next[4];
} TrafficLightState;

GPIOPortRegisters portB;
GPIOPortRegisters portE;

TrafficLightState states[4];
TrafficLightState currentState;

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
checkState(void)
{
  uint8_t input;

  if ((*portE.PINS[0]) == PORT_PIN_0 && (*portE.PINS[1]) == PORT_PIN_1) {
    input = 3;
  } else if ((*portE.PINS[1]) == PORT_PIN_1) {
    input = 2;
  } else if ((*portE.PINS[0]) == PORT_PIN_0) {
    input = 1;
  } else {
    input = 0;
  }

  currentState = states[currentState.Next[input]];

  (*portB.DATA) = currentState.Out;
  SysTickDelay(currentState.Delay);

  /*if ((*portE.PINS[0]) == PORT_PIN_0 || (*portE.PINS[1]) == PORT_PIN_1) {
    (*portB.PINS[0]) ^= PORT_PIN_0;
    (*portB.PINS[1]) ^= PORT_PIN_1;
    (*portB.PINS[2]) ^= PORT_PIN_2;
    (*portB.PINS[3]) ^= PORT_PIN_3;
    (*portB.PINS[4]) ^= PORT_PIN_4;
    (*portB.PINS[5]) ^= PORT_PIN_5;

  } else {
    (*portB.PINS[0]) = 0x00;
    (*portB.PINS[1]) = 0x00;
    (*portB.PINS[2]) = 0x00;
    (*portB.PINS[3]) = 0x00;
    (*portB.PINS[4]) = 0x00;
    (*portB.PINS[5]) = 0x00;
  }*/
}

int
main(void)
{
  states[GoNorth] = (TrafficLightState) {
    .Out = 0x21UL,
    .Delay = 10000,
    .Next = { GoNorth, GoNorth, WaitNorth, WaitNorth }
  };

  states[WaitNorth] = (TrafficLightState) {
    .Out = 0x12UL,
    .Delay = 5000,
    .Next = { GoWest, GoWest, GoWest, GoWest }
  };

  states[GoWest] = (TrafficLightState) {
    .Out = 0x0CUL,
    .Delay = 10000,
    .Next = { GoWest, WaitWest, GoWest, WaitWest }
  };

  states[WaitWest] = (TrafficLightState) {
    .Out = 0x12UL,
    .Delay = 5000,
    .Next = { GoNorth, GoNorth, GoNorth, GoNorth }
  };

  initPorts();

  PLLInitialize(4);

  // Use 1ms gradation.
  SysTickInitialize(1000UL);

  while (1) {
    checkState();
  }

  return 0;
}
