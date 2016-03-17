#ifndef INCLUDE_CORTEXM4_H
#define INCLUDE_CORTEXM4_H

/* Memory mapping of Cortex-M4 Hardware */

// System Control Register Base Address
#define System_CTRL_BASE          (0x400FE000UL)

// Run-Mode Clock Configuration (RCC), offset 0x060
#define System_CTRL_RCC           (System_CTRL_BASE + 0x060UL)

// Run-Mode Clock Configuration 2 (RCC2), offset 0x070
#define System_CTRL_RCC2           (System_CTRL_BASE + 0x070UL)


/** Run Mode Clock Gating Control Register 1 (RCGC1) **/

// Offset 0x104
#define System_CTRL_RCGC1                     (System_CTRL_BASE + 0x104UL)
// SSI0 Clock Gating Control
#define System_CTRL_RCGC1_SSI0_MASK           (0x10UL)
#define System_CTRL_RCGC1_SSI1_MASK           (0x20UL)

#define System_CTRL_RCGC1_R                   (*((volatile uint32_t *)System_CTRL_RCGC1))

/** ------------------------------------------------ **/

/** Run Mode Clock Gating Control Register 2 (RCGC2) **/

// Offset 0x108
#define System_CTRL_RCGC2                 (System_CTRL_BASE + 0x108UL)
#define System_CTRL_RCGC2_GPIOA_MASK      (0x1UL)
#define System_CTRL_RCGC2_GPIOB_MASK      (0x2UL)
#define System_CTRL_RCGC2_GPIOC_MASK      (0x4UL)
#define System_CTRL_RCGC2_GPIOD_MASK      (0x8UL)

#define System_CTRL_RCGC2_R                   (*((volatile uint32_t *)System_CTRL_RCGC2))

/** ------------------------------------------------ **/

/** Synchronous Serial Interface Run Mode Clock Gating Control (RCGCSSI) **/

#define System_CTRL_RCGCSSI                     (System_CTRL_BASE + 0x61CUL)
#define System_CTRL_RCGCSSI_SSI0_MASK           (0x1UL)
#define System_CTRL_RCGCSSI_SSI1_MASK           (0x2UL)
#define System_CTRL_RCGCSSI_SSI2_MASK           (0x4UL)
#define System_CTRL_RCGCSSI_SSI3_MASK           (0x8UL)

#define System_CTRL_RCGCSSI_R                   (*((volatile uint32_t *)System_CTRL_RCGCSSI))
/** ------------------------------------------------ **/

/** Inter-Integrated Circuit Run Mode Clock Gating Control (RCGCI2C) **/

#define System_CTRL_RCGCI2C                     (System_CTRL_BASE + 0x620UL)
#define System_CTRL_RCGCI2C_I2C0_MASK           (0x1UL)
#define System_CTRL_RCGCI2C_I2C1_MASK           (0x2UL)
#define System_CTRL_RCGCI2C_I2C2_MASK           (0x4UL)
#define System_CTRL_RCGCI2C_I2C3_MASK           (0x8UL)

#define System_CTRL_RCGCI2C_R                   (*((volatile uint32_t *)System_CTRL_RCGCI2C))
/** ------------------------------------------------ **/

/** General-Purpose Input/Output Run Mode Clock Gating Control (RCGCGPIO) **/

#define System_CTRL_RCGCGPIO                      (System_CTRL_BASE + 0x608UL)
#define System_CTRL_RCGCGPIO_GPIOA_MASK           (0x1UL)
#define System_CTRL_RCGCGPIO_GPIOB_MASK           (0x2UL)
#define System_CTRL_RCGCGPIO_GPIOC_MASK           (0x4UL)
#define System_CTRL_RCGCGPIO_GPIOD_MASK           (0x8UL)
#define System_CTRL_RCGCGPIO_GPIOE_MASK           (0x10UL)
#define System_CTRL_RCGCGPIO_GPIOF_MASK           (0x20UL)

#define System_CTRL_RCGCGPIO_R                    (*((volatile uint32_t *)System_CTRL_RCGCGPIO))
/** ------------------------------------------------ **/

