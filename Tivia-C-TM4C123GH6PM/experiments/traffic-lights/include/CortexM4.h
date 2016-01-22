/* Memory mapping of Cortex-M4 Hardware */

// System Control Register Base Address
#define System_CTRL_BASE          (0x400FE000UL)

// Run-Mode Clock Configuration (RCC), offset 0x060
#define System_CTRL_RCC           (System_CTRL_BASE + 0x060UL)

// XTAL configuration for 16MHz.
#define System_CTRL_RCC_XTAL_ALL_MASK     (0x7C0UL)

// Run-Mode Clock Configuration 2 (RCC2), offset 0x070
#define System_CTRL_RCC2           (System_CTRL_BASE + 0x070UL)

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



// Default System Clock frequency for Tiva C
#define TivaSystemCoreClock               (16000000UL)
