#include <stdint.h>
#include "cortexm4.h"

/**
 * Structure type to access the SSI.
 */
typedef struct
{
  // Offset: 0x000 GPIO Data Register.
  const uint32_t RESERVED0[1];

  // Offset: 0x004 PIN0 Data Register.
  volatile uint32_t PIN0;

  // Offset: 0x008 PIN1 Data Register.
  volatile uint32_t PIN1;

  const uint32_t RESERVED[1];

  // Offset: 0x010 PIN2 Data Register.
  volatile uint32_t PIN2;

  const uint32_t RESERVED1[3];

  // Offset: 0x020 PIN3 Data Register.
  volatile uint32_t PIN3;

  const uint32_t RESERVED2[7];

  // Offset: 0x040 PIN4 Data Register.
  volatile uint32_t PIN4;

  const uint32_t RESERVED3[15];

  // Offset: 0x080 PIN5 Data Register.
  volatile uint32_t PIN5;

  const uint32_t RESERVED4[31];

  // Offset: 0x100 PIN6 Data Register.
  volatile uint32_t PIN6;

  const uint32_t RESERVED5[63];

  // Offset: 0x200 PIN7 Data Register.
  volatile uint32_t PIN7;

  const uint32_t RESERVED6[126];

  // Offset: 0x3FC All PINs Data Register.
  volatile uint32_t DATA;

  // Offset: 0x400 GPIO Direction Register.
  volatile uint32_t DIR;

  // Offset: 0x404 GPIO Interrupt Sense Register.
  const uint32_t IS;

  // Offset: 0x408 GPIO Interrupt Both Edges Register.
  volatile uint32_t IBE;

  // Offset: 0x40C Interrupt Event Register.
  const uint32_t IE;

  // Offset: 0x410 GPIO Interrupt Mask Register.
  volatile uint32_t IM;

  // Offset: 0x414 GPIO Raw Interrupt Status Register.
  volatile uint32_t RIS;

  // Offset: 0x418 GPIO Masked Interrupt Status Register.
  const uint32_t MIS;

  // Offset: 0x41C GPIO Interrupt Clear Register.
  volatile uint32_t ICR;

  // Offset: 0x420 GPIO Alternate Function Select Register.
  volatile uint32_t AFSEL;

  const uint32_t RESERVED7[55];

  // Offset: 0x500 GPIO 2-mA Drive Select Register.
  const uint32_t DR2R;

  // Offset: 0x504 GPIO 4-mA Drive Select Register.
  const uint32_t DR4R;

  // Offset: 0x508 GPIO 8-mA Drive Select Register.
  const uint32_t DR8R;

  // Offset: 0x50C GPIO Open Drain Select Register.
  const uint32_t ODR;

  // Offset: 0x510 GPIO Pull-Up Select Register.
  volatile uint32_t PUR;

  // Offset: 0x514 GPIO Pull-Down Select Register.
  volatile uint32_t PDR;

  // Offset: 0x518 GPIO Slew Rate Control Select Register.
  const uint32_t SLR;

  // Offset: 0x51C GPIO Digital Enable Register.
  volatile uint32_t DEN;

  // Offset: 0x520 GPIO Lock Register.
  volatile uint32_t LOCK;

  // Offset: 0x524 GPIO Commit Register.
  volatile uint32_t CR;

  // Offset: 0x528 GPIO Analog Mode Select Register.
  volatile uint32_t AMSEL;

  // Offset: 0x52C GPIO Port Control Register.
  volatile uint32_t PCTL;
} GPIORegisters;

#define GPIOA  ((GPIORegisters *) GPIOA_BASE)
#define GPIOB  ((GPIORegisters *) GPIOB_BASE)
#define GPIOC  ((GPIORegisters *) GPIOC_BASE)
#define GPIOD  ((GPIORegisters *) GPIOD_BASE)
#define GPIOE  ((GPIORegisters *) GPIOE_BASE)
