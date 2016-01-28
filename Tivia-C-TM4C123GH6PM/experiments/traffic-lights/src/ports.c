#include "../include/ports.h"

GPIOPortRegisters PORTS[6] = {
  {
    .AMSEL = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET),
    .PINS = {
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x04UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x08UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x10UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x20UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x40UL),
    }
  },
  {
    .AMSEL = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET),
    .PINS = {
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x04UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x08UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x10UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x20UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x40UL),
    }
  },
  {
    .AMSEL = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET),
    .PINS = {
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x04UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x08UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x10UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x20UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x40UL),
    }
  }
};

GPIOPortRegisters
GetPort(PortTypes portType)
{
  switch (portType) {
    case PortA:
      return PORTS[0];
    case PortB:
      return PORTS[1];
    case PortE:
      return PORTS[2];
    default:
      return PORTS[0];
  }
}
