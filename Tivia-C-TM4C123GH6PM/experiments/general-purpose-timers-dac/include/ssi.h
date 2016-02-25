typedef enum {SSI0Module} SSIModules;

/**
 * Structure type to access the SSI.
 */
typedef struct
{
  // Offset: 0x000 SSI Control 0 Register.
  volatile uint32_t CR0;

  // Offset: 0x004 SSI Control 1 Register.
  volatile uint32_t CR1;

  // Offset: 0x008 SSI Data Register.
  volatile uint32_t DR;

  // Offset: 0x00C SSI Status Register.
  volatile uint32_t SR;

  // Offset: 0x010 SSI Clock Prescale Register.
  volatile uint32_t CPSR;

  // Offset: 0x014 SSI Interrupt Mask Register.
  volatile uint32_t IM;

  // Offset: 0x018 SSI Raw Interrupt Status Register.
  volatile uint32_t RIS;

  // Offset: 0x01C SSI Masked Interrupt Status Register.
  volatile uint32_t MIS;

  // Offset: 0x020 SSI Interrupt Clear Register.
  volatile uint32_t ICR;

  // Offset: 0x024 SSI DMA Control Register.
  volatile uint32_t DMACTL;

  // Padding to access following registers.
  const uint32_t RESERVED[1000];

  // Offset: 0xFC8 SSI Clock Configuration Register.
  volatile uint32_t CC;
} SSIRegisters;

#define SSI0  ((SSIRegisters *) SSI0_BASE)

SSIRegisters *
InitializeSSI(SSIModules module, uint8_t clockPrescaleDivisor);
