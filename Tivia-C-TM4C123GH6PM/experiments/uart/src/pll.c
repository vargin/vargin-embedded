#include "../include/cortexm4.h"
#include "../include/pll.h"

#define RCC   (*((volatile uint32_t *)System_CTRL_RCC))
#define RCC2  (*((volatile uint32_t *)System_CTRL_RCC2))
#define RIS   (*((volatile uint32_t *)System_CTRL_RIS))

void
PLLInitialize(uint8_t divider)
{

  // 0) Use RCC2
  // 1) Bypass PLL while initializing
  RCC2 |= System_CTRL_RCC2_USERCC2_MASK |
          System_CTRL_RCC2_BYPASS2_MASK;

  // 2) Select the crystal value and oscillator source, first clear XTAL field
  // at bits 10-6 and then set 10101 to configure for 16 MHz crystal.
  RCC &= ~System_CTRL_RCC_XTAL_ALL_MASK;
  RCC |= System_CTRL_RCC_XTAL_16_MASK;

  // 3) set the desired system divider, use 400 MHz PLL
  // IMPORTANT: this bit should be set BEFORE we clear SYSDIV2LSB - see spec.
  RCC2 |= System_CTRL_RCC2_DIV400_MASK;

  // 4) configure for main oscillator source
  // 5) activate PLL by clearing PWRDN
  // 6) clear system clock divider
  RCC2 &= ~(
    System_CTRL_RCC2_OSCSRC2_ALL_MASK |
    System_CTRL_RCC2_PWRDN2_MASK |
    System_CTRL_RCC2_SYSDIV2LSB_MASK |
    System_CTRL_RCC2_SYSDIV2_MAX_MASK
  );

  // 7) configure for divider based clock
  RCC2 |= (divider << 22);

  // 8) wait for the PLL to lock by polling PLLRIS
  // wait for PLLRIS bit
  while((RIS & 0x00000040) == 0) {};

  // 9) enable use of PLL by clearing BYPASS
  RCC2 &= ~System_CTRL_RCC2_BYPASS2_MASK;
}
