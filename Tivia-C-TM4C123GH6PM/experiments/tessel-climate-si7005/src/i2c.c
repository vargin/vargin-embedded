#include <stdint.h>
#include "cortexm4.h"
#include "i2c.h"
#include "ports.h"

/**
 * I2C pin out:
 * I2C0: I2C0SCL - PB2, I2C0SDA - PB3;
 * I2C1: I2C1SCL - PA6, I2C1SDA - PA7;
 * I2C2: I2C2SCL - PE4, I2C2SDA - PE5;
 * I2C3: I2C3SCL - PD0, I2C3SDA - PD1;
 */

I2CRegisters *
InitializeI2C(I2CModules module, uint8_t systemClockMhz) {
  if (module == I2C0Module) {
    uint32_t sclPin = GPIO_PORT_PIN_2;
    uint32_t sdaPin = GPIO_PORT_PIN_3;

    GPIORegisters *gpioPort = GPIOB;
    I2CRegisters *i2cModule = I2C0;

    // Activate I2C0.
    System_CTRL_RCGCI2C_R |= System_CTRL_RCGCI2C_I2C0_MASK;

    // Activate GPIO port B.
    System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOB_MASK;

    // Configure SCL
    gpioPort->DEN |= sclPin;
    gpioPort->AFSEL |= sclPin;
    gpioPort->AMSEL &= ~sclPin;

    // Configure SDA
    gpioPort->DEN |= sdaPin;
    gpioPort->AFSEL |= sdaPin;
    gpioPort->AMSEL &= ~sdaPin;
    gpioPort->ODR |= sdaPin;

    // Choose I2C alternative function (0x3) for pins 2 and 3.
    gpioPort->PCTL = (gpioPort->PCTL & 0xFFFF00FF) + 0x00003300;

    // Choose master mode
    i2cModule->MCR = 0x00000010;

    // Set the clock speed to be 100 Kpbs assuming a 50MHz clock
    // TPR = (System Clock / (2 * (SCL_LP + SCL_HP) * SCL_CLK)) - 1;
    // TPR = (System Clock / (2 * (6 + 4) * 100000)) - 1
    // TPR = (System Clock / 2000000) - 1
    i2cModule->MTPR = (systemClockMhz / 2) - 1;

    return i2cModule;
  }
}
