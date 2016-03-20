#include <stdint.h>
#include <stdio.h>

#include "cortexm4.h"
#include "pll.h"
#include "systick.h"
#include "ports.h"
#include "uart.h"
#include "nokia5110.h"

GPIORegisters *chipSelectPort = GPIOB;
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

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  UARTRegisters *uart = UARTInitialize(UART1Module, 115200, 80);

  // Activate GPIO port B (Chip Select).
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOB_MASK;

  chipSelectPort->AFSEL &= ~chipSelectPin;
  chipSelectPort->AMSEL &= ~chipSelectPin;
  chipSelectPort->PCTL &= ~chipSelectPin;
  chipSelectPort->DIR |= chipSelectPin;
  chipSelectPort->DEN |= chipSelectPin;

  Nokia5110_Init();
  Nokia5110_Clear();

  toggleSensor();

  UARTInitialize(UART1Module, 115200, 80);

  while (1) {
    SysTickDelay(3000);

    Nokia5110_Clear();
    Nokia5110_WriteString("GPS");

    uint8_t data = readChar(uart);

    printf("Data %c", data);
  }
}
