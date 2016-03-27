#include <stdint.h>
#include <stdio.h>

#include "cortexm4.h"
#include "pll.h"
#include "systick.h"
#include "ports.h"
#include "i2c.h"
#include "nokia5110.h"

/* Device Registers */
#define SLAVE_I2C_ADDRESS (0x40)

GPIORegisters *chipSelectPort = GPIOB;
uint8_t chipSelectPin = GPIO_PORT_PIN_1;

void
turnOnSensor() {
  chipSelectPort->PIN1 = 0x0;
  SysTickDelay(500);
}

void
turnOffSensor() {
  chipSelectPort->PIN1 = 0x1;
  SysTickDelay(500);
}

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  // Activate GPIO port B (Chip Select).
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOB_MASK;

  chipSelectPort->AFSEL &= ~chipSelectPin;
  chipSelectPort->AMSEL &= ~chipSelectPin;
  chipSelectPort->PCTL &= ~chipSelectPin;
  chipSelectPort->DIR |= chipSelectPin;
  chipSelectPort->DEN |= chipSelectPin;

  // I2C0, 80Mhz system clock.
  I2CRegisters *i2c = I2CInitialize(I2C0Module, 80);

  Nokia5110_Init();
  Nokia5110_Clear();

  while (1) {
  }
}
