#ifndef __STAR_ADC_H
#define __STAR_ADC_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "STAR.h"


#ifndef NULL
#define NULL 0
#endif

/** 
  * @brief  ADC Init structure definition  
  */

typedef struct
{	
	uint8_t 	ADC_RefVol_Sel;				//ADC参考电平选择，取值参考 ADC_REF_VOL_EXTERNAL
	uint8_t 	ADC_PDn;					//ADC激活或者掉电，取值参考 ADC_PDn_Type
	uint8_t 	ADC_ClkPreDiv;   			//时钟预分频系数，取值参考 ADC_ClkPreDiv_Type  																									 
	uint8_t 	ADC_ConversionMode;			//转换模式，取值参考 ADC_ConversionMode_Type	 
	uint32_t 	ADC_DataBufEnable; 		//Data buffer是否使能，取值参考 ADC_DataBufEnable_Type
	uint32_t 	ADC_ExternalTrigConvEnable; //外部触发转换是否使能，取值参考 ADC_ExternalTrigConvEnable_Type    
	uint32_t 	ADC_ExternalEventSel;		//触发ADC开始转换事件选择，取值参考 ADC_ExternalEventSel_Type
	uint32_t 	ADC_DataAlign;				//数据对齐方式，取值参考 ADC_DataAlign_Type
	uint32_t 	ADC_ScanModeEanbel;		//扫描模式是否使能，取值参考 ADC_ScanModeEanbel_Type 
}ADC_InitTypeDef;

/**
  * @}
  */

/** @defgroup ADC_ClkPreDiv_Type 
  * @{
  */
#define ADC_ClkPreDiv_2				(0x00)	
#define ADC_ClkPreDiv_4				(0x10)		
#define ADC_ClkPreDiv_6				(0x20)		
#define ADC_ClkPreDiv_8				(0x30)		
#define ADC_ClkPreDiv_10			(0x40)		
#define ADC_ClkPreDiv_12			(0x50)		
#define ADC_ClkPreDiv_24			(0x60)		
#define ADC_ClkPreDiv_48			(0x70)		

#define IS_ADC_ClkPreDiv(Div)    (((Div) == ADC_ClkPreDiv_2)  ||((Div) == ADC_ClkPreDiv_4) || \
                                 ((Div) == ADC_ClkPreDiv_6)  || ((Div) == ADC_ClkPreDiv_8) || \
                                 ((Div) == ADC_ClkPreDiv_10) || ((Div) == ADC_ClkPreDiv_12)|| \
                                 ((Div) == ADC_ClkPreDiv_24) || ((Div) == ADC_ClkPreDiv_48))


/**
  * @}
  */
  
/** @defgroup ADC_ConversionMode_Type 
  * @{
  */
#define ADC_ConversionMode_Single			(0x00)
#define ADC_ConversionMode_Continuous		(0x02)
#define IS_ADC_ConversionMode(MODE) (((MODE) == ADC_ConversionMode_Single) || \
                                   (( MODE) == ADC_ConversionMode_Continuous))

/**
  * @}
  */
  

/** @defgroup ADC_DataBufEnable_Type 
  * @{
  */  
#define ADC_DataBufEnable_Enable      ((uint32_t)0x00020000)
#define ADC_DataBufEnable_Disable     ((uint32_t)0x00000000)	
#define IS_ADC_DataBufEnable_Enable(enable) (((enable) == ADC_DataBufEnable_Enable) || \
																	  ((enable) == ADC_DataBufEnable_Disable))  

/**
  * @}
  */

/** @defgroup ADC_ExternalTrigConvEnable_Type
  * @{
  */ 
#define ADC_ExternalTrigConvEnable_Enable				((uint32_t)0x00000040)
#define ADC_ExternalTrigConvEnable_Disable				((uint32_t)0x00000000)

#define	IS_ADC_ExternalTrigConvEnable (((enable) == ADC_ExternalTrigConvEnable_Enable) || \
																	((enable) == ADC_ExternalTrigConvEnable_Disable))
/**
  * @}
  */																	

/** @defgroup ADC_ExternalEventSel_Type 
  * @{
  */
#define ADC_ExternalEventSel_Timer0				((uint32_t)0x00000000)
#define ADC_ExternalEventSel_Pin				((uint32_t)0x00000010)

#define	IS_ADC_ExternalEventSel (((Event) == ADC_ExternalEventSel_Timer0)     || \
															 ((Event) == ADC_ExternalEventSel_Pin))
/**
  * @}
  */


#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == CM3DS_MPS2_ADC))


/** @defgroup ADC_DataAlign_Type 
  * @{
  */

#define ADC_DataAlign_Right                          ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                           ((uint32_t)0x00000008)
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */


/** @defgroup ADC_ScanModeEanbel_Type
  * @{
  */
	
#define	ADC_ScanModeEanbel_Enable 												 ((uint32_t)0x00000002)
#define ADC_ScanModeEanbel_Disable												 ((uint32_t)0x00000000)
#define	IS_ADC_ScanModeEanbel(Mode) (((Mode) == ADC_ScanModeEanbel_Enable) || \
																		 (Mode) == ADC_ScanModeEanbel_Disable))
