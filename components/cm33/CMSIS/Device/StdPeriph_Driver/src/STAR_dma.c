#include "STAR_rcc.h"
#include "STAR_gpio.h"
#include "STAR.h"	
#include "STAR_dma.h"	

/**
  *
  * @brief: DMA初始配置。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  * @param: DMA_InitStr,设置的参数结构体。
  *	
  * @retVal: void
  */
void DMA_Init(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,DMA_InitTypedef *DMA_InitStr)
{
	uint32_t tmpval;
	
	assert_param(IS_DMA_ADDR_INC_TYPE(DMA_InitStr->DMA_SourceAddr_Inc));
	assert_param(IS_DMA_ADDR_INC_TYPE(DMA_InitStr->DMA_DestinationAddr_Inc));
	assert_param(IS_DMA_DATA_WIDTH_TYPE(DMA_InitStr->DMA_SourceDataWidth));
	assert_param(IS_DMA_DATA_WIDTH_TYPE(DMA_InitStr->DMA_DestinationDataWidth));
	assert_param(IS_DMA_BURST_SIZE_TYPE(DMA_InitStr->DMA_SourceBurstSize));
	assert_param(IS_DMA_BURST_SIZE_TYPE(DMA_InitStr->DMA_DestinationBurstSize));
	assert_param(IS_DMA_TRANSFER_TYPE(DMA_InitStr->DMA_Transfertype));
	assert_param(IS_DMA_PERIPHERAL_TYPE(DMA_InitStr->DMA_DestinationPeripheral));
	assert_param(IS_DMA_PERIPHERAL_TYPE(DMA_InitStr->DMA_SourcePeripheral));
	assert_param(IS_DMA_TC_INT_Enable_TypeDef(DMA_InitStr->DMA_TCInterruptEnable));
	
	DMAx->DMACConfiguration = 0x00000000;
	//DMAC Cofigure
	tmpval=DMAx->DMACConfiguration;
	tmpval &= 0xfffffffc;
	//DMAC AHB Master endianness configuration:little-endian mode,DMAC Enable.
	tmpval |= (DMA_AHBMaster_Endianness_Little<<DMA_AHBMaster_Endianness_Pos)
				|(DMA_DMAC_Enable<<DMA_DMAC_Enable_Pos);
	DMAx->DMACConfiguration =tmpval;
	
	if(DMAChannel==DMA_Channel_0)
	{
		
		DMAx->DMACC0SrcAddr = DMA_InitStr->DMA_Source_Addr;
		DMAx->DMACC0DestAddr = DMA_InitStr->DMA_Destination_Addr;
		
		tmpval = DMAx->DMACC0Control;
		tmpval &= 0x70000fff;
		tmpval |= (DMA_InitStr->DMA_SourceAddr_Inc <<DMA_SourceAddr_Inc_Pos) 
				|(DMA_InitStr->DMA_DestinationAddr_Inc <<DMA_DestinationAddr_Inc_Pos) 	
				|(DMA_InitStr->DMA_SourceDataWidth <<DMA_SourceDataWidth_Pos) 
				|(DMA_InitStr->DMA_DestinationDataWidth<<DMA_DestinationDataWidth_Pos) 		
				|(DMA_InitStr->DMA_SourceBurstSize <<DMA_SourceBurstSize_Pos) 
				|(DMA_InitStr->DMA_DestinationBurstSize<<DMA_DestinationBurstSize_Pos);
		
		tmpval |= (DMA_InitStr->DMA_TCInterruptEnable <<DMA_TCInterruptEnable_Pos);
		
		DMAx->DMACC0Control = tmpval;
		//tmpval = DMAx->DMACC0Configuration;
		tmpval =0x0;
		//Halt:0,enable DMA requests
		//Lock:1
		tmpval |= (1ul<<DMA_ChannelConfig_Lock_Pos);
		tmpval |= (DMA_InitStr->DMA_Transfertype <<DMA_ChannelConfig_Transfertype_Pos) 
					|(DMA_InitStr->DMA_DestinationPeripheral <<DMA_ChannelConfig_DestPeripheral_Pos)
						|(DMA_InitStr->DMA_SourcePeripheral <<DMA_ChannelConfig_SrcPeripheral_Pos);
		
		DMAx->DMACC0Configuration = tmpval;
	}
	else
	{
		DMAx->DMACC1SrcAddr = DMA_InitStr->DMA_Source_Addr;
		DMAx->DMACC1DestAddr = DMA_InitStr->DMA_Destination_Addr;
		
		tmpval = DMAx->DMACC1Control;
		tmpval &= 0x70000fff;
		tmpval |= (DMA_InitStr->DMA_SourceAddr_Inc <<DMA_SourceAddr_Inc_Pos) 
				|(DMA_InitStr->DMA_DestinationAddr_Inc <<DMA_DestinationAddr_Inc_Pos) 
				|(DMA_InitStr->DMA_SourceDataWidth <<DMA_SourceDataWidth_Pos) 
				|(DMA_InitStr->DMA_DestinationDataWidth<<DMA_DestinationDataWidth_Pos) 	
				|(DMA_InitStr->DMA_SourceBurstSize <<DMA_SourceBurstSize_Pos) 
				|(DMA_InitStr->DMA_DestinationBurstSize<<DMA_DestinationBurstSize_Pos);
		
		tmpval |= (DMA_InitStr->DMA_TCInterruptEnable <<DMA_TCInterruptEnable_Pos);
		
		DMAx->DMACC1Control = tmpval;
		
		//tmpval = DMAx->DMACC1Configuration;
		tmpval =0x0;
		//Halt:0,enable DMA requests
		//Lock:1
		tmpval |= (1ul<<DMA_ChannelConfig_Lock_Pos);
		
		tmpval |= (DMA_InitStr->DMA_Transfertype <<DMA_ChannelConfig_Transfertype_Pos) 
				|(DMA_InitStr->DMA_DestinationPeripheral <<DMA_ChannelConfig_DestPeripheral_Pos)
				|(DMA_InitStr->DMA_SourcePeripheral <<DMA_ChannelConfig_SrcPeripheral_Pos);
		
		DMAx->DMACC1Configuration = tmpval;
	}
}

