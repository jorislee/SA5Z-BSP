#include <stdio.h> 
#include <string.h>

#include "CM3DS_gpio.h"
#include "CM3DS_spi.h"
#include "CM3DS_dma.h"
#include "CM3DS_rcc.h"
#include "CM3DS_uart.h"	

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "xs_flash.h"

static SemaphoreHandle_t dma_read_sem = NULL;
static SemaphoreHandle_t dma_write_sem = NULL;

/*SPI管脚初始化*/
static void SPI_PinInit(SPI_TypeDef* spix)
{
	if(spix ==CM3DS_MPS2_SPI0) {
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI0_CLK,     ENABLE); //GPIO[7]  CLK_OUT   
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI0_SEL,     ENABLE); //GPIO[8]	CS_n      
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI0_DATA0,   ENABLE); //GPIO[9]	MOSI	    
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI0_DATA1,   ENABLE); //GPIO[10]	MISO      
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI0_DATA2,   ENABLE); //GPIO[17] WPn       
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI0_DATA3,   ENABLE); //GPIO[18]	HOLDn     
	} else {
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI1_CLK, 	ENABLE); //GPIO[11]  CLK_OUT   
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI1_SEL, 	ENABLE); //GPIO[12]	CS_n      
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI1_DATA0,   ENABLE); //GPIO[13]	MOSI	    
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI1_DATA1,   ENABLE); //GPIO[14]	MISO      
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI1_DATA2,   ENABLE); //GPIO[19] WPn       
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_SPI1_DATA3,   ENABLE); //GPIO[20]	HOLDn     
	}
}

static void SPI_WriteByte(SPI_TypeDef* spix,uint8_t data)
{
	SPI_SendData(spix, data);
}

static uint8_t SPI_ReadByte(SPI_TypeDef* spix)
{
	while (SPI_StatusFlag_Get(spix, SPI_STATUS_RXFIFO_NOT_EMPTY) == RESET);
	return SPI_ReceiveData(spix);
}

static void SPI_WaitSendFinish(SPI_TypeDef* spix)
{
	while(SPI_StatusFlag_Get(spix,SPI_STATUS_TX_BSY)){
		vTaskDelay(1);
	}
}

/*Flash 写使能*/
static void Flash_WriterEnable(void)
{	
	SPI_SendData(CM3DS_MPS2_SPI0, W25Q_WRITE_EN);// Write Enable
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
	SPI_WaitSendFinish(CM3DS_MPS2_SPI0);
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
}

static void Flash_WaitBusyEnd(void)
{
	uint8_t dat;
	do{
		SPI_ReceiveDataNum_Config(CM3DS_MPS2_SPI0, 1);
		SPI_SendData(CM3DS_MPS2_SPI0, W25Q_READ_SR0);
		SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
		SPI_WaitSendFinish(CM3DS_MPS2_SPI0);
		dat = SPI_ReadByte(CM3DS_MPS2_SPI0);
		SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
	}while((dat & 0x0001) == 0x0001); //等待FLASH的状态寄存器1的BUSY位为0
}

static void _flash_erase(uint32_t addr)
{	
	SPI_SendData(CM3DS_MPS2_SPI0, W25Q_SECTOR_ERASE);// 4KB Sector Erase
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF0000)>>16);
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF00)>>8);
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF));
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
	SPI_WaitSendFinish(CM3DS_MPS2_SPI0);
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
}

static void _flash_erase_chip(void)
{
	SPI_WriteByte(CM3DS_MPS2_SPI0, W25Q_ALL_ERASE);// Write Enable
	SPI_Cmd( CM3DS_MPS2_SPI0, ENABLE);
	SPI_WaitSendFinish(CM3DS_MPS2_SPI0);
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
}

