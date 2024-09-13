#ifndef __CM3DS_DUALTIMER_H
#define __CM3DS_DUALTIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "CM3DS_MPS2.h"

typedef struct
{
	uint8_t 	DTIM_Mode;				//工作模式，取值参考 DTIM_Mode_Type
	uint8_t 	DTIM_InterruptEnable;	//是否开启中断，取值参考 DTIM_Interrupt_Enable_Type
	uint8_t 	DTIM_ClkDiv;			//工作时钟预分频系数，取值参考 DTIM_ClkDiv_Type
	uint8_t 	DTIM_CounterSize;		//计数器大小，取值参考 DTIM_CounterSize_Type
	uint32_t 	DTIM_LoadVal;			//计数器初始加载值
    
} DTIM_InitTypeDef;
	 
	 
	 
#define IS_DUALTIMER_ALL_PERIPH(PERIPH) (((PERIPH) == CM3DS_MPS2_DUALTIMER0));	

/** @defgroup DTIM_Mode_Type
  * @{
  */ 	
#define DTIM_Mode_OneShot					((uint8_t)0x01)
#define DTIM_Mode_FreeRunning				((uint8_t)0x00)
#define DTIM_Mode_Periodic					((uint8_t)0x40)
#define IS_DTIM_MODE(MODE) 	(((MODE) == DTIM_Mode_OneShot) || \
																   ((MODE) == DTIM_Mode_FreeRunning) || \
																	(( MODE) == DTIM_Mode_Periodic))	  
																	
/**
  * @}
  */

/** @defgroup DTIM_Interrupt_Enable_Type
  * @{
  */ 	
#define DTIM_Interrupt_Enable					((uint8_t)0x20)
#define DTIM_Interrupt_Disable					((uint8_t)0x00)
#define IS_DTIM_INT_ENABLE(ISENABLE) 	(((ISENABLE) == DTIM_Interrupt_Enable) || \
																   ((ISENABLE) == DTIM_Interrupt_Disable))  
																	
/**
  * @}
  */
  

/** @defgroup DTIM_ClkDiv_Type
  * @{
  */
#define DTIM_ClkDiv_1						((uint8_t)0x00)
#define DTIM_ClkDiv_16						((uint8_t)0x04)	
#define DTIM_ClkDiv_256						((uint8_t)0x08)	
#define IS_DTIM_CLK_DIV(DIV) 	(((DIV) == DTIM_ClkDiv_1) || \
																((DIV) == DTIM_ClkDiv_16) \
																	| ((DIV) == DTIM_ClkDiv_256)) 
/**
  * @}
  */
  

/** @defgroup DTIM_CounterSize_Type
  * @{
  */
#define DTIM_CounterSize_32bit                     ((uint8_t)0x02) 
#define DTIM_CounterSize_16bit                     ((uint8_t)0x00)
#define IS_DTIM_CounterSize(SIZE) 	 (((SIZE) == DTIM_CounterSize_32bit) || \
												(( SIZE) == DTIM_CounterSize_16bit))	

/**
  * @}
  */
  																		

#define DTIM_Enable_SET					((uint8_t)0x80)



#define DTIM_TIMER1				((uint8_t)0x00)
#define DTIM_TIMER2				((uint8_t)0x01)
#define IS_DTIM_TIMER_TYPE(TIMER) (((TIMER) == DTIM_TIMER1) || \
												(( TIMER) == DTIM_TIMER2))	

#define DTIM_CTRREG_INIT_MASK	((uint32_t)0xffffff00)											

#define DTIM_Interrupt_Clear	((uint8_t)0x01)

void DTIM_DeInit(void);
void DTIM_Init(uint8_t DTIMtimerx, DTIM_InitTypeDef* DTIM_InitStruct);
void DTIM_Enable(uint8_t DTIMtimerx, FunctionalState NewState);
void DTIM_SetBGLoad(uint8_t DTIMtimerx,uint32_t BGLoadVal);
void DTIM_InterruptFlag_Clear(uint8_t DTIMtimerx);
uint32_t DTIM_CounterCurrentValue_Get(uint8_t DTIMtimerx);
ITStatus DTIM_InterruptStatus_Get(uint8_t DTIMtimerx);

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_DUALTIMER_H */

