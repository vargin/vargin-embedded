#include <stdint.h>
#include <stdio.h>

#include "pll.h"
#include "systick.h"
#include "i2c.h"

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  // I2C0, 80Mhz system clock.
  I2CRegisters *i2c = InitializeI2C(I2C0Module, 80);

  while (1) {
    SysTickDelay(1000);
  }
}
