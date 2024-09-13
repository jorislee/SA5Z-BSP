#include "STAR_timer.h"
#include "STAR_rcc.h"

/**
  *
  * @brief: 将定时器配置初始化为默认配置。
  *
  * @param: TIMERx,使用哪个定时器，STAR_TIMER0或STAR_TIMER1。
  * 
  * @retVal: void
  */
void TIM_DeInit(TIMER_TypeDef* TIMERx)
{
    assert_param(IS_TIM_ALL_PERIPH(TIMERx));

    if (TIMERx == STAR_TIMER0)
    {
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_TIM0, ENABLE);
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_TIM0, DISABLE);    
    } 
	else if (TIMERx == STAR_TIMER1) 
	{
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_TIM1, ENABLE);
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_TIM1, DISABLE);
    }
}

/**
  *
  * @brief: 定时器初始化设置。
  *
  * @param: TIMERx,使用哪个定时器，STAR_TIMER0或STAR_TIMER1。
  * @param: TIM_InitStruct,定时器设置参数结构体。
  * @retVal: void
  */
void TIM_Init(TIMER_TypeDef* TIMERx, TIM_InitTypeDef* TIM_InitStruct)
{
	uint8_t tmpval;
    assert_param(IS_TIM_ALL_PERIPH(TIMERx));
	assert_param(IS_TIM_INT_ENABLE(TIM_InitStruct->TIM_InterruptEnable));
	assert_param(IS_TIM_SEL_EXTINPUT_AS_CLK(TIM_InitStruct->TIM_SelExtInputAsClk));
	assert_param(IS_TIM_SEL_EXTINPUT_AS_En(TIM_InitStruct->TIM_SelExtInputAsEn));

	tmpval = TIMERx->CTRL;
	tmpval &= TIM_CTR_INIT_MASK;
	tmpval |= (TIM_InitStruct->TIM_InterruptEnable | TIM_InitStruct->TIM_SelExtInputAsClk  
													| TIM_InitStruct->TIM_SelExtInputAsEn);
	TIMERx->CTRL = tmpval;
	
	TIMERx->VALUE  = TIM_InitStruct->TIM_Value;
	TIMERx->RELOAD = TIM_InitStruct->TIM_Reload;
}

/**
  *
  * @brief: 定时器控制寄存器设置。
  *
  * @param: TIMERx,使用哪个定时器，STAR_TIMER0或STAR_TIMER1。
  * @param: NewState,是否使能定时器；ENABLE - 使能；DISABLE - 不使能。
  * @retVal: void
  */
void TIM_Enable(TIMER_TypeDef* TIMERx, FunctionalState NewState) 
{
    assert_param(IS_TIM_ALL_PERIPH(TIMERx));
	
    if (NewState != DISABLE)
    {
       TIMERx->CTRL |= TIM_ENABLE_SET;
    }
    else
    {
	   TIMERx->CTRL &= (~TIM_ENABLE_SET);
    }
}

/**
  *
  * @brief: 获取定时器中断状态。
  *
  * @param: TIMERx,使用哪个定时器，STAR_TIMER0或STAR_TIMER1。
  * 
  * @retVal: bitstatus,定时器中断状态，SET-定时器产生了中断；RESET-定时器未产生中断。
  */
ITStatus TIM_InterruptStatus_Get(TIMER_TypeDef* TIMERx)
{
    ITStatus bitstatus = RESET;
	
    assert_param(IS_TIM_ALL_PERIPH(TIMERx));
	
    if (TIMERx->INTSTATUS)
    { 
		bitstatus = SET; 
	}
    else
    { 
		bitstatus = RESET;
	}
    return bitstatus;
}

/**
  *
  * @brief: 清除定时器中断。
  *
  * @param: TIMERx,使用哪个定时器，STAR_TIMER0或STAR_TIMER1。
  * 
  * @retVal: void
  */
void TIM_InterruptFlag_Clear(TIMER_TypeDef* TIMERx)
{
    assert_param(IS_TIM_ALL_PERIPH(TIMERx));

    TIMERx->INTCLEAR |= TIM_ENABLE_SET;
}

