#include "STAR_retarget.h"
#include "STAR_rcc.h"
#include "STAR_uart.h"
#include "STAR_gpio.h"
#include "STAR.h"
#include <stdio.h>

//struct __FILE { int handle; /* Add whatever you need here */ };
// Verification tests only retarget stdio functions.
#ifndef FPGA_IMAGE
    FILE __stdout;
    FILE __stdin;
#endif

int fputc(int ch, FILE *f) {
  return (UartPutc(ch));
}
int fgetc(FILE *f) {
  return (UartPutc(UartGetc()));
}

 unsigned char UartPutc(unsigned char my_ch)
{
	while ( (STAR_UART0->STATE & UART_STATE_TXBF_Msk));
	STAR_UART0->DATA = (my_ch & (uint8_t)0xff);
	return (my_ch);
}
// Get a character
unsigned char UartGetc(void)
{
	while((STAR_UART0->STATE & UART_STATE_RXBF_Msk) == 0);
	return (STAR_UART0->DATA & (uint8_t) 0xff);
	
}
