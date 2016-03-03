#include <stdint.h>
#include <stdio.h>
#include "../include/cortexm4.h"
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/adc.h"
#include "../include/nokia5110.h"
#include "../include/sounds.h"
#include "../include/timers.h"
#include "../include/nvic.h"

uint8_t* tracks[9] = {one, two, three, four, five, six, seven, eight};
uint32_t tracksLengths[9] = {4080, 4080, 3377, 2000, 982, 1042, 1054, 1098, 1802};
uint8_t trackIndex = 0;

uint8_t currentWaveIndex = 0;
uint32_t currentCount = 4080;

uint8_t armedViaADC = 0;

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

void
WriteDAC(uint8_t number) {
  GPIOB->DATA = number;
}

void
Timer0A_Handler(void) {
  // Acknowledge that interrupt is processed.
  Timer0->GPTMICR = 0x1UL;

  if (currentCount > 0) {
    WriteDAC(tracks[trackIndex][currentWaveIndex] >> 4);
    currentWaveIndex = currentWaveIndex + 1;
    currentCount = currentCount - 1;
  } else if (armedViaADC == 0 && ReadADC0() > 3000UL) {
    armedViaADC = 1;

    if (trackIndex < 8) {
      trackIndex++;
    } else {
      trackIndex = 0;
    }

    currentWaveIndex = 0;
    currentCount = tracksLengths[trackIndex];
  } else if (armedViaADC == 1 && ReadADC0() < 3000UL) {
    armedViaADC = 0;
  }
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

  unsigned long volatile delay;

  // Activate Timer0
  System_CTRL_RCGCTIMER_R |= System_CTRL_RCGCTIMER_TIMER0_MASK;

  delay = System_CTRL_RCGCTIMER_R;

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

  // Disable Timer0.
  Timer0->GPTMCTL = 0x0UL;

  // Choose 32 bit mode.
  Timer0->GPTMCFG = 0x0UL;

  // Choose periodic mode.
  Timer0->GPTMTAMR = 0x2UL;

  // Reload value
  Timer0->GPTMTAILR = 80000;

  // Clock resolution
  Timer0->GPTMTAPR = 0;

  // Clear timeout flag
  Timer0->GPTMICR = 0x1UL;

  // Arm timeout
  Timer0->GPTMIMR = 0x1UL;

  // Timer0A is 35th in vector table, interrupt number is 19.
  // Setting priority 4 (100, last 3 bits).
  NVIC->PRI4 = (NVIC->PRI4 & 0x00FFFFFF) | 0x80000000;

  // Enable IRQ 19
  NVIC->EN0 = 1 << 19;

  // Enable Timer0A
  Timer0->GPTMCTL = 0x1UL;

  Nokia5110_Init();

  Nokia5110_Clear();

  while (1) {
    Nokia5110_Clear();
    Nokia5110_WriteDec(ReadADC0());
    SysTickDelay(1000);
  }
}
