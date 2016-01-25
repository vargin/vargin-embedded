#include "CortexM4.h"
#include "SysTick.h"

void
Tick(void);

// ----------------------------------------------------------------------------

volatile uint32_t timerTicks;

// ----------------------------------------------------------------------------

void
SysTickInitialize(uint32_t ticks)
{
  SysTick->CTRL = 0UL;

  SysTick->RELOAD = TivaSystemCoreClock / ticks;
  SysTick->CURRENT = 0UL;

  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_MASK | SysTick_CTRL_TICKINT_MASK |
  SysTick_CTRL_ENABLE_MASK;
}

void
SysTickDelay(uint32_t ticks)
{
  timerTicks = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (timerTicks != 0u)
    ;
}

void
Tick(void)
{
  // Decrement to zero the counter used by the delay routine.
  if (timerTicks != 0u) {
    --timerTicks;
  }
}

// ----- SysTick_Handler() ----------------------------------------------------

void
SysTick_Handler(void)
{
  Tick();
}

// ----------------------------------------------------------------------------