/**
  *
  * @brief: 设置DMA通道使能。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  * @param: NewState,是否使能要设置的通道，ENABLE：使能通道，DISABLE:不使能通道。
  *	
  * @retVal: void
  */
void DMA_Channel_Enable(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,FunctionalState NewState)
{
	
	if(DMAChannel==DMA_Channel_0)
	{
		if( NewState != DISABLE)
		{
			DMAx->DMACC0Configuration |= DMA_Enable_Channel;
		}
		else
		{
			DMAx->DMACC0Configuration &= (~DMA_Enable_Channel);
		}
	}
	else//channel_1
	{
		if( NewState != DISABLE)
		{
			DMAx->DMACC1Configuration |= DMA_Enable_Channel;
		}
		else
		{
			DMAx->DMACC1Configuration &= (~DMA_Enable_Channel);
		}
	}
}

/**
  *
  * @brief: 设置DMA传输数据的个数。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  * @param: Tx_Size,传输数据的个数。
  *	
  * @retVal: void
  */
void DMA_TransferSize_Config(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,uint16_t TxSize)
{
	uint16_t size;
	
	assert_param(IS_DMA_Channel(DMAChannel));
	
	size = (TxSize&0x0fff);
	
	if(DMAChannel==DMA_Channel_0)
	{
		DMAx->DMACC0Control &= 0xfffff000;
		DMAx->DMACC0Control |= (size<<0);
	}
	else//channel_1
	{
		DMAx->DMACC1Control &= 0xfffff000;
		DMAx->DMACC1Control |= (size<<0);
	}
}


/**
  *
  * @brief: DMA中断配置。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  * @param: DMA_INT,DMA中断类型；可设置的值包括：DMA_INT_TC - DMA传输完成中断；DMA_INT_INTERR -DMA错误中断。
  * @param: NewState,是否使能对应的中断，ENABLE：使能，DISABLE:不使能。
  *	
  * @retVal: void
  */
void DMA_Interrupt_Config(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,uint32_t DMA_INT,FunctionalState NewState)
{
	assert_param(IS_DMA_Channel(DMAChannel));
	assert_param(IS_DMA_INT_TYPE(DMA_INT));
	
	
	if(DMAChannel==DMA_Channel_0)
	{
		if( NewState != DISABLE)
		{
			DMAx->DMACC0Configuration |= DMA_INT;
		}
		else
		{
			DMAx->DMACC0Configuration &= (~DMA_INT);
		}
	}
	else//channel_1
	{
		if( NewState != DISABLE)
		{
			DMAx->DMACC1Configuration |= DMA_INT;
		}
		else
		{
			DMAx->DMACC1Configuration &= (~DMA_INT);
		}
	}
}

/**
  *
  * @brief: 清除DMA中断标志。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  * @param: DMA_INT,DMA中断类型；可设置的值包括：DMA_INT_TC - DMA传输完成中断；DMA_INT_INTERR -DMA错误中断。
  *	
  * @retVal: void
  */