static void _flash_page_write(uint8_t* wrBuf,uint32_t addr,uint16_t num)
{	
	int i;
	SPI_SendData(CM3DS_MPS2_SPI0, W25Q_PAGE_PRG);// Page Write
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF0000)>>16);
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF00)>>8);	 
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF));
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);	

	for(i=0;i<num;i++)
	{
		SPI_SendData(CM3DS_MPS2_SPI0, *wrBuf);
		while(SPI_StatusFlag_Get(CM3DS_MPS2_SPI0,SPI_STATUS_TXFIFO_NOT_FULL)==RESET);
		wrBuf++;
	}
	SPI_WaitSendFinish(CM3DS_MPS2_SPI0);
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
}

uint32_t xs_flash_id(void)
{
	uint8_t MID,ID1,ID2;
	SPI_ReceiveDataNum_Config(CM3DS_MPS2_SPI0, 0x0000003);
	SPI_WriteByte(CM3DS_MPS2_SPI0, W25Q_READ_ID);
	SPI_Cmd(CM3DS_MPS2_SPI0,ENABLE);

	MID = SPI_ReadByte(CM3DS_MPS2_SPI0);
	ID1 = SPI_ReadByte(CM3DS_MPS2_SPI0);
	ID2 = SPI_ReadByte(CM3DS_MPS2_SPI0);
	SPI_Cmd(CM3DS_MPS2_SPI0,DISABLE);

	return (MID<<16)|(ID1<<8)|ID2;
}

void xs_flash_init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_PinInit(CM3DS_MPS2_SPI0);
	SPI_DeInit(CM3DS_MPS2_SPI0);
	SPI_InitStructure.SPI_ClkPreDiv = SPI_CLK_2Prescale;				    //时钟预分频
	SPI_InitStructure.SPI_SCR = 0;										    //时钟速率因子
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						    //主从模式
	SPI_InitStructure.SPI_DataSize = SPI_Data_Size_8bit;				    //数据位数
	SPI_InitStructure.SPI_LoopBackMode = SPI_LoopBackMode_Disable;		    //是否自环
	SPI_InitStructure.SPI_ClkPolarityPhase = SPI_CLK_PL_Low_PH_1Edge;		//工作模式
	SPI_InitStructure.SPI_TxRxTransmitMode = SPI_TxRxTransmit_TimeSharing;	//收发分时
	SPI_InitStructure.SPI_DataWidth = SPI_DataWidth_Standard;				//数据宽度
	SPI_Init(CM3DS_MPS2_SPI0, &SPI_InitStructure);
}

void xs_flash_erase(uint32_t addr)
{	
	Flash_WriterEnable();
	_flash_erase(addr);
	Flash_WaitBusyEnd();
}

void xs_flash_erase_chip(void)
{		
	Flash_WriterEnable();
	_flash_erase_chip();
	Flash_WaitBusyEnd();
}

void xs_flash_page_write(uint32_t addr, uint8_t* buf, uint16_t size)
{	
	Flash_WriterEnable();
	_flash_page_write(buf, addr, size);
	Flash_WaitBusyEnd();
}

/*Flash页读*/
void xs_flash_page_read(uint32_t addr, uint8_t* buf, uint16_t size)
{
	int i=0;
	SPI_ReceiveDataNum_Config(CM3DS_MPS2_SPI0, size);
	SPI_SendData(CM3DS_MPS2_SPI0, W25Q_READ);				//Read Data Order  0x03  ×2：0x3b  ×4：0x6b
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF0000)>>16);	//Read Data Addr:high
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF00)>>8);		//Read Data	Addr:middle
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF));			//Read Data Addr:low
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
	SPI_WaitSendFinish(CM3DS_MPS2_SPI0);
	
	for(i=0;i<size;i++)
	{
		*buf = SPI_ReadByte(CM3DS_MPS2_SPI0);
		buf ++;
	}
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
}

void xs_flash_read(uint32_t addr, uint8_t* buf, uint16_t len)
{
	xs_flash_page_read(addr, buf, len);
}

