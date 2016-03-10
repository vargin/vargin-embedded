#include <stdint.h>
#include <stdio.h>

#include "pll.h"
#include "systick.h"

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  while (1) {
    SysTickDelay(1000);
  }
}
