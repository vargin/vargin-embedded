#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/ports.h"
#include "../include/uart.h"

void
UARTInitialize() {
  // activate UART2.
  SYSTEM_CTRL_RCGC1_R |= 0x00000004;

  // activate port D.
  SYSTEM_CTRL_RCGC2_R |= 0x00000008;

  // disable UART.
  UART2_UARTCTL_R &= ~0x00000001;

  // IBRD = int(80,000,000/(16*9600)) = int(520.833333333).
  UART2_UARTIBRD_R = 520;

  // FBRD = round(0.833333333 * 64) = 53.
  UART2_UARTFBRD_R  = 53;

  // 8 bit, no parity bits, one stop, FIFOs.
  UART2_UARTLCRH_R = 0x00000070;

  // enable UART
  UART2_UARTCTL_R |= 0x00000001;

  GPIOPortRegisters portD = GetPort(PortD);

  uint32_t uartPins = PORT_PIN_6 | PORT_PIN_7;

  // Disable analog on PD6-7.
  (*portD.AMSEL) &= ~uartPins;

  (*portD.PCTL) = ((*portD.PCTL) & 0x00FFFFFF) + 0x11000000;

  // Enable alternative function on PD6-7
  (*portD.AFSEL) |= uartPins;

  // Enable digital I/O on all required pins.
  (*portD.DEN) |= uartPins;
}
