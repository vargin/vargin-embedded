#include <stdint.h>
#include "../include/pll.h"
#include "../include/systick.h"

int main(void){
  // Set system clock to 50 MHz.
  PLLInitialize(7);

  // Use 1ms gradation for 50 Mhz clock.
  SysTickInitialize(50000UL);

  while(1) {
  }
}
