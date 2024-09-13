#include "CM3_retarget.h"
#include "CM3DS_MPS2.h"
#include <stdio.h>

struct __FILE { int handle; /* Add whatever you need here */ };
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
  while ((CM3DS_MPS2_UART0->STATE & 1)); // Wait if Transmit Holding register is full
  CM3DS_MPS2_UART0->DATA = my_ch; // write to transmit holding register
  return (my_ch);
}
// Get a character
unsigned char UartGetc(void)
{
  while ((CM3DS_MPS2_UART0->STATE & 2)==0); // Wait if Receive Holding register is empty
  return (CM3DS_MPS2_UART0->DATA);
}