/** Analog-to-Digital Converter Run Mode Clock Gating Control (RCGCADC) **/

#define System_CTRL_RCGCADC                     (System_CTRL_BASE + 0x638UL)
#define System_CTRL_RCGCADC_ADC0_MASK           (0x1UL)
#define System_CTRL_RCGCADC_ADC1_MASK           (0x2UL)

#define System_ADC0_BASE                        (0x40038000UL)
#define System_ADC1_BASE                        (0x40039000UL)

#define System_CTRL_RCGCADC_R                   (*((volatile uint32_t *)System_CTRL_RCGCADC))
/** ------------------------------------------------ **/

/** 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control (RCGCTIMER) **/

#define System_CTRL_RCGCTIMER                     (System_CTRL_BASE + 0x604UL)
#define System_CTRL_RCGCTIMER_TIMER0_MASK         (0x1UL)
#define System_CTRL_RCGCTIMER_TIMER1_MASK         (0x2UL)
#define System_CTRL_RCGCTIMER_TIMER2_MASK         (0x4UL)
#define System_CTRL_RCGCTIMER_TIMER3_MASK         (0x8UL)
#define System_CTRL_RCGCTIMER_TIMER4_MASK         (0x10UL)
#define System_CTRL_RCGCTIMER_TIMER5_MASK         (0x20UL)

#define System_TIMER0_BASE                        (0x40030000UL)
#define System_TIMER1_BASE                        (0x40031000UL)
#define System_TIMER2_BASE                        (0x40032000UL)
#define System_TIMER3_BASE                        (0x40033000UL)
#define System_TIMER4_BASE                        (0x40034000UL)
#define System_TIMER5_BASE                        (0x40035000UL)

#define System_CTRL_RCGCTIMER_R                   (*((volatile uint32_t *)System_CTRL_RCGCTIMER))
/** ------------------------------------------------ **/


#define SSI0_BASE (0x40008000UL)
#define SSI1_BASE (0x40009000UL)
#define SSI2_BASE (0x4000A000UL)
#define SSI3_BASE (0x4000B000UL)

/** SSI Control 1 (SSICR1) **/

// SSI Serial Clock Rate.
#define SSI_SSICR0_SCR_M          (0xFF00UL)
// SSI Serial Clock Phase.
#define SSI_SSICR0_SPH            (0x80UL)
// SSI Serial Clock Polarity.
#define SSI_SSICR0_SPO            (0x40UL)
// SSI Frame Format Select.
#define SSI_SSICR0_FRF_M          (0x30UL)
// Freescale SPI Frame Format.
#define SSI_SSICR0_FRF_MOTO       (0x00UL)
// SSI Data Size Select.
#define SSI_SSICR0_DSS_M          (0x0FUL)
// 8-bit data.
#define SSI_SSICR0_DSS_8          (0x07UL)

/** ------------------------------------------------ **/

/** SSI Control 1 (SSICR1) **/

#define SSI_SSICR1_SSE_MASK    (0x2UL)
#define SSI_SSICR1_MS_MASK     (0x4UL)

/** ------------------------------------------------ **/

/** SSI Status (SSISR), offset 0x00C **/

// SSI Transmit FIFO Not Full.
#define SSI_SSISR_TNF_MASK    (0x02UL)

// SSI Busy Bit.
#define SSI_SSISR_BSY_MASK    (0x10UL)

/** ------------------------------------------------ **/

/** SSI Clock Configuration (SSICC) **/

#define SSI_SSICC_CS_M          (0xFUL)
#define SSI_SSICC_CS_SYSCLK     (0x0UL)

/** ------------------------------------------------ **/

/** SSI Clock Prescale (SSICPSR) **/
#define SSI_SSICPSR_CPSDVSR_M          (0xFFUL)

/** ------------------------------------------------ **/

#define I2C0_BASE (0x40020000UL)
#define I2C1_BASE (0x40021000UL)
#define I2C2_BASE (0x40022000UL)
#define I2C3_BASE (0x40023000UL)

// XTAL configuration for 16MHz.
#define System_CTRL_RCC_XTAL_ALL_MASK     (0x7C0UL)

