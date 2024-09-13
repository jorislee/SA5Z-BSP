#include "CM3DS_i2c.h"
#include "CM3DS_rcc.h"
#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"

/**
  *
  * @brief: 将I2C初始化为默认配置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: void
  */
void I2C_DeInit(I2C_TypeDef *I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	if(I2Cx == CM3DS_MPS2_I2C)
	{     
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_I2C, ENABLE );     
		RCC_APBPeriphReset_Ctr( RCC_APBPeriph_I2C, DISABLE);
	}
}


/**
  *
  * @brief: I2C软件复位设置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能复位；ENABLE - 使能复位；DISABLE - 释放复位。
  * 
  * @retVal: void
  * others: 使能I2C软件复位后，需要及时释放复位；
  */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	if (NewState != DISABLE)
	{
		I2Cx->CONTROL |= (1ul<<CM3DS_MPS2_I2C_SWRST_Pos);
	}
	else
	{
		I2Cx->CONTROL &= ~(1ul<<CM3DS_MPS2_I2C_SWRST_Pos);
	}
	
}

/**
  *
  * @brief: I2C时钟配置。
  *
  * @param: I2Cx, 设置为CM3DS_MPS2_I2C。
  * @param: ClkSpeed, I2C时钟频率，单位Hz，时钟频率应不大于400KHz。
  * @param: SdaDlySel, SDA 总延迟计数选择，可设置的值包括：SDA_DEL_CNT_X_4 -  	SDA总延迟计数为 SDA延迟计数* 4
  * 													   SDA_DEL_CNT_X_2 -	SDA总延迟计数为 SDA延迟计数* 2
  * 													   SDA_DEL_CNT_X_1 -	SDA总延迟计数为 SDA延迟计数* 1
  * 													   DLY_CNT_0 -			SDA总延迟计数为 0
  * @param: SdaDlyCnt, SDA延迟计数，设置范围0-15。
  * @retVal: void
  */
void I2C_ClkFreq_Config(I2C_TypeDef *I2Cx,uint32_t ClkSpeed,I2C_SDA_DLY_CNT_SEL_TYPE SdaDlySel,uint8_t SdaDlyCnt)
{
	uint32_t tmpval;
	uint32_t pclk,clk_div;
	
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_ClkSpeed(ClkSpeed));
	assert_param(IS_I2C_SdaDlyCnt_Sel(SdaDlySel));
	assert_param(IS_I2C_SdaDlyCnt(SdaDlyCnt));
	
	pclk = RCC_Get_ClockFreq(APB_FREQ);
	clk_div = ((pclk/4)/ClkSpeed -1);
	
	
	tmpval= I2Cx->FREQDIV;
	// Reset clk_div_ratio, sda_del_sel and sda_del_cnt bits 
	tmpval&= ~I2C_FREQ_AND_SDA_DLY_MASK;
	tmpval |= ((clk_div<<I2C_CLK_DIV_RATIO_Pos)|(SdaDlySel<<I2C_SDA_DLY_CNT_SEL_Pos)|(SdaDlyCnt)<<I2C_SDA_DLY_CNT_Pos);
	
	I2Cx->FREQDIV = tmpval;
}

/**
  *
  * @brief: I2C初始化配置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  *	@param: Speed,I2C时钟速率，设置的值应小于400000Hz。
  *	@param: Ack,是否使能ACK: I2C_Ack_Enable - 使能ACK；	I2C_Ack_Disable - 不使能ACK。
  * @param: Mode,I2C主从模式；I2C_Mode_Master - I2C主模式; I2C_Mode_Slave - I2C从模式。
  *	@param: OwnAddress,主机地址。
  *
  * @retVal: void
  */
