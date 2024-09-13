#ifndef __CM3DS_TIMER_H
#define __CM3DS_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "CM3DS_MPS2.h"


/** 
  * @brief  TIM Time Base Init structure definition
  * @note   This structure is used with all TIMx except for TIM6 and TIM7.    
  */

typedef struct
{
	uint8_t		TIM_InterruptEnable;		//是否开启中断，取值参考 TIM_InterruptEnable_Type
	uint8_t		TIM_SelExtInputAsClk;		//是否选择外部输入作为时钟，取值参考 TIM_SelExtInputAsClk_Type
	uint8_t		TIM_SelExtInputAsEn;		//是否选择外部输入作为使能，取值参考 TIM_SelExtInputAsEn_Type
    uint32_t 	TIM_Value;					//初始加载值
    uint32_t 	TIM_Reload;   				//计数器到0后重新加载值
} TIM_InitTypeDef;  


#define IS_TIM_ALL_PERIPH(PERIPH)  (((PERIPH) == CM3DS_MPS2_TIMER0 ) ||((PERIPH) == CM3DS_MPS2_TIMER0))

#define TIM_ENABLE_SET			((uint8_t)0x01)

#define TIM_CTR_INIT_MASK		((uint8_t)0xF0)


/** @defgroup TIM_InterruptEnable_Type
  * @{
  */ 

#define TIM_Interrupt_Enable	((uint8_t)0x08)
#define TIM_Interrupt_Disable	((uint8_t)0x00)

#define IS_TIM_INT_ENABLE(ENABLE) ((ENABLE ==TIM_Interrupt_Enable )||(ENABLE ==TIM_Interrupt_Disable )) 

/**
  * @}
  */

  
/** @defgroup TIM_SelExtInputAsClk_Type
  * @{
  */ 

#define TIM_Sel_ExtInputAsClk		((uint8_t)0x04)
#define TIM_Sel_PclkAsClk			((uint8_t)0x00)

#define IS_TIM_SEL_EXTINPUT_AS_CLK(SEL) (((SEL) ==TIM_Sel_ExtInputAsClk )||((SEL) ==TIM_Sel_PclkAsClk )) 

/**
  * @}
  */



/** @defgroup TIM_SelExtInputAsEn_Type
  * @{
  */ 

#define TIM_Sel_ExtInputAsEn		((uint8_t)0x02)
#define TIM_Sel_SoftSetAsEn			((uint8_t)0x00)

#define IS_TIM_SEL_EXTINPUT_AS_En(En) (((En) ==TIM_Sel_ExtInputAsEn )||((En) ==TIM_Sel_SoftSetAsEn )) 

/**
  * @}
  */

void TIM_DeInit(TIMER_TypeDef* TIMERx);
void TIM_Init(TIMER_TypeDef* TIMERx, TIM_InitTypeDef* TIM_InitStruct);
void TIM_Enable(TIMER_TypeDef* TIMERx ,FunctionalState NewStat);
ITStatus TIM_InterruptStatus_Get(TIMER_TypeDef* TIMERx);
void TIM_InterruptFlag_Clear(TIMER_TypeDef* TIMERx);

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_TIMER_H */

