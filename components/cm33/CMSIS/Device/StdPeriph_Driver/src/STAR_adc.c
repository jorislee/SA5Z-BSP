#include "STAR_adc.h"
#include "STAR_rcc.h"



/**
  *
  * @brief: 将ADC寄存器初始化为默认配置。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * 
  * @retVal: void
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
	if (ADCx == STAR_ADC0)
	{
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_ADC0, ENABLE );
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_ADC0, DISABLE );
	} 
	else if (ADCx == STAR_ADC1)
	{
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_ADC1, ENABLE );
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_ADC1, DISABLE );
	} 
}


/**
  *
  * @brief: ADC初始化设置。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * @param: ADC_InitStruct,ADC设置参数结构体变量，该结构体变量包括时钟分频系数、转换模式（连续或单次）、
  *							上电、数据缓冲、溢出标志、外部触发、触发类型、数据对齐方式、扫描模式。
  * 
  * @retVal: void
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
	uint8_t u8tmpval;
	uint32_t u32tmpval;
	
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_REF_VOL_SEL(ADC_InitStruct->ADC_RefVol_Sel));
	assert_param(IS_ADC_ACTIVE_STATE(ADC_InitStruct->ADC_PDn));
	assert_param(IS_ADC_ClkPreDiv(ADC_InitStruct->ADC_ClkPreDiv));
	assert_param(IS_ADC_ConversionMode(ADC_InitStruct->ADC_ConversionMode));
	assert_param(IS_ADC_DataBufEnable_Enable(ADC_InitStruct->ADC_DataBufEnable));
	assert_param(IS_ADC_ExternalTrigConvEnable(ADC_InitStruct->ADC_ExternalTrigConvEnable)); 
	assert_param(IS_ADC_ExternalEventSel(ADC_InitStruct->ADC_ExternalEventSel)); 
	assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
	assert_param(IS_ADC_ScanModeEanbel(ADC_InitStruct->ADC_ScanModeEanbel));
	
	u8tmpval = ADCx->ADC_CSR_1;
	u8tmpval &=ADC_CSR1_INIT_MASK;
	u8tmpval |= (ADC_InitStruct->ADC_RefVol_Sel | ADC_InitStruct->ADC_PDn);
	ADCx->ADC_CSR_1= u8tmpval;
	 
	u8tmpval = ADCx->ADC_CR_1;
	
	u8tmpval &=ADC_CR1_INIT_MASK;
	
	u8tmpval |= (ADC_InitStruct->ADC_ClkPreDiv | ADC_InitStruct->ADC_ConversionMode |ADC_ENABLE);
	
	ADCx->ADC_CR_1 = u8tmpval;
	
	u32tmpval = ADCx->ADC_CR_2;
	
	u32tmpval &= ADC_CR2_INIT_MASK;
	
	u32tmpval |= (ADC_InitStruct->ADC_DataBufEnable | ADC_InitStruct->ADC_ExternalTrigConvEnable 
		|ADC_InitStruct->ADC_ExternalEventSel
					| ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ScanModeEanbel);
	
	ADCx->ADC_CR_2 = u32tmpval;
}


/**
  *
  * @brief: 设置ADC使能。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * @param: NewState,是否使能ADC，使能后开始进行AD转换；ENABLE - 使能； DISABLE - 不使能。
  * 
  * @retVal: void
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState) 
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	if (NewState != DISABLE)
	{
		ADCx->ADC_CR_1 |= ADC_ENABLE;	
	}
	else
	{
		ADCx->ADC_CR_1 &= (~ADC_ENABLE);
	}
}

/**
  *
  * @brief: ADC转换通道选择。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * @param: Channel,选择的转换通道；可设置的值ADC_Channel_0~ADC_Channel_7。
  * 
  * @retVal: void
  */
 void ADC_Channel_Select(ADC_TypeDef* ADCx, uint8_t Channel)
{		
	uint8_t tmpval;
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_CHANNEL(Channel));
		
	tmpval =ADCx->ADC_CSR_1;
	tmpval &= ADC_CSR1_CH_MASK;
	tmpval |= Channel;
	
	ADCx->ADC_CSR_1 = tmpval;
}


/**
  *
  * @brief: ADC转换结束中断配置。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * @param: NewState,是否使能中断，ENABLE - 使能中断；DISABLE - 不使能中断。
  * 
  * @retVal: void
  */
void ADC_EOCInterrupt_Config(ADC_TypeDef* ADCx,FunctionalState NewState)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
  	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{ 
		ADCx->ADC_CSR_0 |= ADC_EOC_IT_ENABLE;
	}
	else
	{ 	
		ADCx->ADC_CSR_0 &= ~(~ADC_EOC_IT_ENABLE);
	}
}

/**
  *
  * @brief: 清除ADC转换结束中断标志。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * 
  * @retVal: void
  */
void ADC_EOCFlag_Clear(ADC_TypeDef* ADCx)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
	ADCx->ADC_CSR_0 &= (~ADC_EOC_FLAG_MASK);
}


/**
  *
  * @brief: 获取ADC转换结束状态。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * 
  * @retVal: 获取到的状态，SET - ADC转换结束 ；RESET - ADC转换未结束。
  */
