#include <stdint.h>
#include <stdio.h>

#include "cortexm4.h"
#include "pll.h"
#include "systick.h"
#include "ports.h"
#include "i2c.h"

#define SENSOR_ID_SAMPLE   (0xF0)
#define SENSOR_ID          (0x50)

/* Si7005 Registers */
#define SENSOR_I2C_ADDRESS (0x40)
#define SENSOR_I2C_STATUS  (0x00)
#define SENSOR_I2C_DATA    (0x01)
#define SENSOR_I2C_CONFIG  (0x03)
#define SENSOR_I2C_ID      (0x11)

/* Si7005 Config Registers */
#define SENSOR_CONFIG_START       (0x01)
#define SENSOR_CONFIG_HEAT        (0x02)
#define SENSOR_CONFIG_HUMIDITY    (0x00)
#define SENSOR_CONFIG_TEMPERATURE (0x10)
#define SENSOR_CONFIG_FAST        (0x20)

/* Si7005 Status Register */
#define SENSOR_STATUS_NOT_READY (0x01)

/* Coefficients */
#define TEMPERATURE_OFFSET (50)
#define TEMPERATURE_SLOPE  (32)
#define HUMIDITY_OFFSET    (24)
#define HUMIDITY_SLOPE     (16)
#define a0                 (-4.7844)
#define a1                 (0.4008)
#define a2                 (-0.00393)
#define q0                 (0.1973)
#define q1                 (0.00237)

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

/**
 * The following steps should be performed in sequence to take a temperature measurement:
 * 1. Set START (D0) and TEMP (D4) in CONFIG (register 0x03) to begin a new conversion,
 *    i.e., write CONFIG with 0x11;
 * 2. Poll RDY (D0) in STATUS (register 0) until it is low (=0);
 * 3. Read the upper and lower bytes of the temperature value from DATAh and DATAl
 *    (registers 0x01 and 0x02), respectively.
 */
float
readTemperature(I2CRegisters *i2c) {
  turnOnSensor();

  float temperature = -100.0;

  // 1. Set config
  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Write);
  I2COperationResult result = I2CSendByte(i2c, SENSOR_I2C_CONFIG, I2C_MCS_RUN | I2C_MCS_START);

  if (result != OPERATION_OK) {
    printf("Failed to write config register address %d", result);
    return temperature;
  }

  result = I2CSendByte(
      i2c, SENSOR_CONFIG_START | SENSOR_CONFIG_TEMPERATURE, I2C_MCS_RUN | I2C_MCS_STOP
  );

  if (result != OPERATION_OK) {
    printf("Failed to set config %d", result);
    return temperature;
  }

  // 2. Poll STATUS.
  result = I2CSendByte(i2c, SENSOR_I2C_STATUS, I2C_MCS_RUN | I2C_MCS_START);

  if (result != OPERATION_OK) {
    printf("Failed to write status register address %d", result);
    return temperature;
  }

  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Read);

  uint8_t status = 0x1;
  while(status & SENSOR_STATUS_NOT_READY) {
    result = I2CReceiveByte(i2c, &status, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

    if (result != OPERATION_OK) {
      printf("Failed to receive status %d", result);
      return temperature;
    }
  }

  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Write);
  result = I2CSendByte(i2c, SENSOR_I2C_DATA, I2C_MCS_RUN | I2C_MCS_START);

  if (result != OPERATION_OK) {
    printf("Failed to write data register address %d", result);
    return temperature;
  }

  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Read);

  uint8_t dataHigh = 0;
  result = I2CReceiveByte(
      i2c, &dataHigh, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_ACK
  );

  if (result != OPERATION_OK) {
    printf("Failed to receive temperature high bit %d", result);
    return temperature;
  }

  uint8_t dataLow = 0;
  result = I2CReceiveByte(i2c, &dataLow, I2C_MCS_RUN | I2C_MCS_STOP);

  if (result != OPERATION_OK) {
    printf("Failed to receive temperature low bit %d", result);
    return temperature;
  }

  turnOffSensor();

  uint16_t rawTemperature = ((dataHigh << 8) | dataLow) >> 2;
  temperature = (rawTemperature / (float)TEMPERATURE_SLOPE ) - TEMPERATURE_OFFSET;

  return temperature;
}

uint8_t
readSensorId(I2CRegisters *i2c) {
  turnOnSensor();

  // Read device ID:
  // |S| -> |0x40|0| -> |A| -> |0x11| -> |AS| -> |Sr| -> |0x40|1| -> |A| -> |ID| -> |A| -> |P|
  uint8_t deviceId = 0x0;

  // 1. First write the address of the register we want to read
  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Write);
  I2COperationResult result = I2CSendByte(i2c, SENSOR_I2C_ID, I2C_MCS_RUN | I2C_MCS_START);

  if (result != OPERATION_OK) {
    printf("Failed to send byte %d", result);
    return deviceId;
  }

  // 2. Restart with the READ mode
  I2CSetSlaveAddress(i2c, SENSOR_I2C_ADDRESS, Read);
  result = I2CReceiveByte(i2c, &deviceId, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  if (result != OPERATION_OK) {
    printf("Failed to receive byte %d", result);
    return deviceId;
  }

  turnOffSensor();

  return deviceId;
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

  uint8_t deviceId = readSensorId(i2c);

  if ((deviceId & SENSOR_ID_SAMPLE) != SENSOR_ID) {
    printf("Sensor is not found!");
    return -1;
  }

  printf("Device ID is successfully retrieved %d", deviceId);

  int8_t temperature = 0;

  while (1) {
    SysTickDelay(3000);
    temperature = readTemperature(i2c);
    printf("Temperature is successfully retrieved %d", temperature);
  }
}
