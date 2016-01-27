#include <stdint.h>
#include "cortexm4.h"

/**
 * Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile uint32_t CTRL;

  /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile uint32_t RELOAD;

  /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  volatile uint32_t CURRENT;

  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
  volatile uint32_t CALIB;
} SysTickType;

/*!< SysTick configuration structure */
#define SysTick             ((SysTickType   *)     SysTick_BASE)

extern volatile uint32_t timerTicks;

extern void
SysTickInitialize(uint32_t ticks);

extern void
SysTickDelay(uint32_t ticks);
