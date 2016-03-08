#include <stdint.h>
#include <stdio.h>
#include "../include/cortexm4.h"
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/ports.h"
#include "../include/nokia5110.h"

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  Nokia5110_Init();

  Nokia5110_Clear();

  while (1) {
    Nokia5110_Clear();
    Nokia5110_WriteDec(100);
    SysTickDelay(1000);
  }
}
