/* Memory mapping of Cortex-M4 Hardware */

// System Control Register Base Address
#define System_CTRL_BASE          (0x400FE000UL)

// Run-Mode Clock Configuration (RCC), offset 0x060
#define System_CTRL_RCC           (System_CTRL_BASE + 0x060UL)

// Run-Mode Clock Configuration 2 (RCC2), offset 0x070
#define System_CTRL_RCC2           (System_CTRL_BASE + 0x070UL)

// Run Mode Clock Gating Control Register 1 (RCGC1), offset 0x104
#define System_CTRL_RCGC1           (System_CTRL_BASE + 0x104UL)

// Run Mode Clock Gating Control Register 2 (RCGC2), offset 0x108
#define System_CTRL_RCGC2           (System_CTRL_BASE + 0x108UL)

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

#define UART2_UARTFR_RXFE_MASK     (0x10UL)

#define UART0_UARTCTL (UART0_BASE + 0x030UL)
#define UART1_UARTCTL (UART1_BASE + 0x030UL)
#define UART2_UARTCTL (UART2_BASE + 0x030UL)
#define UART3_UARTCTL (UART3_BASE + 0x030UL)
#define UART4_UARTCTL (UART4_BASE + 0x030UL)
#define UART5_UARTCTL (UART5_BASE + 0x030UL)
#define UART6_UARTCTL (UART6_BASE + 0x030UL)
#define UART7_UARTCTL (UART7_BASE + 0x030UL)

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

#define UART0_UARTLCCH (UART0_BASE + 0x02CUL)
#define UART1_UARTLCRH (UART1_BASE + 0x02CUL)
#define UART2_UARTLCRH (UART2_BASE + 0x02CUL)
#define UART3_UARTLCRH (UART3_BASE + 0x02CUL)
#define UART4_UARTLCRH (UART4_BASE + 0x02CUL)
#define UART5_UARTLCRH (UART5_BASE + 0x02CUL)
#define UART6_UARTLCRH (UART6_BASE + 0x02CUL)
#define UART7_UARTLCRH (UART7_BASE + 0x02CUL)


// Default System Clock frequency for Tiva C
#define TivaSystemCoreClock               (16000000UL)
