#include <stdint.h>
#include "CortexM4.h"

/**
 * Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  volatile uint32_t RCC;
  volatile uint32_t RCC2;
  volatile uint32_t RIS;
} PLLType;

extern void
PLLInitialize(uint8_t divisor);
