#include "CM3DS_adc.h"
#include "CM3DS_rcc.h"


/**
  *
  * @brief: 将ADC初始化为默认配置。
  *
  * 
  * @retVal: void
  */
void ADC_DeInit(void)
{
	RCC_APBPeriphReset_Ctr( RCC_APBPeriph_ADC, ENABLE );
	RCC_APBPeriphReset_Ctr( RCC_APBPeriph_ADC, DISABLE );
}


/**
  *
  * @brief: ADC初始化设置。
  *
  * @param: ADC_InitStruct,ADC设置参数结构体变量，该结构体变量包括时钟分频系数、转换模式（连续或单次）、
  *							数据缓冲使能、外部触发、触发类型、数据对齐方式、扫描模式。
  * 
  * @retVal: void
  */
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct)
{
	uint8_t u8tmpval;
	uint32_t u32tmpval;
	
	assert_param(IS_ADC_ClkPreDiv(ADC_InitStruct->ADC_ClkPreDiv));
	assert_param(IS_ADC_ConversionMode(ADC_InitStruct->ADC_ConversionMode));
	assert_param(IS_ADC_DataBufEnable_Enable(ADC_InitStruct->ADC_DataBufEnable));
	assert_param(IS_ADC_ExternalTrigConvEnable(ADC_InitStruct->ADC_ExternalTrigConvEnable)); 
	assert_param(IS_ADC_ExternalEventSel(ADC_InitStruct->ADC_ExternalEventSel)); 
	assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
	assert_param(IS_ADC_ScanModeEanbel(ADC_InitStruct->ADC_ScanModeEanbel));

	u8tmpval = CM3DS_MPS2_ADC->ADC_CR_1;
	
	u8tmpval &=ADC_CR1_INIT_MASK;
	
	u8tmpval |= (ADC_InitStruct->ADC_ClkPreDiv | ADC_InitStruct->ADC_ConversionMode |ADC_ENABLE);
	
	CM3DS_MPS2_ADC->ADC_CR_1 = u8tmpval;
	
	u32tmpval = CM3DS_MPS2_ADC->ADC_CR_2_3;
	
	u32tmpval &= ADC_CR2_INIT_MASK;
	
	u32tmpval |= (ADC_InitStruct->ADC_DataBufEnable | ADC_InitStruct->ADC_ExternalTrigConvEnable 
		|ADC_InitStruct->ADC_ExternalEventSel
					| ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ScanModeEanbel);
	
	CM3DS_MPS2_ADC->ADC_CR_2_3 = u32tmpval;
}

/**
  *
  * @brief: 设置ADC是否使能。
  *
  * @param: NewState,是否使能ADC，使能后开始进行AD转换；ENABLE - 使能； DISABLE - 不使能。
  * 
  * @retVal: void
  */
void ADC_Cmd(FunctionalState NewState)
{
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		CM3DS_MPS2_ADC->ADC_CR_1 |= ADC_ENABLE;	
	}
	else
	{
		CM3DS_MPS2_ADC->ADC_CR_1 &= (~ADC_ENABLE);
	}
}


/**
  *
  * @brief: ADC转换通道选择。
  *
  * @param: Channel,选择的转换通道；可设置的值ADC_Channel_0~ADC_Channel_7。
  * 
  * @retVal: void
  */
 void ADC_Channel_Select(uint8_t Channel)
{		
	uint8_t tmpval;
	assert_param(IS_ADC_CHANNEL(Channel));
		
	tmpval =CM3DS_MPS2_ADC->ADC_CSR_1;
	tmpval &= ADC_CSR1_INIT_MASK;
	tmpval |= Channel;
	
	CM3DS_MPS2_ADC->ADC_CSR_1 = tmpval;
}


/**
  *
  * @brief: ADC转换结束中断配置。
  *
  * @param: NewState,是否使能ADC转换结束中断，ENABLE - 使能中断；DISABLE - 不使能中断。
  * 
  * @retVal: void
  */
