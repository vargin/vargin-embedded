#ifndef INCLUDE_I2C_H
#define INCLUDE_I2C_H

#include <stdint.h>
#include "cortexm4.h"

typedef enum {
  Write = 0x0UL,
  Read = 0x1UL
} I2CReadWrite;

#define I2C_MCS_BUSY    (0x1)
#define I2C_MCS_ERROR   (0x2)
#define I2C_MCS_ADRACK  (0x4)
#define I2C_MCS_DATACK  (0x8)
#define I2C_MCS_ARBLST  (0x10)

#define I2C_MCS_RUN     (0x1)
#define I2C_MCS_START   (0x2)
#define I2C_MCS_STOP    (0x4)
#define I2C_MCS_ACK     (0x8)

typedef enum {
  ARBLST_ERROR,
  BUS_ERROR,
  NO_ACK_ERROR,
  OPERATION_OK
} I2COperationResult;

typedef enum {
  I2C0Module
} I2CModules;

/**
 * Structure type to access the I2C.
 */
typedef struct
{
  // I2C Master Slave Address (I2CMSA), offset 0x000
  volatile uint32_t MSA;

  // I2C Master Control/Status (I2CMCS), offset 0x004
  volatile uint32_t MCS;

  // I2C Master Data (I2CMDR), offset 0x008
  volatile uint32_t MDR;

  // I2C Master Timer Period (I2CMTPR), offset 0x00C
  volatile uint32_t MTPR;

  // I2C Master Interrupt Mask (I2CMIMR), offset 0x010
  const uint32_t MIMR;

  // I2C Master Raw Interrupt Status (I2CMRIS), offset 0x014
  const uint32_t MRIS;

  // I2C Master Masked Interrupt Status (I2CMMIS), offset 0x018
  const uint32_t MMIS;

  // I2C Master Interrupt Clear (I2CMICR), offset 0x01C
  const uint32_t MICR;

  // I2C Master Configuration (I2CMCR), offset 0x020
  volatile uint32_t MCR;
} I2CRegisters;

#define I2C0 ((I2CRegisters *) I2C0_BASE)

I2CRegisters *
I2CInitialize(I2CModules module, uint8_t systemClockMHz);

void
I2CSetSlaveAddress(I2CRegisters *i2cModule, uint8_t slaveAddress, I2CReadWrite readWrite);

uint8_t
I2CMasterBusy(I2CRegisters *i2cModule);

I2COperationResult
I2CSendByte(I2CRegisters *i2cModule, uint8_t data, uint8_t masterControlFlags);

I2COperationResult
I2CReceiveByte(I2CRegisters *i2cModule, uint8_t *data, uint8_t masterControlFlags);

#endif //INCLUDE_I2C_H