void I2C_Init(I2C_TypeDef *I2Cx,uint32_t Speed, uint16_t Ack, uint16_t Mode,uint32_t OwnAddress)
{
	uint32_t tmpval;
	uint8_t sda_dly_cnt;
	I2C_SDA_DLY_CNT_SEL_TYPE sda_dly_sel;
	
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_ACK_STATE(Ack));
	assert_param(IS_I2C_Mode_STATE(Mode));
	
	I2C_DeInit(I2Cx);
	
	I2C_SoftwareResetCmd(I2Cx,ENABLE);
	I2C_SoftwareResetCmd(I2Cx,DISABLE);
	
	tmpval = I2Cx->CONTROL;
	tmpval &= ~(I2C_Ack_Set_Mask|I2C_Mode_Mask);
	
	tmpval |= (Ack|Mode);
	
	I2Cx->CONTROL = tmpval;
	
	if(Speed<=110000)
	{
		sda_dly_sel = DLY_CNT_0;
		sda_dly_cnt = 2;
	}
	else if((Speed>110000)&&(Speed<=210000))
	{
		sda_dly_sel = SDA_DEL_CNT_X_1;
		sda_dly_cnt = 4;
	}
	else if((Speed>210000)&&(Speed<=310000))
	{
		sda_dly_sel = SDA_DEL_CNT_X_1;
		sda_dly_cnt = 2;
	}
	else
	{
		sda_dly_sel = SDA_DEL_CNT_X_2;
		sda_dly_cnt = 2;
	}
	I2C_ClkFreq_Config(I2Cx,Speed,sda_dly_sel,sda_dly_cnt);
	
	I2Cx->OWNADDR = OwnAddress;
	
}


/**
  *
  * @brief: I2C从机地址设置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: SlvAddr,要设置的从机地址。读操作或写操作由SlvAddr[15]位确定，该位为0表示写，为1表示读。
  * 
  * @retVal: void
  */
void I2C_SlaveAddr_Config( I2C_TypeDef *I2Cx, uint32_t SlvAddr)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
		
	I2Cx->SLVADDR = SlvAddr;
}

/**
  *
  * @brief: 生成I2C起始信号。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能生成I2C起始信号；ENABLE - 使能；DISABLE - 不使能。
  * 
  * @retVal: void
  */
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState)
{		
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState != DISABLE)
	{
		I2Cx->CONTROL  |= CM3DS_MPS2_I2C_START_SET_Msk;
		while ((I2Cx->STATUS1 & 1) != 1);
	}
	else
	{
		I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_START_SET_Msk);
	}	 	
}

/**
  *
  * @brief: 使能I2C发送。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能I2C发送；ENABLE - 使能；DISABLE - 不使能。
  * 
  * @retVal: void
  */
void I2C_TxEnable( I2C_TypeDef *I2Cx, FunctionalState NewState)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		I2Cx->CONTROL |= CM3DS_MPS2_I2C_TX_ENA_Msk ;
	}
	else
	{
		I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_TX_ENA_Msk);
	}	
}

/**
  *
  * @brief: 使能I2C接收。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否使能I2C接收；ENABLE - 使能；DISABLE - 不使能。
  * 
  * @retVal: void
  */
void I2C_RxEnable(I2C_TypeDef *I2Cx,FunctionalState NewState)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if(NewState != DISABLE)
	{
		I2Cx->CONTROL |= CM3DS_MPS2_I2C_RX_ENA_Msk;
	}
	else
	{
		I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_RX_ENA_Msk);
	}
}

/**
  *
  * @brief: 生成I2C停止信号。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: NewState,是否生成I2C停止信号；ENABLE - 使能；DISABLE - 不使能。
  * 
  * @retVal: void
  */
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState)
{	
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
    if (NewState != DISABLE)
    {
        I2Cx->CONTROL |= CM3DS_MPS2_I2C_STOP_SET_Msk ;
		while ((I2Cx-> STATUS1 & (1ul << 15)) == 0);  //stop bit detect
    }
    else
    {
        I2Cx->CONTROL &= (~CM3DS_MPS2_I2C_STOP_SET_Msk);
    }
}


/**
  *
  * @brief: 设置I2C收发数据的个数。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: Num,需要收发数据的个数。
  * 
  * @retVal: void
  */
void I2C_WriteByteNum_Config(I2C_TypeDef *I2Cx,uint16_t Num)
{		
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	I2Cx->CONTROL &= ~(0x0f <<CM3DS_MPS2_I2C_TX_NUM_Pos);
	I2Cx->CONTROL |= ((Num&0x0f) << CM3DS_MPS2_I2C_TX_NUM_Pos );
}

/**
  *
  * @brief: 使用I2C发送数据。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: Byte,需要发送的数据。
  * 
  * @retVal: void
  */