void ADC_EOCInterrupt_Config(FunctionalState NewState)
{
  	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{ 
		CM3DS_MPS2_ADC->ADC_CSR_0 |= ADC_EOC_IT_ENABLE;
	}
	else
	{ 	
		CM3DS_MPS2_ADC->ADC_CSR_0 &= (~ADC_EOC_IT_ENABLE);
	}
}


/**
  *
  * @brief: 清除ADC转换结束标志。
  *
  * 
  * @retVal: void
  */
void ADC_EOCFlag_Clear(void)
{
	CM3DS_MPS2_ADC->ADC_CSR_0 &= (~ADC_EOC_FLAG_MASK);
}


/**
  *
  * @brief: 获取ADC转换结束状态。
  *
  * @param: void
  * 
  * @retVal: 获取到的状态，SET - ADC转换结束 ；RESET - ADC转换未结束。
  */
FlagStatus ADC_EOCFlag_Get(void)
{
	if(CM3DS_MPS2_ADC->ADC_CSR_0 & ADC_EOC_FLAG_MASK)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
  *
  * @brief: 获取ADC转换数据缓存寄存器溢出状态(data buffer overrun)。
  *
  * 
  * @retVal: 获取到的状态，SET- ADC转换数据缓存寄存器溢出；RESET - ADC转换数据缓存寄存器未溢出。
  */
FlagStatus ADC_DataBufOVRFlag_Get(void)
{
	if(CM3DS_MPS2_ADC->ADC_CR_2_3 & ADC_DATA_BUF_OVR)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
  *
  * @brief: 清除ADC转换数据缓存寄存器溢出状态。
  *
  * 
  * @retVal: void
  */
void ADC_DataBufOVRFlag_Clear(void)
{
	CM3DS_MPS2_ADC->ADC_CR_2_3 &= (~ADC_DATA_BUF_OVR);
}


/**
  *
  * @brief: 获取ADC数据缓存使能状态。
  *
  * 
  * @retVal: 获取到的状态，SET- ADC数据缓存使能；RESET - ADC数据缓存未使能。
  */
FlagStatus ADC_DataBufEnable_Get(void)
{
	if(CM3DS_MPS2_ADC->ADC_CR_2_3 & ADC_DataBufEnable_Enable)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}


/**
  *
  * @brief: 读取ADC采样数据(单次采样或非缓冲连续模式时)。
  *
  * 
  * @retVal: 读取到的ADC采样数据。
  */
uint16_t ADC_GetValueFromDR(void)
{	
	uint16_t tmpval;
	uint16_t adcval;
	
	tmpval = (uint16_t)CM3DS_MPS2_ADC->ADC_DR;
	if(CM3DS_MPS2_ADC->ADC_CR_2_3&ADC_DataAlign_Left)
	{
		adcval = (tmpval>>4);
	}
	else
	{
		adcval = tmpval;
	}
	
	
	return adcval;
}

/**
  *
  * @brief: 读取ADC采样数据(数据缓冲模式或扫描模式时)。
  *
  * @param: ADC_buf,存储ADC采样数据的缓存，长度至少要4。
  * 
  * @retVal: void
  */
void ADC_GetValueFromDBR(uint32_t* ADC_buf)
{		
	
	if(CM3DS_MPS2_ADC->ADC_CR_2_3&ADC_DataAlign_Left)
	{
		ADC_buf[0] = (CM3DS_MPS2_ADC->ADC_DBR_1_0>>4);
		ADC_buf[1] = (CM3DS_MPS2_ADC->ADC_DBR_3_2>>4);
		ADC_buf[2] = (CM3DS_MPS2_ADC->ADC_DBR_5_4>>4);
		ADC_buf[3] = (CM3DS_MPS2_ADC->ADC_DBR_7_6>>4);
	}
	else
	{
		ADC_buf[0] = CM3DS_MPS2_ADC->ADC_DBR_1_0;
		ADC_buf[1] = CM3DS_MPS2_ADC->ADC_DBR_3_2;
		ADC_buf[2] = CM3DS_MPS2_ADC->ADC_DBR_5_4;
		ADC_buf[3] = CM3DS_MPS2_ADC->ADC_DBR_7_6;
	}

}

