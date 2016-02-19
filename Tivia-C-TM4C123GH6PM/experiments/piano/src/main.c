#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/nvic.h"

#define NVIC_PRI0_R  (*((volatile uint32_t *)0xE000E400))

uint8_t isSoundEnabled = 0;

// Define period for the four needed tones. Points per 1 wave length = 16 (4 bits).
// System clock frequency = 80 MHz
// System clock period = 12.5ns
// Frequency of the wave = 1/period = 1/(12.5ns * period * 16)
#define C_0 9555 // 523.3 Hz
#define D   8514 // 587.3 Hz
#define E   7584 // 659.3 Hz
#define G   6377 // 784 Hz

const uint8_t SineWave[16] = { 4, 5, 6, 7, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 2, 3 };
uint8_t waveIndex = 0;

void
DAC_Out(uint8_t number) {
  GPIOB->DATA = number;
}

void
OnTick(void) {
  waveIndex = (waveIndex + 1) & 0x0F;

  DAC_Out(isSoundEnabled ? SineWave[waveIndex] : 0);
}

int main(void){
  // Enable 80Mhz clock.
  PLLInitialize(4);

  SysTickInitializeWithCustomTicker(C_0, OnTick);

  uint32_t inputPins = GPIO_PORT_PIN_0 | GPIO_PORT_PIN_1 | GPIO_PORT_PIN_2 | GPIO_PORT_PIN_3;
  uint32_t outputPins = GPIO_PORT_PIN_0 | GPIO_PORT_PIN_1 | GPIO_PORT_PIN_2 | GPIO_PORT_PIN_3;

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
  }
}

void GPIOPortE_Handler(void) {
  GPIOE->ICR |= GPIO_PORT_PIN_0 | GPIO_PORT_PIN_1 | GPIO_PORT_PIN_2 | GPIO_PORT_PIN_3;
  isSoundEnabled = ~isSoundEnabled;

  if (isSoundEnabled) {
    uint32_t note;
    uint8_t data = GPIOE->DATA & 0x0F;

    switch(data) {
      case 1: note = C_0; break;
      case 2: note = D; break;
      case 4: note = E; break;
      case 8: note = G; break;
    }

    SysTickInitializeWithCustomTicker(note, OnTick);
  }
}
