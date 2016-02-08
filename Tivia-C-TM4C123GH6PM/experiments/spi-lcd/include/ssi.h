typedef enum {SSI0Module} SSIModules;

/**
 * Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  // Offset: 0x000 SSI Control 0 Register.
  volatile uint32_t SSICR0;

  // Offset: 0x004 SSI Control 1 Register.
  volatile uint32_t SSICR1;

  // Offset: 0x008 SSI Data Register.
  volatile uint32_t SSIDR;

  // Offset: 0x00C SSI Status Register.
  volatile uint32_t SSISR;

  // Offset: 0x010 SSI Clock Prescale Register.
  volatile uint32_t SSICPSR;

  // Offset: 0x014 SSI Interrupt Mask Register.
  volatile uint32_t SSIIM;

  // Offset: 0x018 SSI Raw Interrupt Status Register.
  volatile uint32_t SSIRIS;

  // Offset: 0x01C SSI Masked Interrupt Status Register.
  volatile uint32_t SSIMIS;

  // Offset: 0x020 SSI Interrupt Clear Register.
  volatile uint32_t SSIICR;

  // Offset: 0x024 SSI DMA Control Register.
  volatile uint32_t SSIDMACTL;

  // Padding to access following registers.
  const uint32_t RESERVED[1000];

  // Offset: 0xFC8 SSI Clock Configuration Register.
  volatile uint32_t SSICC;
} SSIType;

#define SSI0  ((SSIType *) SSI0_BASE)

void
InitializeSSI(SSIModules module, uint8_t clockPrescaleDivisor);
