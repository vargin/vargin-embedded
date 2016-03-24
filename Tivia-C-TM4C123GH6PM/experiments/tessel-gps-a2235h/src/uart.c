#include <stdint.h>
#include "cortexm4.h"
#include "ports.h"
#include "nvic.h"
#include "uart.h"

UARTRegisters*
UARTInitialize(UARTModules module, uint32_t baudRate, uint8_t systemClockMhz) {
  UARTRegisters *uart;
  GPIORegisters *gpio;

  uint32_t uartClockMask;
  uint32_t gpioClockMask;

  uint32_t pins;

  if (module == UART0Module) {
    uart = UART0;
    gpio = GPIOA;

    uartClockMask = System_CTRL_RCGCSSI_UART0_MASK;
    gpioClockMask = System_CTRL_RCGCGPIO_GPIOA_MASK;

    pins = GPIO_PORT_PIN_0 | GPIO_PORT_PIN_1;
  } else if (module == UART1Module) {
    uart = UART1;
    gpio = GPIOB;

    uartClockMask = System_CTRL_RCGCSSI_UART1_MASK;
    gpioClockMask = System_CTRL_RCGCGPIO_GPIOB_MASK;

    pins = GPIO_PORT_PIN_0 | GPIO_PORT_PIN_1;
  } else if (module == UART2Module) {
    uart = UART2;
    gpio = GPIOD;

    uartClockMask = System_CTRL_RCGCSSI_UART2_MASK;
    gpioClockMask = System_CTRL_RCGCGPIO_GPIOD_MASK;

    pins = GPIO_PORT_PIN_6 | GPIO_PORT_PIN_7;
  } else {
    // Other UART modules are not supported yet.
    return 0;
  }

  System_CTRL_RCGCUART_R |= uartClockMask;
  System_CTRL_RCGCGPIO_R |= gpioClockMask;

  // Configure UART:

  // Disable UART until it's configured.
  uart->CTL &= ~0x1UL;

  // IBRD = int(80,000,000/(16*9600)) = int(520.833333333).
  // 80.000.000 / (16 * 9.600) = 80 / 0.1536
  float baudRateDivisor = systemClockMhz / (16 * (baudRate / 1000000.0));

  uint32_t integerBaudRateDivisor = (uint32_t)baudRateDivisor;
  float fractionalBaudRateDivisor = baudRateDivisor - integerBaudRateDivisor;

  // IBRD = int(80,000,000/(16*9600)) = int(520.833333333).
  uart->IBRD = integerBaudRateDivisor;

  // FBRD = round(0.833333333 * 64) = 53.
  uart->FBRD = (uint32_t)(fractionalBaudRateDivisor * 64);

  // 8 bit, no parity bits, one stop, FIFOs.
  uart->LCRH = 0x00000070;

  // Configure GPIO
  if (module == UART0Module) {
    // Choose UART alternative function (0x1) for pins 0 and 1.
    gpio->PCTL = (gpio->PCTL & 0xFFFFFF00) + 0x00000011;
  } else if (module == UART1Module) {
    // Only UART1 now enabled with interruptions
    // Enable interrupt for 4th bit - RXIM and 6th bit - RTIM.
    uart->IM |= 0x50UL;
    // UART1 is 22nd in vector table, interrupt number is 6.
    // Setting priority 2 (0100, 3 bits).
    NVIC->PRI1 = (NVIC->PRI1 & 0xFF00FFFF) | 0x00400000;

    // Enable IRQ 6
    NVIC->EN0 = 1 << 6;

    // Choose UART alternative function (0x1) for pins 0 and 1.
    gpio->PCTL = (gpio->PCTL & 0xFFFFFF00) + 0x00000011;
  } else if (module == UART2Module) {
    // If port D is used it should be unlocked first.
    gpio->LOCK = 0x4C4F434B;
    gpio->CR |= pins;

    // Choose UART alternative function (0x1) for pins 6 and 7.
    gpio->PCTL = (gpio->PCTL & 0x00FFFFFF) + 0x11000000;
  }

  // Disable analog on pins.
  gpio->AMSEL &= ~pins;

  // Enable alternative function on pins.
  gpio->AFSEL |= pins;

  // Enable digital I/O on all required pins.
  gpio->DEN |= pins;

  // Enable UART.
  uart->CTL |= 0x1UL;

  return uart;
}
