#include "STAR_rcc.h"
#include "STAR.h"


extern uint32_t SystemCoreClock;

#define PCLK_DIV	0 //PCLK分频系数 该系数需与FPGA工程例化CM33时的PCLK_DIV参数一致

/**
  *
  * @brief: 复位指定的APB总线外设。
  *
  * @param: Periph,需要进行时钟复位的APB总线外设；
  * 			可设置的值包括：RCC_APB1Periph_TIM0; RCC_APB1Periph_TIM1;
  *				RCC_APB1Periph_DTIMER0; RCC_APB1Periph_UART0 - UART0; RCC_APB1Periph_UART1;
  *				RCC_APB1Periph_I2C; RCC_APB1Periph_ADC; RCC_APB1Periph_Wdog;
  *				RCC_APB1Periph_SPI0; RCC_APB1Periph_SPI1.
  *					
  * @param: NewState,是否进行复位操作；ENABLE - 复位；DISABLE - 释放复位。
  * 
  * @retVal: void
  */
void RCC_APBPeriphReset_Ctr(uint16_t Periph, FunctionalState NewState)
{
    assert_param(IS_RCC_APB_PERIPH(Periph) );
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
         APB_PERI_RSTCTL->RESETPERI &= ~Periph;
    }
    else
    {
         APB_PERI_RSTCTL->RESETPERI |= Periph;
    }
}

/**
  *
  * @brief: 获取系统时钟和APB、AHB总线时钟的频率。
  *
  * @param: freqType 需要获取的时钟频率类型；
  * 			可设置的值包括：SYS_FREQ - 系统时钟频率; 
  *								AHB_FREQ - AHB总线时钟频率;
  *								APB_FREQ - APB总线时钟频率;
  * 
  * @retVal: freq,获取到的时钟频率。
  */
uint32_t RCC_Get_ClockFreq(Clock_Freq_Type freqType)
{
	uint32_t freq=0;
	
	switch(freqType)
	{
		case SYS_FREQ:
			freq = SystemCoreClock;
			break;
		case AHB_FREQ:
			freq = SystemCoreClock;
			break;
		case APB_FREQ:
			freq= (SystemCoreClock / (PCLK_DIV+1));	
			break;
		default:
			break;
			
	}
	
	return freq;
}