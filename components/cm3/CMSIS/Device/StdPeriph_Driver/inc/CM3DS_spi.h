
#ifndef __CM3DS_SPI_H
#define __CM3DS_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "CM3DS_MPS2.h"


typedef struct
{
	
	uint16_t	SPI_ClkPreDiv;			//SPI时钟预分频系数，必须是2~254的偶数
	uint16_t	SPI_SCR;				//Serial clock rate，决定SPI时钟速率的因子系数，有效值0~255
	uint16_t	SPI_ClkPolarityPhase;	//SPI时钟极性及相位，取值参考 SPI_CLK_PL_PH_Type 的定义
	uint16_t	SPI_DataSize;  			//Data Size Select, 取值参考SPI_Data_Size_Type 的定义
	uint16_t  	SPI_TxRxTransmitMode; 	//TXRXSIMULT 收发传输模式，取值参考SPI_TxRxTransmit_Mode 的定义
	uint16_t	SPI_DataWidth;			//data width, 取值参考SPI_DataWidth_Type 的定义 
	uint16_t	SPI_Mode;				//Master or slave mode,  取值参考SPI_Mode_Type 的定义
	uint16_t	SPI_LoopBackMode;		//回环模式或正常串口运行，取值参考SPI_LoopBackMode_Type 的定义
		
}SPI_InitTypeDef; 

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == CM3DS_MPS2_SSP0)||((PERIPH) == CM3DS_MPS2_SSP1);	

/////////////////////////SSPCR0//////////////////////////////////
#define SPI_CR0_INIT_MASK		((uint16_t)0x0000)
#define SPI_CR1_INIT_MASK		((uint16_t)0x0000)
 
/** @defgroup SPI_Data_Size_Type 
  * @{
  */
#define SPI_Data_Size_4bit			((uint16_t)0x0003)
#define SPI_Data_Size_5bit			((uint16_t)0x0004)
#define SPI_Data_Size_6bit			((uint16_t)0x0005)
#define SPI_Data_Size_7bit			((uint16_t)0x0006)
#define SPI_Data_Size_8bit			((uint16_t)0x0007)
#define SPI_Data_Size_9bit 			((uint16_t)0x0008)
#define SPI_Data_Size_10bit			((uint16_t)0x0009)
#define SPI_Data_Size_11bit			((uint16_t)0x000a)
#define SPI_Data_Size_12bit			((uint16_t)0x000b)
#define SPI_Data_Size_13bit			((uint16_t)0x000c)
#define SPI_Data_Size_14bit			((uint16_t)0x000d)
#define SPI_Data_Size_15bit			((uint16_t)0x000e)
#define SPI_Data_Size_16bit			((uint16_t)0x000f)
#define IS_SPI_Data_Size(Size) 			( ((Size) ==  SPI_Data_Size_4bit )|| \
																			((Size) ==  SPI_Data_Size_5bit) || \
																			((Size) ==  SPI_Data_Size_6bit) || \
																			((Size) ==  SPI_Data_Size_7bit) || \
																			((Size) ==  SPI_Data_Size_8bit) || \
                                      ((Size) ==  SPI_Data_Size_9bit) || \
																			((Size) ==  SPI_Data_Size_10bit) || \
																			((Size) ==  SPI_Data_Size_11bit) || \
																			((Size) ==  SPI_Data_Size_12bit) || \
																			((Size) ==  SPI_Data_Size_13bit) || \
																			((Size) ==  SPI_Data_Size_14bit) || \
																			((Size) ==  SPI_Data_Size_15bit) || \
																			((Size) ==  SPI_Data_Size_16bit))

/**
  * @}
  */
  
  
/** @defgroup SPI_CLK_PL_PH_Type 
  * @{
  */	
//SSPCLKOUT phase and polarity	
#define SPI_CLK_PL_Low_PH_1Edge				((uint16_t)0x0000)	
#define SPI_CLK_PL_Hight_PH_1Edge			((uint16_t)0x0040)	
#define SPI_CLK_PL_Low_PH_2Edge				((uint16_t)0x0080)	
#define SPI_CLK_PL_Hight_PH_2Edge			((uint16_t)0x00C0)	

#define IS_SPI_CLK_PL_PH_Mode(Mode) 					(((Mode) ==  SPI_CLK_PL_Low_PH_1Edge) || \
																						((Mode) ==  SPI_CLK_PL_Hight_PH_1Edge) || \
																						((Mode) ==  SPI_CLK_PL_Low_PH_2Edge) || \
																						((Mode) ==  SPI_CLK_PL_Hight_PH_2Edge))
/**
  * @}
  */
  
#define IS_SPI_SCR(SCR) ((SCR>=0)&&(SCR<=255))
#define SPI_SCR_Pos		8

/////////////////////////SSPCR1//////////////////////////////////
#define SPI_ENABLE		(uint16_t)0x0002

/** @defgroup SPI_TxRxTransmit_Mode 
  * @{
  */
#define SPI_TxRxTransmit_TimeSharing			(0x0ul<<6)				//分时收发				
#define SPI_TxRxTransmit_Simultaneous			(0x1ul<<6)				//同时收发	
#define IS_SPI_TxRxTransmit_Mode(Mode)		(((Mode) ==  SPI_TxRxTransmit_TimeSharing) || \
																						 ((Mode) ==  SPI_TxRxTransmit_Simultaneous))

/**
  * @}
  */

