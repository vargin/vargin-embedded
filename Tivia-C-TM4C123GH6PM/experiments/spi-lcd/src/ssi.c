#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/ssi.h"
#include "../include/ports.h"

// PA2 - SSI0Clk, SCLK
// PA3 - SSIOFss, SCE
// PA5 - SSI0Tx, DN
// PA6 - Data/Command, D/C
// PA7 - Reset, RST

SSIRegisters *
InitializeSSI(SSIModules module, uint8_t clockPrescaleDivisor) {
  if (module == SSI0Module) {
    uint32_t ssiPins = GPIO_PORT_PIN_2 | GPIO_PORT_PIN_3 | GPIO_PORT_PIN_5;

    // Activate SSI0.
    System_CTRL_RCGCSSI_R |= System_CTRL_RCGCSSI_SSI0_MASK;
    // Activate GPIO port A.
    System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOA_MASK;

    GPIOA->AFSEL |= ssiPins;
    GPIOA->AMSEL &= ~ssiPins;
    GPIOA->DEN |= ssiPins;
    GPIOA->PCTL = (GPIOA->PCTL & 0xFF0F00FF) + 0x00202200;

    // Disable SSI and choose master mode.
    SSI0->SSICR1 &= ~(SSI_SSICR1_SSE_MASK | SSI_SSICR1_MS_MASK);

    // Configure for system clock/PLL.
    SSI0->SSICC = (SSI0->SSICC & ~SSI_SSICC_CS_M) + SSI_SSICC_CS_SYSCLK;

    // Set clock prescale divisor.
    SSI0->SSICPSR = (SSI0->SSICPSR & ~SSI_SSICPSR_CPSDVSR_M) +
        clockPrescaleDivisor;

    SSI0->SSICR0 &= ~(SSI_SSICR0_SCR_M | SSI_SSICR0_SPH | SSI_SSICR0_SPO);

    // Choose Freescale SPI Frame Format and 8-bit data format (DSS).
    SSI0->SSICR0 = (SSI0->SSICR0 & ~(SSI_SSICR0_FRF_M | SSI_SSICR0_DSS_M)) +
                   SSI_SSICR0_FRF_MOTO + SSI_SSICR0_DSS_8;

    // Enable SSI.
    SSI0->SSICR1 |= SSI_SSICR1_SSE_MASK;

    return SSI0;
  }
}
