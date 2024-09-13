#include  "STAR_dualtimer.h"
#include  "STAR_rcc.h"

/**
  *
  * @brief: 将DualTimer配置初始化为默认配置。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * 
  * @retVal: void
  */
void DTIM_DeInit(DUALTIMER_TypeDef* DUALTIMERx)
{	
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	
	if (DUALTIMERx == STAR_DUALTIMER0)
	{
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_DTIMER0, ENABLE);
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_DTIMER0, DISABLE);
	}
	else 
	{
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_DTIMER1, ENABLE);
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_DTIMER1, DISABLE);
	}
}

/**
  *
  * @brief: DualTimer初始化设置。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * @param: DTIMtimerx_n,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  * @param: DTIM_InitStruct,双定时器设置参数结构体变量，用于对双定时器进行初始设置
  *
  * @retVal: void
  */
void DTIM_Init(DUALTIMER_TypeDef* DUALTIMERx, uint8_t DTIMtimerx_n, DTIM_InitTypeDef* DTIM_InitStruct)
{	
	uint32_t tmpval;
	
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx_n));
	assert_param(IS_DTIM_MODE(DTIM_InitStruct->DTIM_Mode));
	assert_param(IS_DTIM_INT_ENABLE(DTIM_InitStruct->DTIM_InterruptEnable));
	assert_param(IS_DTIM_CLK_DIV(DTIM_InitStruct->DTIM_ClkDiv));
	assert_param(IS_DTIM_CounterSize(DTIM_InitStruct->DTIM_CounterSize));
		
	if(DTIMtimerx_n == DTIM_TIMER1)
	{
		tmpval = DUALTIMERx->Timer1Control;
		tmpval &=DTIM_CTRREG_INIT_MASK;
		tmpval |= (DTIM_InitStruct->DTIM_Mode | DTIM_InitStruct->DTIM_InterruptEnable 	
							|DTIM_InitStruct->DTIM_ClkDiv |DTIM_InitStruct->DTIM_CounterSize);
		DUALTIMERx->Timer1Control = tmpval;
		
		DUALTIMERx->Timer1Load = DTIM_InitStruct->DTIM_LoadVal;
	}
	else 
	{
		tmpval = DUALTIMERx->Timer2Control;
		tmpval &=DTIM_CTRREG_INIT_MASK;
		tmpval |= (DTIM_InitStruct->DTIM_Mode | DTIM_InitStruct->DTIM_InterruptEnable 	
							|DTIM_InitStruct->DTIM_ClkDiv |DTIM_InitStruct->DTIM_CounterSize);
		DUALTIMERx->Timer2Control = tmpval;
		
		DUALTIMERx->Timer2Load = DTIM_InitStruct->DTIM_LoadVal;
	}
}


/**
  *
  * @brief: DualTimer使能设置。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * @param: DTIMtimerx_n,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  * @param: NewState,是否使能DualTimer;ENABLE：使能， DISABLE：不使能。
  *
  * @retVal: void
  */
void DTIM_Enable(DUALTIMER_TypeDef* DUALTIMERx, uint8_t DTIMtimerx_n, FunctionalState NewState)
{	
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx_n));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(DTIMtimerx_n ==DTIM_TIMER1)
	{
		if(NewState !=DISABLE)
		{
			DUALTIMERx->Timer1Control |= DTIM_Enable_SET;
		}
		else
		{
			DUALTIMERx->Timer1Control &= (~DTIM_Enable_SET);
		}
	}
	else
	{
		if(NewState !=DISABLE)
		{
			DUALTIMERx->Timer2Control |= DTIM_Enable_SET;
		}
		else
		{
			DUALTIMERx->Timer2Control &= (~DTIM_Enable_SET);
		}
	}
}

/**
  *
  * @brief: 设置DualTimer的重新加载值。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * @param: DTIMtimerx_n,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  * @param: BGLoadVal,重新加载值。
  *
  * @retVal: void
  */
void DTIM_SetBGLoad(DUALTIMER_TypeDef* DUALTIMERx, uint8_t DTIMtimerx_n, uint32_t BGLoadVal)
{
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx_n));
	
	if(DTIMtimerx_n ==DTIM_TIMER1)
	{
		DUALTIMERx->Timer1BGLoad  = BGLoadVal;
	}
	else
	{
		DUALTIMERx->Timer2BGLoad  = BGLoadVal;
	}
}


/**
  *
  * @brief: 清除DualTimer中断。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * @param: DTIMtimerx_n,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  *
  * @retVal: void
  */
void DTIM_InterruptFlag_Clear(DUALTIMER_TypeDef* DUALTIMERx, uint8_t DTIMtimerx_n)
{			
	
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx_n));	
	
	if(DTIMtimerx_n ==DTIM_TIMER1)
	{
		DUALTIMERx->Timer1IntClr  = DTIM_Interrupt_Clear;
	}
	else
	{
		DUALTIMERx->Timer2IntClr  = DTIM_Interrupt_Clear;
	}
}

/**
  *
  * @brief: 查看DualTimer计数器当前值。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * @param: DTIMtimerx_n,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  *
  * @retVal: value,获取到的计数器当前值。
  */
uint32_t DTIM_CounterCurrentValue_Get(DUALTIMER_TypeDef* DUALTIMERx, uint8_t DTIMtimerx_n)
{	
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx_n));
	
	if(DTIMtimerx_n ==DTIM_TIMER1)
	{
		return DUALTIMERx->Timer1Value;
	}
	else
	{
		return DUALTIMERx->Timer2Value;
	}
}

/**
  *
  * @brief: 获取DualTimer中断状态。
  *
  * @param: DUALTIMERx,设置为STAR_DUALTIMER0或STAR_DUALTIMER1。
  * @param: DTIMtimerx_n,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  *
  * @retVal:获取到的状态，SET - 发生了中断；RESET - 未发生中断。
  */
ITStatus DTIM_InterruptStatus_Get(DUALTIMER_TypeDef* DUALTIMERx, uint8_t DTIMtimerx_n)
{		
	ITStatus bitStatus = RESET;
	assert_param(IS_DUALTIMER_ALL_PERIPH(DUALTIMERx));
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx_n));
	
	if(DTIMtimerx_n ==DTIM_TIMER1)
	{
		if(DUALTIMERx->Timer1MIS)
		{
			bitStatus = SET;
		}
		else
		{
			bitStatus = RESET;
		}
	}
	else
	{
		if(DUALTIMERx->Timer2MIS)
		{
			bitStatus = SET;
		}
		else
		{
			bitStatus = RESET;
		}
	}
	
	return bitStatus;
}