FlagStatus ADC_EOCFlag_Get(ADC_TypeDef* ADCx)
{
	if(ADCx->ADC_CSR_0 & ADC_EOC_FLAG_MASK)
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
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  *
  * @retVal: 获取到的状态，SET- ADC转换数据缓存寄存器溢出；RESET - ADC转换数据缓存寄存器未溢出。
  */
FlagStatus ADC_DataBufOVRFlag_Get(ADC_TypeDef* ADCx)
{
	if(ADCx->ADC_CR_2 & ADC_DATA_BUF_OVR)
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
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  *
  * @retVal: void
  */
void ADC_DataBufOVRFlag_Clear(ADC_TypeDef* ADCx)
{
	ADCx->ADC_CR_2 &= (~ADC_DATA_BUF_OVR);
}

/**
  *
  * @brief: 获取ADC数据缓存使能状态
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * 
  * @retVal: 获取到的状态，SET- ADC数据缓存使能；RESET - ADC数据缓存未使能。
  */
FlagStatus ADC_DataBufEnable_Get(ADC_TypeDef* ADCx)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
	if(STAR_ADC0->ADC_CR_2 & ADC_DataBufEnable_Enable)
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
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * 
  * @retVal: 读取到的ADC采样数据。
  */
uint16_t ADC_GetValueFromDR(ADC_TypeDef* ADCx)
{	
	uint16_t tmpval;
	uint16_t adcval;
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
	tmpval = (uint16_t)ADCx->ADC_DR;
	if(ADCx->ADC_CR_2 & ADC_DataAlign_Left)
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
  * @brief:读取ADC采样数据(数据缓冲模式或扫描模式时)。
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * @param: ADC_buf,存储ADC采样数据的缓存，长度至少要8。
  * 
  * @retVal: void
  */
void ADC_GetValueFromDBR(ADC_TypeDef* ADCx, uint32_t* ADC_buf)
{	
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
	
	if(ADC_buf ==NULL)
	{
		return;
	}
	if(ADCx->ADC_CR_2 & ADC_DataAlign_Left)
	{
		ADC_buf[0] = (ADCx->ADC_DBR_1_0>>4);	//ADC_DBR0:bit0~bit15;	ADC_DBR1:bit16~bit31
		ADC_buf[1] = (ADCx->ADC_DBR_3_2>>4);	//ADC_DBR2:bit0~bit15;	ADC_DBR3:bit16~bit31 
		ADC_buf[2] = (ADCx->ADC_DBR_5_4>>4);	//ADC_DBR4:bit0~bit15;	ADC_DBR5:bit16~bit31
		ADC_buf[3] = (ADCx->ADC_DBR_7_6>>4);	//ADC_DBR6:bit0~bit15;	ADC_DBR7:bit16~bit31
		ADC_buf[4] = (ADCx->ADC_DBR_9_8>>4);	//ADC_DBR8:bit0~bit15;	ADC_DBR9:bit16~bit31
		ADC_buf[5] = (ADCx->ADC_DBR_11_10>>4);	//ADC_DBR10:bit0~bit15;	ADC_DBR11:bit16~bit31 
		ADC_buf[6] = (ADCx->ADC_DBR_13_12>>4);	//ADC_DBR12:bit0~bit15;	ADC_DBR13:bit16~bit31
		ADC_buf[7] = (ADCx->ADC_DBR_15_14>>4);	//ADC_DBR14:bit0~bit15;	ADC_DBR15:bit16~bit31
	}
	else
	{
		ADC_buf[0] = ADCx->ADC_DBR_1_0;		//ADC_DBR0:bit0~bit15;	ADC_DBR1:bit16~bit31
		ADC_buf[1] = ADCx->ADC_DBR_3_2;		//ADC_DBR2:bit0~bit15;	ADC_DBR3:bit16~bit31 
		ADC_buf[2] = ADCx->ADC_DBR_5_4;		//ADC_DBR4:bit0~bit15;	ADC_DBR5:bit16~bit31
		ADC_buf[3] = ADCx->ADC_DBR_7_6;		//ADC_DBR6:bit0~bit15;	ADC_DBR7:bit16~bit31
		ADC_buf[4] = ADCx->ADC_DBR_9_8;		//ADC_DBR8:bit0~bit15;	ADC_DBR9:bit16~bit31
		ADC_buf[5] = ADCx->ADC_DBR_11_10;	//ADC_DBR10:bit0~bit15;	ADC_DBR11:bit16~bit31 
		ADC_buf[6] = ADCx->ADC_DBR_13_12;	//ADC_DBR12:bit0~bit15;	ADC_DBR13:bit16~bit31
		ADC_buf[7] = ADCx->ADC_DBR_15_14;	//ADC_DBR14:bit0~bit15;	ADC_DBR15:bit16~bit31
	}
	
}

/**
  *
  * @brief: 获取ADC busy状态
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  * 
  * @retVal: 获取到的ADC busy状态，SET-ADC busy状态；RESET- ADC非busy状态。
  */
FlagStatus ADC_Get_BusyState(ADC_TypeDef* ADCx)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	if(ADCx->ADC_CSR_1 &ADC_IS_BUSY)
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
  * @brief: 设置ADC的激活或PowerDown状态
  *
  * @param: ADCx,使用哪组ADC,STAR有两组ADC,可设置为STAR_ADC0或STAR_ADC1。
  *			ADC_ActiveState,ADC的激活或PowerDown状态，可设置为激活(ADC_ACTIVE)或PowerDown(ADC_INACTIVE_POWER_DOWN)。
  * 
  * @retVal: void
  */
void ADC_Active_Set(ADC_TypeDef* ADCx, uint8_t ADC_ActiveState)
{
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_ACTIVE_STATE(ADC_ActiveState));
	
	if(ADC_ActiveState ==ADC_ACTIVE)
	{
		ADCx->ADC_CSR_1 |= ADC_ACTIVE;
	}
	else
	{
		ADCx->ADC_CSR_1 &= (~ADC_ACTIVE);
	}
}





