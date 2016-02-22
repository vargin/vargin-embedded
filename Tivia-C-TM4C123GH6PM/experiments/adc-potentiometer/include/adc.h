/**
 * Structure type to access ADC registers.
 */
typedef struct
{
  // ADC Active Sample Sequencer (ADCACTSS), offset 0x000.
  volatile uint32_t ADCACTSS;

  // ADC Raw Interrupt Status (ADCRIS), offset 0x004
  volatile uint32_t ADCRIS;

  // ADC Interrupt Mask (ADCIM), offset 0x008
  const uint32_t ADCIM;

  // ADC Interrupt Status and Clear (ADCISC), offset 0x00C
  volatile uint32_t ADCISC;

  // ADC Overflow Status (ADCOSTAT), offset 0x010
  const uint32_t ADCOSTAT;

  // ADC Event Multiplexer Select (ADCEMUX), offset 0x014
  volatile uint32_t ADCEMUX;

  // ADC Underflow Status (ADCUSTAT), offset 0x018
  const uint32_t ADCUSTAT;

  // ADC Trigger Source Select (ADCTSSEL), offset 0x01C
  const uint32_t ADCTSSEL;

  // ADC Sample Sequencer Priority (ADCSSPRI), offset 0x020
  volatile uint32_t ADCSSPRI;

  // ADC Sample Phase Control (ADCSPC), offset 0x024
  const uint32_t ADCSPC;

  // ADC Processor Sample Sequence Initiate (ADCPSSI), offset 0x028
  volatile uint32_t ADCPSSI;

  const uint32_t RESERVED3[29];

  // ADC Sample Sequence Input Multiplexer Select 3 (ADCSSMUX3), offset 0x0A0
  volatile uint32_t ADCSSMUX3;

  // ADC Sample Sequence Control 3 (ADCSSCTL3), offset 0x0A4
  volatile uint32_t ADCSSCTL3;

  // ADC Sample Sequence Result FIFO 3 (ADCSSFIFO3), offset 0x0A8
  volatile uint32_t ADCSSFIFO3;

} ADCRegisters;

#define ADC0  ((ADCRegisters *) System_ADC0_BASE)
