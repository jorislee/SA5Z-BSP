#ifndef __STAR_DMA_H
#define __STAR_DMA_H

#ifdef __cplusplus 
extern "C" {
#endif

#include "STAR.h"
	
typedef struct
{	
	uint32_t	DMA_Source_Addr;		//源地址
	uint32_t	DMA_Destination_Addr;	//目的地址
	uint8_t		DMA_SourceAddr_Inc;		//源地址是否递增
	uint8_t 	DMA_DestinationAddr_Inc;//目的地址是否递增
	uint8_t		DMA_SourceDataWidth;		//源地址数据宽度
	uint8_t		DMA_DestinationDataWidth;	//目的地址数据宽度
	uint8_t		DMA_SourceBurstSize;		//源地址数据突发传输的数据个数
	uint8_t		DMA_DestinationBurstSize;	//源地址数据突发传输的数据个数
	uint8_t		DMA_Transfertype;			//传输类型
	uint8_t		DMA_DestinationPeripheral;	//目的地址外设
	uint8_t		DMA_SourcePeripheral;		//源地址外设
	uint8_t		DMA_TCInterruptEnable;		//TC中断使能
}DMA_InitTypedef;

typedef enum
{
    DMA_Channel_0 = 0,
    DMA_Channel_1
}DMA_Channel_TypeDef;

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == STAR_DMA)) 
	
#define IS_DMA_Channel(Channel) 	(((Channel) == DMA_Channel_0)||((Channel) == DMA_Channel_1) )

#define DMA_Enable_Channel 0x01ul


/////////////////////////DMAC Configuration Register//////////////////////////////////   															
typedef enum
{
    DMA_AHBMaster_Endianness_Little = 0,	//little-endian mode
    DMA_AHBMaster_Endianness_Big			//big-endian mode
}DMA_AHBMaster_Endianness_TypeDef;

typedef enum
{
    DMA_DMAC_Disable = 0,					//DMAC disable
    DMA_DMAC_Enable							//DMAC enable
}DMA_DMAC_Enable_TypeDef;

#define DMA_DMAC_Enable_Pos					0
#define DMA_AHBMaster_Endianness_Pos		1




/////////////////////////DMA Channel Control Registers////////////////////////////////// 

typedef enum
{
    DMA_Addr_Inc_Disable = 0,
    DMA_Addr_Inc_Enable
}DMA_AddrInc_TypeDef;

#define IS_DMA_ADDR_INC_TYPE(type) (((type) == DMA_Addr_Inc_Disable)||((type) == DMA_Addr_Inc_Enable) )

typedef enum
{
    DMA_DataWidth_Byte = 0,
    DMA_DataWidth_Halfword,
	DMA_DataWidth_Word
}DMA_DataWidth_TypeDef;

#define IS_DMA_DATA_WIDTH_TYPE(addrWidth) (((addrWidth) == DMA_DataWidth_Byte)||((addrWidth) == DMA_DataWidth_Halfword) 	\
													||((addrWidth) == DMA_DataWidth_Word))
													
													
													
typedef enum
{
    DMA_BurstSize_1 = 0,
    DMA_BurstSize_4,
	DMA_BurstSize_8,
	DMA_BurstSize_16,
	DMA_BurstSize_32,
	DMA_BurstSize_64,
	DMA_BurstSize_128,
	DMA_BurstSize_256
	
}DMA_BurstSize_TypeDef;

#define IS_DMA_BURST_SIZE_TYPE(brustSize) (((brustSize) == DMA_BurstSize_1)||((brustSize) == DMA_BurstSize_4) 	\
													||((brustSize) == DMA_BurstSize_8)||((brustSize) == DMA_BurstSize_16) 	\
														||((brustSize) == DMA_BurstSize_32)||((brustSize) == DMA_BurstSize_64) 	\
															||((brustSize) == DMA_BurstSize_128)||((brustSize) == DMA_BurstSize_256))


#define DMA_TC_INT_ENABLE	0x80000000	

typedef enum
{
    DMA_TC_INT_Disable = 0,
    DMA_TC_INT_Enable
}DMA_TC_INT_Enable_TypeDef;

#define IS_DMA_TC_INT_Enable_TypeDef(type) (((type) == DMA_TC_INT_Disable)||((type) == DMA_TC_INT_Enable) )

														
#define DMA_SourceBurstSize_Pos				12
#define DMA_DestinationBurstSize_Pos		15
#define DMA_SourceDataWidth_Pos				18
#define DMA_DestinationDataWidth_Pos		21
#define DMA_SourceAddr_Inc_Pos  			26
#define DMA_DestinationAddr_Inc_Pos  		27
#define DMA_TCInterruptEnable_Pos			31


