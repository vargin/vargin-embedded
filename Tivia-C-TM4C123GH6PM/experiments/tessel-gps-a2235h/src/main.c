#include <stdint.h>
#include <stdio.h>

#include "cortexm4.h"
#include "pll.h"
#include "systick.h"
#include "ports.h"
#include "nokia5110.h"

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  Nokia5110_Init();
  Nokia5110_Clear();

  while (1) {
    SysTickDelay(3000);

    Nokia5110_Clear();
    Nokia5110_WriteString("GPS");
  }
}
