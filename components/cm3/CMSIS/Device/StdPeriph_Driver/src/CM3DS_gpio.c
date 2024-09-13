#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"

/**
  *
  * @brief: 将GPIO外设寄存器初始化为默认值。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * 
  * @retVal: void
  */
void GPIO_DeInit( GPIO_TypeDef *CM3DS_MPS2_GPIOx)
{
	uint16_t i;
	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));

	if (CM3DS_MPS2_GPIOx == CM3DS_MPS2_GPIO0)
	{
		CM3DS_MPS2_GPIOx->DATA = 0x0;
		CM3DS_MPS2_GPIOx->DATAOUT = 0x0;
		CM3DS_MPS2_GPIOx->OUTENABLECLR = 0xffffffff;
		CM3DS_MPS2_GPIOx->ALTFUNCCLR = 0xffffffff;
		CM3DS_MPS2_GPIOx->INTENCLR = 0xffffffff;
		CM3DS_MPS2_GPIOx->INTTYPECLR= 0xffffffff;
		CM3DS_MPS2_GPIOx->INTPOLCLR = 0xffffffff;
		CM3DS_MPS2_GPIOx->INTCLEAR = 0xffffffff;
		
		for(i=0;i<256;i++)
		{
			CM3DS_MPS2_GPIOx->BYTE0_MASKED[i]=0x0;
		}
		for(i=0;i<256;i++)
		{
			CM3DS_MPS2_GPIOx->BYTE1_MASKED[i]=0x0;
		}
		for(i=0;i<256;i++)
		{
			CM3DS_MPS2_GPIOx->BYTE2_MASKED[i]=0x0;
		}
		for(i=0;i<256;i++)
		{
			CM3DS_MPS2_GPIOx->BYTE3_MASKED[i]=0x0;
		}
	}
}


/**
  *
  * @brief: 设置GPIO的模式。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: GPIO_Mode, GPIO模式类型；
  *					取值范围：GPIO_Mode_Output - 输出模式；GPIO_Mode_Input - 输入模式；
  *							  GPIO_Mode_AF - 复用模式。
  * 
  * @retVal: void
  */
void GPIO_Mode_Set(GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, GPIO_Mode_TypeDef GPIO_Mode)
{
	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	assert_param(IS_GPIO_MODE_TYPE(GPIO_Mode));
	
	if(GPIO_Mode ==GPIO_Mode_Input)
	{
		CM3DS_MPS2_GPIOx->OUTENABLECLR = (1 << GPIO_Pin_x);
		CM3DS_MPS2_GPIOx->ALTFUNCCLR  = ( 1 << GPIO_Pin_x );
		CM3DS_MPS2_GPIOx->INTENCLR = ( 1 << GPIO_Pin_x );
	}
	else if(GPIO_Mode ==GPIO_Mode_AF)
	{
		CM3DS_MPS2_GPIOx->OUTENABLECLR = (1 << GPIO_Pin_x);
		//CM3DS_MPS2_GPIOx->ALTFUNCCLR  = ( 1 << GPIO_Pin_x );
		CM3DS_MPS2_GPIOx->INTENCLR = ( 1 << GPIO_Pin_x );
	}
	else
	{
		CM3DS_MPS2_GPIOx->OUTENABLESET = ( 1 << GPIO_Pin_x );
		CM3DS_MPS2_GPIOx->ALTFUNCCLR  = ( 1 << GPIO_Pin_x );
		CM3DS_MPS2_GPIOx->INTENCLR = ( 1 << GPIO_Pin_x );
	}
}

/**
  *
  * @brief: 读取GPIO的输入电平。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: bitStatus，读取到的GPIO电平值;取值范围: 低电平-Bit_RESET(0)或高电平-Bit_SET(1)。
  */
uint8_t GPIO_ReadInputBit( GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x)
{
	uint8_t bitStatus  = 0x00;

	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

	if((CM3DS_MPS2_GPIOx->DATA & ( 1ul << GPIO_Pin_x)) == 0)
	{
		bitStatus = (uint8_t) Bit_RESET;
	}
	else
	{
		bitStatus = (uint8_t) Bit_SET;
	}

    return bitStatus;
}

