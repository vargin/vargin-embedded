#include <stdint.h>
#include <stdio.h>
#include "../include/cortexm4.h"
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/adc.h"
#include "../include/nokia5110.h"
#include "../include/sounds.h"

const uint8_t SineWave[16] = { 4, 5, 6, 7, 7, 7, 6, 5, 4, 3, 2, 1, 1, 1, 2, 3 };
uint8_t waveIndex = 0;

void
WriteDAC(uint8_t number) {
  GPIOB->DATA = number;
}

uint32_t
ReadADC0(void) {
  unsigned long result;

  // Initiate SS3.
  ADC0->ADCPSSI = 0x0008;

  // Wait for conversion done.
  while ((ADC0->ADCRIS & 0x08) == 0) {
  }

  // Read result (12 bits).
  result = ADC0->ADCSSFIFO3 & 0xFFF;

  // Acknowledge completion.
  ADC0->ADCISC = 0x0008;

  return result;
}

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  const ADC_PIN = GPIO_PORT_PIN_3;

  const DAC_PINS = GPIO_PORT_PIN_0 | GPIO_PORT_PIN_1 | GPIO_PORT_PIN_2 | GPIO_PORT_PIN_3;

  // Active ADC0.
  System_CTRL_RCGCADC_R |= System_CTRL_RCGCADC_ADC0_MASK;

  // Activate GPIO port B (DAC) and E (ADC).
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOB_MASK | System_CTRL_RCGCGPIO_GPIOE_MASK;

  GPIOE->AFSEL |= ADC_PIN;
  GPIOE->AMSEL |= ADC_PIN;
  GPIOE->DIR &= ~ADC_PIN;
  GPIOE->DEN &= ~ADC_PIN;

  GPIOB->AFSEL &= ~DAC_PINS;
  GPIOB->AMSEL &= ~DAC_PINS;
  GPIOB->PCTL &= ~DAC_PINS;
  GPIOB->DIR |= DAC_PINS;
  GPIOB->DEN |= DAC_PINS;

  // Sequencer 3 is highest priority.
  ADC0->ADCSSPRI = 0x0123;

  // Disable sample sequencer 3.
  ADC0->ADCACTSS &= ~0x0008;

  // Sequencer 3 is software trigger.
  ADC0->ADCEMUX &= ~0xF000;

  // Clear SS3 field, saying that AIN0 will be used.
  ADC0->ADCSSMUX3 &= ~0x000F;

  // No TS0 D0, yes IE0 END0.
  ADC0->ADCSSCTL3 = 0x0006;

  // Enable sample sequencer 3.
  ADC0->ADCACTSS |= 0x0008;

  Nokia5110_Init();

  Nokia5110_Clear();

  while (1) {
    Nokia5110_Clear();
    Nokia5110_WriteDec(ReadADC0());
    SysTickDelay(1);

    waveIndex = (waveIndex + 1) & 0x0F;

    WriteDAC(SineWave[waveIndex]);
  }
}
