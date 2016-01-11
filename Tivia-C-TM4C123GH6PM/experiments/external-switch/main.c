#include <stdint.h>

// General-Purpose Input/Output Run Mode Clock Gating Control (spec, p. 340).
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

// GPIO Analog Mode Select (GPIOAMSEL) (spec, p. 687).
#define GPIO_PORTF_AMSEL_R      (*((volatile uint32_t *)0x40025528))
#define GPIO_PORTE_AMSEL_R      (*((volatile uint32_t *)0x40024528))

// GPIO Port Control (GPIOPCTL) (spec, p. 688).
#define GPIO_PORTF_PCTL_R       (*((volatile uint32_t *)0x4002552C))
#define GPIO_PORTE_PCTL_R       (*((volatile uint32_t *)0x4002452C))

// GPIO Alternate Function Select (GPIOAFSEL) (spec, p. 671).
#define GPIO_PORTF_AFSEL_R      (*((volatile uint32_t *)0x40025420))
#define GPIO_PORTE_AFSEL_R      (*((volatile uint32_t *)0x40024420))

// The GPIODIR register is the data direction register (spec, p. 663).
#define GPIO_PORTF_DIR_R        (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))

// GPIO Digital Enable (GPIODEN) (spec, p. 682).
#define GPIO_PORTF_DEN_R        (*((volatile uint32_t *)0x4002551C))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))

// The GPIODATA register is the data register (spec, p. 662)
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x400253FC))
#define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))

// 0x4002 5000 + 0x0020
#define PORTF_PIN3_DATA         (*((volatile uint32_t *)0x40025020))

// 0x4002 4000 + 0x0020
#define PORTE_PIN2_DATA         (*((volatile uint32_t *)0x40024010))

void initPortFE(void) {
  /**
   * Enable the Port’s Clock in RCGCGPIO. You are required to enable the clock
   * prior to accessing any of the peripherals registers.  If you don’t enable
   * the peripheral’s clock, your application will end up in the fault handler.
   * Here we enabled clock only for Port F and E (5th and 4th bits): OR ----0011.0000.
   * Specification, page 340.
   */
  SYSCTL_RCGCGPIO_R |= 0x00000030;

  /**
   * Disable analog on all pins of port F.
   */
  GPIO_PORTF_AMSEL_R = 0x00;
  GPIO_PORTE_AMSEL_R = 0x00;

  /**
   * Disable analog on all pins of port F.
   */
  GPIO_PORTF_PCTL_R = 0x00000000;
  GPIO_PORTE_PCTL_R = 0x00000000;

  /**
   * Clear the bits in the Alternate Function Select register (AFSEL).
   * Pins on the TM4C123 can be configured as GPIO pins or as an alternate
   * function (eg: serial interface). We want them to be GPIO pins, so make sure
   * to clear this register. All pins are GPIO.
   */
  GPIO_PORTF_AFSEL_R = 0x00;
  GPIO_PORTE_AFSEL_R = 0x00;

  /**
   * Configure each pin as an input or output in the DIR register. PF3-1 - output ones.
   * xx00.1110.
   */
  GPIO_PORTF_DIR_R |= 0x08;
  GPIO_PORTE_DIR_R &= ~0x04;

  /*
   * Enable digital I/O on PF4-0, 0x1F is 0001 1111.
   */
  GPIO_PORTF_DEN_R |= 0x08;
  GPIO_PORTE_DEN_R |= 0x04;
}

int main(void) {
	initPortFE();

	while(1) {
	    switch(PORTE_PIN2_DATA){
	      case 0x04:
	    	PORTF_PIN3_DATA = 0x08;
	        break;

	      case 0x0:
	        PORTF_PIN3_DATA = 0x0;
	        break;
	    }
	  }

	return 0;
}
