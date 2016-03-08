//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu
//

// ----------------------------------------------------------------------------

#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
// TODO: Rename this and add the actual routines here.

void __attribute__ ((weak, alias ("Default_Handler")))
    GPIOPortA_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    GPIOPortB_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    GPIOPortC_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    GPIOPortD_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    GPIOPortE_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    Timer0A_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    Timer0B_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    Timer1A_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    Timer1B_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    Timer2A_Handler(void);

void __attribute__ ((weak, alias ("Default_Handler")))
    Timer2B_Handler(void);

// ----------------------------------------------------------------------------

extern unsigned int _estack;

typedef void
(* const pHandler)(void);

// ----------------------------------------------------------------------------

// The vector table.
// This relies on the linker script to place at correct location in memory.

__attribute__ ((section(".isr_vector"),used))
pHandler __isr_vectors[] =
  { //
    (pHandler) &_estack,                          // The initial stack pointer
        Reset_Handler,                            // The reset handler

        NMI_Handler,                              // The NMI handler
        HardFault_Handler,                        // The hard fault handler

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
        MemManage_Handler,                        // The MPU fault handler
        BusFault_Handler,// The bus fault handler
        UsageFault_Handler,// The usage fault handler
#else
        0, 0, 0,				  // Reserved
#endif
        0,                                        // Reserved
        0,                                        // Reserved
        0,                                        // Reserved
        0,                                        // Reserved
        SVC_Handler,                              // SVCall handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
        DebugMon_Handler,                         // Debug monitor handler
#else
        0,					  // Reserved
#endif
        0,                                        // Reserved
        PendSV_Handler,                           // The PendSV handler
        SysTick_Handler,                          // The SysTick handler
        // ----------------------------------------------------------------------
        // DEVICE vectors
        GPIOPortA_Handler,
        GPIOPortB_Handler,
        GPIOPortC_Handler,
        GPIOPortD_Handler,
        GPIOPortE_Handler,
        // 21 UART0
        0,
        // 22 UART1,
        0,
        // 23 SSI0,
        0,
        // 24 I2C0,
        0,
        // 25 PWM0 Fault,
        0,
        // 26 PWM0 Generator 0,
        0,
        // 27 PWM0 Generator 1,
        0,
        // 28 PWM0 Generator 2,
        0,
        // 29 QEI0,
        0,
        // 30 ADC0 Sequence 0
        0,
        // 31 ADC0 Sequence 1
        0,
        // 32 ADC0 Sequence 2
        0,
        // 33 ADC0 Sequence 3
        0,
        // 34 Watchdog Timers 0 and 1
        0,
        // 35 16/32-Bit Timer 0A,
        Timer0A_Handler,
        // 36 16/32-Bit Timer 0B,
        Timer0B_Handler,
        // 37 16/32-Bit Timer 1A
        Timer1A_Handler,
        // 38 16/32-Bit Timer 1B
        Timer1B_Handler,
        // 39 16/32-Bit Timer 2A
        Timer2A_Handler,
        // 40 16/32-Bit Timer 2B,
        Timer2B_Handler
    };

// ----------------------------------------------------------------------------

// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
  while (1)
    {
    }
}

// ----------------------------------------------------------------------------
