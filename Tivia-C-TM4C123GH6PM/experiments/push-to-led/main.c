/**
 * NOTE: The NMI (non-maskable interrupt) is on PF0. That means that the
 * Alternate Function Select, Pull-Up Resistor, Pull-Down Resistor, and Digital
 * Enable are all locked for PF0 until a value of 0x4C4F434B is written to the
 * Port F GPIO Lock Register. After Port F is unlocked, bit 0 of the Port F GPIO
 * Commit Register must be set to allow access to PF0's control registers.
 */
#include <stdint.h>

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

// GPIO Lock (spec, p. 684).
#define GPIO_PORTF_LOCK_R       (*((volatile uint32_t *)0x40025520))

// GPIO Commit (GPIOCR) (spec, p. 685).
#define GPIO_PORTF_CR_R         (*((volatile uint32_t *)0x40025524))

// GPIO Analog Mode Select (GPIOAMSEL) (spec, p. 687).
#define GPIO_PORTF_AMSEL_R      (*((volatile uint32_t *)0x40025528))

// GPIO Port Control (GPIOPCTL) (spec, p. 688).
#define GPIO_PORTF_PCTL_R       (*((volatile uint32_t *)0x4002552C))

// GPIO Alternate Function Select (GPIOAFSEL) (spec, p. 671).
#define GPIO_PORTF_AFSEL_R      (*((volatile uint32_t *)0x40025420))

// The GPIODIR register is the data direction register (spec, p. 663).
#define GPIO_PORTF_DIR_R        (*((volatile uint32_t *)0x40025400))

// The GPIOPUR register is the pull-up control register
#define GPIO_PORTF_PUR_R        (*((volatile uint32_t *)0x40025510))

// GPIO Digital Enable (GPIODEN) (spec, p. 682).
#define GPIO_PORTF_DEN_R        (*((volatile uint32_t *)0x4002551C))

// The GPIODATA register is the data register (spec, p. 662)
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x400253FC))

// Unlocks the GPIO_CR register, magic number from spec (spec, p. 684).
#define GPIO_LOCK_KEY           0x4C4F434B

#define BLUE      0x04
#define RED       0x02
#define NO_LED    0x00
#define ALL_LEDS  0x0E

void initPortF(void) {
  /**
   * Enable the Port’s Clock in RCGCGPIO. You are required to enable the clock
   * prior to accessing any of the peripherals registers.  If you don’t enable
   * the peripheral’s clock, your application will end up in the fault handler.
   * Here we enabled clock only for Port F (5th bit): OR ----0010.0000.
   * Specification, page 340.
   */
  SYSCTL_RCGCGPIO_R |= 0x00000020;

  /**
   * Unlock the Port F.
   */
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;

  /**
   * The value of the GPIOCR register determines which bits of the GPIOAFSEL,
   * GPIOPUR, GPIOPDR, and GPIODEN registers are committed when a write to these
   * registers is performed. Only PF0 needs to be unlocked, other bits can't be
   * locked. 0x1F is 0111 1111.
   */
  GPIO_PORTF_CR_R = 0x1F;

  /**
   * Disable analog on all pins of port F.
   */
  GPIO_PORTF_AMSEL_R = 0x00;

  /**
   * Disable analog on all pins of port F.
   */
  GPIO_PORTF_PCTL_R = 0x00000000;

  /**
   * Clear the bits in the Alternate Function Select register (AFSEL).
   * Pins on the TM4C123 can be configured as GPIO pins or as an alternate
   * function (eg: serial interface). We want them to be GPIO pins, so make sure
   * to clear this register. All pins are GPIO.
   */
  GPIO_PORTF_AFSEL_R = 0x00;

  /**
   * Configure each pin as an input or output in the DIR register. PF4 and PF0
   * pins will be input pins and PF3-1 - output ones.
   * xx00.1110.
   */
  GPIO_PORTF_DIR_R = 0x0E;

  /**
   * Enable pull-up on PF0 and PF4. 0x11 is 00010001.
   */
  GPIO_PORTF_PUR_R = 0x11;

  /*
   * Enable digital I/O on PF4-0, 0x1F is 0001 1111.
   */
  GPIO_PORTF_DEN_R = 0x1F;
}

uint32_t readPortF(void){
  return (GPIO_PORTF_DATA_R&0x11);  // read PF4,PF0 inputs
}

void writePortF(uint32_t data){ // write PF3-PF1 outputs
  GPIO_PORTF_DATA_R = data;
}

int main(void){ uint32_t status;
  initPortF();

  while(1){
    status = readPortF();
    switch(status){
      // Switch #1 is pressed: xxx0 xxx1 & 1111 1111 = 0x01.
      case 0x01:
        writePortF(BLUE);
        break;

      // Switch #2 is pressed: xxx1 xxx0 & 1111 1111 = 0x10.
      case 0x10:
        writePortF(NO_LED);
        break;

      // Switch #1 and #2 are pressed: xxx0 xxx0 & 1111 1111 = 0x0
      case 0x00:
        writePortF(ALL_LEDS);
        break;

      // Switch #1 and #2 are NOT pressed: xxx1 xxx1 & 1111 1111 = 0x11
      case 0x11:
        // writePortF();
        break;
    }
  }
}
