#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/nvic.h"

#define NVIC_PRI0_R  (*((volatile uint32_t *)0xE000E400))

unsigned char isSoundEnabled = 0;

int main(void){
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80Mhz clock.
  SysTickInitialize(80000UL);

  uint32_t inputPins = GPIO_PORT_PIN_0;
  uint32_t outputPins = GPIO_PORT_PIN_3;

  // Activate GPIO ports B and E.
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOB_MASK |
                            System_CTRL_RCGCGPIO_GPIOE_MASK;

  GPIOE->AFSEL &= ~inputPins;
  GPIOB->AFSEL &= ~outputPins;

  GPIOE->AMSEL &= ~inputPins;
  GPIOB->AMSEL &= ~outputPins;

  GPIOE->PCTL &= ~inputPins;
  GPIOB->PCTL &= ~outputPins;

  GPIOE->DIR &= ~inputPins;
  GPIOB->DIR |= outputPins;

  GPIOE->DEN |= inputPins;
  GPIOB->DEN |= outputPins;

  GPIOE->IM |= inputPins;

  // Generate interrupt on both touch and release!
  GPIOE->IBE |= inputPins;

  // Port E is Interrupt 20.
  NVIC->PRI5 |= 0x20;
  NVIC->EN0 |= 0x10;

  while(1) {
    if (isSoundEnabled) {
      GPIOB->PIN3 = ~GPIOB->PIN3;
      SysTickDelay(1);
    }
  }
}

void GPIOPortE_Handler(void) {
  GPIOE->ICR |= GPIO_PORT_PIN_0;
  isSoundEnabled = ~isSoundEnabled;
}

