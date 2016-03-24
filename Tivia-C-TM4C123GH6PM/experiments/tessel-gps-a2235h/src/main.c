#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cortexm4.h"
#include "pll.h"
#include "systick.h"
#include "ports.h"
#include "uart.h"
#include "nokia5110.h"

GPIORegisters *chipSelectPort = GPIOB;
UARTRegisters *uart = UART1;
uint8_t chipSelectPin = GPIO_PORT_PIN_2;

typedef struct {
  uint8_t *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (uint8_t *)malloc(initialSize * sizeof(uint8_t));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, uint8_t element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (uint8_t *)realloc(a->array, a->size * sizeof(uint8_t));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void
toggleSensor() {
  chipSelectPort->PIN2 = 0x1;
  SysTickDelay(200);
  chipSelectPort->PIN2 = 0x0;
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

Array uartData;

void
UART1_Handler(void) {
  // Acknowledge that interrupt is processed.
  uart->ICR |= 0x50UL;

  while((uart->FR & (1 << 4)) == 0) {
    insertArray(&uartData, (uint8_t)uart->DR);
  }
}

int main(void) {
  initArray(&uartData, 5);

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

  while (1) {
    if (uartData.used == 0) {
      Nokia5110_Clear();
      Nokia5110_WriteString("No data!");
    } else {
      char symbol[4];
      for (uint32_t i = 0; i < uartData.used; i++) {
        if (i % 17 == 0) {
          SysTickDelay(5000);
          Nokia5110_Clear();
        }

        sprintf(symbol, "_%02x_", uartData.array[i]);

        Nokia5110_WriteString(symbol);
      }

      SysTickDelay(5000);
      Nokia5110_Clear();
      Nokia5110_WriteString("End of data!");
    }
  }
}
