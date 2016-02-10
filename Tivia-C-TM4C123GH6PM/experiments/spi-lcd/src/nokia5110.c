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
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total
#include <stdint.h>
#include <stdio.h>
#include "../include/ports.h"
#include "../include/systick.h"
#include "../include/ssi.h"
#include "../include/nokia5110.h"

#define DC_COMMAND              0
#define DC_DATA                 0x40

static GPIORegisters * SERVICE_PORT = GPIOA;
static SSIRegisters * SSI_PORT = SSI0;

static const NUMBER_OF_OCTETS = (LCD_WIDTH * LCD_HEIGHT) / 8;

static void
writeCommand(uint8_t data) {
  while((SSI_PORT->SR & SSI_SSISR_BSY_MASK) == SSI_SSISR_BSY_MASK) {};

  SERVICE_PORT->PIN6 = DC_COMMAND;
  SSI_PORT->DR = data;

  while((SSI_PORT->SR & SSI_SSISR_BSY_MASK) == SSI_SSISR_BSY_MASK) {};
}

static void
writeData(uint8_t data) {
  while((SSI_PORT->SR & SSI_SSISR_TNF_MASK) == 0) {};

  SERVICE_PORT->PIN6 = DC_DATA;
  SSI_PORT->DR = data;
}

void
Nokia5110_Init(void){
  // Nokia 5110 LCD max clock frequency is 4Mhz, so with 50Mhz system clock,
  // clock prescale divisor (must be even number) is calculated via
  // SysClk/(CPSDVSR*(1+SCR)) formula, where SCR=0, so 50 / (14 * (1 + 0)) =
  // 3.571 MHz (slower than 4 MHz).
  InitializeSSI(SSI0Module, 14);

  // 6 - command chooser pin, 7 - reset pin.
  uint32_t servicePins = GPIO_PORT_PIN_6 | GPIO_PORT_PIN_7;

  SERVICE_PORT->DIR |= servicePins;
  SERVICE_PORT->AFSEL &= ~servicePins;
  SERVICE_PORT->AMSEL &= ~servicePins;
  SERVICE_PORT->DEN |= servicePins;
  SERVICE_PORT->PCTL &= 0x00FFFFFF;

  // Reset to a known state, wait for 100ms between writes.
  SERVICE_PORT->PIN7 = 0x0;
  SysTickDelay(100);
  SERVICE_PORT->PIN7 = 0x80;

  // Chip active;
  // Horizontal addressing mode (V = 0);
  // Use extended instruction set (H = 1).
  writeCommand(0x21);

  // Set LCD Vop (contrast), minimal contrast is 0xA0 and maximum is 0xCF.
  writeCommand(0xB1);

  // Set temp coefficient.
  writeCommand(0x04);

  // LCD bias mode 1:48: try 0x13 or 0x14.
  writeCommand(0x14);

  // We must send 0x20 before modifying the display control mode.
  writeCommand(0x20);

  // Set display control to normal mode: 0x0D for inverse.
  writeCommand(0x0C);
}

void
Nokia5110_WriteOctet(uint8_t data) {
  writeData(data);
}

// Move the cursor to the desired X- and Y-position.  The
// next character will be printed here. X=0 is the leftmost
// column. Y=0 is the top row.
void Nokia5110_SetCursor(uint8_t cursorX, uint8_t cursorY){
  if((cursorX > 83) || (cursorY > 5)) {
    return;
  }

  // 7 bit is responsible for X position.
  writeCommand(0x80 | cursorX);
  // 6 bit is responsible for Y position.
  writeCommand(0x40 | cursorY);
}

// Clear the LCD by writing zeros to the entire screen and
// reset the cursor to (0,0).
void Nokia5110_Clear(void) {
  uint32_t i;
  for(i = 0; i < NUMBER_OF_OCTETS; i++) {
    writeData(0x00);
  }

  Nokia5110_SetCursor(0, 0);
}

// Fill the whole screen by drawing a 48x84 bitmap image (504 bytes in total).
void Nokia5110_WriteFullScreen(const uint8_t *ptr) {
  Nokia5110_SetCursor(0, 0);

  uint32_t i;
  for(i = 0; i < NUMBER_OF_OCTETS; i++) {
    writeData(ptr[i]);
  }
}
