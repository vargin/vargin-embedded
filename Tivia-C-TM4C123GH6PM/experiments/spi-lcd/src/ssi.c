#include <stdint.h>
#include "../include/cortexm4.h"
#include "../include/ssi.h"
#include "../include/ports.h"

// PA2 - SSI0Clk, SCLK
// PA3 - SSIOFss, SCE
// PA5 - SSI0Tx, DN
// PA6 - Data/Command, D/C
// PA7 - Reset, RST

void
InitializeSSI(SSIModules module, uint8_t clockPrescaleDivisor) {
  if (module == SSI0) {
    uint32_t ssiPins = PORT_PIN_2 | PORT_PIN_3 | PORT_PIN_5;
    uint32_t gpioPins = PORT_PIN_6 | PORT_PIN_7;

    // Activate SSI0.
    System_CTRL_RCGCSSI_R |= System_CTRL_RCGCSSI_SSI0_MASK;
    // Activate GPIO port A.
    System_CTRL_RCGCGPIO_R |= System_CTRL_RCGCGPIO_GPIOA_MASK;

    GPIOPortRegisters port = GetPort(PortA);

    (*port.DIR) |= gpioPins;
    (*port.AFSEL) |= ssiPins;
    (*port.AFSEL) &= ~gpioPins;
    (*port.AMSEL) &= ~(ssiPins | gpioPins);

    (*port.DEN) |= ssiPins | gpioPins;

    // Configure SSI pins (PA2, PA3, PA5).
    (*port.PCTL) = ((*port.PCTL) & 0xFF0F00FF) + 0x00202200;

    // Configure GPIO pins (PA6, PA7).
    (*port.PCTL) = ((*port.PCTL) & 0x00FFFFFF);

    // Disable SSI and choose master mode.
    SSI0_SSICR1_R &= ~(SSI_SSICR1_SSE_MASK | SSI_SSICR1_MS_MASK);

    // Configure for system clock/PLL.
    SSI0_SSICC_R = (SSI0_SSICC_R & ~SSI_SSICC_CS_M) + SSI_SSICC_CS_SYSCLK;

    // Set clock prescale divisor.
    SSI0_SSICPSR_R = (SSI0_SSICPSR_R & ~SSI_SSICPSR_CPSDVSR_M) +
        clockPrescaleDivisor;

    SSI0_SSICR0_R &= ~(SSI_SSICR0_SCR_M | SSI_SSICR0_SPH | SSI_SSICR0_SPO);

    // Choose Freescale SPI Frame Format.
    SSI0_SSICR0_R = (SSI0_SSICR0_R & ~SSI_SSICR0_FRF_M) + SSI_SSICR0_FRF_MOTO;

    // DSS = 8-bit data.
    SSI0_SSICR0_R = (SSI0_SSICR0_R & ~SSI_SSICR0_DSS_M) + SSI_SSICR0_DSS_8;

    // Enable SSI.
    SSI0_SSICR1_R |= SSI_SSICR1_SSE_MASK ;
  }
}