void xs_flash_write(uint32_t addr, uint8_t* buf, uint16_t len)
{
    uint32_t page_size;
    uint32_t pgm_len, pgm_num;
    uint8_t i;

    page_size = FLASH_PAGE_SIZE;
    pgm_len = page_size - (addr % page_size);

    if (len < pgm_len) {
		xs_flash_page_write(addr, buf, len);
    } else {
        xs_flash_page_write(addr, buf, pgm_len);
        pgm_num = (len - pgm_len) / page_size;
        for (i = 0; i < pgm_num; i++) {
			xs_flash_page_write(addr + pgm_len, buf + pgm_len, page_size);
            pgm_len += page_size;
        }
		if(len - pgm_len > 0){
			xs_flash_page_write( addr + pgm_len, buf + pgm_len, len - pgm_len);
		}
    }
}

/*DMA计数中断服务函数*/
void DMACINTTC_Handler(void)
{
	ITStatus state;
	
	state=DMA_Get_TCInterruptStatus(CM3DS_MPS2_DMA,DMA_Channel_0);
	if(state==SET){
		DMA_Interrupt_Clear(CM3DS_MPS2_DMA,DMA_Channel_0,DMA_INT_TC);
		DMA_Channel_Enable(CM3DS_MPS2_DMA,DMA_Channel_0,DISABLE);
		BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(dma_read_sem, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	state=DMA_Get_TCInterruptStatus(CM3DS_MPS2_DMA,DMA_Channel_1);
	if(state==SET) {
		DMA_Interrupt_Clear(CM3DS_MPS2_DMA,DMA_Channel_1,DMA_INT_TC);
		DMA_Channel_Enable(CM3DS_MPS2_DMA,DMA_Channel_1,DISABLE);
		BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(dma_write_sem, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

void xs_flash_dma_init(void)
{
	SPI_DMA_Cmd(CM3DS_MPS2_SPI0, SPI_DMA_TX_ENABLE, ENABLE);
	SPI_DMA_Cmd(CM3DS_MPS2_SPI0, SPI_DMA_RX_ENABLE, ENABLE);

	#if configSUPPORT_STATIC_ALLOCATION == 1
	dma_read_sem = xSemaphoreCreateBinaryStatic(&dma_read_sem_buffer);
	dma_write_sem = xSemaphoreCreateBinaryStatic(&dma_write_sem_buffer);
	#else
	dma_read_sem = xSemaphoreCreateBinary();
	dma_write_sem = xSemaphoreCreateBinary();
	#endif

	NVIC_ClearPendingIRQ(DMACINTTC);
	NVIC_EnableIRQ(DMACINTTC);
}

void xs_flash_dma_page_read(uint32_t addr, uint8_t* buf, uint16_t len)
{
	static uint8_t Page_buf[FLASH_PAGE_SIZE] = {0};
	taskENTER_CRITICAL();
	SPI_ReceiveDataNum_Config(CM3DS_MPS2_SPI0, len);
	SPI_SendData(CM3DS_MPS2_SPI0, W25Q_READ);				//Read Data Order  0x03  ×2：0x3b  ×4：0x6b
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF0000)>>16);	//Read Data Addr:high
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF00)>>8);		//Read Data	Addr:middle
	SPI_SendData(CM3DS_MPS2_SPI0, (addr & 0xFF));			//Read Data Addr:low
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
   	DMA_InitTypedef DMA_InitStr;
	DMA_InitStr.DMA_Source_Addr = 0x4000B008; 	//SPI0 Data Reg Addr
	DMA_InitStr.DMA_Destination_Addr = (uint32_t)&Page_buf;
	DMA_InitStr.DMA_SourceAddr_Inc = DMA_Addr_Inc_Disable;
	DMA_InitStr.DMA_DestinationAddr_Inc = DMA_Addr_Inc_Enable;
	DMA_InitStr.DMA_SourceDataWidth = DMA_DataWidth_Byte;
	DMA_InitStr.DMA_DestinationDataWidth = DMA_DataWidth_Byte;
	DMA_InitStr.DMA_SourceBurstSize = DMA_BurstSize_1;
	DMA_InitStr.DMA_DestinationBurstSize = DMA_BurstSize_1;
	DMA_InitStr.DMA_Transfertype = PtoM_DMA;					//DMA传输类型 外设到内存
	DMA_InitStr.DMA_DestinationPeripheral = DMA_Peripheral_Unused; 
	DMA_InitStr.DMA_SourcePeripheral = DMA_Peripheral_SPI0RX;
	DMA_InitStr.DMA_TCInterruptEnable = DMA_TC_INT_Enable;		//使能DMA传输完成中断
	DMA_Init(CM3DS_MPS2_DMA,DMA_Channel_0,&DMA_InitStr);
	DMA_TransferSize_Config(CM3DS_MPS2_DMA,DMA_Channel_0, len);
	DMA_Interrupt_Config(CM3DS_MPS2_DMA,DMA_Channel_0,DMA_INT_TC,ENABLE);
	DMA_Channel_Enable(CM3DS_MPS2_DMA,DMA_Channel_0,ENABLE);
	taskEXIT_CRITICAL();

	if (xSemaphoreTake(dma_read_sem, portMAX_DELAY) != pdTRUE) {
		printf("dma_read_sem take failed\n");
	}
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
	memcpy(buf, Page_buf, len);
}


void xs_flash_dma_page_write(uint32_t addr, uint8_t* buf, uint16_t len)
{
	Flash_WriterEnable();

	static uint8_t Page_buf[FLASH_HDR_SIZE + FLASH_PAGE_SIZE] = {0};
	Page_buf[0] = W25Q_PAGE_PRG;
	Page_buf[1] = (addr & 0xFF0000)>>16;
	Page_buf[2] = (addr & 0xFF00)>>8;
	Page_buf[3] = (addr & 0xFF);
	memcpy(Page_buf + FLASH_HDR_SIZE, buf, len);
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
	DMA_InitTypedef DMA_InitStr;
	DMA_InitStr.DMA_Source_Addr = (uint32_t)&Page_buf;
	DMA_InitStr.DMA_Destination_Addr = 0x4000B008;					//SPI0 Data Reg Addr
	DMA_InitStr.DMA_SourceAddr_Inc = DMA_Addr_Inc_Enable;
	DMA_InitStr.DMA_DestinationAddr_Inc = DMA_Addr_Inc_Disable;
	DMA_InitStr.DMA_SourceDataWidth = DMA_DataWidth_Byte;
	DMA_InitStr.DMA_DestinationDataWidth = DMA_DataWidth_Byte;
	DMA_InitStr.DMA_SourceBurstSize = DMA_BurstSize_1;
	DMA_InitStr.DMA_DestinationBurstSize = DMA_BurstSize_1;
	DMA_InitStr.DMA_Transfertype = MtoP_DMA;					    //DMA传输类型 内存到外设
	DMA_InitStr.DMA_DestinationPeripheral = DMA_Peripheral_SPI0TX;
	DMA_InitStr.DMA_SourcePeripheral = DMA_Peripheral_Unused;
	DMA_InitStr.DMA_TCInterruptEnable = DMA_TC_INT_Enable;			//使能DMA传输完成中断
	DMA_Init(CM3DS_MPS2_DMA, DMA_Channel_1, &DMA_InitStr);
	
	DMA_TransferSize_Config(CM3DS_MPS2_DMA, DMA_Channel_1, FLASH_HDR_SIZE + len);
	DMA_Interrupt_Config(CM3DS_MPS2_DMA, DMA_Channel_1, DMA_INT_TC, ENABLE);
	DMA_Channel_Enable(CM3DS_MPS2_DMA, DMA_Channel_1, ENABLE);

	if (xSemaphoreTake(dma_write_sem, portMAX_DELAY) != pdTRUE) {
		printf("dma_write_sem take failed\n");
	}
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
	Flash_WaitBusyEnd();
}

void xs_flash_dma_read(uint32_t addr, uint8_t* buf, uint16_t len)
{
    uint32_t page_size;
    uint32_t pgm_len, pgm_num;
    uint8_t i;

    page_size = FLASH_PAGE_SIZE;
    pgm_len = page_size - (addr % page_size);

    if (len < pgm_len) {
		xs_flash_dma_page_read(addr, buf, len);
    } else {
        xs_flash_dma_page_read(addr, buf, pgm_len);
        pgm_num = (len - pgm_len) / page_size;
        for (i = 0; i < pgm_num; i++) {
			xs_flash_dma_page_read(addr + pgm_len, buf + pgm_len, page_size);
            pgm_len += page_size;
        }
		if(len - pgm_len > 0){
			xs_flash_dma_page_read(addr + pgm_len, buf + pgm_len, len - pgm_len);
		}
    }
}

void xs_flash_dma_write(uint32_t addr, uint8_t* buf, uint16_t len)
{
    uint32_t page_size;
    uint32_t pgm_len, pgm_num;
    uint8_t i;

    page_size = FLASH_PAGE_SIZE;
    pgm_len = page_size - (addr % page_size);

    if (len < pgm_len) {
		xs_flash_dma_page_write(addr, buf, len);
    } else {
        xs_flash_dma_page_write(addr, buf, pgm_len);
        pgm_num = (len - pgm_len) / page_size;
        for (i = 0; i < pgm_num; i++) {
			xs_flash_dma_page_write(addr + pgm_len, buf + pgm_len, page_size);
            pgm_len += page_size;
        }
		if(len - pgm_len > 0){
			xs_flash_dma_page_write( addr + pgm_len, buf + pgm_len, len - pgm_len);
		}
    }
}

void xs_flash_dma_erase(uint32_t addr)
{
	Flash_WriterEnable();
	static uint8_t Sector_buf[FLASH_HDR_SIZE] = {0};
	Sector_buf[0] = W25Q_SECTOR_ERASE;
	Sector_buf[1] = (addr & 0xFF0000)>>16;
	Sector_buf[2] = (addr & 0xFF00)>>8;
	Sector_buf[3] = (addr & 0xFF);
	SPI_Cmd(CM3DS_MPS2_SPI0, ENABLE);
	DMA_InitTypedef DMA_InitStr;
	DMA_InitStr.DMA_Source_Addr = (uint32_t)&Sector_buf;
	DMA_InitStr.DMA_Destination_Addr = 0x4000B008;					//SPI0 Data Reg Addr
	DMA_InitStr.DMA_SourceAddr_Inc = DMA_Addr_Inc_Enable;
	DMA_InitStr.DMA_DestinationAddr_Inc = DMA_Addr_Inc_Disable;
	DMA_InitStr.DMA_SourceDataWidth = DMA_DataWidth_Byte;
	DMA_InitStr.DMA_DestinationDataWidth = DMA_DataWidth_Byte;
	DMA_InitStr.DMA_SourceBurstSize = DMA_BurstSize_1;
	DMA_InitStr.DMA_DestinationBurstSize = DMA_BurstSize_1;
	DMA_InitStr.DMA_Transfertype = MtoP_DMA;					    //DMA传输类型 内存到外设
	DMA_InitStr.DMA_DestinationPeripheral = DMA_Peripheral_SPI0TX;
	DMA_InitStr.DMA_SourcePeripheral = DMA_Peripheral_Unused;
	DMA_InitStr.DMA_TCInterruptEnable = DMA_TC_INT_Enable;			//使能DMA传输完成中断
	DMA_Init(CM3DS_MPS2_DMA, DMA_Channel_1, &DMA_InitStr);
	
	DMA_TransferSize_Config(CM3DS_MPS2_DMA, DMA_Channel_1, FLASH_HDR_SIZE);
	DMA_Interrupt_Config(CM3DS_MPS2_DMA, DMA_Channel_1, DMA_INT_TC, ENABLE);
	DMA_Channel_Enable(CM3DS_MPS2_DMA, DMA_Channel_1, ENABLE);
	if (xSemaphoreTake(dma_write_sem, portMAX_DELAY) != pdTRUE) {
		printf("dma_write_sem take failed\n");
	}
	SPI_Cmd(CM3DS_MPS2_SPI0, DISABLE);
	Flash_WaitBusyEnd();
}
