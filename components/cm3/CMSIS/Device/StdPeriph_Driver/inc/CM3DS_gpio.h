
#ifndef __CM3DS_GPIO_H
#define __CM3DS_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "CM3DS_MPS2.h"


#define IS_GPIO_ALL_PERIPH(PERIPH)  (((PERIPH) == CM3DS_MPS2_GPIO0))
                                 
  
typedef enum
{ GPIO_Mode_Output = 0x0,
  GPIO_Mode_Input,
  GPIO_Mode_AF
  
}GPIO_Mode_TypeDef;

#define IS_GPIO_MODE_TYPE(TYPE) (((TYPE) == GPIO_Mode_Output) || ((TYPE) == GPIO_Mode_Input) || ((TYPE) == GPIO_Mode_AF))

/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */
typedef enum
{
   Bit_RESET = 0,
   Bit_SET
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))


/** 
  * @brief External interrupt trigger type
  */

typedef enum
{
    Bit_LOWLEVEL = 0,
    Bit_HIGHLEVEL,
    Bit_FALLINGEDGE,
    Bit_RISINGEDGE
}GPIO_IntTrigger_TypeDef;

#define IS_GPIO_INT_TRIGGER_TYPE(TYPE) (((TYPE) == Bit_LOWLEVEL) || ((TYPE) == Bit_HIGHLEVEL) || \
                                                                  ((TYPE) == Bit_FALLINGEDGE)|| ((TYPE) == Bit_RISINGEDGE))


typedef enum 
{
    Interrupt_DISABLE = 0,
    Interrupt_ENABLE
} InterruptState;

#define IS_INTERRUPT_STATE(STATE) (((STATE) == Interrupt_DISABLE) || ((STATE) == Interrupt_ENABLE))

/**
  * @defgroup GPIO_pins_define 
  * @{
  */
#define GPIO_Pin_0                  (0)  /*!< Pin 0 selected */
#define GPIO_Pin_1                  (1)  /*!< Pin 1 selected */
#define GPIO_Pin_2                  (2)  /*!< Pin 2 selected */
#define GPIO_Pin_3                  (3)  /*!< Pin 3 selected */
#define GPIO_Pin_4                  (4)  /*!< Pin 4 selected */
#define GPIO_Pin_5                  (5)  /*!< Pin 5 selected */
#define GPIO_Pin_6                  (6)  /*!< Pin 6 selected */
#define GPIO_Pin_7                  (7)  /*!< Pin 7 selected */
#define GPIO_Pin_8                  (8)  /*!< Pin 8 selected */
#define GPIO_Pin_9                  (9)  /*!< Pin 9 selected */
#define GPIO_Pin_10                (10)  /*!< Pin 10 selected */
#define GPIO_Pin_11                (11)  /*!< Pin 11 selected */
#define GPIO_Pin_12                (12)  /*!< Pin 12 selected */
#define GPIO_Pin_13                (13)  /*!< Pin 13 selected */
#define GPIO_Pin_14                (14)  /*!< Pin 14 selected */
#define GPIO_Pin_15                (15)  /*!< Pin 15 selected */

#define GPIO_Pin_16                (16)  /*!< Pin 16 selected */
#define GPIO_Pin_17                (17)  /*!< Pin 17 selected */
#define GPIO_Pin_18                (18)  /*!< Pin 18 selected */
#define GPIO_Pin_19                (19)  /*!< Pin 19 selected */
#define GPIO_Pin_20                (20)  /*!< Pin 20 selected */
#define GPIO_Pin_21                (21)  /*!< Pin 21 selected */
#define GPIO_Pin_22                (22)  /*!< Pin 22 selected */
#define GPIO_Pin_23                (23)  /*!< Pin 23 selected */
#define GPIO_Pin_24                (24)  /*!< Pin 24 selected */
#define GPIO_Pin_25                (25)  /*!< Pin 25 selected */
#define GPIO_Pin_26                (26)  /*!< Pin 26 selected */
#define GPIO_Pin_27                (27)  /*!< Pin 27 selected */
#define GPIO_Pin_28                (28)  /*!< Pin 28 selected */
#define GPIO_Pin_29                (29)  /*!< Pin 29 selected */
#define GPIO_Pin_30                (30)  /*!< Pin 30 selected */
#define GPIO_Pin_31                (31)  /*!< Pin 31 selected */
#define GPIO_Pin_All               ((uint32_t)0xFFFFFFFF)  /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || ((PIN) == GPIO_Pin_2) || ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || ((PIN) == GPIO_Pin_6) || ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || ((PIN) == GPIO_Pin_9) || ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) ||((PIN) == GPIO_Pin_12) ||((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || ((PIN) == GPIO_Pin_15)||((PIN) == GPIO_Pin_16) || \
                              ((PIN) == GPIO_Pin_17) || ((PIN) == GPIO_Pin_18)||((PIN) == GPIO_Pin_19) || \
                              ((PIN) == GPIO_Pin_20) || ((PIN) == GPIO_Pin_21)||((PIN) == GPIO_Pin_22) || \
                              ((PIN) == GPIO_Pin_23) || ((PIN) == GPIO_Pin_24)||((PIN) == GPIO_Pin_25) || \
                              ((PIN) == GPIO_Pin_26) || ((PIN) == GPIO_Pin_27)||((PIN) == GPIO_Pin_28) || \
                              ((PIN) == GPIO_Pin_29) || ((PIN) == GPIO_Pin_30)||((PIN) == GPIO_Pin_31))
