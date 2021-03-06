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
#define LED0_ON_L_ADDRESS 0x06
#define LED0_ON_H_ADDRESS 0x07
#define LED0_OFF_L_ADDRESS 0x08
#define LED0_OFF_H_ADDRESS 0x09

#define SERVO_INDEX 1
#define MAX_FREQUENCY 4096
#define LOW_PWM 0.05
#define HIGH_PWM 0.14

GPIORegisters *servicePort = GPIOA;
const uint8_t address2Pin = GPIO_PORT_PIN_2;
const uint8_t address3Pin = GPIO_PORT_PIN_3;
const uint8_t servoSwitchPin = GPIO_PORT_PIN_4;
const uint8_t switchPin = GPIO_PORT_PIN_5;

I2CRegisters *i2c = I2C0;
float position = 0.0;
uint8_t moveRequested = 0;


/**
 * Sets the PWM frequency in Hz for the PCA9685 chip.
 */
void
setModuleFrequency(I2CRegisters *i2c, uint16_t frequencyHz) {
  I2CSetSlaveAddress(i2c, SLAVE_I2C_ADDRESS, Write);
  I2CSendByte(i2c, MODE1_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);

  uint8_t mode = 0x0;
  I2CSetSlaveAddress(i2c, SLAVE_I2C_ADDRESS, Read);
  I2CReceiveByte(i2c, &mode, I2C_MCS_START | I2C_MCS_RUN);

  I2CSetSlaveAddress(i2c, SLAVE_I2C_ADDRESS, Write);

  // Writes to PRE_SCALE register are blocked when SLEEP bit is logic 0 (MODE 1).
  // So we're setting SLEEP bit to set prescale.
  I2CSendByte(i2c, MODE1_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, mode | 0x10, I2C_MCS_RUN);

  float prescaleValue = ((25000000 / MAX_FREQUENCY) / frequencyHz) - 1;
  uint8_t prescale = floor(prescaleValue);

  I2CSendByte(i2c, PRESCALE_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, prescale, I2C_MCS_RUN);

  I2CSendByte(i2c, MODE1_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, mode, I2C_MCS_RUN);

  I2CSendByte(i2c, MODE1_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, 0xa1, I2C_MCS_RUN | I2C_MCS_STOP);
}

void
setDutyCycle(I2CRegisters *i2c, float cycle) {
  uint16_t convertOn = 0;
  uint16_t convertOff = floor(MAX_FREQUENCY * cycle);

  I2CSetSlaveAddress(i2c, SLAVE_I2C_ADDRESS, Write);

  I2CSendByte(i2c, LED0_ON_L_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, convertOn & 0xFF, I2C_MCS_RUN);
  I2CSendByte(i2c, LED0_ON_H_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, convertOn >> 8, I2C_MCS_RUN);
  I2CSendByte(i2c, LED0_OFF_L_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, convertOff & 0xFF, I2C_MCS_RUN);
  I2CSendByte(i2c, LED0_OFF_H_ADDRESS, I2C_MCS_START | I2C_MCS_RUN);
  I2CSendByte(i2c, convertOff >> 8, I2C_MCS_RUN | I2C_MCS_STOP);
}

void move(I2CRegisters *i2c, float position) {
  setDutyCycle(i2c, (position * (HIGH_PWM - LOW_PWM)) + LOW_PWM);
}

int main(void) {
  // Enable 50Mhz clock.
  PLLInitialize(7);

  // Use 1ms gradation for 80 Mhz clock.
  SysTickInitialize(50000UL);

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

  // I2C0, 50Mhz system clock.
  I2CInitialize(I2C0Module, 50);

  // Turn on servo
  // servicePort->DATA &= ~servoSwitchPin;
  servicePort->PIN4 = 0x0;

  // Make address 2 and address 3 pins low
  // servicePort->DATA &= ~(address2Pin | address3Pin);
  servicePort->PIN2 = 0x0;
  servicePort->PIN3 = 0x0;

  setModuleFrequency(i2c, 50);

  while (1) {
    //if (moveRequested) {
      move(i2c, position);

       position += 0.1;
       if (position >= 1) {
         // Reset servo position
         position = 0.0;
       }

       SysTickDelay(500);

       moveRequested = 0;
    //}
  }
}

void GPIOPortA_Handler(void) {
  servicePort->ICR |= switchPin;

  //moveRequested = 1;
}
