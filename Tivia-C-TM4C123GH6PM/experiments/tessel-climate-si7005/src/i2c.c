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
I2CInitialize(I2CModules module, uint8_t systemClockMhz) {
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
  } else {
    return 0;
  }
}

void
I2CSetSlaveAddress(I2CRegisters *i2cModule, uint8_t slaveAddress, I2CReadWrite readWrite) {
  // Set the slave address to transmit data
  i2cModule->MSA = (slaveAddress << 1) | readWrite;
}

uint8_t
I2CMasterBusy(I2CRegisters *i2cModule) {
  return i2cModule->MCS & I2C_MCS_BUSY;
}

I2COperationResult
I2CSendByte(I2CRegisters *i2cModule, uint8_t data, uint8_t masterControlFlags) {
  // Write the upper address to the data register
  i2cModule->MDR = data;

  // Start the transaction
  i2cModule->MCS = masterControlFlags;

  // Wait for the device to be free
  while (I2CMasterBusy(i2cModule)) {};

  // Check for error conditions
  if (i2cModule->MCS & (I2C_MCS_ERROR | I2C_MCS_ARBLST)) {
    return ARBLST_ERROR;
  } else if (i2cModule->MCS & I2C_MCS_ERROR) {
    i2cModule->MCS = I2C_MCS_STOP;
    return BUS_ERROR;
  } else if (i2cModule->MCS & I2C_MCS_DATACK) {
    return NO_ACK_ERROR;
  } else {
    return OPERATION_OK;
  }
}

I2COperationResult
I2CReceiveByte(I2CRegisters *i2cModule, uint8_t *data, uint8_t masterControlFlags) {
  // Start the transaction
  i2cModule->MCS = masterControlFlags;

  // Wait for the device to be free
  while (I2CMasterBusy(i2cModule)) {};

  // Check for error conditions
  if (i2cModule->MCS & I2C_MCS_ERROR) {
    i2cModule->MCS = I2C_MCS_STOP;
    return BUS_ERROR;
  }

  *data = i2cModule->MDR;

  return OPERATION_OK;
}