/** @defgroup SPI_DataWidth_Type
  * @{
  */ 
#define SPI_DataWidth_Standard				(0x0ul<<4)			//标准SPI						
#define SPI_DataWidth_Dual					(0x1ul<<4)			//Dual SPI
#define SPI_DataWidth_Quad					(0x2ul<<4)			//Quad SPI
#define IS_SPI_DataWidth(Width)				(((Width) ==  SPI_DataWidth_Standard) || \
																						((Width) ==  SPI_DataWidth_Dual) || \
																							((Width) ==  SPI_DataWidth_Quad))	
/**
  * @}
  */

/** @defgroup SPI_Mode_Type
  * @{
  */ 
#define SPI_Mode_Master						(0x0ul<<2)
#define SPI_Mode_Slave						(0x1ul<<2)
#define IS_SPI_Mode(Mode)					(((Mode) ==  SPI_Mode_Master)||((Mode) ==  SPI_Mode_Slave))

/**
  * @}
  */

/** @defgroup SPI_LoopBackMode_Type
  * @{
  */ 							
#define SPI_LoopBackMode_Disable			(0x0ul<<0)								
#define SPI_LoopBackMode_Enable				(0x1ul<<0)	
#define IS_SPI_LoopBackMode(Mode)							( ((Mode) ==  SPI_LoopBackMode_Disable) || \
																						((Mode) ==  SPI_LoopBackMode_Enable))							
										
/**
  * @}
  */
  

#define SPI_CLK_250Prescale									((uint16_t)0x00fa)	 
#define SPI_CLK_200Prescale									((uint16_t)0x00c8)	 
#define SPI_CLK_100Prescale									((uint16_t)0x0064)	 
#define SPI_CLK_50Prescale									((uint16_t)0x0032)   
#define SPI_CLK_20Prescale									((uint16_t)0x0014)   
#define SPI_CLK_12Prescale									((uint16_t)0x000c)   
#define SPI_CLK_10Prescale								  	((uint16_t)0x000a)
#define SPI_CLK_8Prescale								  	((uint16_t)0x0008)
#define SPI_CLK_6Prescale								  	((uint16_t)0x0006)   
#define SPI_CLK_4Prescale									((uint16_t)0x0004)	 
#define SPI_CLK_2Prescale								    ((uint16_t)0x0002)

#define SPI_SCR_0              										((uint16_t)0x0000)		
#define SPI_SCR_2              										((uint16_t)0x0200)		
#define SPI_SCR_4              										((uint16_t)0x0400)	
#define SPI_SCR_8              										((uint16_t)0x0500)	
#define SPI_SCR_10              									((uint16_t)0x0a00)	
#define SPI_SCR_16              									((uint16_t)0x1000)	
#define SPI_SCR_32              									((uint16_t)0x2000)	


/////////////////////////SSPCPSR//////////////////////////////////

#define IS_SPI_CLK_PRE_DIV(DIV)	((DIV%2)==0)


/////////////////////////SSPSR//////////////////////////////////

#define SPI_STATUS_TX_BSY				0x20
#define SPI_STATUS_SPI_BSY				0x10
#define SPI_STATUS_RXFIFO_FULL			0x08
#define SPI_STATUS_RXFIFO_NOT_EMPTY		0x04
#define SPI_STATUS_TXFIFO_NOT_FULL		0x02
#define SPI_STATUS_TXFIFO_EMPTY			0x01


/////////////////////////SSPIMSC //////////////////////////////////
#define SPI_INT_RX_AMFULLL				((uint16_t)0x0010)
#define SPI_INT_TX						((uint16_t)0x0008)
#define SPI_INT_RX						((uint16_t)0x0004)
#define SPI_INT_RX_TIMEOUT				((uint16_t)0x0002)
#define SPI_INT_RX_OVR					((uint16_t)0x0001)
#define IS_SPI_INT_TYPE(SPI_IT) 			( ((SPI_IT) == SPI_INT_RX_AMFULLL) || \
	                                			((SPI_IT) == SPI_INT_TX)  || \
	                                			((SPI_IT) == SPI_INT_RX)  || \
	                                			((SPI_IT) == SPI_INT_RX_TIMEOUT)  || \
	                                			((SPI_IT) == SPI_INT_RX_OVR))

/////////////////////////SSPDMACR //////////////////////////////////
#define SPI_DMA_TX_ENABLE		((uint16_t)0x0002)
#define SPI_DMA_RX_ENABLE		((uint16_t)0x0001)
#define IS_SPI_DMA_TXRX_TYPE(DMA_TXRX) 			( ((DMA_TXRX) == SPI_DMA_TX_ENABLE) || \
														((DMA_TXRX) == SPI_DMA_RX_ENABLE))



void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);
FlagStatus SPI_StatusFlag_Get(SPI_TypeDef* SPIx,uint8_t flag);
void SPI_ReceiveDataNum_Config(SPI_TypeDef* SPIx, uint32_t RxNum);
void SPI_Interrupt_Config(SPI_TypeDef* SPIx, uint16_t SPI_INT, FunctionalState NewState);
ITStatus SPI_Interrupt_StatusFlag_Get(SPI_TypeDef* SPIx,uint16_t SPI_INT);
void SPI_Interrupt_Clear(SPI_TypeDef* SPIx, uint16_t SPI_INT);
void SPI_DMA_Cmd(SPI_TypeDef* SPIx,uint16_t SPI_DMA_TxRx,FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_SPI_H */
															

