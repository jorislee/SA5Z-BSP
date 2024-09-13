#include "STAR_gpio.h"
#include "STAR.h"

/**
  *
  * @brief: 将GPIO相关寄存器初始化为默认值。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * 
  * @retVal: void
  */
void GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	uint16_t i;
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	
	if(GPIOx == STAR_GPIO0)
	{
		GPIOx->DATA = 0x0;
		GPIOx->DATAOUT = 0x0;
		GPIOx->OUTENCLR = 0xffffffff;
		GPIOx->ALTFUNCCLR = 0xffffffff;
		GPIOx->INTENCLR = 0xffffffff;
		GPIOx->INTTYPECLR =0xffffffff;
		GPIOx->INTPOLCLR = 0xffffffff;
		GPIOx->INTCLEAR = 0xffffffff;
		
		for(i=0;i<256;i++)
		{
			GPIOx->MASKBYTE0[i]=0x0;
		}
		for(i=0;i<256;i++)
		{
			GPIOx->MASKBYTE1[i]=0x0;
		}
		for(i=0;i<256;i++)
		{
			GPIOx->MASKBYTE2[i]=0x0;
		}
		for(i=0;i<256;i++)
		{
			GPIOx->MASKBYTE3[i]=0x0;
		}
	}
}

/**
  *
  * @brief: 设置GPIO的模式。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: GPIO_Mode, GPIO模式类型；
  *					取值范围：GPIO_Mode_Output - 输出模式；GPIO_Mode_Input - 输入模式；
  *							  GPIO_Mode_AF - 复用模式。
  * 
  * @retVal: void
  */
void GPIO_Mode_Set(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin_x, GPIO_Mode_TypeDef GPIO_Mode)
{
	assert_param(IS_GPIO_ALL_PERIPH(CM3DS_MPS2_GPIOx));
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	assert_param(IS_GPIO_MODE_TYPE(GPIO_Mode));
	
	if(GPIO_Mode ==GPIO_Mode_Input)
	{
		GPIOx->OUTENCLR = (1 << GPIO_Pin_x);
		GPIOx->ALTFUNCCLR  = ( 1 << GPIO_Pin_x );
		GPIOx->INTENCLR = ( 1 << GPIO_Pin_x );
	}
	else if(GPIO_Mode ==GPIO_Mode_AF)
	{
		GPIOx->OUTENCLR = (1 << GPIO_Pin_x);
		//GPIOx->ALTFUNCCLR  = ( 1 << GPIO_Pin_x );
		GPIOx->INTENCLR = ( 1 << GPIO_Pin_x );
	}
	else
	{
		GPIOx->OUTENSET = ( 1 << GPIO_Pin_x );
		GPIOx->ALTFUNCCLR  = ( 1 << GPIO_Pin_x );
		GPIOx->INTENCLR = ( 1 << GPIO_Pin_x );
	}
}
/**
  *
  * @brief: 读取GPIO的输入电平。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: bitStatus，读取到的GPIO电平值;取值范围: 低电平-Bit_RESET(0)或高电平-Bit_SET(1)。
  */
