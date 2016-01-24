#include <stdint.h>
#include "ports.h"

uint32_t PORT_BASE_ADDRESSES[6] = {
PORTA_BASE,
PORTB_BASE,
PORTC_BASE,
PORTD_BASE,
PORTE_BASE,
PORTF_BASE
};

GPIOPortAdresses PORTS[6] = {
    {
      .AMSEL = (volatile uint32_t *) (PORTE_BASE + PORT_GPIOAMSEL_OFFSET),
      .AFSEL = (volatile uint32_t *) (PORTE_BASE + PORT_GPIOAFSEL_OFFSET),
      .PCTL = (volatile uint32_t *) (PORTE_BASE + PORT_GPIOPCTL_OFFSET),
      .DIR = (volatile uint32_t *) (PORTE_BASE + PORT_GPIODIR_OFFSET),
      .DEN = (volatile uint32_t *) (PORTE_BASE + PORT_GPIODEN_OFFSET),
      .DATA = (volatile uint32_t *) (PORTE_BASE + PORT_GPIODATA_OFFSET),
      .PINS = {
        (volatile uint32_t *) (PORTE_BASE + PORT_GPIODATA_OFFSET + 0x04UL),
        (volatile uint32_t *) (PORTE_BASE + PORT_GPIODATA_OFFSET + 0x08UL),
        (volatile uint32_t *) (PORTE_BASE + PORT_GPIODATA_OFFSET + 0x10UL),
        (volatile uint32_t *) (PORTE_BASE + PORT_GPIODATA_OFFSET + 0x20UL),
        (volatile uint32_t *) (PORTE_BASE + PORT_GPIODATA_OFFSET + 0x40UL),
      }
    }
};

GPIOPortAdresses
GetPort(PortTypes portType)
{
  GPIOPortAdresses port;

  switch (portType) {
  case PortE:
    return port = PORTS[0];
  }

  return port;
}
