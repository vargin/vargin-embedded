#include <stdint.h>
#include <stdio.h>

#include "cortexm4.h"
#include "pll.h"
#include "systick.h"
#include "ports.h"
#include "i2c.h"

#define SENSOR_ID_SAMPLE    (0xF0)
#define SENSOR_ID           (0x50)

/* Si7005 Registers */
#define SENSOR_I2C_ADDRESS  (0x40)
#define SENSOR_I2C_STATUS   (0x00)
#define SENSOR_I2C_DATA     (0x01)
#define SENSOR_I2C_CONFIG   (0x03)
#define SENSOR_I2C_ID       (0x11)

int main(void) {
  GPIORegisters *chipSelectPort = GPIOB;
  uint8_t chipSelectPin = GPIO_PORT_PIN_1;

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

  // Enable sensor
  chipSelectPort->PIN1 = 0x0;

  // Wait until sensor is enabled.
  SysTickDelay(500);

  // I2C0, 80Mhz system clock.
  I2CRegisters *i2c = I2CInitialize(I2C0Module, 80);

  // Read device ID:
  // |S| -> |0x40|0| -> |A| -> |0x11| -> |AS| -> |Sr| -> |0x40|1| -> |A| -> |ID| -> |A| -> |P|
  uint8_t deviceId = 0x0;

  // 1. First write the address of the register we want to read
  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Write);
  I2COperationResult result = I2CSendByte(i2c, SENSOR_I2C_ID, I2C_MCS_RUN | I2C_MCS_START);

  if (result != OPERATION_OK) {
    printf("Failed to send byte %d", result);
    return result;
  }

  // 2. Restart with the READ mode
  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Read);
  result = I2CReceiveByte(i2c, &deviceId, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  if (result != OPERATION_OK) {
    printf("Failed to receive byte %d", result);
    return result;
  }

  printf("Device is successfully retrieved %d", deviceId);

  while (1) {
    SysTickDelay(1000);
  }
}
