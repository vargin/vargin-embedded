#include <stdint.h>

#define SYSTEM_CTRL_RCGC1_R       (*((volatile uint32_t *) System_CTRL_RCGC1))
#define SYSTEM_CTRL_RCGC2_R       (*((volatile uint32_t *) System_CTRL_RCGC2))

typedef struct
{
  volatile uint32_t* DR;
  volatile uint32_t* FR;
  volatile uint32_t* IBRD;
  volatile uint32_t* FBRD;
  volatile uint32_t* LCRH;
  volatile uint32_t* CTL;
  volatile uint32_t* RIS;
  volatile uint32_t* CC;
} UARTPortRegisters;

extern UARTPortRegisters
UARTInitialize(PortTypes portType);
