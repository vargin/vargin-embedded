#include <stdint.h>
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/cortexm4.h"
#include "../include/ports.h"

#define NVIC_EN0_R   (*((volatile uint32_t *)0xE000E100))
#define NVIC_PRI0_R  (*((volatile uint32_t *)0xE000E400))



int main(void){
  // Set system clock to 50 MHz.
  PLLInitialize(7);

  // Use 1ms gradation for 50 Mhz clock.
  SysTickInitialize(50000UL);

  uint32_t inputPins = GPIO_PORT_PIN_2;
  uint32_t outputPins = GPIO_PORT_PIN_3;

  // Activate GPIO port A.
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOA_MASK;

  GPIOA->AFSEL &= ~inputPins;
  GPIOA->AFSEL &= ~outputPins;

  GPIOA->AMSEL &= ~inputPins;
  GPIOA->AMSEL &= ~outputPins;

  GPIOA->PCTL &= ~inputPins;
  GPIOA->PCTL &= ~outputPins;

  GPIOA->DIR &= ~inputPins;
  GPIOA->DIR |= outputPins;

  GPIOA->DEN |= inputPins;
  GPIOA->DEN |= outputPins;

  GPIOA->IM |= inputPins;

  NVIC_PRI0_R |= 0x20;
  NVIC_EN0_R |= 0x01;

  while(1) {
  }
}


void DeviceInterrupt_Handler(void) {
  GPIOA->ICR |= GPIO_PORT_PIN_2;
  GPIOA->PIN3 = ~GPIOA->PIN3;
}