void I2C_WriteByte(I2C_TypeDef*I2Cx,uint8_t Byte)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	I2Cx->TXDATA = Byte;
}

/**
  *
  * @brief: 等待I2C发送完成。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: void
  */
void I2C_WaitWriteDataFinish(I2C_TypeDef *I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	while((I2Cx->STATUS1 & (1ul << 4))==0);	//wait until tx fifo is empty
	while ((I2Cx->STATUS1 & (1ul << 16))==0);		   //transmit complete flag
}

/**
  *
  * @brief: I2C等待接收数据，直到RX FIFO非空。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: void
  */
void I2C_WaitReceiveReady(I2C_TypeDef *I2Cx)
{		
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	while ((I2Cx->STATUS1&0x00000400));
}

/**
  *
  * @brief: I2C接收数据。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: I2C接收到的数据。
  */
uint8_t I2C_ReceiveByte(I2C_TypeDef *I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	return  (uint8_t)I2Cx->RXDATA;
}

/**
  *
  * @brief: 获取I2C状态寄存器1的值。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: Values,获取到的状态寄存器值。
  */
uint32_t I2C_GetStatus1Values(I2C_TypeDef *I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
		
	return I2Cx-> STATUS1;
}

/**
  *
  * @brief: 获取I2C状态寄存器2的值。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: 获取到的状态寄存器值。
  */
uint16_t I2C_GetStatus2Values(I2C_TypeDef *I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
		
	return (uint16_t)I2Cx->STATUS2;
}


/**
  *
  * @brief: 获取I2C指定状态是否发生。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: Status,要获取的状态类型；
  *					可设置的值包括:
  *						start_bit_det - 起始位信号被检测; 
  *						addr_7bit_match - 地址7位发送/接收匹配;	addr_10bit_math - 地址10位发送/接收匹配；
  *						tx_fifo_full - 发送FIFO已满;	tx_fifo_empty - 发送FIFO已空；
  *						rx_fifo_full - 接收FIFO已满;	rx_fifo_empty - 接收FIFO已空；
  *						stop_bit_det - 停止位信号被检测; tc_flag - 发送完成；
  *						data_received - 数据到达。
  *						
  * 
  * @retVal: bitStatus,获取到的状态，SET - 指定状态已发生；RESET - 指定状态未发生。
  */
ITStatus I2C_CheckStatus(I2C_TypeDef*I2Cx,uint32_t Status)
{
	ITStatus bitStatus = RESET;
    
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_STATUS1(Status));
	
	if ((I2Cx->STATUS1 & Status) != RESET)
	{
		bitStatus = SET;
	}
	else
	{
		bitStatus = RESET;
	}
	return bitStatus;
}

/**
  *
  * @brief: 等待I2C总线为IDLE状态。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: void
  */
void I2C_WaitBusIdle(I2C_TypeDef* I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	while((I2Cx-> STATUS2 & (1ul<<4)));
}

/**
  *
  * @brief: 等待直到I2C的Tx FIFO不为满状态。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * 
  * @retVal: void
  */
void I2C_WaitTxFIFOIsNotFull (I2C_TypeDef* I2Cx)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	while((I2Cx->STATUS1 & (1ul<<3)));
}

/**
  *
  * @brief: 检查ACK是否失败。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  *						
  * @retVal: isFail,获取到的ACK失败状态，SET - ACK失败；RESET - ACK正常。
  */
FlagStatus I2C_CheckACKIsFail(I2C_TypeDef* I2Cx)
{
	FlagStatus isFail;
	
	if(I2Cx->STATUS2 &(1ul<<3))
	{
		isFail= SET;
	}
	else
	{
		isFail= RESET;
	}
	
	return isFail;
}


/**
  *
  * @brief: I2C中断配置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: I2C_Interrupt,I2C中断触发类型；
  *					可设置的值包括：
  *						I2C_TxInterrupt(0x02)-I2C发送中断；
  *						I2C_BusErrInterrupt(0x80) - I2C总线错误中断；
  *						I2C_RxInterrupt(0x0200)- I2C接收中断。  
  *						I2C_TCInterrupt(0x2000) - I2C发送完成中断；
  *						I2C_StopInterrupt(0x4000) - I2C停止中断；
  * @param: NewState,是否使能中断；ENABLE - 使能；DISABLE - 不使能。
  * 
  * @retVal: void
  */
