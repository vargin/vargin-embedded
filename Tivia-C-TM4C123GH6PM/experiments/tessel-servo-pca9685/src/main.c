#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "cortexm4.h"
#include "pll.h"
#include "nvic.h"
#include "systick.h"
#include "ports.h"
#include "i2c.h"

/*
 * Pin map:
 * PA2 - Address 2 Pin - will be low;
 * PA3 - Address 3 Pin - will be low;
 * PA4 - Servo turn on/off pin;
 * PA5 - Switch control pin;
 */

/* Device Registers */
// See PDF with circuit, 01(fixed)1(3.3v)1(3.3v)001(3.3v)1(3.3v)
#define SLAVE_I2C_ADDRESS (0x73)
#define MODE1_ADDRESS 0x0
#define PRESCALE_ADDRESS 0xFE

#define MAX_FREQUENCY 4096

GPIORegisters *servicePort = GPIOA;
const uint8_t address2Pin = GPIO_PORT_PIN_2;
const uint8_t address3Pin = GPIO_PORT_PIN_3;
const uint8_t servoSwitchPin = GPIO_PORT_PIN_4;
const uint8_t switchPin = GPIO_PORT_PIN_5;

/**
 * Sets the PWM frequency in Hz for the PCA9685 chip.
 * 1. Set START (D0) and TEMP (D4) in CONFIG (register 0x03) to begin a new conversion,
 *    i.e., write CONFIG with 0x11;
 * 2. Poll RDY (D0) in STATUS (register 0) until it is low (=0);
 * 3. Read the upper and lower bytes of the temperature value from DATAh and DATAl
 *    (registers 0x01 and 0x02), respectively.
 */
void
setModuleFrequency(I2CRegisters *i2c, uint16_t frequencyHz) {
  float prescaleValue = ((25000000 / MAX_FREQUENCY) / frequencyHz) - 1;
  uint32_t prescale = floor(prescaleValue);

  // 1. Set config
  I2CSetSlaveAddress(i2c, SLAVE_I2C_ADDRESS, Write);
  I2COperationResult result = I2CSendByte(i2c, MODE1_ADDRESS, I2C_MCS_RUN | I2C_MCS_START);

  if (result != OPERATION_OK) {
    printf("Failed to write mode1 register address %d", result);
    return;
  }

  I2CSetSlaveAddress(i2c, SLAVE_I2C_ADDRESS, Read);

  uint8_t mode = 0x0;
  result = I2CReceiveByte(i2c, &mode, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  if (result != OPERATION_OK) {
    printf("Failed to receive mode %d", result);
    return;
  }

  printf("Mode has been read successfully: %02x", mode);
}

int main(void) {
  // Enable 80Mhz clock.
  PLLInitialize(4);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(80000UL);

  // Activate service port A.
  System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOA_MASK;

  const uint8_t allServicePins = address2Pin | address3Pin | servoSwitchPin |
      switchPin;

  servicePort->AFSEL &= ~allServicePins;
  servicePort->AMSEL &= ~allServicePins;
  servicePort->PCTL &= ~allServicePins;
  servicePort->DEN |= allServicePins;

  servicePort->DIR |= address2Pin | address3Pin | servoSwitchPin;
  servicePort->DIR &= ~switchPin;

  // Configure interrupt for switch pin.
  servicePort->IM |= switchPin;
  // A rising edge or a High level on the corresponding pin triggers an interrupt.
  servicePort->IBE &= ~switchPin;
  servicePort->IEV |= switchPin;

  // Port a is 16th in vector table, interrupt number is 0.
  // Setting priority 2 (0100, 3 bits).
  NVIC->PRI0 = (NVIC->PRI0 & 0xFFFFFF00) | 0x00000040;
  // Enable IRQ 0
  NVIC->EN0 = 1 << 0;

  // Turn on servo
  servicePort->DATA &= ~servoSwitchPin;

  // Make address 2 and address 3 pins low
  servicePort->DATA &= ~(address2Pin | address3Pin);

  // I2C0, 80Mhz system clock.
  I2CRegisters *i2c = I2CInitialize(I2C0Module, 80);

  setModuleFrequency(i2c, 50);

  while (1) {
  }
}

void GPIOPortA_Handler(void) {
  servicePort->ICR |= switchPin;
}