/////////////////////////Channel Configuration Registers////////////////////////////////// 

typedef enum
{
    MtoM_DMA = 0,					//Memory-to-memory(Controller:DMA)
    MtoP_DMA,						//Memory-to-peripheral(Controller:DMA)
	PtoM_DMA,						//Peripheral-to-memory(Controller:DMA)
	SPtoDP_DMA,						//Source peripheral-to-destination peripheral(Controller:DMA)
	SPtoDP_DP,						//Source peripheral-to-destination peripheral(Controller:Destination peripheral)
	MtoP_P,							//Memory-to-peripheral(Controller:Peripheral)
	PtoM_P,							//Peripheral-to-memory(Controller:Peripheral)
	SPtoDP_SP						//Source peripheral-to-destination peripheral(Controller:Source peripheral)
}DMA_Transfertype_TypeDef;

#define IS_DMA_TRANSFER_TYPE(type) (((type) == MtoM_DMA)||((type) == MtoP_DMA) 	\
													||((type) == PtoM_DMA)||((type) == SPtoDP_DMA) 	\
														||((type) == SPtoDP_DP)||((type) == MtoP_P) 	\
															||((type) == PtoM_P)||((type) == SPtoDP_SP))


typedef enum
{
    DMA_Peripheral_Unused = 0,						//
    DMA_Peripheral_Reserve1,						//
	DMA_Peripheral_Reserve2,
	DMA_Peripheral_Reserve3,
	DMA_Peripheral_SPI0TX=4,
	DMA_Peripheral_SPI0RX,
	DMA_Peripheral_SPI1TX,
	DMA_Peripheral_SPI1RX
}DMA_Peripheral_TypeDef;

#define IS_DMA_PERIPHERAL_TYPE(type) (((type) == DMA_Peripheral_Unused)||((type) == DMA_Peripheral_SPI0TX) 	\
													||((type) == DMA_Peripheral_SPI0RX)||((type) == DMA_Peripheral_SPI1TX) 	\
														||((type) == DMA_Peripheral_SPI1RX))

#define DMA_ChannelConfig_SrcPeripheral_Pos		1
#define DMA_ChannelConfig_DestPeripheral_Pos	6

#define DMA_ChannelConfig_Transfertype_Pos	11	
#define DMA_ChannelConfig_Lock_Pos			16
#define DMA_ChannelConfig_Halt_Pos			18
 
//Terminal count interrupt
#define DMA_INT_TC		0x08000ul
//Interrupt error
#define DMA_INT_INTERR	0x04000ul

#define IS_DMA_INT_TYPE(INT) 	(((INT) == DMA_INT_TC)||((INT) == DMA_INT_INTERR))




															
/////////////////////////Others//////////////////////////////////    
#define DMA_CH0_TC_INT_Clear	0x01ul
#define DMA_CH1_TC_INT_Clear	0x02ul

#define DMA_CH0_INTErr_INT_Clear	0x01ul
#define DMA_CH1_INTErr_INT_Clear	0x02ul

//////////////////////////////////////////////////////////////////////////////////   	
void DMA_Init(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,DMA_InitTypedef *DMA_InitStr);
void DMA_Channel_Enable(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,FunctionalState NewState);
void DMA_TransferSize_Config(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,uint16_t TxSize);
void DMA_Interrupt_Config(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,uint32_t DMA_INT,FunctionalState NewState);
void DMA_Interrupt_Clear(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel,uint32_t DMA_INT);
ITStatus DMA_Get_InterruptStatus(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel);
ITStatus DMA_Get_TCInterruptStatus(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel);
ITStatus DMA_Get_ErrInterruptStatus(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel);
uint32_t DMA_Raw_Interrupt_Terminal_Count_Status(DMA_TypeDef *CM3DS_MPS2_DMAx);
uint32_t DMA_Raw_Error_Interrupt_Status(DMA_TypeDef *CM3DS_MPS2_DMAx);
void DMA_Wait_Channel_Free(DMA_TypeDef *DMAx,DMA_Channel_TypeDef DMAChannel);


#ifdef __cplusplus
}
#endif

#endif /* __STAR_DMA_H */
