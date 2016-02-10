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

  Nokia5110_Init();

  Nokia5110_Clear();

  uint8_t rowCursor = 0;
  uint8_t picCursor = 0;

  const uint8_t maxRows = 6;
  const uint8_t maxPicCount = 4;

  for (rowCursor = 0; rowCursor < maxRows; rowCursor++) {
    Nokia5110_WriteOctet(0x00);
    Nokia5110_WriteOctet(0x00);

    for (picCursor = 0; picCursor < maxPicCount; picCursor++) {
      Nokia5110_WriteOctet(0x00);
      Nokia5110_WriteOctet(0x0E);
      Nokia5110_WriteOctet(0x11);
      Nokia5110_WriteOctet(0x21);
      Nokia5110_WriteOctet(0x42);
      Nokia5110_WriteOctet(0x41);
      Nokia5110_WriteOctet(0x21);
      Nokia5110_WriteOctet(0x11);
      Nokia5110_WriteOctet(0x0E);
      Nokia5110_WriteOctet(0x00);

      Nokia5110_WriteOctet(0x00);
      Nokia5110_WriteOctet(0x0E);
      Nokia5110_WriteOctet(0x1F);
      Nokia5110_WriteOctet(0x3F);
      Nokia5110_WriteOctet(0x7E);
      Nokia5110_WriteOctet(0x7F);
      Nokia5110_WriteOctet(0x3F);
      Nokia5110_WriteOctet(0x1F);
      Nokia5110_WriteOctet(0x0E);
      Nokia5110_WriteOctet(0x00);
    }

    Nokia5110_WriteOctet(0x00);
    Nokia5110_WriteOctet(0x00);
  }


  while(1) {
  }
}