uint8_t GPIO_ReadInputBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin_x)
{
    uint8_t bitStatus  = 0x00;
    
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
    
    if((GPIOx->DATA &(Bit_SET << GPIO_Pin_x)) == Bit_RESET)
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
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_SetBit(GPIO_TypeDef *GPIOx,  uint16_t GPIO_Pin_x)
{
    uint32_t gpioDatamask = 0x00;
    
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

	if(GPIOx  == STAR_GPIO0)
	{
		gpioDatamask = ( 1 << GPIO_Pin_x % 8);

		if (GPIO_Pin_x<= 7) 
		{
			GPIOx->MASKBYTE0[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		} 
		else if ( (8 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 15) ) 
		{
			GPIOx->MASKBYTE1[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		} 
		else if ( (16 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 23) ) 
		{
			GPIOx->MASKBYTE2[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		} 
		else if ( (24 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 31) ) 
		{
			GPIOx->MASKBYTE3[gpioDatamask] |= ( 1 << GPIO_Pin_x );
		}
	}
	
}

/**
  *
  * @brief: 设置GPIO低电平输出。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_ResetBit( GPIO_TypeDef * GPIOx,  uint16_t GPIO_Pin_x)
{
    uint32_t gpioDatamask = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	
	if(GPIOx  == STAR_GPIO0)
	{
		gpioDatamask = ( 1 << GPIO_Pin_x % 8);

		if (GPIO_Pin_x <= 7) 
		{
			GPIOx->MASKBYTE0[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		} 
		else if ( (8 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 15) ) 
		{
			GPIOx->MASKBYTE1[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		} 
		else if ( (16 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 23) ) 
		{
			GPIOx->MASKBYTE2[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		} 
		else if ( (24 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 31) ) 
		{
			GPIOx->MASKBYTE3[gpioDatamask] &= (~( 1 << GPIO_Pin_x ));
		}
	}
}

/**
  *
  * @brief: 设置GPIO输出电平取反。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_TogglePin(GPIO_TypeDef *GPIOx,  uint16_t GPIO_Pin_x)
{
    uint32_t gpioDatamask = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));

    if(GPIOx  == STAR_GPIO0)
	{
		gpioDatamask = ( 1 << GPIO_Pin_x % 8);

		if (GPIO_Pin_x <= 7) 
		{
			GPIOx->MASKBYTE0[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		} 
		else if ( (8 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 15) ) 
		{
			GPIOx->MASKBYTE1[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		} 
		else if ( (16 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 23) ) 
		{
			GPIOx->MASKBYTE2[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		} 
		else if ( (24 <= GPIO_Pin_x) &&  (GPIO_Pin_x <= 31) ) 
		{
			GPIOx->MASKBYTE3[gpioDatamask] ^= ( 1 << GPIO_Pin_x );
		}
	}
	
}

/**
  *
  * @brief: 设置GPIO输出高电平或低电平。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: BitVal，高电平(Bit_SET)或低电平(Bit_RESET)。
  * 
  * @retVal: void
  */
void GPIO_WriteBit(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin_x, BitAction BitVal)
{
    
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if(BitVal != Bit_RESET)
    {
        GPIOx->DATAOUT |= (Bit_SET << GPIO_Pin_x );
    }
    else
    {
        GPIOx->DATAOUT &= (~(Bit_SET << GPIO_Pin_x ));
    }
}


/**
  *
  * @brief: 设置GPIO的复用功能，如UART、ADC、Timer、I2C、SPI等。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_AF，选择的GPIO复用功能，取值参考GPIO_AF_define。
  * @param: NewState，是否使能复用，ENABLE：使能复用，DISABLE:不使能复用。
  * 
  * @retVal: void
  * @notes: 一个IO复用为某个功能后就不能再取消该复用功能。
  */
void GPIO_AF_Config(GPIO_TypeDef *GPIOx,  uint32_t  GPIO_AF, FunctionalState NewState)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_REMAP(GPIO_AF));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if(NewState != DISABLE)
    {
		GPIOx->ALTFUNCSET  = GPIO_AF;
    }
    else
    {
        GPIOx->ALTFUNCCLR  = GPIO_AF; 
    }
}


/**
  *
  * @brief: 设置GPIO的中断触发方式。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * @param: TriggerType，中断触发方式;
  *					取值范围：Bit_LOWLEVEL - 低电平触发；Bit_HIGHLEVEL - 高电平触发；
  *							  Bit_FALLINGEDGE - 下降沿触发；Bit_RISINGEDGE - 上升沿触发。
  * @param: NewState，是否使能中断，Interrupt_ENABLE：使能，Interrupt_DISABLE:不使能。
  * @retVal: void
  */
void GPIO_Interrupt_Config(GPIO_TypeDef *GPIOx,  uint16_t GPIO_Pin_x,
                                         GPIO_IntTrigger_TypeDef TriggerType, InterruptState NewState)
{
    
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
    assert_param(IS_GPIO_INT_TRIGGER_TYPE(TriggerType));
    assert_param(IS_INTERRUPT_STATE(NewState));

    
    if (NewState != Interrupt_DISABLE)
    {
         GPIOx->INTENSET  = (Interrupt_ENABLE << GPIO_Pin_x);
         switch (TriggerType)
         {
            case  Bit_LOWLEVEL:
                GPIOx->INTTYPECLR = (Interrupt_ENABLE<< GPIO_Pin_x);
                GPIOx->INTPOLCLR  = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
            case  Bit_HIGHLEVEL:
                GPIOx->INTTYPECLR = (Interrupt_ENABLE << GPIO_Pin_x);
                GPIOx->INTPOLSET  = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
            case  Bit_FALLINGEDGE:
                GPIOx->INTTYPESET = (Interrupt_ENABLE << GPIO_Pin_x);
                GPIOx->INTPOLCLR  = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
            case  Bit_RISINGEDGE:
                GPIOx->INTTYPESET = (Interrupt_ENABLE << GPIO_Pin_x);
                GPIOx->INTPOLSET  = (Interrupt_ENABLE << GPIO_Pin_x);
            break;
        }
    }
    else
    {
        GPIOx->INTENCLR = (Interrupt_ENABLE << GPIO_Pin_x);
    }
}

/**
  *
  * @brief: 清除GPIO的中断标志。
  *
  * @param: GPIOx，使用哪组GPIO;由于STAR只提供1组GPIO，因此该参数只能设为STAR_GPIO0。
  * @param: GPIO_Pin_x，使用哪个GPIO;取值范围：GPIO_Pin_0~GPIO_Pin_31。
  * 
  * @retVal: void
  */
void GPIO_Interrupt_Clear(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin_x)
{
	
	assert_param(IS_GET_GPIO_PIN(GPIO_Pin_x));
	
	GPIOx->INTCLEAR = ( 1 << GPIO_Pin_x );
}




