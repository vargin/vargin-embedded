#include <stdint.h>
#include <stdio.h>
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/uart.h"

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

#define UART0_UARTFR_R          (*((volatile uint32_t *)0x4000C018))
#define UART0_UARTDR_R          (*((volatile uint32_t *)0x4000C000))

#define UART2_UARTFR_R          (*((volatile uint32_t *)0x4000E018))
#define UART2_UARTDR_R          (*((volatile uint32_t *)0x4000E000))

void
printChar(uint8_t c) {
  while((UART0_UARTFR_R & (1 << 5)) != 0);
  UART0_UARTDR_R = c;
}

uint8_t
readChar(void) {
  uint8_t c;
  while((UART0_UARTFR_R & (1 << 4)) != 0);
  c = UART0_UARTDR_R;
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
  SYSCTL_RCGCGPIO_R |= 0x00000002;

  UARTInitialize();

  initPorts();

  //PLLInitialize(4);

  // Use 1ms gradation.
  //SysTickInitialize(1000UL);

  unsigned char data;

  uint8_t i = 0;
  while (1) {
    printf("Value %#010x\n", readChar());
    printChar(i++);
    // printf("Value: %d\n", UART2_UARTFR_R);
    /*if ((*portB.PINS[0]) == PORT_PIN_0 || (UART0_UARTFR_R & 0x10UL) == 0) {
      data = (unsigned char)(UART0_UARTDR_R&0xFF);
      if (data) {
        printf("Data %#010x %c\n", data, data);
        (*portB.PINS[1]) = PORT_PIN_1;
        //SysTickDelay(500);
      }
    } else {
      (*portB.PINS[1]) = 0x0UL;
    }*/
    //if (UART2_UARTFR_RXFE_R == 0) {
      //((unsigned char)(UART1_DR_R&0xFF));
    //}
  }

  return 0;
}
