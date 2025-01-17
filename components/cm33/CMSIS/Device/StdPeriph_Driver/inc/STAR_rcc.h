#ifndef __STAR_RCC_H
#define __STAR_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/*---------Include---------*/
#include "STAR.h"

/** @defgroup APB_peripheral 
  * @{
  */
#define RCC_APBPeriph_TIM0     ((uint16_t)0x0001)
#define RCC_APBPeriph_TIM1     ((uint16_t)0x0002)
#define RCC_APBPeriph_DTIMER0  ((uint16_t)0x0004)
#define RCC_APBPeriph_UART0    ((uint16_t)0x0008)
#define RCC_APBPeriph_UART1    ((uint16_t)0x0010)
#define RCC_APBPeriph_I2C      ((uint16_t)0x0020)
#define RCC_APBPeriph_ADC0      ((uint16_t)0x0040)
#define RCC_APBPeriph_Wdog     ((uint16_t)0x0080)
#define RCC_APBPeriph_SPI0     ((uint16_t)0x0100)
#define RCC_APBPeriph_SPI1     ((uint16_t)0x0200)
#define RCC_APBPeriph_DTIMER1  ((uint16_t)0x0400)
#define RCC_APBPeriph_UART2    ((uint16_t)0x0800)
#define RCC_APBPeriph_ADC1     ((uint16_t)0x1000)
 
#define IS_RCC_APB_PERIPH(PERIPH) ((((PERIPH) & 0xE000) == 0x00) && ((PERIPH) != 0x00)) 

/**
  * @}
  */
  
/** @defgroup Clock_Freq_Type_Def 
  * @{
  */
typedef enum
{
	SYS_FREQ =0x0,
	AHB_FREQ,
	APB_FREQ,
}Clock_Freq_Type;

/**
  * @}
  */
 

/** @defgroup RCC_Exported_Functions
  * @{
  */

void RCC_APBPeriphReset_Ctr(uint16_t APBPeriph, FunctionalState NewState);
uint32_t RCC_Get_ClockFreq(Clock_Freq_Type freqType);
/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __STAR_RCC_H */
