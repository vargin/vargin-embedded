/**
 * Structure type to access NVIC registers.
 */
typedef struct
{
  const uint32_t RESERVED[64];

  // Interrupt 0-31 Set Enable (EN0), offset 0x100
  volatile uint32_t EN0;

  // Interrupt 32-63 Set Enable (EN1), offset 0x104
  const uint32_t EN1;

  // Interrupt 64-95 Set Enable (EN2), offset 0x108
  const uint32_t EN2;

  // Interrupt 96-127 Set Enable (EN3), offset 0x10C
  const uint32_t EN3;

  // Interrupt 128-138 Set Enable (EN4), offset 0x110
  const uint32_t EN4;

  const uint32_t RESERVED2[27];

  // Interrupt 0-31 Clear Enable (DIS0), offset 0x180
  const uint32_t DIS0;

  // Interrupt 32-63 Clear Enable (DIS1), offset 0x184
  const uint32_t DIS1;

  // Interrupt 64-95 Clear Enable (DIS2), offset 0x188
  const uint32_t DIS2;

  // Interrupt 96-127 Clear Enable (DIS3), offset 0x18C
  const uint32_t DIS3;

  // Interrupt 128-138 Clear Enable (DIS4), offset 0x190
  const uint32_t DIS4;

  const uint32_t RESERVED3[27];

  // Interrupt 0-31 Set Pending (PEND0), offset 0x200
  const uint32_t PEND0;

  // Interrupt 32-63 Set Pending (PEND1), offset 0x204
  const uint32_t PEND1;

  // Interrupt 64-95 Set Pending (PEND2), offset 0x208
  const uint32_t PEND2;

  // Interrupt 96-127 Set Pending (PEND3), offset 0x20C
  const uint32_t PEND3;

  // Interrupt 128-138 Set Pending (PEND4), offset 0x210
  const uint32_t PEND4;

  const uint32_t RESERVED4[27];

  // Interrupt 0-31 Clear Pending (UNPEND0), offset 0x280
  const uint32_t UNPEND0;

  // Interrupt 32-63 Clear Pending (UNPEND1), offset 0x284
  const uint32_t UNPEND1;

  // Interrupt 64-95 Clear Pending (UNPEND2), offset 0x288
  const uint32_t UNPEND2;

  // Interrupt 96-127 Clear Pending (UNPEND3), offset 0x28C
  const uint32_t UNPEND3;

  // Interrupt 128-138 Clear Pending (UNPEND4), offset 0x290
  const uint32_t UNPEND4;

  const uint32_t RESERVED5[27];

  // Interrupt 0-31 Active Bit (ACTIVE0), offset 0x300
  const uint32_t ACTIVE0;

  // Interrupt 32-63 Active Bit (ACTIVE1), offset 0x304
  const uint32_t ACTIVE1;

  // Interrupt 64-95 Active Bit (ACTIVE2), offset 0x308
  const uint32_t ACTIVE2;

  // Interrupt 96-127 Active Bit (ACTIVE3), offset 0x30C
  const uint32_t ACTIVE3;

  // Interrupt 128-138 Active Bit (ACTIVE4), offset 0x310
  const uint32_t ACTIVE4;

  const uint32_t RESERVED6[59];

  // Interrupt 0-3 Priority (PRI0), offset 0x400
  volatile uint32_t PRI0;

  // Interrupt 4-7 Priority (PRI1), offset 0x404
  const uint32_t PRI1;

  // Interrupt 8-11 Priority (PRI2), offset 0x408
  const uint32_t PRI2;

  // Interrupt 12-15 Priority (PRI3), offset 0x40C
  const uint32_t PRI3;

  // Interrupt 16-19 Priority (PRI4), offset 0x410
  const uint32_t PRI4;

  // Interrupt 20-23 Priority (PRI5), offset 0x414
  const uint32_t PRI5;

  // Interrupt 24-27 Priority (PRI6), offset 0x418
  const uint32_t PRI6;

  // Interrupt 28-31 Priority (PRI7), offset 0x41C
  const uint32_t PRI7;

  // Interrupt 32-35 Priority (PRI8), offset 0x420
  const uint32_t PRI8;

  // Interrupt 36-39 Priority (PRI9), offset 0x424
  const uint32_t PRI9;

  // Interrupt 40-43 Priority (PRI10), offset 0x428
  const uint32_t PRI10;

  // Interrupt 44-47 Priority (PRI11), offset 0x42C
  const uint32_t PRI11;

  // Interrupt 48-51 Priority (PRI12), offset 0x430
  const uint32_t PRI12;

  // Interrupt 52-55 Priority (PRI13), offset 0x434
  const uint32_t PRI13;

  // Interrupt 56-59 Priority (PRI14), offset 0x438
  const uint32_t PRI14;

  // Interrupt 60-63 Priority (PRI15), offset 0x43C
  const uint32_t PRI15;

} NVICRegisters;

#define NVIC  ((NVICRegisters *) SCS_BASE)