// XTAL configuration for 16MHz.
#define System_CTRL_RCC_XTAL_16_MASK     (0x540UL)

// XTAL configuration for 16MHz.
#define System_CTRL_RCC2_OSCSRC2_ALL_MASK     (0x70UL)

// SYSDIV2 MAX.
#define System_CTRL_RCC2_SYSDIV2_MAX_MASK     (0x1FC00000)

// Use RCC2
#define System_CTRL_RCC2_USERCC2_POS     31U
// Use RCC2 MASK
#define System_CTRL_RCC2_USERCC2_MASK     (1UL << System_CTRL_RCC2_USERCC2_POS)

// Use DIV400
#define System_CTRL_RCC2_DIV400_POS     30U
// Use DIV400 MASK
#define System_CTRL_RCC2_DIV400_MASK     (1UL << System_CTRL_RCC2_DIV400_POS)

// Use SYSDIV2LSB
#define System_CTRL_RCC2_SYSDIV2LSB_POS     22U
// Use SYSDIV2LSB MASK
#define System_CTRL_RCC2_SYSDIV2LSB_MASK    (1UL << System_CTRL_RCC2_SYSDIV2LSB_POS)

// Use BYPASS2
#define System_CTRL_RCC2_BYPASS2_POS     11U
// Use BYPASS2 MASK
#define System_CTRL_RCC2_BYPASS2_MASK     (1UL << System_CTRL_RCC2_BYPASS2_POS)

// Use PWRDN2
#define System_CTRL_RCC2_PWRDN2_POS     13U
// Use PWRDN2 MASK
#define System_CTRL_RCC2_PWRDN2_MASK     (1UL << System_CTRL_RCC2_PWRDN2_POS)

// Raw Interrupt Status (RIS), offset 0x050
#define System_CTRL_RIS           (System_CTRL_BASE + 0x050UL)


/*!< System Control Space Base Address */
#define SCS_BASE            (0xE000E000UL)

/*!< SysTick Base Address */
#define SysTick_BASE        (SCS_BASE + 0x0010UL)

/*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_POS     0U

/*!< SysTick CTRL: ENABLE Mask */
#define SysTick_CTRL_ENABLE_MASK     (1UL << SysTick_CTRL_ENABLE_POS)

/*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_POS          2U

/*!< SysTick CTRL: CLKSOURCE Mask */
#define SysTick_CTRL_CLKSOURCE_MASK         (1UL << SysTick_CTRL_CLKSOURCE_POS)

/*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_POS            1U

/*!< SysTick CTRL: TICKINT Mask */
#define SysTick_CTRL_TICKINT_MASK           (1UL << SysTick_CTRL_TICKINT_POS)

#define GPIOA_BASE          (0x40004000UL)
#define GPIOB_BASE          (0x40005000UL)
#define GPIOC_BASE          (0x40006000UL)
#define GPIOD_BASE          (0x40007000UL)
#define GPIOE_BASE          (0x40024000UL)
#define GPIOF_BASE          (0x40025000UL)

#define GPIO_PORT_PIN_0              (0x01UL)
#define GPIO_PORT_PIN_1              (0x02UL)
#define GPIO_PORT_PIN_2              (0x04UL)
#define GPIO_PORT_PIN_3              (0x08UL)
#define GPIO_PORT_PIN_4              (0x10UL)
#define GPIO_PORT_PIN_5              (0x20UL)
#define GPIO_PORT_PIN_6              (0x40UL)
#define GPIO_PORT_PIN_7              (0x80UL)

#define UART0_BASE (0x4000C000)
#define UART1_BASE (0x4000D000)
#define UART2_BASE (0x4000E000)
#define UART3_BASE (0x4000F000)
#define UART4_BASE (0x40010000)
#define UART5_BASE (0x40011000)
#define UART6_BASE (0x40012000)
#define UART7_BASE (0x40013000)

#define UART0_UARTFR (UART0_BASE + 0x018UL)
#define UART1_UARTFR (UART1_BASE + 0x018UL)
#define UART2_UARTFR (UART2_BASE + 0x018UL)
#define UART3_UARTFR (UART3_BASE + 0x018UL)
#define UART4_UARTFR (UART4_BASE + 0x018UL)
#define UART5_UARTFR (UART5_BASE + 0x018UL)
#define UART6_UARTFR (UART6_BASE + 0x018UL)
#define UART7_UARTFR (UART7_BASE + 0x018UL)

