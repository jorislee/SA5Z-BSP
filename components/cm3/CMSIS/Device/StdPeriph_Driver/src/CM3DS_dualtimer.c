#include  "CM3DS_dualtimer.h"
#include  "CM3DS_rcc.h"

/**
  *
  * @brief: 将DualTimer配置初始化为默认配置。
  *
  * 
  * @retVal: void
  */
void DTIM_DeInit(void)
{	
	RCC_APBPeriphReset_Ctr(RCC_APBPeriph_DTIMER0, ENABLE);
	RCC_APBPeriphReset_Ctr(RCC_APBPeriph_DTIMER0, DISABLE);
}

/**
  *
  * @brief: DualTimer初始化设置。
  *
  * @param: DTIMtimerx,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  * @param: DTIM_InitStruct,双定时器设置参数结构体变量，用于对双定时器进行初始设置。
  *
  * @retVal: void
  */
void DTIM_Init(uint8_t DTIMtimerx, DTIM_InitTypeDef* DTIM_InitStruct)
{
	uint32_t tmpval;
	
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx));
	assert_param(IS_DTIM_MODE(DTIM_InitStruct->DTIM_Mode));
	assert_param(IS_DTIM_INT_ENABLE(DTIM_InitStruct->DTIM_InterruptEnable));
	assert_param(IS_DTIM_CLK_DIV(DTIM_InitStruct->DTIM_ClkDiv));
	assert_param(IS_DTIM_CounterSize(DTIM_InitStruct->DTIM_CounterSize));
	
	if(DTIMtimerx ==DTIM_TIMER1)
	{
		tmpval = CM3DS_MPS2_DUALTIMER0->Timer1Control;
		tmpval &=DTIM_CTRREG_INIT_MASK;
		tmpval |= (DTIM_InitStruct->DTIM_Mode | DTIM_InitStruct->DTIM_InterruptEnable 	
							|DTIM_InitStruct->DTIM_ClkDiv |DTIM_InitStruct->DTIM_CounterSize);
		CM3DS_MPS2_DUALTIMER0->Timer1Control = tmpval;
		
		CM3DS_MPS2_DUALTIMER0->Timer1Load = DTIM_InitStruct->DTIM_LoadVal;
	}
	else
	{
		tmpval = CM3DS_MPS2_DUALTIMER0->Timer2Control;
		tmpval &=DTIM_CTRREG_INIT_MASK;
		tmpval |= (DTIM_InitStruct->DTIM_Mode | DTIM_InitStruct->DTIM_InterruptEnable 	
							|DTIM_InitStruct->DTIM_ClkDiv |DTIM_InitStruct->DTIM_CounterSize);
		CM3DS_MPS2_DUALTIMER0->Timer2Control = tmpval;
		
		CM3DS_MPS2_DUALTIMER0->Timer2Load = DTIM_InitStruct->DTIM_LoadVal;
	}
}

/**
  *
  * @brief: DualTimer使能设置。
  *
  * @param: TIMtimerx,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  * @param: NewState,是否使能DualTimer;ENABLE：使能， DISABLE：不使能。
  *
  * @retVal: void
  */
void DTIM_Enable(uint8_t DTIMtimerx, FunctionalState NewState)
{
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx));
	
	if(DTIMtimerx ==DTIM_TIMER1)
	{
		if(NewState !=DISABLE)
		{
			CM3DS_MPS2_DUALTIMER0->Timer1Control |= DTIM_Enable_SET;
		}
		else
		{
			CM3DS_MPS2_DUALTIMER0->Timer1Control &= (~DTIM_Enable_SET);
		}
	}
	else
	{
		if(NewState !=DISABLE)
		{
			CM3DS_MPS2_DUALTIMER0->Timer2Control |= DTIM_Enable_SET;
		}
		else
		{
			CM3DS_MPS2_DUALTIMER0->Timer2Control &= (~DTIM_Enable_SET);
		}
	}
}


/**
  *
  * @brief: 设置DualTimer的重新加载值。
  *
  * @param: DTIMtimerx,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  * @param: BGLoadVal,重新加载值。
  *
  * @retVal: void
  */
void DTIM_SetBGLoad(uint8_t DTIMtimerx,uint32_t BGLoadVal)
{
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx));
	
	if(DTIMtimerx ==DTIM_TIMER1)
	{
		CM3DS_MPS2_DUALTIMER0->Timer1BGLoad  = BGLoadVal;
	}
	else
	{
		CM3DS_MPS2_DUALTIMER0->Timer2BGLoad  = BGLoadVal;
	}
}

/**
  *
  * @brief: 清除DualTimer中断标志。
  *
  * @param: DTIMtimerx,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  *
  * @retVal: void
  */
void DTIM_InterruptFlag_Clear(uint8_t DTIMtimerx)
{			
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx));
	
	if(DTIMtimerx ==DTIM_TIMER1)
	{
		CM3DS_MPS2_DUALTIMER0->Timer1IntClr  = DTIM_Interrupt_Clear;
	}
	else
	{
		CM3DS_MPS2_DUALTIMER0->Timer2IntClr  = DTIM_Interrupt_Clear;
	}
}

/**
  *
  * @brief: 获取DualTimer计数器当前值。
  *
  * @param: DTIMtimerx,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  *
  * @retVal: 获取到的计数器当前值。
  */
uint32_t DTIM_CounterCurrentValue_Get(uint8_t DTIMtimerx)
{	
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx));
	
	if(DTIMtimerx ==DTIM_TIMER1)
	{
		return CM3DS_MPS2_DUALTIMER0->Timer1Value;
	}
	else
	{
		return CM3DS_MPS2_DUALTIMER0->Timer2Value;
	}
	
}


/**
  *
  * @brief: 获取DualTimer中断状态。
  *
  * @param: DTIMtimerx,双定时器下的哪个定时器,DTIM_TIMER1或DTIM_TIMER2。
  *
  * @retVal: 获取到的状态，SET - 发生了中断；RESET - 未发生中断。
  */
ITStatus DTIM_InterruptStatus_Get(uint8_t DTIMtimerx)
{	
	ITStatus bitStatus = RESET;
	
	assert_param(IS_DTIM_TIMER_TYPE(DTIMtimerx));
	
	if(DTIMtimerx ==DTIM_TIMER1)
	{
		if(CM3DS_MPS2_DUALTIMER0->Timer1MIS)
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
		if(CM3DS_MPS2_DUALTIMER0->Timer2MIS)
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