void I2C_Interrupt_Config(I2C_TypeDef* I2Cx,uint16_t I2C_Interrupt,FunctionalState NewState)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_I2C_INT(I2C_Interrupt));

	if (NewState != DISABLE)
	{
		I2Cx->CONTROL |= I2C_Interrupt;	
	}
	else
	{
		I2Cx->CONTROL &= ~I2C_Interrupt;
	}
}

/**
  *
  * @brief: 获取I2C指定中断状态。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: I2C_Interrupt,I2C中断触发类型；
  *					可设置的值包括：
  *						I2C_TxInterrupt(0x02)-I2C发送中断；
  *						I2C_BusErrInterrupt(0x80) - I2C总线错误中断；
  *						I2C_RxInterrupt(0x0200)- I2C接收中断。  
  *						I2C_TCInterrupt(0x2000) - I2C发送完成中断；
  *						I2C_StopInterrupt(0x4000) - I2C停止中断；
  *						
  * 
  * @retVal: bitStatus,获取到的状态，SET - 指定状态已发生；RESET - 指定状态未发生。
  */
ITStatus I2C_Get_InterruptStatus(I2C_TypeDef *I2Cx,uint32_t I2C_Interrupt)
{
	ITStatus bitStatus = RESET;
	uint16_t itStatusOffset =0;
	uint32_t enablestatus = 0;
	
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	assert_param(IS_I2C_INT(I2C_Interrupt));
	
	enablestatus = (uint32_t)(I2Cx->CONTROL & I2C_Interrupt); //获取对应的中断使能状态
	switch(I2C_Interrupt)
	{
		case I2C_BusErrInterrupt:
			itStatusOffset = 5;
			break;
		case I2C_TCInterrupt:
			itStatusOffset = 8;
			break;
		case I2C_StopInterrupt:
			itStatusOffset = 9;
			break;
		case I2C_TxInterrupt:
			itStatusOffset = 6;
			break;
		case I2C_RxInterrupt:
			itStatusOffset = 7;
			break;
		default:
			
			break;
	}	
	if ((itStatusOffset !=0)&&((I2Cx->STATUS2 & (1<<itStatusOffset)) != RESET)&& enablestatus)
	{
		bitStatus = SET;
	}
	else
	{
		bitStatus = RESET;
	}
	
	return bitStatus;
}

/**
  *
  * @brief: I2C发送中断tx buffer门限配置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: TxbufferWlevel, 发送buffer中断触发门限ctrl_tx_buff_wlevel；当TX FIFO占用的空间大于该值时将触发I2C发送中断；
  *						可设置的值为0/1/2/3。
  * 
  * @retVal: void
  */
void I2C_TxInterrupt_TxbufferLevel_Config(I2C_TypeDef* I2Cx, uint8_t TxbufferWlevel)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    
	if(TxbufferWlevel <4)
	{
		I2Cx->CONTROL &= ~(0x03<<CM3DS_MPS2_I2C_TX_BUFFER_LEVEL_Pos);
		I2Cx->CONTROL  |= (TxbufferWlevel<<CM3DS_MPS2_I2C_TX_BUFFER_LEVEL_Pos);
	}
}

/**
  *
  * @brief: I2C接收中断rx buffer门限配置。
  *
  * @param: I2Cx,设置为CM3DS_MPS2_I2C。
  * @param: RxbufferWlevel, 接收buffer中断触发门限ctrl_rx_buff_wlevel；当RX FIFO占用的空间大于该值时将触发I2C接收中断；
  *						可设置的值为0/1/2/3。
  * 
  * @retVal: void
  */
void I2C_RxInterrupt_RxbufferLevel_Config(I2C_TypeDef* I2Cx, uint8_t RxbufferWlevel)
{
	assert_param(IS_I2C_ALL_PERIPH(I2Cx));
	
	if(RxbufferWlevel<4)
	{
		I2Cx->CONTROL &= ~(0x03<<CM3DS_MPS2_I2C_RX_BUFFER_LEVEL_Pos);
		I2Cx->CONTROL |= ( RxbufferWlevel << CM3DS_MPS2_I2C_RX_BUFFER_LEVEL_Pos);
	}
}