/**
  * @}
  */ 

/** 
  * @defgroup GPIO_AF_define 
  * @{
  */
#define GPIO_AF_TIM0EXTIN        ((uint32_t)0x00000001)
#define GPIO_AF_TIM1EXTIN        ((uint32_t)0x00000002)
#define GPIO_AF_USART0_RXD       ((uint32_t)0x00000004)
#define GPIO_AF_USART0_TXD       ((uint32_t)0x00000008)

#define GPIO_AF_USART1_RXD       ((uint32_t)0x00000010)
#define GPIO_AF_USART1_TXD       ((uint32_t)0x00000020)
#define GPIO_AF_ADCETR           ((uint32_t)0x00000040)
#define GPIO_AF_SPI0_CLK     	((uint32_t)0x00000080)

#define GPIO_AF_SPI0_SEL         ((uint32_t)0x00000100)
#define GPIO_AF_SPI0_DATA0       ((uint32_t)0x00000200)
#define GPIO_AF_SPI0_DATA1       ((uint32_t)0x00000400)
#define GPIO_AF_SPI1_CLK    	((uint32_t)0x00000800)

#define GPIO_AF_SPI1_SEL         ((uint32_t)0x00001000)
#define GPIO_AF_SPI1_DATA0       ((uint32_t)0x00002000)
#define GPIO_AF_SPI1_DATA1       ((uint32_t)0x00004000)
#define GPIO_AF_I2C0SCL          ((uint32_t)0x00008000)

#define GPIO_AF_I2C0SDA          ((uint32_t)0x00010000)
#define GPIO_AF_SPI0_DATA2       ((uint32_t)0x00020000)
#define GPIO_AF_SPI0_DATA3       ((uint32_t)0x00040000)
#define GPIO_AF_SPI1_DATA2       ((uint32_t)0x00080000)
#define GPIO_AF_SPI1_DATA3       ((uint32_t)0x00100000)

#define IS_GPIO_AF(AF) (((AF) == GPIO_Remap_TIM0EXTIN  ) || ((AF) == GPIO_Remap_TIM1EXTIN )  ||\
                                  ((AF) == GPIO_Remap_USART0_RXD ) || ((AF) ==  GPIO_Remap_USART0_TXD )  ||\
                                  ((AF) == GPIO_Remap_USART1_RXD ) || ((AF) ==  GPIO_Remap_USART1_TXD )  ||\
                                  ((AF) ==  GPIO_Remap_ADCETR  ) || ((AF) ==  GPIO_Remap_SPI0_CLK_OUT  )  ||\
                                  ((AF) == GPIO_Remap_SPI0_SEL  ) || ((AF) ==  GPIO_Remap_SPI0_DATA0 )  ||\
                                  ((AF) == GPIO_Remap_SPI0_DATA1 ) || ((AF) ==  GPIO_Remap_SPI0_DATA2 )  ||\
                                  ((AF) == GPIO_Remap_SPI0_DATA3 ) || ((AF) ==  GPIO_Remap_SPI1_CLK_OUT )  ||\
                                  ((AF) == GPIO_Remap_SPI1_SEL  ) || ((AF) ==  GPIO_Remap_SPI1_DATA0 )  ||\
                                  ((AF) == GPIO_Remap_SPI1_DATA1 ) || ((AF) ==  GPIO_Remap_SPI1_DATA2 )  ||\
                                  ((AF) == GPIO_Remap_SPI1_DATA3 ) || ((AF) ==  GPIO_Remap_I2C0SCL ) ||\
                                  ((AF) == GPIO_Remap_I2C0SDA ))
/**
  * @}
  */

/**
  * @defgroup GPIO_Exported_Functions
  * @{
  */
void GPIO_DeInit( GPIO_TypeDef *CM3DS_MPS2_GPIOx);
void GPIO_Mode_Set(GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, GPIO_Mode_TypeDef GPIO_Mode);
uint8_t GPIO_ReadInputBit( GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x);
void GPIO_SetBit( GPIO_TypeDef * CM3DS_MPS2_GPIOx,  uint16_t GPIO_Pin_x);
void GPIO_ResetBit( GPIO_TypeDef * CM3DS_MPS2_GPIOx,  uint16_t GPIO_Pin_x);
void GPIO_TogglePin( GPIO_TypeDef * CM3DS_MPS2_GPIOx,  uint16_t GPIO_Pin_x);
void GPIO_WriteBit(GPIO_TypeDef * CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, BitAction BitVal);
void GPIO_AF_Config( GPIO_TypeDef *CM3DS_MPS2_GPIOx,  uint32_t  GPIO_AF, FunctionalState NewState );
void GPIO_Interrupt_Config(GPIO_TypeDef *CM3DS_MPS2_GPIOx, uint16_t GPIO_Pin_x, GPIO_IntTrigger_TypeDef TriggerType, InterruptState NewState);
void GPIO_Interrupt_Clear(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin_x);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_GPIO_H */
