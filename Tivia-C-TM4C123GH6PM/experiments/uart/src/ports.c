#include "../include/ports.h"

GPIOPortRegisters GPIO_PORTS[6] = {
  {
    .AMSEL = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x3FCUL),
    .PINS = {
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x004UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x008UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x010UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x020UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x040UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x080UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x100UL),
      (volatile uint32_t *) (PORT_A_BASE + PORT_GPIODATA_OFFSET + 0x200UL)
    }
  },
  {
    .AMSEL = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x3FCUL),
    .PINS = {
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x004UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x008UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x010UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x020UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x040UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x080UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x100UL),
      (volatile uint32_t *) (PORT_B_BASE + PORT_GPIODATA_OFFSET + 0x200UL)
    }
  },
  {
    .AMSEL = (volatile uint32_t *) (PORT_C_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_C_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_C_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x3FCUL),
    .PINS = {
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x004UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x008UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x010UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x020UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x040UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x080UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x100UL),
      (volatile uint32_t *) (PORT_C_BASE + PORT_GPIODATA_OFFSET + 0x200UL)
    }
  },
  {
    .AMSEL = (volatile uint32_t *) (PORT_D_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_D_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_D_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x3FCUL),
    .PINS = {
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x004UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x008UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x010UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x020UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x040UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x080UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x100UL),
      (volatile uint32_t *) (PORT_D_BASE + PORT_GPIODATA_OFFSET + 0x200UL)
    }
  },
  {
    .AMSEL = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIOAMSEL_OFFSET),
    .AFSEL = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIOAFSEL_OFFSET),
    .PCTL = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIOPCTL_OFFSET),
    .DIR = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODIR_OFFSET),
    .DEN = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODEN_OFFSET),
    .DATA = (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x3FCUL),
    .PINS = {
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x004UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x008UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x010UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x020UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x040UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x080UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x100UL),
      (volatile uint32_t *) (PORT_E_BASE + PORT_GPIODATA_OFFSET + 0x200UL)
    }
  }
};

GPIOPortRegisters
GetPort(PortTypes portType)
{
  switch (portType) {
    case PortA:
      return GPIO_PORTS[0];
    case PortB:
      return GPIO_PORTS[1];
    case PortC:
      return GPIO_PORTS[2];
    case PortD:
      return GPIO_PORTS[3];
    case PortE:
      return GPIO_PORTS[4];
    default:
      return GPIO_PORTS[0];
  }
}