/**
  * @}
  */


/** @defgroup ADC_PDn_Type
  * @{
  */
#define ADC_POWER_DOWN				(0x0)
#define ADC_ACTIVE					(0x20)
#define	IS_ADC_ACTIVE_STATE(ActiveState) (((ActiveState) == ADC_POWER_DOWN) || \
																				((ActiveState) == ADC_ACTIVE))
/**
  * @}
  */

  
/** @defgroup ADC_REF_VOL_Type
  * @{
  */																				
#define ADC_REF_VOL_INTERIOR			(0x0)
#define ADC_REF_VOL_EXTERNAL			(0x10)																			
#define IS_ADC_REF_VOL_SEL(ADC_RefVol)	(((ADC_RefVol) == ADC_REF_VOL_INTERIOR) || \
																					((ADC_RefVol) == ADC_REF_VOL_EXTERNAL))
/**
  * @}
  */


/** @defgroup ADC_channels 
  * @{
  */

#define ADC_Channel_0                                (0x0)	 // Available ADC_IN0
#define ADC_Channel_1                                (0x1)   // Available ADC_IN1
#define ADC_Channel_2                                (0x2)   // Available ADC_IN2
#define ADC_Channel_3                                (0x3)   // Available ADC_IN3
#define ADC_Channel_4                                (0x4)   // Available ADC_IN4
#define ADC_Channel_5                                (0x5)   // Available ADC_IN5
#define ADC_Channel_6                                (0x6)   // Available ADC_IN6
#define ADC_Channel_7                                (0x7)   // Available ADC_IN7

//Channel_8 ~ Channel_11 are only useful for ADC0.
#define ADC_Channel_8                                (0x8)   // Available ADC_IN8
#define ADC_Channel_9                                (0x9)   // Available ADC_IN9
#define ADC_Channel_10                               (0x10)  // Available ADC_IN10
#define ADC_Channel_11                               (0x11)  // Available ADC_IN11



#define IS_ADC_CHANNEL(CHANNEL) 	 (((CHANNEL) == ADC_Channel_0) || ((CHANNEL) == ADC_Channel_1) \
																		((CHANNEL) == ADC_Channel_2) || \
																		((CHANNEL) == ADC_Channel_3) || \
																		((CHANNEL) == ADC_Channel_4) || \
																		((CHANNEL) == ADC_Channel_5) || \
																		((CHANNEL) == ADC_Channel_6) || \
																		((CHANNEL) == ADC_Channel_7)) || \
																		((CHANNEL) == ADC_Channel_8)) || \
																		((CHANNEL) == ADC_Channel_9)) || \
																		((CHANNEL) == ADC_Channel_10))|| \
																		((CHANNEL) == ADC_Channel_11))
/**
  * @}
  */

/////////////////////////ADC_CR1//////////////////////////////////
#define ADC_CR1_INIT_MASK		((uint8_t)0x00)
#define ADC_CR2_INIT_MASK		((uint32_t)0x00000000)

#define ADC_ENABLE				((uint8_t)0x01)


/////////////////////////ADC_CR1//////////////////////////////////
#define ADC_DATA_BUF_OVR		0x10000


/////////////////////////ADC_CSR1//////////////////////////////////
#define ADC_CSR1_INIT_MASK		((uint8_t)0x80)
#define ADC_CSR1_CH_MASK		((uint8_t)0xF0)
#define ADC_IS_BUSY				((uint16_t)0x100)

/////////////////////////ADC_CSR0//////////////////////////////////
#define ADC_EOC_IT_ENABLE		((uint8_t)0x02)
#define ADC_EOC_FLAG_MASK		((uint8_t)0x01)

/** @defgroup ADC_Exported_Functions
  * @{
  */
 
void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_Channel_Select(ADC_TypeDef* ADCx, uint8_t Channel);
void ADC_EOCInterrupt_Config(ADC_TypeDef* ADCx,FunctionalState NewState);
void ADC_EOCFlag_Clear(ADC_TypeDef* ADCx);
FlagStatus ADC_EOCFlag_Get(ADC_TypeDef* ADCx);
FlagStatus ADC_DataBufOVRFlag_Get(ADC_TypeDef* ADCx);
void ADC_DataBufOVRFlag_Clear(ADC_TypeDef* ADCx);
FlagStatus ADC_DataBufEnable_Get(ADC_TypeDef* ADCx);
uint16_t ADC_GetValueFromDR(ADC_TypeDef* ADCx);
void ADC_GetValueFromDBR(ADC_TypeDef* ADCx, uint32_t* ADC_buf);
FlagStatus ADC_Get_BusyState(ADC_TypeDef* ADCx);
void ADC_Active_Set(ADC_TypeDef* ADCx, uint8_t ADC_ActiveState);

#ifdef __cplusplus
}
#endif

#endif /* __STAR_ADC_H */

