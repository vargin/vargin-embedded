#include <stdint.h>

#define SYSTEM_CTRL_RCGC1_R       (*((volatile uint32_t *) System_CTRL_RCGC1))
#define SYSTEM_CTRL_RCGC2_R       (*((volatile uint32_t *) System_CTRL_RCGC2))

#define UART2_UARTCTL_R           (*((volatile uint32_t *) UART2_UARTCTL))
#define UART2_UARTIBRD_R          (*((volatile uint32_t *) UART2_UARTIBRD))
#define UART2_UARTFBRD_R          (*((volatile uint32_t *) UART2_UARTFBRD))
#define UART2_UARTLCRH_R          (*((volatile uint32_t *) UART2_UARTLCRH))

extern void
UARTInitialize();
