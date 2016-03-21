#include <stdint.h>
#include <stdio.h>

#include "cortexm4.h"
#include "pll.h"
#include "nvic.h"
#include "systick.h"
#include "ports.h"
#include "uart.h"
#include "nokia5110.h"

GPIORegisters *chipSelectPort = GPIOB;
UARTRegisters *uart = UART1;
uint8_t chipSelectPin = GPIO_PORT_PIN_2;

void
toggleSensor() {
  chipSelectPort->PIN2 = 0x1;
  SysTickDelay(250);
  chipSelectPort->PIN2 = 0x0;
  SysTickDelay(500);
}

uint8_t
readChar(UARTRegisters *uart) {
  while((uart->FR & (1 << 4)) != 0);
  return (uint8_t)uart->DR;
}

void
sendByte(UARTRegisters *uart, uint8_t data) {
  while((uart->FR & (1 << 5)) != 0);
  uart->DR = data;
}

void
UART1_Handler(void) {
  // Acknowledge that interrupt is processed.
  uart->ICR |= 0xFFFFUL;

  while((uart->FR & (1 << 4)) == 0) {
    uint8_t data = (uint8_t)uart->DR;
    printf("Data %c", data);
  }

/*  if (uart->MIS & 0x10UL) {

  }*/
}

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  UARTInitialize(UART1Module, 115200, 80);

  // Activate GPIO port B (Chip Select).
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOB_MASK;

  chipSelectPort->AFSEL &= ~chipSelectPin;
  chipSelectPort->AMSEL &= ~chipSelectPin;
  chipSelectPort->PCTL &= ~chipSelectPin;
  chipSelectPort->DIR |= chipSelectPin;
  chipSelectPort->DEN |= chipSelectPin;

  Nokia5110_Init();
  Nokia5110_Clear();
  Nokia5110_WriteString("GPS");

  toggleSensor();

  UARTInitialize(UART1Module, 115200, 80);

  // Enable interrupt for 4th bit - RXIM.
  uart->IM |= 0x10UL;
  //uart->IFLS &= ~0x38UL;

  // UART1 is 22nd in vector table, interrupt number is 6.
  // Setting priority 4 (100, 3 bits).
  NVIC->PRI1 = (NVIC->PRI1 & 0xFF00FFFF) | 0x00800000;

  // Enable IRQ 6
  NVIC->EN0 = 1 << 6;

  while (1) {
  }
}
