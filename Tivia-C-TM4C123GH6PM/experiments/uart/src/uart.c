#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/ports.h"
#include "../include/uart.h"

#define RCGCUART_R          (*((volatile uint32_t *)0x400FE618))
#define RCGCGPIO_R          (*((volatile uint32_t *)0x400FE608))
#define AFSEL_R             (*((volatile uint32_t *)0x40004420))
#define PCTL_R              (*((volatile uint32_t *)0x4000452C))
#define DEN_R               (*((volatile uint32_t *)0x4000451C))

#define UART_CTL_R          (*((volatile uint32_t *)0x4000C030))
#define UART_IBRD_R         (*((volatile uint32_t *)0x4000C024))
#define UART_FBRD_R         (*((volatile uint32_t *)0x4000C028))
#define UART_LCRH_R         (*((volatile uint32_t *)0x4000C02C))
#define UART_CC_R           (*((volatile uint32_t *)0x4000CFC8))

void
initializeUARTPort(GPIOPortRegisters port, uint32_t pins) {
   // Disable analog on pins.
  (*port.AMSEL) &= ~pins;

  (*port.PCTL) = ((*port.PCTL) & 0xFFFFFF00) + 0x00000011;

  // Enable alternative function on pins.
  (*port.AFSEL) |= pins;

  // Enable digital I/O on all required pins.
  (*port.DEN) |= pins;
}

void UARTInitialize1() {
  RCGCUART_R |= (1 << 0);
  RCGCGPIO_R |= (1 << 0);

  AFSEL_R = (1 << 1) | (1 << 0);
  PCTL_R = (1 << 0) | (1 << 1);
  DEN_R = (1 << 0) | (1 << 1);

  UART_CTL_R &= ~(1 << 0);
  UART_IBRD_R = 104;
  UART_FBRD_R = 11;
  UART_LCRH_R = (0x3 << 5);
  UART_CC_R = 0x0;

  UART_CTL_R = (1 << 0) | (1 << 8) | (1 << 9);
}

void
UARTInitialize() {
  // activate UART2.
  SYSTEM_CTRL_RCGC1_R |= 0x00000001;

  // activate port D.
  SYSTEM_CTRL_RCGC2_R |= 0x00000001;

  // disable UART.
  UART0_UARTCTL_R &= ~0x00000001;

  // IBRD = int(80,000,000/(16*9600)) = int(520.833333333).
  UART0_UARTIBRD_R = 104;

  // FBRD = round(0.833333333 * 64) = 53.
  UART0_UARTFBRD_R  = 11;

  // 8 bit, no parity bits, one stop, FIFOs.
  UART0_UARTLCRH_R = 0x00000070;

  // enable UART
  UART0_UARTCTL_R |= 0x00000001;

  initializeUARTPort(GetPort(PortA), PORT_PIN_0 | PORT_PIN_1);
}
