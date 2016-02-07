// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected

#include <stdint.h>
#include "../include/pll.h"
#include "../include/systick.h"
#include "../include/nokia5110.h"

int main(void){
  // Set system clock to 50 MHz.
  PLLInitialize(7);

  // Use 1ms gradation for 50 Mhz clock.
  SysTickInitialize(50000UL);

  uint32_t count = 0;

  Nokia5110_Init();

  Nokia5110_OutChar(127);               // print UT sign
  while(1){
    Nokia5110_SetCursor(5, 5);          // five leading spaces, bottom row
    Nokia5110_OutChar((count%26)+'A');
    Nokia5110_OutChar(' ');
    Nokia5110_OutUDec(count);
    SysTickDelay(1000);                     // delay ~0.5 sec at 50 MHz
    count = count + 1;
  }
}
