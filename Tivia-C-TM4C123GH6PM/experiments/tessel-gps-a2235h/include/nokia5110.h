#ifndef INCLUDE_NOKIA_H
#define INCLUDE_NOKIA_H

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

// Maximum dimensions of the LCD.
#define LCD_WIDTH     84
#define LCD_HEIGHT    48

void
Nokia5110_Init(void);

// Writes 8-bit value to the LCD, every character has empty banks from both
// sides for readability purpose.
// Since characters are 8 pixels tall and 5 pixels wide, 12 characters fit per
// row, and there are six rows.
void
Nokia5110_WriteOctet(uint8_t data);

void
Nokia5110_WriteChar(char data);

void
Nokia5110_WriteString(char *ptr);

void
Nokia5110_WriteDec(uint16_t n);

// Move the cursor to the desired X- and Y-position.  The
// next character will be printed here. X=0 is the leftmost
// column. Y=0 is the top row.
void Nokia5110_SetCursor(uint8_t cursorX, uint8_t cursorY);

// Clear the LCD by writing zeros to the entire screen and
// reset the cursor to (0,0).
void Nokia5110_Clear(void);

// Fill the whole screen by drawing a 48x84 bitmap image (504 bytes in total).
void Nokia5110_WriteFullScreen(const uint8_t *ptr);

#endif //INCLUDE_NOKIA_H
