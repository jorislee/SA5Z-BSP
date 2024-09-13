#include  "CM3DS_rcc.h"
#include "CM3DS_spi.h"
#include "CM3DS_MPS2.h"
#include "CM3DS_gpio.h"



/**
  *
  * @brief: 将SPI初始化为默认配置。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * 
  * @retVal: void
  */
void SPI_DeInit(SPI_TypeDef* SPIx)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	if (SPIx == CM3DS_MPS2_SPI0)
	{
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_SPI0, ENABLE);
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_SPI0, DISABLE);
	}
	else if(SPIx == CM3DS_MPS2_SPI1)
	{
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_SPI1, ENABLE);
		RCC_APBPeriphReset_Ctr(RCC_APBPeriph_SPI1, DISABLE);
	}
}

/**
  *
  * @brief: SPI初始化配置。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: SPI_InitStruct,SPI设置参数结构体变量，该结构体的成员变量包括传输数据的大小、SPI 工作模式、
  *								时钟分频系数、传输方式（分时或同时）、数据宽度、为回环模式或正常传输。
  * 
  * @retVal: void
  */

void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef *SPI_InitStruct)
{	
	uint16_t tmpval;
	
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_CLK_PRE_DIV(SPI_InitStruct->SPI_ClkPreDiv));
	assert_param(IS_SPI_SCR(SPI_InitStruct->SPI_SCR));
	assert_param(IS_SPI_CLK_PL_PH_Mode(SPI_InitStruct->SPI_ClkPolarityPhase));
	assert_param(IS_SPI_Data_Size(SPI_InitStruct->SPI_DataSize));
	assert_param(IS_SPI_TxRxTransmit_Mode(SPI_InitStruct->SPI_TxRxTransmitMode));
	assert_param(IS_SPI_DataWidth(SPI_InitStruct->SPI_DataWidth));
	assert_param(IS_SPI_Mode(SPI_InitStruct->SPI_Mode));
	assert_param(IS_SPI_LoopBackMode(SPI_InitStruct->SPI_LoopBackMode));	
	
	tmpval = SPIx->CR0;
	tmpval &= SPI_CR0_INIT_MASK;
	tmpval |= (uint16_t)(((uint16_t)SPI_InitStruct->SPI_SCR<<SPI_SCR_Pos)
				|(SPI_InitStruct->SPI_ClkPolarityPhase)
						|(0x000F & (SPI_InitStruct->SPI_DataSize)));
	SPIx->CR0 = tmpval;
	
	tmpval = SPIx->CR1;
	tmpval &= SPI_CR1_INIT_MASK;
	
	tmpval |= (uint16_t)(SPI_InitStruct->SPI_TxRxTransmitMode)
					|(SPI_InitStruct->SPI_DataWidth)
					|(SPI_InitStruct->SPI_Mode)|(SPI_InitStruct->SPI_LoopBackMode);									
	SPIx->CR1 = tmpval;
	
	SPIx->CPSR = SPI_InitStruct->SPI_ClkPreDiv;
}

/**
  *
  * @brief: 设置SPI是否使能。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: NewState,是否使能SPI，ENABLE - 使能； DISABLE - 不使能。
  * 
  * @retVal: void
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
		
	if (NewState != DISABLE)
	{
		SPIx-> CR1 |= SPI_ENABLE;	
	}
	else
	{
		SPIx-> CR1 &= (~SPI_ENABLE);
	}
}

/**
  *
  * @brief: 使用SPI发送数据。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: Data,需要发送的数据。
  * 
  * @retVal: void
  */
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->DR = Data;
}

/**
  *
  * @brief: SPI接收数据。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * 
  * @retVal: 接收到的数据。
  */
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));

	return (uint16_t)SPIx->DR;
	
}

/**
  *
  * @brief: 确认SPI指定状态是否发生。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: flag, 要获取的状态类型，可设置的值包括:
  *						SPI_STATUS_TX_BSY - SPI 发送忙; 
  *						SPI_STATUS_SPI_BSY - SPI忙;	
  *						SPI_STATUS_RXFIFO_FULL - SPI接收FIFO满;	SPI_STATUS_RXFIFO_NOT_EMPTY - SPI 接收FIFO非空；
  *						SPI_STATUS_TXFIFO_NOT_FULL - SPI发送FIFO非满;	SPI_STATUS_TXFIFO_EMPTY - SPI发送FIFO空；
  * 
  * @retVal: 获取到的状态，SET - 指定状态已发生；RESET - 指定状态未发生。
  */
