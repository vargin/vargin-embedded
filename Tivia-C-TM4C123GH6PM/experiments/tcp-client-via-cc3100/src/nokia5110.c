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

static const uint8_t ASCII[][5] = {
     {0x00, 0x00, 0x00, 0x00, 0x00} // 20
    ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
    ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
    ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
    ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
    ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
    ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
    ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
    ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
    ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
    ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
    ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
    ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
    ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
    ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
    ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
    ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
    ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
    ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
    ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
    ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
    ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
    ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
    ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
    ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
    ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
    ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
    ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
    ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
    ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
    ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
    ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
    ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
    ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
    ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
    ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
    ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
    ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
    ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
    ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
    ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
    ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
    ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
    ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
    ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
    ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
    ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
    ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
    ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
    ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
    ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
    ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
    ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
    ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
    ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
    ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
    ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
    ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
    ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
    ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
    ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c '\'
    ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
    ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
    ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
    ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
    ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
    ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
    ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
    ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
    ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
    ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
    ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
    ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
    ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
    ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
    ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
    ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
    ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
    ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
    ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
    ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
    ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
    ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
    ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
    ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
    ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
    ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
    ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
    ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
    ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
    ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
    ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
    ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
    ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
    ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
};

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
  // Nokia 5110 LCD max clock frequency is 4Mhz, so with 80Mhz system clock,
  // clock prescale divisor (must be even number) is calculated via
  // SysClk/(CPSDVSR*(1+SCR)) formula, where SCR=0, so 80 / (20 * (1 + 0)) =
  // 4 MHz.
  InitializeSSI(SSI0Module, 20);

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

void
Nokia5110_WriteChar(uint8_t data) {
  // Blank vertical line padding.
  Nokia5110_WriteOctet(0x00);

  int i;
  for(i = 0; i < 5; i = i + 1){
    Nokia5110_WriteOctet(ASCII[data - 0x20][i]);
  }

  // Blank vertical line padding.
  Nokia5110_WriteOctet(0x00);
}

void
Nokia5110_WriteString(uint8_t *ptr) {
  while(*ptr) {
    Nokia5110_WriteChar((uint8_t)*ptr);
    ptr = ptr + 1;
  }
}

void
Nokia5110_WriteDec(uint16_t n) {
  if (n < 10) {
    Nokia5110_WriteString("    ");
    // n is between 0 and 9.
    Nokia5110_WriteChar(n + '0');
  } else if (n < 100) {
    Nokia5110_WriteString("   ");
    // Tens digit.
    Nokia5110_WriteChar(n / 10 + '0');
    // Ones digit.
    Nokia5110_WriteChar(n % 10 + '0');
  } else if (n < 1000) {
    Nokia5110_WriteString("  ");
    // Hundreds digit.
    Nokia5110_WriteChar(n / 100 + '0');
    n = n % 100;
    // Tens digit.
    Nokia5110_WriteChar(n / 10 + '0');
    // Ones digit.
    Nokia5110_WriteChar(n % 10 + '0');
  } else if (n < 10000) {
    Nokia5110_WriteChar(' ');
    // Thousands digit.
    Nokia5110_WriteChar(n / 1000 + '0');
    n = n % 1000;
    // Hundreds digit.
    Nokia5110_WriteChar(n / 100 + '0');
    n = n % 100;
    // Tens digit.
    Nokia5110_WriteChar(n / 10 + '0');
    // Ones digit.
    Nokia5110_WriteChar(n % 10 + '0');
  } else {
    // Ten-thousands digit.
    Nokia5110_WriteChar(n / 10000 + '0');
    n = n % 10000;
    // Thousands digit.
    Nokia5110_WriteChar(n / 1000 + '0');
    n = n % 1000;
    // Hundreds digit.
    Nokia5110_WriteChar(n / 100 + '0');
    n = n % 100;
    // Tens digit.
    Nokia5110_WriteChar(n / 10 + '0');
    // Ones digit.
    Nokia5110_WriteChar(n % 10 + '0');
  }
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
