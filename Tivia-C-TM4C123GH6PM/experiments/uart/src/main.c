#include <stdint.h>
#include <stdio.h>
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/uart.h"

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

void
printChar(UARTPortRegisters port, uint8_t c) {
  while(((*port.FR) & (1 << 5)) != 0);
  (*port.DR) = c;
}

uint8_t
readChar(UARTPortRegisters port) {
  uint8_t c;
  while(((*port.FR) & (1 << 4)) != 0);
  c = (*port.DR);
  return c;
}

GPIOPortRegisters portB;

void
initPorts(void)
{
  portB = GetPort(PortB);

  /**
   * Enable the Port’s Clock in RCGCGPIO. You are required to enable the clock
   * prior to accessing any of the peripherals registers.  If you don’t enable
   * the peripheral’s clock, your application will end up in the fault handler.
   * Here we enabled clock only for Port B and E (1st and 4th bits):
   * OR ----0000.0010.
   * Specification, page 340.
   */
  SYSCTL_RCGCGPIO_R |= 0x00000002;

  uint32_t inputPins = PORT_PIN_0;
  uint32_t outputPins = PORT_PIN_1;

   // Disable analog on all pins.
  (*portB.AMSEL) &= ~(inputPins | outputPins);
  (*portB.PCTL) &= ~(inputPins | outputPins);

  // Clear the bits in the Alternate Function Select register (AFSEL).
  (*portB.AFSEL) &= ~(inputPins | outputPins);

  // Configure each pin as an input or output in the DIR register.
  (*portB.DIR) &= ~inputPins;
  (*portB.DIR) |= outputPins;

  // Enable digital I/O on all required pins.
  (*portB.DEN) |= inputPins | outputPins;
}

int
main(void)
{
  UARTPortRegisters uartPort = UARTInitialize(PortD);

  initPorts();

  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80Mhz clock.
  SysTickInitialize(80000UL);

  while (1) {
    uint8_t c = readChar(uartPort);

    printf("Value %#010x %c\n", c, c);
    // Just blink once to indicate that we've received byte.
    (*portB.PINS[1]) = PORT_PIN_1;
    SysTickDelay(100);
    printChar(uartPort, c);
    (*portB.PINS[1]) = 0x0;
  }

  return 0;
}