void DMA_Interrupt_Clear(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,uint32_t DMA_INT)
{
	assert_param(IS_DMA_Channel(DMAChannel));
	assert_param(IS_DMA_INT_TYPE(DMA_INT));
	
	if(DMAChannel==DMA_Channel_0)
	{
		if(DMA_INT ==DMA_INT_TC)
		{
			DMAx->DMACIntTCClear |= DMA_CH0_TC_INT_Clear;
		}
		else if(DMA_INT ==DMA_INT_INTERR)
		{
			DMAx->DMACIntErrClr |= DMA_CH0_INTErr_INT_Clear;
		}
	}
	else//channel_1
	{
		if(DMA_INT ==DMA_INT_TC)
		{
			DMAx->DMACIntTCClear |= DMA_CH1_TC_INT_Clear;
		}
		else if(DMA_INT ==DMA_INT_INTERR)
		{
			DMAx->DMACIntErrClr |= DMA_CH1_INTErr_INT_Clear;
		}
	}
}

/**
  *
  * @brief: 确认指定的DMA通道是否产生中断。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  *	
  * @retVal: bitStatus,获取到的状态，SET - 指定的通道有中断产生；RESET - 指定的通道没有中断产生。
  */
ITStatus DMA_Get_InterruptStatus(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel)
{
	ITStatus bitStatus = RESET;
	
	assert_param(IS_DMA_Channel(DMAChannel));
	
	if(DMAChannel==DMA_Channel_0)
	{
		if(DMAx->DMACIntStatus&0x01)
		{
			bitStatus = SET;
		}
		else
		{
			bitStatus = RESET;
		}
	}
	else//channel_1
	{
		if(DMAx->DMACIntStatus&0x02)
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

/**
  *
  * @brief: 获取指定通道的DMA传输完成中断状态。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  *	
  * @retVal: bitStatus,获取到的状态，SET - 指定的通道有DMA传输完成中断产生；RESET - 指定的通道没有DMA传输完成中断产生。
  */
ITStatus DMA_Get_TCInterruptStatus(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel)
{
	ITStatus bitStatus = RESET;
	
	assert_param(IS_DMA_Channel(DMAChannel));
	
	if(DMAChannel==DMA_Channel_0)
	{
		if(DMAx->DMACIntTCStatus&0x01)
		{
			bitStatus = SET;
		}
		else
		{
			bitStatus = RESET;
		}
	}
	else//channel_1
	{
		if(DMAx->DMACIntTCStatus&0x02)
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

/**
  *
  * @brief: 获取指定DMA通道的错误中断状态。
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  *	
  * @retVal: bitStatus,获取到的状态，SET - 指定的通道有错误中断产生；RESET - 指定的通道没有错误中断产生。
  */
ITStatus DMA_Get_ErrInterruptStatus(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel)
{
	ITStatus bitStatus = RESET;
	
	assert_param(IS_DMA_Channel(DMAChannel));
	
	if(DMAChannel==DMA_Channel_0)
	{
		if(DMAx->DMACIntErrorStatus&0x01)
		{
			bitStatus = SET;
		}
		else
		{
			bitStatus = RESET;
		}
	}
	else//channel_1
	{
		if(DMAx->DMACIntErrorStatus&0x02)
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


/**
  *
  * @brief: 读取屏蔽之前的DMA传输完成中断状态。
  * 
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  *
  * @retVal: RawIntTCStatus,读取到的DMA传输完成中断状态。
  */
uint32_t DMA_Raw_Interrupt_Terminal_Count_Status(DMA_TypeDef *DMAx)
{		
	uint32_t RawIntTCStatus;
	assert_param(IS_DMA_ALL_PERIPH(DMAx));
	
	RawIntTCStatus = DMAx->DMACRawIntTCStatus;
	return RawIntTCStatus;
}

/**
  *
  * @brief: 读取屏蔽之前的DMA错误中断状态。
  *
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * 
  * @retVal: RawIntErrorStatus,读取到的DMA错误中断状态。
  */
uint32_t DMA_Raw_Error_Interrupt_Status(DMA_TypeDef *DMAx)
{
	uint32_t RawIntErrorStatus;
	assert_param(IS_DMA_ALL_PERIPH(DMAx));
	
	RawIntErrorStatus = DMAx->DMACRawIntErrorStatus;
	return RawIntErrorStatus;
}

/**
  *
  * @brief: 等待DMA的传输通道空闲。
  *
  * @param: DMAx,STAR只有1组DMA,只能设置为STAR_DMA。
  * @param: DMAChannel,使用哪个通道；可设置的值包括：DMA_Channel_0(0x00) - 通道0；DMA_Channel_1(0x01) - 通道1。
  *
  * @retVal: void
  */
void DMA_Wait_Channel_Free(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel)
{
	uint32_t busy = 1;
	while(busy)
	{
		busy = (DMAx->DMACEnbldChns & (1 << DMAChannel));
	}
}

