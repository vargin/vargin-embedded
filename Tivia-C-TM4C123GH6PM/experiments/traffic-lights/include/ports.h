#include <stdint.h>

#define PORTA_BASE          (0x40004000UL)
#define PORTB_BASE          (0x40005000UL)
#define PORTC_BASE          (0x40006000UL)
#define PORTD_BASE          (0x40007000UL)
#define PORTE_BASE          (0x40024000UL)
#define PORTF_BASE          (0x40025000UL)

#define PORT_GPIODATA_OFFSET    (0x000UL)
#define PORT_GPIODIR_OFFSET     (0x400UL)
#define PORT_GPIORIS_OFFSET     (0x414UL)
#define PORT_GPIOAFSEL_OFFSET   (0x420UL)
#define PORT_GPIODEN_OFFSET     (0x51CUL)
#define PORT_GPIOLOCK_OFFSET    (0x520UL)
#define PORT_GPIOCR_OFFSET      (0x524UL)
#define PORT_GPIOAMSEL_OFFSET   (0x528UL)
#define PORT_GPIOPCTL_OFFSET    (0x52CUL)

#define PORT_PIN_0              (0x01UL)
#define PORT_PIN_1              (0x02UL)
#define PORT_PIN_2              (0x04UL)
#define PORT_PIN_3              (0x08UL)
#define PORT_PIN_4              (0x10UL)
#define PORT_PIN_5              (0x20UL)
#define PORT_PIN_6              (0x40UL)
#define PORT_PIN_7              (0x80UL)

typedef struct
{
  volatile uint32_t* AMSEL;
  volatile uint32_t* AFSEL;
  volatile uint32_t* PCTL;
  volatile uint32_t* DIR;
  volatile uint32_t* DEN;
  volatile uint32_t* DATA;
  volatile uint32_t *PINS[8];
} GPIOPortAdresses;

typedef enum {PortA, PortB, PortC, PortD, PortE} PortTypes;

GPIOPortAdresses
GetPort(PortTypes portType);
