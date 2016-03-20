#ifndef INCLUDE_UART_H
#define INCLUDE_UART_H

#include <stdint.h>
#include "cortexm4.h"

typedef enum {UART0Module, UART1Module, UART2Module, UART3Module} UARTModules;

typedef struct
{
  // UART Data (UARTDR), offset 0x000
  volatile uint32_t DR;

  // UART Receive Status/Error Clear (UARTRSR/UARTECR), offset 0x004
  const uint32_t RSR;

  const uint32_t RESERVED0[4];

  // UART Flag (UARTFR), offset 0x018
  volatile uint32_t FR;

  const uint32_t RESERVED1[1];

  // UART IrDA Low-Power Register (UARTILPR), offset 0x020
  const uint32_t ILPR;

  // UART Integer Baud-Rate Divisor (UARTIBRD), offset 0x024
  volatile uint32_t IBRD;

  // UART Fractional Baud-Rate Divisor (UARTFBRD), offset 0x028
  volatile uint32_t FBRD;

  // UART Line Control (UARTLCRH), offset 0x02C
  volatile uint32_t LCRH;

  // UART Control (UARTCTL), offset 0x030
  volatile uint32_t CTL;

  // UART Interrupt FIFO Level Select (UARTIFLS), offset 0x034
  const uint32_t IFLS;

  // UART Interrupt Mask (UARTIM), offset 0x038
  const uint32_t TIM;

  // UART Raw Interrupt Status (UARTRIS), offset 0x03C
  volatile uint32_t RIS;

  // UART Masked Interrupt Status (UARTMIS), offset 0x040
  const uint32_t MIS;

  // UART Interrupt Clear (UARTICR), offset 0x044
  const uint32_t ICR;

  // UART DMA Control (UARTDMACTL), offset 0x048
  const uint32_t DMACTL;

  const uint32_t RESERVED2[22];

  // UART 9-Bit Self Address (UART9BITADDR), offset 0x0A4
  const uint32_t BIT9ADDR;

  // UART 9-Bit Self Address Mask (UART), offset 0x0A8
  const uint32_t BIT9AMASK;

  const uint32_t RESERVED3[965];

  // UART Peripheral Properties (UARTPP), offset 0xFC0
  const uint32_t PP;

  const uint32_t RESERVED4[1];

  // UART Clock Configuration (UARTCC), offset 0xFC8
  volatile uint32_t CC;
} UARTRegisters;

#define UART0  ((UARTRegisters *) UART0_BASE)
#define UART1  ((UARTRegisters *) UART1_BASE)
#define UART2  ((UARTRegisters *) UART2_BASE)
#define UART3  ((UARTRegisters *) UART3_BASE)

extern UARTRegisters*
UARTInitialize(UARTModules module, uint32_t baudRate, uint8_t systemClockMhz);

#endif //INCLUDE_UART_H