/**
  *
  * @brief: 设置GPIO高电平输出。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_SetBit( GPIO_TypeDef * CM3DS_MPS2_GPIOx,  uint16_t GPIO_Pin_x)
{
	uint32_t gpioDatamask = 0x00;

	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

	if (CM3DS_MPS2_GPIOx  == CM3DS_MPS2_GPIO0)
	{
		gpioDatamask = ( 1 << GPIO_Pin_x % 8);

		if (GPIO_Pin_x<= 7) 
		{
			CM3DS_MPS2_GPIOx->BYTE0_MASKED[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		} 
		else if ( (8 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 15) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE1_MASKED[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		} 
		else if ( (16 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 23) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE2_MASKED[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		} 
		else if ( (24 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 31) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE3_MASKED[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		}
	}
}

/**
  *
  * @brief: 设置GPIO低电平输出。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_ResetBit( GPIO_TypeDef * CM3DS_MPS2_GPIOx,  uint16_t GPIO_Pin_x)
{
	uint32_t gpioDatamask = 0x00;

	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

	if (CM3DS_MPS2_GPIOx  == CM3DS_MPS2_GPIO0)
	{
		gpioDatamask = ( 1 << GPIO_Pin_x % 8);

		if (GPIO_Pin_x <= 7) 
		{
			CM3DS_MPS2_GPIOx->BYTE0_MASKED[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		} 
		else if ( (8 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 15) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE1_MASKED[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		} 
		else if ( (16 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 23) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE2_MASKED[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		} 
		else if ( (24 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 31) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE3_MASKED[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		}
	}
}

/**
  *
  * @brief: 设置GPIO输出电平取反。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_TogglePin( GPIO_TypeDef * CM3DS_MPS2_GPIOx,  uint16_t GPIO_Pin_x)
{
	uint32_t gpioDatamask = 0x00;

	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

	if (CM3DS_MPS2_GPIOx  == CM3DS_MPS2_GPIO0)
	{
		gpioDatamask = ( 1 << GPIO_Pin_x % 8);

		if (GPIO_Pin_x <= 7) 
		{
			CM3DS_MPS2_GPIOx->BYTE0_MASKED[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		} 
		else if ( (8 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 15) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE1_MASKED[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		} 
		else if ( (16 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 23) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE2_MASKED[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		} 
		else if ( (24 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 31) ) 
		{
			CM3DS_MPS2_GPIOx->BYTE3_MASKED[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		}
	}
}

/**
  *
  * @brief: 设置GPIO输出高电平或低电平。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: BitVal，高电平(Bit_SET)或低电平(Bit_RESET)。
  * 
  * @retVal: void
  */
void GPIO_WriteBit(GPIO_TypeDef * CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, BitAction BitVal)
{
	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	assert_param(IS_GPIO_BIT_ACTION(BitVal));

	if (BitVal != Bit_RESET)
	{
		CM3DS_MPS2_GPIOx->DATA |= ( Bit_SET << GPIO_Pin_x );
	}
	else
	{
		CM3DS_MPS2_GPIOx->DATA &= (~( Bit_SET << GPIO_Pin_x ));
	}
}

/**
  *
  * @brief: 设置GPIO的复用功能，如UART、ADC、Timer、I2C、SPI等。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_AF，选择的GPIO复用功能，取值参考GPIO_AF_define。
  * @param: NewState，是否使能复用，ENABLE：使能复用，DISABLE:不使能复用。
  * 
  * @retVal: void
  */
void GPIO_AF_Config( GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint32_t  GPIO_AF, FunctionalState NewState )
{
	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GPIO_AF(GPIO_AF));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if ( NewState != DISABLE)
	{
		CM3DS_MPS2_GPIOx->ALTFUNCSET  = GPIO_AF;
	}
	else
	{
		CM3DS_MPS2_GPIOx->ALTFUNCCLR   = GPIO_AF;
	}
}

/**
  *
  * @brief: 设置GPIO的中断触发方式。
  *
  * @param: CM3DS_MPS2_GPIOx，使用哪组GPIO;由于CM3只提供1组GPIO，只能设为CM3DS_MPS2_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: TriggerType，中断触发方式;
  *					取值范围：Bit_LOWLEVEL - 低电平触发；Bit_HIGHLEVEL - 高电平触发；
  *							  Bit_FALLINGEDGE - 下降沿触发；Bit_RISINGEDGE - 上升沿触发。
  * @param: NewState，是否使能中断，Interrupt_ENABLE：使能，Interrupt_DISABLE:不使能。
  * 
  * @retVal: void
  */
void GPIO_Interrupt_Config(GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, GPIO_IntTrigger_TypeDef TriggerType, InterruptState NewState)
{
	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	assert_param(IS_GPIO_INT_TRIGGER_TYPE(TriggerType));
	assert_param(IS_INTERRUPT_STATE(NewState));

	if (NewState != Interrupt_DISABLE)
	{
		CM3DS_MPS2_GPIOx->INTENSET  = (Interrupt_ENABLE << GPIO_Pin_x);
		switch (TriggerType)
		{
			case  Bit_LOWLEVEL:
				CM3DS_MPS2_GPIOx->INTTYPECLR = ( Interrupt_ENABLE<< GPIO_Pin_x);
				CM3DS_MPS2_GPIOx->INTPOLCLR = ( Interrupt_ENABLE << GPIO_Pin_x);
			break;
			case  Bit_HIGHLEVEL:
				CM3DS_MPS2_GPIOx->INTTYPECLR = ( Interrupt_ENABLE << GPIO_Pin_x);
				CM3DS_MPS2_GPIOx->INTPOLSET = ( Interrupt_ENABLE << GPIO_Pin_x);
			break;
			case  Bit_FALLINGEDGE:
				CM3DS_MPS2_GPIOx->INTTYPESET = ( Interrupt_ENABLE << GPIO_Pin_x);
				CM3DS_MPS2_GPIOx->INTPOLCLR = ( Interrupt_ENABLE << GPIO_Pin_x);
			break;
			case  Bit_RISINGEDGE:
				CM3DS_MPS2_GPIOx->INTTYPESET = ( Interrupt_ENABLE << GPIO_Pin_x);
				CM3DS_MPS2_GPIOx->INTPOLSET = ( Interrupt_ENABLE << GPIO_Pin_x);
			break;
		}
	}
	else
	{
		CM3DS_MPS2_GPIOx->INTENCLR = (Interrupt_ENABLE << GPIO_Pin_x);
	}
}

/**
  *
  * @brief: 清除GPIO的中断标志。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_Interrupt_Clear(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin_x)
{
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	
	GPIOx->INTCLEAR = ( 1 << GPIO_Pin_x );
}

