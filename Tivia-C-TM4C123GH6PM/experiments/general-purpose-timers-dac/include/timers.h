#include <stdint.h>
#include "cortexm4.h"

/**
 * Structure type to access ADC registers.
 */
typedef struct
{
  // GPTM Configuration (GPTMCFG), offset 0x000
  volatile uint32_t GPTMCFG;

  // GPTM Timer A Mode (GPTMTAMR), offset 0x004
  volatile uint32_t GPTMTAMR;

  // GPTM Timer B Mode (GPTMTBMR), offset 0x008
  volatile uint32_t GPTMTBMR;

  // GPTM Control (GPTMCTL), offset 0x00C
  volatile uint32_t GPTMCTL;

  // GPTM Synchronize (GPTMSYNC), offset 0x010
  volatile uint32_t GPTMSYNC;

  const uint32_t RESERVED0[1];

  // GPTM Interrupt Mask (GPTMIMR), offset 0x018
  volatile uint32_t GPTMIMR;

  // GPTM Raw Interrupt Status (GPTMRIS), offset 0x01C
  volatile uint32_t GPTMRIS;

  // GPTM Masked Interrupt Status (GPTMMIS), offset 0x020
  volatile uint32_t GPTMMIS;

  // GPTM Interrupt Clear (GPTMICR), offset 0x024
  volatile uint32_t GPTMICR;

  // GPTM Timer A Interval Load (GPTMTAILR), offset 0x028
  volatile uint32_t GPTMTAILR;

  // GPTM Timer B Interval Load (GPTMTBILR), offset 0x02C
  volatile uint32_t GPTMTBILR;

  // GPTM Timer A Match (GPTMTAMATCHR), offset 0x030
  volatile uint32_t GPTMTAMATCHR;

  // GPTM Timer B Match (GPTMTBMATCHR), offset 0x034
  volatile uint32_t GPTMTBMATCHR;

  // GPTM Timer A Prescale (GPTMTAPR), offset 0x038
  volatile uint32_t GPTMTAPR;
} GPTMRegisters;

#define Timer0  ((GPTMRegisters *) System_TIMER0_BASE)
#define Timer1  ((GPTMRegisters *) System_TIMER1_BASE)
#define Timer2  ((GPTMRegisters *) System_TIMER2_BASE)
