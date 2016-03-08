#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/systick.h"

typedef void (*TickerType)(void);

TickerType ticker;

void
Tick(void);

// ----------------------------------------------------------------------------

volatile uint32_t timerTicks;

// ----------------------------------------------------------------------------

void
SysTickInitialize(uint32_t sysTickEventPeriod)
{
  SysTickInitializeWithCustomTicker(sysTickEventPeriod, Tick);
}

void
SysTickInitializeWithCustomTicker(uint32_t sysTickEventPeriod, TickerType customTicker) {
  SysTick->CTRL = 0UL;

  SysTick->RELOAD = sysTickEventPeriod;
  SysTick->CURRENT = 0UL;

  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_MASK |
                  SysTick_CTRL_TICKINT_MASK |
                  SysTick_CTRL_ENABLE_MASK;

  ticker = customTicker;
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

// Handler is called every Clock / SysTick->RELOAD times, so if say we have
// 66.67 Mhz clock and we set 66670 as Reaload register - that means or handler
// will be called every 1ms.
void
SysTick_Handler(void)
{
  ticker();
}

// ----------------------------------------------------------------------------