FlagStatus SPI_StatusFlag_Get(SPI_TypeDef* SPIx,uint8_t flag)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	
	if(SPIx->SR & flag)
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
  * @brief: 设置SPI接收数据个数。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: RxNum,需要接收数据的个数。
  * 
  * @retVal: void
  */
void SPI_ReceiveDataNum_Config(SPI_TypeDef* SPIx, uint32_t RxNum)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx-> rx_cnt_lsb =  (RxNum&0xffff);
	SPIx-> rx_cnt_msb =  (RxNum>>16);
}

/**
  *
  * @brief: SPI中断设置。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: SPI_INT,SPI中断类型，可设置的值包括：
  *					SPI_INT_RX_OVR - 接收溢出中断； SPI_INT_RX_TIMEOUT - 接收超时中断；
  *					SPI_INT_RX - 接收FIFO中断(接收FIFO半满或更少条件中断)；	SPI_INT_TX - 发送FIFO中断(发送FIFO半空或更少条件中断)；
  *					SPI_INT_RX_AMFULL - 接收FIFO几乎满条件中断。
  * @param: NewState,是否使能中断；ENABLE - 使能中断；DISABLE - 不使能中断。
  * 
  * @retVal: void
  */
void SPI_Interrupt_Config(SPI_TypeDef* SPIx, uint16_t SPI_INT, FunctionalState NewState)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_INT_TYPE(SPI_INT));
	
	if (NewState != DISABLE)
	{
		SPIx->IMSC |= SPI_INT;	
	}
	else
	{
		SPIx->IMSC &= ~SPI_INT;
	}
}

/**
  *
  * @brief: 获取SPI指定的中断状态。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: SPI_INT,SPI中断类型，可设置的值包括：
  *					SPI_INT_RX_OVR - 接收溢出中断； SPI_INT_RX_TIMEOUT - 接收超时中断；
  *					SPI_INT_RX - 接收FIFO中断(接收FIFO半满或更少条件中断)；	SPI_INT_TX - 发送FIFO中断(发送FIFO半空或更少条件中断)；
  *					SPI_INT_RX_AMFULL - 接收FIFO几乎满条件中断。。
  * 
  * @retVal: 获取到的状态，SET - 发生了指定的中断；RESET - 未发生指定的中断。
  */
ITStatus SPI_Interrupt_StatusFlag_Get(SPI_TypeDef* SPIx,uint16_t SPI_INT)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_INT_TYPE(SPI_INT));
	
	if(SPIx->MIS & SPI_INT)
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
  * @brief: 清除SPI中断。
  *
  * @param: SPIx,使用哪组SPI；CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: SPI_INT,中断类型，可设置的值包括：
  *						SPI_INT_RX_OVR - 接收溢出中断； SPI_INT_RX_TIMEOUT - 接收超时中断。
  * 
  * @retVal: void
  */
void SPI_Interrupt_Clear(SPI_TypeDef* SPIx, uint16_t SPI_INT)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_INT_TYPE(SPI_INT));
	
	SPIx->ICR |= (uint16_t)(SPI_INT&0x0003);
}


/**
  *
  * @brief: SPI DMA使能设置。
  *
  * @param: SPIx,使用哪组SPI;CM3有2组SPI:CM3DS_MPS2_SPI0和CM3DS_MPS2_SPI1。
  * @param: SPI_DMA_TxRx,需要使能DMA的是SPI发送还是SPI接收，可设置的值包括： 
  *						SPI_DMA_TX_ENABLE - SPI发送DMA使能；SPI_DMA_RX_ENABLE - SPI接收DMA使能。
  * @param: NewState,是否使能DMA；可设置的值包括：ENABLE- 使能；DISABLE- 不使能。
  *	
  * @retVal: void
  */
void SPI_DMA_Cmd(SPI_TypeDef* SPIx,uint16_t SPI_DMA_TxRx,FunctionalState NewState)
{
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_DMA_TXRX_TYPE(SPI_DMA_TxRx));
	
	if(NewState != DISABLE)
	{
		SPIx->DMACR |= SPI_DMA_TxRx;
	}
	else
	{
		SPIx->DMACR &= (uint16_t)(~SPI_DMA_TxRx);
	}
}

