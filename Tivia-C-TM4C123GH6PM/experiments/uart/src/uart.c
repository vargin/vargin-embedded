#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/ports.h"
#include "../include/uart.h"

UARTPortRegisters UART_PORTS[2] = {
  {
    .DR = (volatile uint32_t *) (UART0_BASE),
    .FR = (volatile uint32_t *) (UART0_UARTFR),
    .IBRD = (volatile uint32_t *) (UART0_UARTIBRD),
    .FBRD = (volatile uint32_t *) (UART0_UARTFBRD),
    .LCRH = (volatile uint32_t *) (UART0_UARTLCRH),
    .CTL = (volatile uint32_t *) (UART0_UARTCTL),
    .RIS = (volatile uint32_t *) (UART0_UARTRIS),
    .CC = (volatile uint32_t *) (UART0_UARTCC)
  },
  {
    .DR = (volatile uint32_t *) (UART2_BASE),
    .FR = (volatile uint32_t *) (UART2_UARTFR),
    .IBRD = (volatile uint32_t *) (UART2_UARTIBRD),
    .FBRD = (volatile uint32_t *) (UART2_UARTFBRD),
    .LCRH = (volatile uint32_t *) (UART2_UARTLCRH),
    .CTL = (volatile uint32_t *) (UART2_UARTCTL),
    .RIS = (volatile uint32_t *) (UART2_UARTRIS),
    .CC = (volatile uint32_t *) (UART2_UARTCC)
  }
};

UARTPortRegisters
UARTInitialize(PortTypes portType) {
  UARTPortRegisters uartPort;

  uint32_t rcgc1;
  uint32_t rcgc2;
  uint32_t pins;
  uint32_t pctl;

  if (portType == PortA) {
    uartPort = UART_PORTS[0];
    rcgc1 = 0x1UL;
    rcgc2 = 0x1UL;
    pins = PORT_PIN_0 | PORT_PIN_1;
    // Activate pins 0 and 1.
    pctl = 0x11UL;
  } else if (portType == PortD) {
    uartPort = UART_PORTS[1];
    rcgc1 = 0x4UL;
    rcgc2 = 0x8UL;
    pins = PORT_PIN_6 | PORT_PIN_7;
    // Activate pins 6 and 7.
    pctl = 0x11000000UL;
  }

  // activate UART port.
  SYSTEM_CTRL_RCGC1_R |= rcgc1;
  SYSTEM_CTRL_RCGC2_R |= rcgc2;

  // disable UART.
  (*uartPort.CTL) &= ~0x1UL;

  // IBRD = int(16,000,000/(16*9600)) = int(520.833333333).
  (*uartPort.IBRD) = 104;

  // FBRD = round(0.833333333 * 64) = 53.
  (*uartPort.FBRD)  = 11;

  // 8 bit, no parity bits, one stop, FIFOs.
  (*uartPort.LCRH) = 0x00000070;

  // enable UART.
  (*uartPort.CTL) |= 0x1UL;

  GPIOPortRegisters gpioPort = GetPort(portType);

  // Disable analog on pins.
  (*gpioPort.AMSEL) &= ~pins;

  (*gpioPort.PCTL) |= pctl;

  // Enable alternative function on pins.
  (*gpioPort.AFSEL) |= pins;

  // Enable digital I/O on all required pins.
  (*gpioPort.DEN) |= pins;

  return uartPort;
}