#define UART0_UARTIBRD (UART0_BASE + 0x024UL)
#define UART1_UARTIBRD (UART1_BASE + 0x024UL)
#define UART2_UARTIBRD (UART2_BASE + 0x024UL)
#define UART3_UARTIBRD (UART3_BASE + 0x024UL)
#define UART4_UARTIBRD (UART4_BASE + 0x024UL)
#define UART5_UARTIBRD (UART5_BASE + 0x024UL)
#define UART6_UARTIBRD (UART6_BASE + 0x024UL)
#define UART7_UARTIBRD (UART7_BASE + 0x024UL)

#define UART0_UARTFBRD (UART0_BASE + 0x028UL)
#define UART1_UARTFBRD (UART1_BASE + 0x028UL)
#define UART2_UARTFBRD (UART2_BASE + 0x028UL)
#define UART3_UARTFBRD (UART3_BASE + 0x028UL)
#define UART4_UARTFBRD (UART4_BASE + 0x028UL)
#define UART5_UARTFBRD (UART5_BASE + 0x028UL)
#define UART6_UARTFBRD (UART6_BASE + 0x028UL)
#define UART7_UARTFBRD (UART7_BASE + 0x028UL)

#define UART0_UARTLCRH (UART0_BASE + 0x02CUL)
#define UART1_UARTLCRH (UART1_BASE + 0x02CUL)
#define UART2_UARTLCRH (UART2_BASE + 0x02CUL)
#define UART3_UARTLCRH (UART3_BASE + 0x02CUL)
#define UART4_UARTLCRH (UART4_BASE + 0x02CUL)
#define UART5_UARTLCRH (UART5_BASE + 0x02CUL)
#define UART6_UARTLCRH (UART6_BASE + 0x02CUL)
#define UART7_UARTLCRH (UART7_BASE + 0x02CUL)

#define UART0_UARTCTL (UART0_BASE + 0x030UL)
#define UART1_UARTCTL (UART1_BASE + 0x030UL)
#define UART2_UARTCTL (UART2_BASE + 0x030UL)
#define UART3_UARTCTL (UART3_BASE + 0x030UL)
#define UART4_UARTCTL (UART4_BASE + 0x030UL)
#define UART5_UARTCTL (UART5_BASE + 0x030UL)
#define UART6_UARTCTL (UART6_BASE + 0x030UL)
#define UART7_UARTCTL (UART7_BASE + 0x030UL)

#define UART0_UARTRIS (UART0_BASE + 0x03CUL)
#define UART1_UARTRIS (UART1_BASE + 0x03CUL)
#define UART2_UARTRIS (UART2_BASE + 0x03CUL)
#define UART3_UARTRIS (UART3_BASE + 0x03CUL)
#define UART4_UARTRIS (UART4_BASE + 0x03CUL)
#define UART5_UARTRIS (UART5_BASE + 0x03CUL)
#define UART6_UARTRIS (UART6_BASE + 0x03CUL)
#define UART7_UARTRIS (UART7_BASE + 0x03CUL)

#define UART0_UARTCC (UART0_BASE + 0xFC8UL)
#define UART1_UARTCC (UART1_BASE + 0xFC8UL)
#define UART2_UARTCC (UART2_BASE + 0xFC8UL)
#define UART3_UARTCC (UART3_BASE + 0xFC8UL)
#define UART4_UARTCC (UART4_BASE + 0xFC8UL)
#define UART5_UARTCC (UART5_BASE + 0xFC8UL)
#define UART6_UARTCC (UART6_BASE + 0xFC8UL)
#define UART7_UARTCC (UART7_BASE + 0xFC8UL)

#define UART2_UARTFR_RXFE_MASK     (0x10UL)


// Default System Clock frequency for Tiva C
#define TivaSystemCoreClock               (16000000UL)

#endif //INCLUDE_CORTEXM4_H
