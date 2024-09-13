/**************************************************************************//**
 * @file     CM3DS_MPS2.h
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Header File for
 *           Device CM3DS_MPS2
 * @version  V3.01
 * @date     06. March 2012
 *
 * @note
 * Copyright (C) 2010-2017 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef CM3DS_MPS2_H
#define CM3DS_MPS2_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup CM3DS_MPS2_Definitions CM3DS_MPS2 Definitions
  This file defines all structures and symbols for CM3DS_MPS2:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - Peripheral definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup CM3DS_MPS2_CMSIS Device CMSIS Definitions
  Configuration of the Cortex-M3 Processor and Core Peripherals
  @{
*/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
	NonMaskableInt_IRQn           = -14,    /*!<  2 Cortex-M3 Non Maskable Interrupt                        */
	HardFault_IRQn                = -13,    /*!<  3 Cortex-M3 Hard Fault Interrupt                          */
	MemoryManagement_IRQn         = -12,    /*!<  4 Cortex-M3 Memory Management Interrupt            */
	BusFault_IRQn                 = -11,    /*!<  5 Cortex-M3 Bus Fault Interrupt                    */
	UsageFault_IRQn               = -10,    /*!<  6 Cortex-M3 Usage Fault Interrupt                  */
	SVCall_IRQn                   = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                      */
	DebugMonitor_IRQn             = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                */
	PendSV_IRQn                   = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                      */
	SysTick_IRQn                  = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                  */

/******  CM3DS_MPS2 Specific Interrupt Numbers *******************************************************/
	UART0_IRQn                    = 0,       /* UART 0 RX and TX Combined Interrupt   */
	ADC_IRQn                      = 1,       /* ADC Interrupt                         */
	UART1_IRQn                    = 2,       /* UART 1 RX and TX Combined Interrupt   */
	DMACINTERR                    = 3,       /* DMA Error Interrupt                             */
	DMACINTTC                     = 4,       /* DMA Count Interrupt                             */
	DMACINTR                      = 5,       /* DMA Interrupt                             */
	PORT0_ALL_IRQn                = 6,       /* GPIO Port 0 combined Interrupt        */
	Spare7_IRQn                   = 7,       /* GPIO Port 1 combined Interrupt        */
	TIMER0_IRQn                   = 8,       /* TIMER 0 Interrupt                     */
	TIMER1_IRQn                   = 9,       /* TIMER 1 Interrupt                     */
	DUALTIMER_IRQn                = 10,      /* Dual Timer Interrupt                  */
	Spare11_IRQn                  = 11,      /* Undefined                             */
	UARTOVF_IRQn                  = 12,      /* UART 0,1       Overflow Interrupt     */
	EXT13_IRQn                    = 13,      /* Undefined                             */
	EXT14_IRQn                    = 14,      /* Undefined                             */
	EXT15_IRQn                    = 15,      /* Undefined                             */
	PORT0_0_IRQn                  = 16,      /*!< All P0 I/O pins can be used as interrupt source. */
	PORT0_1_IRQn                  = 17,      /*!< There are 32 pins in total                       */
	PORT0_2_IRQn                  = 18,
	PORT0_3_IRQn                  = 19,
	PORT0_4_IRQn                  = 20,
	PORT0_5_IRQn                  = 21,
	PORT0_6_IRQn                  = 22,
	PORT0_7_IRQn                  = 23,
	PORT0_8_IRQn                  = 24,
	PORT0_9_IRQn                  = 25,
	PORT0_10_IRQn                 = 26,
	PORT0_11_IRQn                 = 27,
	PORT0_12_IRQn                 = 28,
	PORT0_13_IRQn                 = 29,
	PORT0_14_IRQn                 = 30,
	PORT0_15_IRQn                 = 31,
	PORT0_16_IRQn                 = 32,      
	PORT0_17_IRQn                 = 33,      
	PORT0_18_IRQn                 = 34,      
	PORT0_19_IRQn                 = 35,      
	PORT0_20_IRQn                 = 36,      
	PORT0_21_IRQn                 = 37,      
	PORT0_22_IRQn                 = 38,      
	PORT0_23_IRQn                 = 39,      
	PORT0_24_IRQn                 = 40,      
	PORT0_25_IRQn                 = 41,      
	PORT0_26_IRQn                 = 42,      
	PORT0_27_IRQn                 = 43,      
	PORT0_28_IRQn                 = 44,      
	PORT0_29_IRQn                 = 45,      
	PORT0_30_IRQn                 = 46,      
	PORT0_31_IRQn                 = 47,      
	I2C_IRQn                      = 48,      /* I2C Interrupt                         */
	MPS2_SSP0_IRQn                = 49,      /* SPI0 Interrupt                        */
	MPS2_SSP1_IRQn                = 50,      /* SPI1 Interrupt                        */
	EXT0_IRQn                     = 51,      /* External Interrupts                   */
	EXT1_IRQn                     = 52,      /* !< There are 16 pins in total         */
	EXT2_IRQn                     = 53,      
	EXT3_IRQn                     = 54,      
	EXT4_IRQn                     = 55,      
	EXT5_IRQn                     = 56,      	
	EXT6_IRQn                     = 57,      	
	EXT7_IRQn                     = 58,
	EXT8_IRQn                     = 59,
	EXT9_IRQn                     = 60,
	EXT10_IRQn                    = 61,
	EXT11_IRQn                    = 62,
	EXT12_IRQn                    = 63
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __CM3_REV                 0x0201    /*!< Core Revision r2p1                             */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels        */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used   */
#define __MPU_PRESENT             1         /*!< MPU present or not                             */

/*@}*/ /* end of group CM3DS_MPS2_CMSIS */


#include "core_cm3.h"                     /* Cortex-M3 processor and core peripherals           */
#include "system_CM3DS.h"             /* CM3DS System include file                      */
#include "CM3DS_conf.h"





/** @addtogroup Exported_types
  * @{
  */  

typedef enum {
	RESET = 0, 
	SET = !RESET
} FlagStatus, ITStatus;

/*!< CM3 Standard Peripheral Library old types (maintained for legacy purpose) */
typedef enum {
	DISABLE = 0, 
	ENABLE = !DISABLE
} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {
	ERROR = 0, 
	SUCCESS = !ERROR
} ErrorStatus;

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/** @addtogroup CM3DS_MPS2_Peripherals CM3DS_MPS2 Peripherals
  CM3DS_MPS2 Device Specific Peripheral registers structures
  @{
*/

#if defined ( __CC_ARM   )
  #pragma push
#pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
typedef struct
{
  __IO   uint32_t  DATA;          /*!< Offset: 0x000 Data Register    (R/W) */
  __IO   uint32_t  STATE;         /*!< Offset: 0x004 Status Register  (R/W) */
  __IO   uint32_t  CTRL;          /*!< Offset: 0x008 Control Register (R/W) */
  union {
    __I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
    __O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W) */
    };
  __IO   uint32_t  BAUDDIV;       /*!< Offset: 0x010 Baudrate Divider Register (R/W) */

}UART_TypeDef;

/* CM3DS_MPS2_UART DATA Register Definitions */

#define CM3DS_MPS2_UART_DATA_Pos               0                                            /*!< CM3DS_MPS2_UART_DATA_Pos: DATA Position */
#define CM3DS_MPS2_UART_DATA_Msk              (0xFFul << CM3DS_MPS2_UART_DATA_Pos)               /*!< CM3DS_MPS2_UART DATA: DATA Mask */

#define CM3DS_MPS2_UART_STATE_RXOR_Pos         3                                            /*!< CM3DS_MPS2_UART STATE: RXOR Position */
#define CM3DS_MPS2_UART_STATE_RXOR_Msk         (0x1ul << CM3DS_MPS2_UART_STATE_RXOR_Pos)         /*!< CM3DS_MPS2_UART STATE: RXOR Mask */

#define CM3DS_MPS2_UART_STATE_TXOR_Pos         2                                            /*!< CM3DS_MPS2_UART STATE: TXOR Position */
#define CM3DS_MPS2_UART_STATE_TXOR_Msk         (0x1ul << CM3DS_MPS2_UART_STATE_TXOR_Pos)         /*!< CM3DS_MPS2_UART STATE: TXOR Mask */

#define CM3DS_MPS2_UART_STATE_RXBF_Pos         1                                            /*!< CM3DS_MPS2_UART STATE: RXBF Position */
#define CM3DS_MPS2_UART_STATE_RXBF_Msk         (0x1ul << CM3DS_MPS2_UART_STATE_RXBF_Pos)         /*!< CM3DS_MPS2_UART STATE: RXBF Mask */

#define CM3DS_MPS2_UART_STATE_TXBF_Pos         0                                            /*!< CM3DS_MPS2_UART STATE: TXBF Position */
#define CM3DS_MPS2_UART_STATE_TXBF_Msk         (0x1ul << CM3DS_MPS2_UART_STATE_TXBF_Pos )        /*!< CM3DS_MPS2_UART STATE: TXBF Mask */

#define CM3DS_MPS2_UART_CTRL_HSTM_Pos          6                                            /*!< CM3DS_MPS2_UART CTRL: HSTM Position */
#define CM3DS_MPS2_UART_CTRL_HSTM_Msk          (0x01ul << CM3DS_MPS2_UART_CTRL_HSTM_Pos)         /*!< CM3DS_MPS2_UART CTRL: HSTM Mask */

#define CM3DS_MPS2_UART_CTRL_RXORIRQEN_Pos     5                                            /*!< CM3DS_MPS2_UART CTRL: RXORIRQEN Position */
#define CM3DS_MPS2_UART_CTRL_RXORIRQEN_Msk     (0x01ul << CM3DS_MPS2_UART_CTRL_RXORIRQEN_Pos)    /*!< CM3DS_MPS2_UART CTRL: RXORIRQEN Mask */

#define CM3DS_MPS2_UART_CTRL_TXORIRQEN_Pos     4                                            /*!< CM3DS_MPS2_UART CTRL: TXORIRQEN Position */
#define CM3DS_MPS2_UART_CTRL_TXORIRQEN_Msk     (0x01ul << CM3DS_MPS2_UART_CTRL_TXORIRQEN_Pos)    /*!< CM3DS_MPS2_UART CTRL: TXORIRQEN Mask */

#define CM3DS_MPS2_UART_CTRL_RXIRQEN_Pos       3                                            /*!< CM3DS_MPS2_UART CTRL: RXIRQEN Position */
#define CM3DS_MPS2_UART_CTRL_RXIRQEN_Msk       (0x01ul << CM3DS_MPS2_UART_CTRL_RXIRQEN_Pos)      /*!< CM3DS_MPS2_UART CTRL: RXIRQEN Mask */

#define CM3DS_MPS2_UART_CTRL_TXIRQEN_Pos       2                                            /*!< CM3DS_MPS2_UART CTRL: TXIRQEN Position */
#define CM3DS_MPS2_UART_CTRL_TXIRQEN_Msk       (0x01ul << CM3DS_MPS2_UART_CTRL_TXIRQEN_Pos)      /*!< CM3DS_MPS2_UART CTRL: TXIRQEN Mask */

#define CM3DS_MPS2_UART_CTRL_RXEN_Pos          1                                            /*!< CM3DS_MPS2_UART CTRL: RXEN Position */
#define CM3DS_MPS2_UART_CTRL_RXEN_Msk          (0x01ul << CM3DS_MPS2_UART_CTRL_RXEN_Pos)         /*!< CM3DS_MPS2_UART CTRL: RXEN Mask */

#define CM3DS_MPS2_UART_CTRL_TXEN_Pos          0                                            /*!< CM3DS_MPS2_UART CTRL: TXEN Position */
#define CM3DS_MPS2_UART_CTRL_TXEN_Msk          (0x01ul << CM3DS_MPS2_UART_CTRL_TXEN_Pos)         /*!< CM3DS_MPS2_UART CTRL: TXEN Mask */

#define CM3DS_MPS2_UART_INTSTATUS_RXORIRQ_Pos  3                                            /*!< CM3DS_MPS2_UART CTRL: RXORIRQ Position */
#define CM3DS_MPS2_UART_CTRL_RXORIRQ_Msk       (0x01ul << CM3DS_MPS2_UART_INTSTATUS_RXORIRQ_Pos) /*!< CM3DS_MPS2_UART CTRL: RXORIRQ Mask */

#define CM3DS_MPS2_UART_CTRL_TXORIRQ_Pos       2                                            /*!< CM3DS_MPS2_UART CTRL: TXORIRQ Position */
#define CM3DS_MPS2_UART_CTRL_TXORIRQ_Msk       (0x01ul << CM3DS_MPS2_UART_CTRL_TXORIRQ_Pos)      /*!< CM3DS_MPS2_UART CTRL: TXORIRQ Mask */

#define CM3DS_MPS2_UART_CTRL_RXIRQ_Pos         1                                            /*!< CM3DS_MPS2_UART CTRL: RXIRQ Position */
#define CM3DS_MPS2_UART_CTRL_RXIRQ_Msk         (0x01ul << CM3DS_MPS2_UART_CTRL_RXIRQ_Pos)        /*!< CM3DS_MPS2_UART CTRL: RXIRQ Mask */

#define CM3DS_MPS2_UART_CTRL_TXIRQ_Pos         0                                            /*!< CM3DS_MPS2_UART CTRL: TXIRQ Position */
#define CM3DS_MPS2_UART_CTRL_TXIRQ_Msk         (0x01ul << CM3DS_MPS2_UART_CTRL_TXIRQ_Pos)        /*!< CM3DS_MPS2_UART CTRL: TXIRQ Mask */

#define CM3DS_MPS2_UART_BAUDDIV_Pos            0                                            /*!< CM3DS_MPS2_UART BAUDDIV: BAUDDIV Position */
#define CM3DS_MPS2_UART_BAUDDIV_Msk            (0xFFFFFul << CM3DS_MPS2_UART_BAUDDIV_Pos)        /*!< CM3DS_MPS2_UART BAUDDIV: BAUDDIV Mask */


/*----------------------------- Timer (TIMER) -------------------------------*/
typedef struct
{
	__IO   uint32_t  CTRL;          /*!< Offset: 0x000 Control Register (R/W) */
	__IO   uint32_t  VALUE;         /*!< Offset: 0x004 Current Value Register (R/W) */
	__IO   uint32_t  RELOAD;        /*!< Offset: 0x008 Reload Value Register  (R/W) */
	union {
		__I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
		__O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W) */
	};

}TIMER_TypeDef;

/* CM3DS_MPS2_TIMER CTRL Register Definitions */

#define CM3DS_MPS2_TIMER_CTRL_IRQEN_Pos          3                                              /*!< CM3DS_MPS2_TIMER CTRL: IRQEN Position */
#define CM3DS_MPS2_TIMER_CTRL_IRQEN_Msk          (0x01ul << CM3DS_MPS2_TIMER_CTRL_IRQEN_Pos)         /*!< CM3DS_MPS2_TIMER CTRL: IRQEN Mask */

#define CM3DS_MPS2_TIMER_CTRL_SELEXTCLK_Pos      2                                              /*!< CM3DS_MPS2_TIMER CTRL: SELEXTCLK Position */
#define CM3DS_MPS2_TIMER_CTRL_SELEXTCLK_Msk      (0x01ul << CM3DS_MPS2_TIMER_CTRL_SELEXTCLK_Pos)     /*!< CM3DS_MPS2_TIMER CTRL: SELEXTCLK Mask */

#define CM3DS_MPS2_TIMER_CTRL_SELEXTEN_Pos       1                                              /*!< CM3DS_MPS2_TIMER CTRL: SELEXTEN Position */
#define CM3DS_MPS2_TIMER_CTRL_SELEXTEN_Msk       (0x01ul << CM3DS_MPS2_TIMER_CTRL_SELEXTEN_Pos)      /*!< CM3DS_MPS2_TIMER CTRL: SELEXTEN Mask */

#define CM3DS_MPS2_TIMER_CTRL_EN_Pos             0                                              /*!< CM3DS_MPS2_TIMER CTRL: EN Position */
#define CM3DS_MPS2_TIMER_CTRL_EN_Msk             (0x01ul << CM3DS_MPS2_TIMER_CTRL_EN_Pos)            /*!< CM3DS_MPS2_TIMER CTRL: EN Mask */

#define CM3DS_MPS2_TIMER_VAL_CURRENT_Pos         0                                              /*!< CM3DS_MPS2_TIMER VALUE: CURRENT Position */
#define CM3DS_MPS2_TIMER_VAL_CURRENT_Msk         (0xFFFFFFFFul << CM3DS_MPS2_TIMER_VAL_CURRENT_Pos)  /*!< CM3DS_MPS2_TIMER VALUE: CURRENT Mask */

#define CM3DS_MPS2_TIMER_RELOAD_VAL_Pos          0                                              /*!< CM3DS_MPS2_TIMER RELOAD: RELOAD Position */
#define CM3DS_MPS2_TIMER_RELOAD_VAL_Msk          (0xFFFFFFFFul << CM3DS_MPS2_TIMER_RELOAD_VAL_Pos)   /*!< CM3DS_MPS2_TIMER RELOAD: RELOAD Mask */

#define CM3DS_MPS2_TIMER_INTSTATUS_Pos           0                                              /*!< CM3DS_MPS2_TIMER INTSTATUS: INTSTATUSPosition */
#define CM3DS_MPS2_TIMER_INTSTATUS_Msk           (0x01ul << CM3DS_MPS2_TIMER_INTSTATUS_Pos)          /*!< CM3DS_MPS2_TIMER INTSTATUS: INTSTATUSMask */

#define CM3DS_MPS2_TIMER_INTCLEAR_Pos            0                                              /*!< CM3DS_MPS2_TIMER INTCLEAR: INTCLEAR Position */
#define CM3DS_MPS2_TIMER_INTCLEAR_Msk            (0x01ul << CM3DS_MPS2_TIMER_INTCLEAR_Pos)           /*!< CM3DS_MPS2_TIMER INTCLEAR: INTCLEAR Mask */


/*------------- Timer (TIM) --------------------------------------------------*/
typedef struct
{
	__IO uint32_t Timer1Load;                  /* Offset: 0x000 (R/W) Timer 1 Load */
	__I  uint32_t Timer1Value;                 /* Offset: 0x004 (R/ ) Timer 1 Counter Current Value */
	__IO uint32_t Timer1Control;               /* Offset: 0x008 (R/W) Timer 1 Control */
	__O  uint32_t Timer1IntClr;                /* Offset: 0x00C ( /W) Timer 1 Interrupt Clear */
	__I  uint32_t Timer1RIS;                   /* Offset: 0x010 (R/ ) Timer 1 Raw Interrupt Status */
	__I  uint32_t Timer1MIS;                   /* Offset: 0x014 (R/ ) Timer 1 Masked Interrupt Status */
	__IO uint32_t Timer1BGLoad;                /* Offset: 0x018 (R/W) Background Load Register */
		uint32_t RESERVED0;
	__IO uint32_t Timer2Load;                  /* Offset: 0x020 (R/W) Timer 2 Load */
	__I  uint32_t Timer2Value;                 /* Offset: 0x024 (R/ ) Timer 2 Counter Current Value */
	__IO uint32_t Timer2Control;               /* Offset: 0x028 (R/W) Timer 2 Control */
	__O  uint32_t Timer2IntClr;                /* Offset: 0x02C ( /W) Timer 2 Interrupt Clear */
	__I  uint32_t Timer2RIS;                   /* Offset: 0x030 (R/ ) Timer 2 Raw Interrupt Status */
	__I  uint32_t Timer2MIS;                   /* Offset: 0x034 (R/ ) Timer 2 Masked Interrupt Status */
	__IO uint32_t Timer2BGLoad;                /* Offset: 0x038 (R/W) Background Load Register */
		uint32_t RESERVED1[945];
	__IO uint32_t ITCR;                        /* Offset: 0xF00 (R/W) Integration Test Control Register */
	__O  uint32_t ITOP;                        /* Offset: 0xF04 ( /W) Integration Test Output Set Register */
}DUALTIMER_BOTH_TypeDef;

#define CM3DS_MPS2_DUALTIMER1_LOAD_Pos            0                                                /* CM3DS_MPS2_DUALTIMER1 LOAD: LOAD Position */
#define CM3DS_MPS2_DUALTIMER1_LOAD_Msk            (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER1_LOAD_Pos)      /* CM3DS_MPS2_DUALTIMER1 LOAD: LOAD Mask */

#define CM3DS_MPS2_DUALTIMER1_VALUE_Pos           0                                                /* CM3DS_MPS2_DUALTIMER1 VALUE: VALUE Position */
#define CM3DS_MPS2_DUALTIMER1_VALUE_Msk           (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER1_VALUE_Pos)     /* CM3DS_MPS2_DUALTIMER1 VALUE: VALUE Mask */

#define CM3DS_MPS2_DUALTIMER1_CTRL_EN_Pos         7                                                /* CM3DS_MPS2_DUALTIMER1 CTRL_EN: CTRL Enable Position */
#define CM3DS_MPS2_DUALTIMER1_CTRL_EN_Msk         (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_EN_Pos)          /* CM3DS_MPS2_DUALTIMER1 CTRL_EN: CTRL Enable Mask */

#define CM3DS_MPS2_DUALTIMER1_CTRL_MODE_Pos       6                                                /* CM3DS_MPS2_DUALTIMER1 CTRL_MODE: CTRL MODE Position */
#define CM3DS_MPS2_DUALTIMER1_CTRL_MODE_Msk       (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_MODE_Pos)        /* CM3DS_MPS2_DUALTIMER1 CTRL_MODE: CTRL MODE Mask */

#define CM3DS_MPS2_DUALTIMER1_CTRL_INTEN_Pos      5                                                /* CM3DS_MPS2_DUALTIMER1 CTRL_INTEN: CTRL Int Enable Position */
#define CM3DS_MPS2_DUALTIMER1_CTRL_INTEN_Msk      (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_INTEN_Pos)       /* CM3DS_MPS2_DUALTIMER1 CTRL_INTEN: CTRL Int Enable Mask */

#define CM3DS_MPS2_DUALTIMER1_CTRL_PRESCALE_Pos   2                                                /* CM3DS_MPS2_DUALTIMER1 CTRL_PRESCALE: CTRL PRESCALE Position */
#define CM3DS_MPS2_DUALTIMER1_CTRL_PRESCALE_Msk   (0x3ul << CM3DS_MPS2_DUALTIMER1_CTRL_PRESCALE_Pos)    /* CM3DS_MPS2_DUALTIMER1 CTRL_PRESCALE: CTRL PRESCALE Mask */

#define CM3DS_MPS2_DUALTIMER1_CTRL_SIZE_Pos       1                                                /* CM3DS_MPS2_DUALTIMER1 CTRL_SIZE: CTRL SIZE Position */
#define CM3DS_MPS2_DUALTIMER1_CTRL_SIZE_Msk       (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_SIZE_Pos)        /* CM3DS_MPS2_DUALTIMER1 CTRL_SIZE: CTRL SIZE Mask */

#define CM3DS_MPS2_DUALTIMER1_CTRL_ONESHOOT_Pos   0                                                /* CM3DS_MPS2_DUALTIMER1 CTRL_ONESHOOT: CTRL ONESHOOT Position */
#define CM3DS_MPS2_DUALTIMER1_CTRL_ONESHOOT_Msk   (0x1ul << CM3DS_MPS2_DUALTIMER1_CTRL_ONESHOOT_Pos)    /* CM3DS_MPS2_DUALTIMER1 CTRL_ONESHOOT: CTRL ONESHOOT Mask */

#define CM3DS_MPS2_DUALTIMER1_INTCLR_Pos          0                                                /* CM3DS_MPS2_DUALTIMER1 INTCLR: INT Clear Position */
#define CM3DS_MPS2_DUALTIMER1_INTCLR_Msk          (0x1ul << CM3DS_MPS2_DUALTIMER1_INTCLR_Pos)           /* CM3DS_MPS2_DUALTIMER1 INTCLR: INT Clear  Mask */

#define CM3DS_MPS2_DUALTIMER1_RAWINTSTAT_Pos      0                                                /* CM3DS_MPS2_DUALTIMER1 RAWINTSTAT: Raw Int Status Position */
#define CM3DS_MPS2_DUALTIMER1_RAWINTSTAT_Msk      (0x1ul << CM3DS_MPS2_DUALTIMER1_RAWINTSTAT_Pos)       /* CM3DS_MPS2_DUALTIMER1 RAWINTSTAT: Raw Int Status Mask */

#define CM3DS_MPS2_DUALTIMER1_MASKINTSTAT_Pos     0                                                /* CM3DS_MPS2_DUALTIMER1 MASKINTSTAT: Mask Int Status Position */
#define CM3DS_MPS2_DUALTIMER1_MASKINTSTAT_Msk     (0x1ul << CM3DS_MPS2_DUALTIMER1_MASKINTSTAT_Pos)      /* CM3DS_MPS2_DUALTIMER1 MASKINTSTAT: Mask Int Status Mask */

#define CM3DS_MPS2_DUALTIMER1_BGLOAD_Pos          0                                                /* CM3DS_MPS2_DUALTIMER1 BGLOAD: Background Load Position */
#define CM3DS_MPS2_DUALTIMER1_BGLOAD_Msk          (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER1_BGLOAD_Pos)    /* CM3DS_MPS2_DUALTIMER1 BGLOAD: Background Load Mask */

#define CM3DS_MPS2_DUALTIMER2_LOAD_Pos            0                                                /* CM3DS_MPS2_DUALTIMER2 LOAD: LOAD Position */
#define CM3DS_MPS2_DUALTIMER2_LOAD_Msk            (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER2_LOAD_Pos)      /* CM3DS_MPS2_DUALTIMER2 LOAD: LOAD Mask */

#define CM3DS_MPS2_DUALTIMER2_VALUE_Pos           0                                                /* CM3DS_MPS2_DUALTIMER2 VALUE: VALUE Position */
#define CM3DS_MPS2_DUALTIMER2_VALUE_Msk           (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER2_VALUE_Pos)     /* CM3DS_MPS2_DUALTIMER2 VALUE: VALUE Mask */

#define CM3DS_MPS2_DUALTIMER2_CTRL_EN_Pos         7                                                /* CM3DS_MPS2_DUALTIMER2 CTRL_EN: CTRL Enable Position */
#define CM3DS_MPS2_DUALTIMER2_CTRL_EN_Msk         (0x1ul << CM3DS_MPS2_DUALTIMER2_CTRL_EN_Pos)          /* CM3DS_MPS2_DUALTIMER2 CTRL_EN: CTRL Enable Mask */

#define CM3DS_MPS2_DUALTIMER2_CTRL_MODE_Pos       6                                                /* CM3DS_MPS2_DUALTIMER2 CTRL_MODE: CTRL MODE Position */
#define CM3DS_MPS2_DUALTIMER2_CTRL_MODE_Msk       (0x1ul << CM3DS_MPS2_DUALTIMER2_CTRL_MODE_Pos)        /* CM3DS_MPS2_DUALTIMER2 CTRL_MODE: CTRL MODE Mask */

#define CM3DS_MPS2_DUALTIMER2_CTRL_INTEN_Pos      5                                                /* CM3DS_MPS2_DUALTIMER2 CTRL_INTEN: CTRL Int Enable Position */
#define CM3DS_MPS2_DUALTIMER2_CTRL_INTEN_Msk      (0x1ul << CM3DS_MPS2_DUALTIMER2_CTRL_INTEN_Pos)       /* CM3DS_MPS2_DUALTIMER2 CTRL_INTEN: CTRL Int Enable Mask */

#define CM3DS_MPS2_DUALTIMER2_CTRL_PRESCALE_Pos   2                                                /* CM3DS_MPS2_DUALTIMER2 CTRL_PRESCALE: CTRL PRESCALE Position */
#define CM3DS_MPS2_DUALTIMER2_CTRL_PRESCALE_Msk   (0x3ul << CM3DS_MPS2_DUALTIMER2_CTRL_PRESCALE_Pos)    /* CM3DS_MPS2_DUALTIMER2 CTRL_PRESCALE: CTRL PRESCALE Mask */

#define CM3DS_MPS2_DUALTIMER2_CTRL_SIZE_Pos       1                                                /* CM3DS_MPS2_DUALTIMER2 CTRL_SIZE: CTRL SIZE Position */
#define CM3DS_MPS2_DUALTIMER2_CTRL_SIZE_Msk       (0x1ul << CM3DS_MPS2_DUALTIMER2_CTRL_SIZE_Pos)        /* CM3DS_MPS2_DUALTIMER2 CTRL_SIZE: CTRL SIZE Mask */

#define CM3DS_MPS2_DUALTIMER2_CTRL_ONESHOOT_Pos   0                                                /* CM3DS_MPS2_DUALTIMER2 CTRL_ONESHOOT: CTRL ONESHOOT Position */
#define CM3DS_MPS2_DUALTIMER2_CTRL_ONESHOOT_Msk   (0x1ul << CM3DS_MPS2_DUALTIMER2_CTRL_ONESHOOT_Pos)    /* CM3DS_MPS2_DUALTIMER2 CTRL_ONESHOOT: CTRL ONESHOOT Mask */

#define CM3DS_MPS2_DUALTIMER2_INTCLR_Pos          0                                                /* CM3DS_MPS2_DUALTIMER2 INTCLR: INT Clear Position */
#define CM3DS_MPS2_DUALTIMER2_INTCLR_Msk          (0x1ul << CM3DS_MPS2_DUALTIMER2_INTCLR_Pos)           /* CM3DS_MPS2_DUALTIMER2 INTCLR: INT Clear  Mask */

#define CM3DS_MPS2_DUALTIMER2_RAWINTSTAT_Pos      0                                                /* CM3DS_MPS2_DUALTIMER2 RAWINTSTAT: Raw Int Status Position */
#define CM3DS_MPS2_DUALTIMER2_RAWINTSTAT_Msk      (0x1ul << CM3DS_MPS2_DUALTIMER2_RAWINTSTAT_Pos)       /* CM3DS_MPS2_DUALTIMER2 RAWINTSTAT: Raw Int Status Mask */

#define CM3DS_MPS2_DUALTIMER2_MASKINTSTAT_Pos     0                                                /* CM3DS_MPS2_DUALTIMER2 MASKINTSTAT: Mask Int Status Position */
#define CM3DS_MPS2_DUALTIMER2_MASKINTSTAT_Msk     (0x1ul << CM3DS_MPS2_DUALTIMER2_MASKINTSTAT_Pos)      /* CM3DS_MPS2_DUALTIMER2 MASKINTSTAT: Mask Int Status Mask */

#define CM3DS_MPS2_DUALTIMER2_BGLOAD_Pos          0                                                /* CM3DS_MPS2_DUALTIMER2 BGLOAD: Background Load Position */
#define CM3DS_MPS2_DUALTIMER2_BGLOAD_Msk          (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER2_BGLOAD_Pos)    /* CM3DS_MPS2_DUALTIMER2 BGLOAD: Background Load Mask */


typedef struct
{
	__IO uint32_t TimerLoad;                   /* Offset: 0x000 (R/W) Timer Load */
	__I  uint32_t TimerValue;                  /* Offset: 0x000 (R/W) Timer Counter Current Value */
	__IO uint32_t TimerControl;                /* Offset: 0x000 (R/W) Timer Control */
	__O  uint32_t TimerIntClr;                 /* Offset: 0x000 (R/W) Timer Interrupt Clear */
	__I  uint32_t TimerRIS;                    /* Offset: 0x000 (R/W) Timer Raw Interrupt Status */
	__I  uint32_t TimerMIS;                    /* Offset: 0x000 (R/W) Timer Masked Interrupt Status */
	__IO uint32_t TimerBGLoad;                 /* Offset: 0x000 (R/W) Background Load Register */
}DUALTIMER_SINGLE_TypeDef;

#define CM3DS_MPS2_DUALTIMER_LOAD_Pos             0                                               /* CM3DS_MPS2_DUALTIMER LOAD: LOAD Position */
#define CM3DS_MPS2_DUALTIMER_LOAD_Msk             (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER_LOAD_Pos)      /* CM3DS_MPS2_DUALTIMER LOAD: LOAD Mask */

#define CM3DS_MPS2_DUALTIMER_VALUE_Pos            0                                               /* CM3DS_MPS2_DUALTIMER VALUE: VALUE Position */
#define CM3DS_MPS2_DUALTIMER_VALUE_Msk            (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER_VALUE_Pos)     /* CM3DS_MPS2_DUALTIMER VALUE: VALUE Mask */

#define CM3DS_MPS2_DUALTIMER_CTRL_EN_Pos          7                                               /* CM3DS_MPS2_DUALTIMER CTRL_EN: CTRL Enable Position */
#define CM3DS_MPS2_DUALTIMER_CTRL_EN_Msk          (0x1ul << CM3DS_MPS2_DUALTIMER_CTRL_EN_Pos)          /* CM3DS_MPS2_DUALTIMER CTRL_EN: CTRL Enable Mask */

#define CM3DS_MPS2_DUALTIMER_CTRL_MODE_Pos        6                                               /* CM3DS_MPS2_DUALTIMER CTRL_MODE: CTRL MODE Position */
#define CM3DS_MPS2_DUALTIMER_CTRL_MODE_Msk        (0x1ul << CM3DS_MPS2_DUALTIMER_CTRL_MODE_Pos)        /* CM3DS_MPS2_DUALTIMER CTRL_MODE: CTRL MODE Mask */

#define CM3DS_MPS2_DUALTIMER_CTRL_INTEN_Pos       5                                               /* CM3DS_MPS2_DUALTIMER CTRL_INTEN: CTRL Int Enable Position */
#define CM3DS_MPS2_DUALTIMER_CTRL_INTEN_Msk       (0x1ul << CM3DS_MPS2_DUALTIMER_CTRL_INTEN_Pos)       /* CM3DS_MPS2_DUALTIMER CTRL_INTEN: CTRL Int Enable Mask */

#define CM3DS_MPS2_DUALTIMER_CTRL_PRESCALE_Pos    2                                               /* CM3DS_MPS2_DUALTIMER CTRL_PRESCALE: CTRL PRESCALE Position */
#define CM3DS_MPS2_DUALTIMER_CTRL_PRESCALE_Msk    (0x3ul << CM3DS_MPS2_DUALTIMER_CTRL_PRESCALE_Pos)    /* CM3DS_MPS2_DUALTIMER CTRL_PRESCALE: CTRL PRESCALE Mask */

#define CM3DS_MPS2_DUALTIMER_CTRL_SIZE_Pos        1                                               /* CM3DS_MPS2_DUALTIMER CTRL_SIZE: CTRL SIZE Position */
#define CM3DS_MPS2_DUALTIMER_CTRL_SIZE_Msk        (0x1ul << CM3DS_MPS2_DUALTIMER_CTRL_SIZE_Pos)        /* CM3DS_MPS2_DUALTIMER CTRL_SIZE: CTRL SIZE Mask */

#define CM3DS_MPS2_DUALTIMER_CTRL_ONESHOOT_Pos    0                                               /* CM3DS_MPS2_DUALTIMER CTRL_ONESHOOT: CTRL ONESHOOT Position */
#define CM3DS_MPS2_DUALTIMER_CTRL_ONESHOOT_Msk    (0x1ul << CM3DS_MPS2_DUALTIMER_CTRL_ONESHOOT_Pos)    /* CM3DS_MPS2_DUALTIMER CTRL_ONESHOOT: CTRL ONESHOOT Mask */

#define CM3DS_MPS2_DUALTIMER_INTCLR_Pos           0                                               /* CM3DS_MPS2_DUALTIMER INTCLR: INT Clear Position */
#define CM3DS_MPS2_DUALTIMER_INTCLR_Msk           (0x1ul << CM3DS_MPS2_DUALTIMER_INTCLR_Pos)           /* CM3DS_MPS2_DUALTIMER INTCLR: INT Clear  Mask */

#define CM3DS_MPS2_DUALTIMER_RAWINTSTAT_Pos       0                                               /* CM3DS_MPS2_DUALTIMER RAWINTSTAT: Raw Int Status Position */
#define CM3DS_MPS2_DUALTIMER_RAWINTSTAT_Msk       (0x1ul << CM3DS_MPS2_DUALTIMER_RAWINTSTAT_Pos)       /* CM3DS_MPS2_DUALTIMER RAWINTSTAT: Raw Int Status Mask */

#define CM3DS_MPS2_DUALTIMER_MASKINTSTAT_Pos      0                                               /* CM3DS_MPS2_DUALTIMER MASKINTSTAT: Mask Int Status Position */
#define CM3DS_MPS2_DUALTIMER_MASKINTSTAT_Msk      (0x1ul << CM3DS_MPS2_DUALTIMER_MASKINTSTAT_Pos)      /* CM3DS_MPS2_DUALTIMER MASKINTSTAT: Mask Int Status Mask */

#define CM3DS_MPS2_DUALTIMER_BGLOAD_Pos           0                                               /* CM3DS_MPS2_DUALTIMER BGLOAD: Background Load Position */
#define CM3DS_MPS2_DUALTIMER_BGLOAD_Msk           (0xFFFFFFFFul << CM3DS_MPS2_DUALTIMER_BGLOAD_Pos)    /* CM3DS_MPS2_DUALTIMER BGLOAD: Background Load Mask */

/*--------- added by gsl 2018-05-29 ---------*/
/*---------------------- Analog Digital Convertion (ADC) ---------------------*/
typedef struct
{
	__I uint32_t  ADC_DBR_1_0;              /* Offset: 0x000 (R/ ) DATA Buffer Register1 and Register0 */
	__I uint32_t  ADC_DBR_3_2;              /* Offset: 0x004 (R/ ) DATA Buffer Register3 and Register2 */
	__I uint32_t  ADC_DBR_5_4;              /* Offset: 0x008 (R/ ) DATA Buffer Register5 and Register4 */	
	__I uint32_t  ADC_DBR_7_6;              /* Offset: 0x00C (R/ ) DATA Buffer Register7 and Register6 */	
	__I uint32_t  ADC_DR;   			           /* Offset: 0x010	(R/ ) DATA Register */		
		uint32_t  RESERVED0[3];	
	__IO uint32_t  ADC_CSR_0;                /* Offset: 0x020 (R/W) Control and Status Register0 */	
	__IO uint32_t  ADC_CSR_1;                /* Offset: 0x024 (R/W) Control and Status Register1 */		
	__IO uint32_t  ADC_CR_1;                 /* Offset: 0x028 (R/W) Configuration Register1 */		
	__IO uint32_t  ADC_CR_2_3;               /* Offset: 0x02C (R/W) Configuration Register2 and Register3 */		
	__IO uint32_t  ADC_TDR;                  /* Offset: 0x030 (R/W) schmitt Trigger Disable Register */		

}ADC_TypeDef;


/*-------------------- General Purpose Input Output (GPIO) -------------------*/
typedef struct
{
	__IO uint32_t  DATA;                     /* Offset: 0x000 (R/W) DATA Register */
	__IO uint32_t  DATAOUT;                  /* Offset: 0x004 (R/W) Data Output Latch Register */
		uint32_t  RESERVED0[2];
	__IO uint32_t  OUTENABLESET;             /* Offset: 0x010 (R/W) Output Enable Set Register */
	__IO uint32_t  OUTENABLECLR;             /* Offset: 0x014 (R/W) Output Enable Clear Register */
	__IO uint32_t  ALTFUNCSET;               /* Offset: 0x018 (R/W) Alternate Function Set Register */
	__IO uint32_t  ALTFUNCCLR;               /* Offset: 0x01C (R/W) Alternate Function Clear Register */
	__IO uint32_t  INTENSET;                 /* Offset: 0x020 (R/W) Interrupt Enable Set Register */
	__IO uint32_t  INTENCLR;                 /* Offset: 0x024 (R/W) Interrupt Enable Clear Register */
	__IO uint32_t  INTTYPESET;               /* Offset: 0x028 (R/W) Interrupt Type Set Register */
	__IO uint32_t  INTTYPECLR;               /* Offset: 0x02C (R/W) Interrupt Type Clear Register */
	__IO uint32_t  INTPOLSET;                /* Offset: 0x030 (R/W) Interrupt Polarity Set Register */
	__IO uint32_t  INTPOLCLR;                /* Offset: 0x034 (R/W) Interrupt Polarity Clear Register */
	union{
		__I uint32_t  INTSTATUS;              /* Offset: 0x038 (R/ ) Interrupt Status Register */
		__O uint32_t  INTCLEAR;               /* Offset: 0x038 ( /W) Interrupt Clear Register */
	};
		uint32_t RESERVED1[241];
	__IO uint32_t BYTE0_MASKED[256];            /* Offset: 0x400 - 0x7FC Lower byte Masked Access Register (R/W) */
	__IO uint32_t BYTE1_MASKED[256];            /* Offset: 0x800 - 0xBFC Upper byte Masked Access Register (R/W) */
	__IO uint32_t BYTE2_MASKED[256];            /* Offset: 0xC00 - 0xFFC Lower byte Masked Access Register (R/W) */
	__IO uint32_t BYTE3_MASKED[256];            /* Offset: 0x1000 - 0x13FC Upper byte Masked Access Register (R/W) */		
}GPIO_TypeDef;

#define CM3DS_MPS2_GPIO_DATA_Pos            0                                                   /* CM3DS_MPS2_GPIO DATA: DATA Position */
#define CM3DS_MPS2_GPIO_DATA_Msk            (0xFFFFFFFFul << CM3DS_MPS2_GPIO_DATA_Pos)          /* CM3DS_MPS2_GPIO DATA: DATA Mask */

#define CM3DS_MPS2_GPIO_DATAOUT_Pos         0                                                   /* CM3DS_MPS2_GPIO DATAOUT: DATAOUT Position */
#define CM3DS_MPS2_GPIO_DATAOUT_Msk         (0xFFFFFFFFul << CM3DS_MPS2_GPIO_DATAOUT_Pos)       /* CM3DS_MPS2_GPIO DATAOUT: DATAOUT Mask */

#define CM3DS_MPS2_GPIO_OUTENSET_Pos        0                                                   /* CM3DS_MPS2_GPIO OUTEN: OUTEN Position */
#define CM3DS_MPS2_GPIO_OUTENSET_Msk        (0xFFFFFFFFul << CM3DS_MPS2_GPIO_OUTEN_Pos)         /* CM3DS_MPS2_GPIO OUTEN: OUTEN Mask */

#define CM3DS_MPS2_GPIO_OUTENCLR_Pos        0                                                   /* CM3DS_MPS2_GPIO OUTEN: OUTEN Position */
#define CM3DS_MPS2_GPIO_OUTENCLR_Msk        (0xFFFFFFFFul << CM3DS_MPS2_GPIO_OUTEN_Pos)         /* CM3DS_MPS2_GPIO OUTEN: OUTEN Mask */

#define CM3DS_MPS2_GPIO_ALTFUNCSET_Pos      0                                                   /* CM3DS_MPS2_GPIO ALTFUNC: ALTFUNC Position */
#define CM3DS_MPS2_GPIO_ALTFUNCSET_Msk      (0xFFFFFFFFul << CM3DS_MPS2_GPIO_ALTFUNC_Pos)       /* CM3DS_MPS2_GPIO ALTFUNC: ALTFUNC Mask */

#define CM3DS_MPS2_GPIO_ALTFUNCCLR_Pos      0                                                   /* CM3DS_MPS2_GPIO ALTFUNC: ALTFUNC Position */
#define CM3DS_MPS2_GPIO_ALTFUNCCLR_Msk      (0xFFFFFFFFul << CM3DS_MPS2_GPIO_ALTFUNC_Pos)       /* CM3DS_MPS2_GPIO ALTFUNC: ALTFUNC Mask */

#define CM3DS_MPS2_GPIO_INTENSET_Pos        0                                                   /* CM3DS_MPS2_GPIO INTEN: INTEN Position */
#define CM3DS_MPS2_GPIO_INTENSET_Msk        (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTEN_Pos)         /* CM3DS_MPS2_GPIO INTEN: INTEN Mask */

#define CM3DS_MPS2_GPIO_INTENCLR_Pos        0                                                   /* CM3DS_MPS2_GPIO INTEN: INTEN Position */
#define CM3DS_MPS2_GPIO_INTENCLR_Msk        (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTEN_Pos)         /* CM3DS_MPS2_GPIO INTEN: INTEN Mask */

#define CM3DS_MPS2_GPIO_INTTYPESET_Pos      0                                                   /* CM3DS_MPS2_GPIO INTTYPE: INTTYPE Position */
#define CM3DS_MPS2_GPIO_INTTYPESET_Msk      (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTTYPE_Pos)       /* CM3DS_MPS2_GPIO INTTYPE: INTTYPE Mask */

#define CM3DS_MPS2_GPIO_INTTYPECLR_Pos      0                                                   /* CM3DS_MPS2_GPIO INTTYPE: INTTYPE Position */
#define CM3DS_MPS2_GPIO_INTTYPECLR_Msk      (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTTYPE_Pos)       /* CM3DS_MPS2_GPIO INTTYPE: INTTYPE Mask */

#define CM3DS_MPS2_GPIO_INTPOLSET_Pos       0                                                   /* CM3DS_MPS2_GPIO INTPOL: INTPOL Position */
#define CM3DS_MPS2_GPIO_INTPOLSET_Msk       (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTPOL_Pos)        /* CM3DS_MPS2_GPIO INTPOL: INTPOL Mask */

#define CM3DS_MPS2_GPIO_INTPOLCLR_Pos       0                                                   /* CM3DS_MPS2_GPIO INTPOL: INTPOL Position */
#define CM3DS_MPS2_GPIO_INTPOLCLR_Msk       (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTPOL_Pos)        /* CM3DS_MPS2_GPIO INTPOL: INTPOL Mask */

#define CM3DS_MPS2_GPIO_INTSTATUS_Pos       0                                                   /* CM3DS_MPS2_GPIO INTSTATUS: INTSTATUS Position */
#define CM3DS_MPS2_GPIO_INTSTATUS_Msk       (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTSTATUS_Pos)     /* CM3DS_MPS2_GPIO INTSTATUS: INTSTATUS Mask */

#define CM3DS_MPS2_GPIO_INTCLEAR_Pos        0                                                   /* CM3DS_MPS2_GPIO INTCLEAR: INTCLEAR Position */
#define CM3DS_MPS2_GPIO_INTCLEAR_Msk        (0xFFFFFFFFul << CM3DS_MPS2_GPIO_INTCLEAR_Pos)      /* CM3DS_MPS2_GPIO INTCLEAR: INTCLEAR Mask */

#define CM3DS_MPS2_GPIO_MASKBYTE0_Pos       0                                                   /* CM3DS_MPS2_GPIO MASKLOWBYTE: MASKLOWBYTE Position */
#define CM3DS_MPS2_GPIO_MASKBYTE0_Msk       (0x000000FFul << CM3DS_MPS2_GPIO_MASKBYTE0_Pos)     /* CM3DS_MPS2_GPIO MASKLOWBYTE: MASKLOWBYTE Mask */

#define CM3DS_MPS2_GPIO_MASKBYTE1_Pos       0                                                   /* CM3DS_MPS2_GPIO MASKHIGHBYTE: MASKHIGHBYTE Position */
#define CM3DS_MPS2_GPIO_MASKBYTE1_Msk       (0x0000FF00ul << CM3DS_MPS2_GPIO_MASKBYTE1_Pos)     /* CM3DS_MPS2_GPIO MASKHIGHBYTE: MASKHIGHBYTE Mask */

#define CM3DS_MPS2_GPIO_MASKBYTE2_Pos       0                                                   /* CM3DS_MPS2_GPIO MASKLOWBYTE: MASKLOWBYTE Position */
#define CM3DS_MPS2_GPIO_MASKBYTE2_Msk       (0x00FF0000ul << CM3DS_MPS2_GPIO_MASKBYTE2_Pos)     /* CM3DS_MPS2_GPIO MASKLOWBYTE: MASKLOWBYTE Mask */

#define CM3DS_MPS2_GPIO_MASKBYTE3_Pos       0                                                   /* CM3DS_MPS2_GPIO MASKHIGHBYTE: MASKHIGHBYTE Position */
#define CM3DS_MPS2_GPIO_MASKBYTE3_Msk       (0xFF000000ul << CM3DS_MPS2_GPIO_MASKBYTE3_Pos)     /* CM3DS_MPS2_GPIO MASKHIGHBYTE: MASKHIGHBYTE Mask */

/*------------- System Control (SYSCON) --------------------------------------*/
typedef struct
{
	__IO uint32_t  REMAP;                    /* Offset: 0x000 (R/W) Remap Control Register */
	__IO uint32_t  PMUCTRL;                  /* Offset: 0x004 (R/W) PMU Control Register */
	__IO uint32_t  RESETOP;                  /* Offset: 0x008 (R/W) Reset Option Register */
	__IO uint32_t  RESERVED0;
	__IO uint32_t  RSTINFO;                  /* Offset: 0x010 (R/W) Reset Information Register */
	//__IO uint32_t  RESETPERI;		   /* Offset: 0x014 (R/W) Peripherals Reset Control Register */
	
}SYSCON_TypeDef;

#define CM3DS_MPS2_SYSCON_REMAP_Pos                 0
#define CM3DS_MPS2_SYSCON_REMAP_Msk                 (0x01ul << CM3DS_MPS2_SYSCON_REMAP_Pos)               /* CM3DS_MPS2_SYSCON MEME_CTRL: REMAP Mask */

#define CM3DS_MPS2_SYSCON_PMUCTRL_EN_Pos            0
#define CM3DS_MPS2_SYSCON_PMUCTRL_EN_Msk            (0x01ul << CM3DS_MPS2_SYSCON_PMUCTRL_EN_Pos)          /* CM3DS_MPS2_SYSCON PMUCTRL: PMUCTRL ENABLE Mask */

#define CM3DS_MPS2_SYSCON_LOCKUPRST_RESETOP_Pos     0
#define CM3DS_MPS2_SYSCON_LOCKUPRST_RESETOP_Msk     (0x01ul << CM3DS_MPS2_SYSCON_LOCKUPRST_RESETOP_Pos)   /* CM3DS_MPS2_SYSCON SYS_CTRL: LOCKUP RESET ENABLE Mask */

#define CM3DS_MPS2_SYSCON_RSTINFO_SYSRESETREQ_Pos   0
#define CM3DS_MPS2_SYSCON_RSTINFO_SYSRESETREQ_Msk   (0x00001ul << CM3DS_MPS2_SYSCON_RSTINFO_SYSRESETREQ_Pos) /* CM3DS_MPS2_SYSCON RSTINFO: SYSRESETREQ Mask */

#define CM3DS_MPS2_SYSCON_RSTINFO_WDOGRESETREQ_Pos  1
#define CM3DS_MPS2_SYSCON_RSTINFO_WDOGRESETREQ_Msk  (0x00001ul << CM3DS_MPS2_SYSCON_RSTINFO_WDOGRESETREQ_Pos) /* CM3DS_MPS2_SYSCON RSTINFO: WDOGRESETREQ Mask */

#define CM3DS_MPS2_SYSCON_RSTINFO_LOCKUPRESET_Pos   2
#define CM3DS_MPS2_SYSCON_RSTINFO_LOCKUPRESET_Msk   (0x00001ul << CM3DS_MPS2_SYSCON_RSTINFO_LOCKUPRESET_Pos) /* CM3DS_MPS2_SYSCON RSTINFO: LOCKUPRESET Mask */

//#define CM3DS_MPS2_SYSCON_RESETPERI_SRAM_Pos   0
//#define CM3DS_MPS2_SYSCON_RESETPERI_SRAM_Msk   (0x00001ul << CM3DS_MPS2_SYSCON_RESETPERI_SRAM_Pos) /* CM3DS_MPS2_SYSCON RESETPERI: SRAM Reset Mask */

//#define CM3DS_MPS2_SYSCON_RESETPERI_GPIO_Pos   1
//#define CM3DS_MPS2_SYSCON_RESETPERI_GPIO_Msk   (0x00001ul << CM3DS_MPS2_SYSCON_RESETPERI_GPIO_Pos) /* CM3DS_MPS2_SYSCON RESETPERI: GPIO Reset Mask */

/*------------- APB peripherals soft reset control --------------------------------------*/
typedef struct
{
	__IO uint32_t  RESETPERI;                /* Offset: 0x000 (R/W) Peripherals Reset Control Register */
	
}PERI_RSTCTL_TypeDef;

#define PERI_RSTCTL_TIMER0_Pos   0
#define PERI_RSTCTL_TIMER0_Msk   (0x00001ul << PERI_RSTCTL_TIMER0_Pos) /* RESETPERI: Timer0 Reset Mask */

#define PERI_RSTCTL_TIMER1_Pos   1
#define PERI_RSTCTL_TIMER1_Msk   (0x00001ul << PERI_RSTCTL_TIMER1_Pos) /* RESETPERI: Timer1 Reset Mask */

#define PERI_RSTCTL_DTIMER_Pos   2
#define PERI_RSTCTL_DTIMER_Msk   (0x00001ul << PERI_RSTCTL_DTIMER_Pos) /* RESETPERI: DTIMER Reset Mask */

#define PERI_RSTCTL_UART0_Pos   3
#define PERI_RSTCTL_UART0_Msk   (0x00001ul << PERI_RSTCTL_UART0_Pos) /* RESETPERI: UART0 Reset Mask */

#define PERI_RSTCTL_UART1_Pos   4
#define PERI_RSTCTL_UART1_Msk   (0x00001ul << PERI_RSTCTL_UART1_Pos) /* RESETPERI: UART1 Reset Mask */

#define PERI_RSTCTL_I2C_Pos   5
#define PERI_RSTCTL_I2C_Msk   (0x00001ul << PERI_RSTCTL_I2C_Pos) /* RESETPERI: I2C Reset Mask */

#define PERI_RSTCTL_ADC_Pos   6
#define PERI_RSTCTL_ADC_Msk   (0x00001ul << PERI_RSTCTL_ADC_Pos) /* RESETPERI: ADC Reset Mask */

#define PERI_RSTCTL_WDOG_Pos   7
#define PERI_RSTCTL_WDOG_Msk   (0x00001ul << PERI_RSTCTL_WDOG_Pos) /* RESETPERI: WDOG Reset Mask */

#define PERI_RSTCTL_SSP0_Pos   8
#define PERI_RSTCTL_SSP0_Msk   (0x00001ul << PERI_RSTCTL_SSP0_Pos) /* RESETPERI: SSP0 Reset Mask */

#define PERI_RSTCTL_SSP1_Pos   9
#define PERI_RSTCTL_SSP1_Msk   (0x00001ul << PERI_RSTCTL_SSP1_Pos) /* RESETPERI: SSP1 Reset Mask */



/*------------------- Watchdog ----------------------------------------------*/
typedef struct
{
	__IO uint32_t  LOAD;                   /* Offset: 0x000 (R/W) Watchdog Load Register */
	__I  uint32_t  VALUE;                  /* Offset: 0x004 (R/ ) Watchdog Value Register */
	__IO uint32_t  CTRL;                   /* Offset: 0x008 (R/W) Watchdog Control Register */
	__O  uint32_t  INTCLR;                 /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register */
	__I  uint32_t  RAWINTSTAT;             /* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register */
	__I  uint32_t  MASKINTSTAT;            /* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register */
		uint32_t RESERVED0[762];
	__IO uint32_t  LOCK;                   /* Offset: 0xC00 (R/W) Watchdog Lock Register */
		uint32_t RESERVED1[191];
	__IO uint32_t  ITCR;                   /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register */
	__O uint32_t  ITOP;                   /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register */
}WATCHDOG_TypeDef;

#define Watchdog_LOAD_Pos               0                                              /* CM3DS_MPS2_Watchdog LOAD: LOAD Position */
#define Watchdog_LOAD_Msk              (0xFFFFFFFFul << Watchdog_LOAD_Pos)       /* CM3DS_MPS2_Watchdog LOAD: LOAD Mask */

#define Watchdog_VALUE_Pos              0                                              /* CM3DS_MPS2_Watchdog VALUE: VALUE Position */
#define Watchdog_VALUE_Msk             (0xFFFFFFFFul << Watchdog_VALUE_Pos)      /* CM3DS_MPS2_Watchdog VALUE: VALUE Mask */

#define Watchdog_CTRL_RESEN_Pos         1                                              /* CM3DS_MPS2_Watchdog CTRL_RESEN: Enable Reset Output Position */
#define Watchdog_CTRL_RESEN_Msk        (0x1ul << Watchdog_CTRL_RESEN_Pos)        /* CM3DS_MPS2_Watchdog CTRL_RESEN: Enable Reset Output Mask */

#define Watchdog_CTRL_INTEN_Pos         0                                              /* CM3DS_MPS2_Watchdog CTRL_INTEN: Int Enable Position */
#define Watchdog_CTRL_INTEN_Msk        (0x1ul << Watchdog_CTRL_INTEN_Pos)        /* CM3DS_MPS2_Watchdog CTRL_INTEN: Int Enable Mask */

#define Watchdog_INTCLR_Pos             0                                   /* CM3DS_MPS2_Watchdog INTCLR: Int Clear Position */
#define Watchdog_INTCLR_Msk            (0x1ul << Watchdog_INTCLR_Pos)            /* CM3DS_MPS2_Watchdog INTCLR: Int Clear Mask */

#define Watchdog_RAWINTSTAT_Pos         0                                   /* CM3DS_MPS2_Watchdog RAWINTSTAT: Raw Int Status Position */
#define Watchdog_RAWINTSTAT_Msk        (0x1ul << Watchdog_RAWINTSTAT_Pos)        /* CM3DS_MPS2_Watchdog RAWINTSTAT: Raw Int Status Mask */

#define Watchdog_MASKINTSTAT_Pos        0                                   /* CM3DS_MPS2_Watchdog MASKINTSTAT: Mask Int Status Position */
#define Watchdog_MASKINTSTAT_Msk       (0x1ul << Watchdog_MASKINTSTAT_Pos)       /* CM3DS_MPS2_Watchdog MASKINTSTAT: Mask Int Status Mask */

#define Watchdog_LOCK_Pos               0                                   /* CM3DS_MPS2_Watchdog LOCK: LOCK Position */
#define Watchdog_LOCK_Msk              (0x1ul << Watchdog_LOCK_Pos)              /* CM3DS_MPS2_Watchdog LOCK: LOCK Mask */

#define Watchdog_INTEGTESTEN_Pos        0                                   /* CM3DS_MPS2_Watchdog INTEGTESTEN: Integration Test Enable Position */
#define Watchdog_INTEGTESTEN_Msk       (0x1ul << Watchdog_INTEGTESTEN_Pos)       /* CM3DS_MPS2_Watchdog INTEGTESTEN: Integration Test Enable Mask */

#define Watchdog_INTEGTESTOUTSET_Pos    1                                   /* CM3DS_MPS2_Watchdog INTEGTESTOUTSET: Integration Test Output Set Position */
#define Watchdog_INTEGTESTOUTSET_Msk   (0x1ul << Watchdog_INTEGTESTOUTSET_Pos)   /* CM3DS_MPS2_Watchdog INTEGTESTOUTSET: Integration Test Output Set Mask */


/*------------------- I2C ----------------------------------------------*/
typedef struct
{
	__IO uint32_t  CONTROL;
	__IO uint32_t  FREQDIV;
	__IO uint32_t  OWNADDR;
	__IO uint32_t  SLVADDR;
	__IO uint32_t  TXDATA;
	__O  uint32_t  RXDATA;
	__O  uint32_t  STATUS1;
	__O  uint32_t  STATUS2;
}I2C_TypeDef;

//#define CM3DS_MPS2_I2C_SCL_Pos  0
//#define CM3DS_MPS2_I2C_SCL_Msk  (1UL<<CM3DS_MPS2_I2C_SCL_Pos)

//#define CM3DS_MPS2_I2C_SDA_Pos  1
//#define CM3DS_MPS2_I2C_SDA_Msk  (1UL<<CM3DS_MPS2_I2C_SDA_Pos)

#define CM3DS_MPS2_I2C_TX_ENA_Pos  0
#define CM3DS_MPS2_I2C_TX_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_TX_ENA_Pos)

#define CM3DS_MPS2_I2C_TX_IRQ_ENA_Pos  1
#define CM3DS_MPS2_I2C_TX_IRQ_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_TX_IRQ_ENA_Pos)

#define CM3DS_MPS2_I2C_TX_BUFFER_LEVEL_Pos  2
#define CM3DS_MPS2_I2C_TX_BUFFER_LEVEL_Msk  (0x3UL<<CM3DS_MPS2_I2C_TX_BUFFER_LEVEL_Pos)

#define CM3DS_MPS2_I2C_START_SET_Pos  4
#define CM3DS_MPS2_I2C_START_SET_Msk  (0x1UL<<CM3DS_MPS2_I2C_START_SET_Pos)

#define CM3DS_MPS2_I2C_STOP_SET_Pos  5
#define CM3DS_MPS2_I2C_STOP_SET_Msk  (0x1UL<<CM3DS_MPS2_I2C_STOP_SET_Pos)

#define CM3DS_MPS2_I2C_AUTO_STOP_SET_Pos  6
#define CM3DS_MPS2_I2C_AUTO_STOP_SET_Msk  (0x1UL<<CM3DS_MPS2_I2C_AUTO_STOP_SET_Pos)

#define CM3DS_MPS2_I2C_RX_ENA_Pos  8
#define CM3DS_MPS2_I2C_RX_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_RX_ENA_Pos)

#define CM3DS_MPS2_I2C_RX_IRQ_ENA_Pos  9
#define CM3DS_MPS2_I2C_RX_IRQ_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_RX_IRQ_ENA_Pos)

#define CM3DS_MPS2_I2C_RX_BUFFER_LEVEL_Pos  10
#define CM3DS_MPS2_I2C_RX_BUFFER_LEVEL_Msk  (0x3UL<<CM3DS_MPS2_I2C_RX_BUFFER_LEVEL_Pos)

#define CM3DS_MPS2_I2C_NACK_ENA_Pos  12
#define CM3DS_MPS2_I2C_NACK_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_NACK_ENA_Pos)

#define CM3DS_MPS2_I2C_TC_IRQ_ENA_Pos  13
#define CM3DS_MPS2_I2C_TC_IRQ_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_TC_IRQ_ENA_Pos)

#define CM3DS_MPS2_I2C_STOP_IRQ_ENA_Pos  14
#define CM3DS_MPS2_I2C_STOP_IRQ_ENA_Msk  (1UL<<CM3DS_MPS2_I2C_STOP_IRQ_ENA_Pos)

#define CM3DS_MPS2_I2C_WORK_MODE_Pos  15
#define CM3DS_MPS2_I2C_WORK_MODE_Msk  (0x1UL<<CM3DS_MPS2_I2C_WORK_MODE_Pos)

#define CM3DS_MPS2_I2C_TX_NUM_Pos  16
#define CM3DS_MPS2_I2C_TX_NUM_Msk  (0xFUL<<CM3DS_MPS2_I2C_TX_NUM_Pos)

#define CM3DS_MPS2_I2C_SWRST_Pos 31
#define CM3DS_MPS2_I2C_SWRST_Msk (1UL<<CM3DS_MPS2_I2C_SWRST_Pos)


/******************************************************************************/
/*                        SSP Peripheral declaration                          */
/******************************************************************************/

typedef struct                   // Document DDI0194G_SPI_pl022_r1p3_trm.pdf
{
	__IO uint32_t CR0;           // Offset: 0x000 (R/W)  Control register 0
                                 //                        [31:16] : Reserved
                                 //                         [15:8] : Serial clock rate
                                 //                            [7] : SSPCLKOUT phase,    applicable to Motorola SPI frame format only
                                 //                            [6] : SSPCLKOUT polarity, applicable to Motorola SPI frame format only
                                 //                          [5:4] : Frame format
                                 //                          [3:0] : Data Size Select
	__IO uint32_t CR1;           // Offset: 0x004 (R/W)  Control register 1
                                 //                         [31:4] : Reserved
                                 //                            [3] : Slave-mode output disable
                                 //                            [2] : Master or slave mode select
                                 //                            [1] : Synchronous serial port enable
                                 //                            [0] : Loop back mode
	__IO uint32_t DR;            // Offset: 0x008 (R/W)  Data register
                                 //                        [31:16] : Reserved
                                 //                         [15:0] : Transmit/Receive FIFO
	__I  uint32_t SR;            // Offset: 0x00C (R/ )  Status register
                                 //                         [31:5] : Reserved
                                 //                            [4] : PrimeCell SSP busy flag
                                 //                            [3] : Receive FIFO full
                                 //                            [2] : Receive FIFO not empty
                                 //                            [1] : Transmit FIFO not full
                                 //                            [0] : Transmit FIFO empty
	__IO uint32_t CPSR;          // Offset: 0x010 (R/W)  Clock prescale register
                                 //                         [31:8] : Reserved
                                 //                          [8:0] : Clock prescale divisor
	__IO uint32_t IMSC;          // Offset: 0x014 (R/W)  Interrupt mask set or clear register
                                 //                         [31:4] : Reserved
                                 //                            [3] : Transmit FIFO interrupt mask
                                 //                            [2] : Receive FIFO interrupt mask
                                 //                            [1] : Receive timeout interrupt mask
                                 //                            [0] : Receive overrun interrupt mask
	__I  uint32_t RIS;           // Offset: 0x018 (R/ )  Raw interrupt status register
                                 //                         [31:4] : Reserved
                                 //                            [3] : raw interrupt state, prior to masking, of the SSPTXINTR interrupt
                                 //                            [2] : raw interrupt state, prior to masking, of the SSPRXINTR interrupt
                                 //                            [1] : raw interrupt state, prior to masking, of the SSPRTINTR interrupt
                                 //                            [0] : raw interrupt state, prior to masking, of the SSPRORINTR interrupt
	__I  uint32_t MIS;           // Offset: 0x01C (R/ )  Masked interrupt status register
                                 //                         [31:4] : Reserved
                                 //                            [3] : transmit FIFO masked interrupt state, after masking, of the SSPTXINTR interrupt
                                 //                            [2] : receive FIFO masked interrupt state, after masking, of the SSPRXINTR interrupt
                                 //                            [1] : receive timeout masked interrupt state, after masking, of the SSPRTINTR interrupt
                                 //                            [0] : receive over run masked interrupt status, after masking, of the SSPRORINTR interrupt
	__O  uint32_t ICR;           // Offset: 0x020 ( /W)  Interrupt clear register
                                 //                         [31:2] : Reserved
                                 //                            [1] : Clears the SSPRTINTR interrupt
                                 //                            [0] : Clears the SSPRORINTR interrupt
	__IO uint32_t DMACR;         // Offset: 0x024 (R/W)  DMA control register
                                 //                         [31:2] : Reserved
                                 //                            [1] : Transmit DMA Enable
                                 //                            [0] : Receive DMA Enable
	__IO uint32_t rev;  
	__IO uint32_t rx_cnt_msb;    // Offset: 0x02c (R/W)  rx_cnt_msb register
 
	__IO uint32_t rx_cnt_lsb;    // Offset: 0x030 (R/W)  rx_cnt_lsb register

} SPI_TypeDef;

/*-------------------- DMA(Direct Memory Access) -------------------*/
typedef struct
{
	__I  uint32_t DMACIntStatus;    //Offset 0x000
                                    //[31:2] : Read undefined
									//[1]: IntStatus1 Channel1 interrupt status after masking
									//[0]: IntStatus0 Channel0 interrupt status after masking
  										
	__I  uint32_t DMACIntTCStatus;  //Offset 0x004
									//[31:2] : Read undefined
                                    //[1] : IntTCStatus1 Channel1 terminal count interrupt status after masking
                                    //[0] : IntTCStatus0 Channel0 terminal count interrupt status after masking
                                                               
	__O uint32_t DMACIntTCClear;    //Offset 0x008
									//[31:2] : Read undefined 
                                    //[1] : IntTCClear1 Clear terminal count interrupt request of channel 1
                                    //[0] : IntTCClear0 Clear terminal count interrupt request of channel 0
                                                               
	__I  uint32_t DMACIntErrorStatus;     	//Offset 0x00C
											//[31:2] : Read undefined
                                            //[1] : IntErrorStatus1 Channel1 error interrupt status after masking
                                            //[0] : IntErrorStatus0 Channel0 error interrupt status after masking
                                                               
	__O uint32_t DMACIntErrClr;     //Offset 0x010
									//[31:2] : Read undefined
                                    //[1] : IntErrClear1 Clear error interrupt request of channel 1
                                    //[0] : IntErrClear0 Clear error interrupt request of channel 0
                                                               
	__I  uint32_t DMACRawIntTCStatus;       //Offset 0x014
											//[31:2] : Read undefined
                                            //[1] : RawIntTCStatus1 Channel1 terminal count interrupt status prior to masking
                                            //[0] : RawIntTCStatus0 Channel0 terminal count interrupt status prior to masking
                                                               
	__I  uint32_t DMACRawIntErrorStatus;  	//Offset 0x018
											//[31:2] : Read undefined
                                            //[1] : RawIntEerrStatus1 Channel1 error interrupt status prior to masking
                                            //[0] RawIntEerrStatus0 Channel0 error interrupt status prior to masking
                                                                
	__I  uint32_t DMACEnbldChns;            //Offset 0x01c
											//[31:2] : Read undefined
                                            //[1] :EnabledChannel1 Channel1 enable status
                                            //[0] : EnabledChannel0 Channel0 enable status
                                                                
	__IO uint32_t DMACSoftBReq;             //Offset 0x020
											//[31:16] : Read undefined
                                            //[15:0] : SoftBReq Software burst request
                                                                
	__IO uint32_t DMACSoftSReq;             //Offset 0x024
											//[31:16] : Read undefined
                                            //[15:0] : SoftSReq Software single request
                                                                
	__IO uint32_t DMACSoftLBReq;            //Offset 0x028
											//[31:16] : Read undefined
                                            //[15:0] : SoftLBReq Software last burst request
                                                                
	__IO uint32_t DMACSoftLSReq;            //Offset 0x02C
											//[31:16] : Read undefined
                                            //[15:0]: SoftLSReq Software last single request
                                                               
	__IO uint32_t DMACConfiguration;        //Offset 0x030
											//[31:2] : Read undefined
                                            // [1] M AHB Master endianness configuration:
												// 0 = little-endian mode
                                                // 1 = big-endian mode.
                                                //This bit is reset to 0
                                            // [0] E DMAC enable:
                                                //0 = disabled
                                                // 1 = enabled
                                                //This bit is reset to 0
                                                //Disabling the DMAC reduces power consumption
                                                                
	__IO uint32_t DMACSync;                 //Offset 0x034
											//[31:16] : Read undefined
                                            //[15:0] : DMACSync

         uint32_t RESERVED[50];																
                                                               
	__IO uint32_t DMACC0SrcAddr;            //Offset 0x100 
                                            //[31:0]:SrcAddr DMA source address
                                                                
	__IO uint32_t DMACC0DestAddr;           //Offset 0x104 
                                            //[31:0]: DesAddr DMA destination address
                                                                
	__IO uint32_t DMACC0LLI;                //Offset 0x108
                                            //[31:2] LLI Linked list item. Bits [31:2] of the address for the next LLI. Address bits [1:0] are 0.
                                            //[1:0] : Read undefined. Write as zero.
                                                               
	__IO uint32_t DMACC0Control;            //Offset 0x10C 
                                                                
	__IO uint32_t DMACC0Configuration;    	//Offset 0x110
                                                             
		 uint32_t RESERVED1[3]; 
                                                                
	__IO uint32_t DMACC1SrcAddr;            //Offset 0x120               
                                                                
	__IO uint32_t DMACC1DestAddr;          //Offset 0x124             
                                                                
	__IO uint32_t DMACC1LLI;                //Offset 0x128   
                                                                
	__IO uint32_t DMACC1Control;            //Offset 0x12C       
                                                                
	__IO uint32_t DMACC1Configuration;  	//Offset 0x130   
                                                                
}DMA_TypeDef;


// SPI_CR0 Control register 0
#define SPI_CR0_DSS_Pos         0           // Data Size Select
#define SPI_CR0_DSS_Msk         (0xF<<SPI_CR0_DSS_Pos)
#define SPI_CR0_FRF_Pos         4           // Frame Format Select
#define SPI_CR0_FRF_Msk         (3UL<<SPI_CR0_FRM_Pos)
#define SPI_CR0_SPO_Pos         6           // SSPCLKOUT polarity
#define SPI_CR0_SPO_Msk         (1UL<<SPI_CR0_SPO_Pos)
#define SPI_CR0_SPH_Pos         7           // SSPCLKOUT phase
#define SPI_CR0_SPH_Msk         (1UL<<SPI_CR0_SPH_Pos)
#define SPI_CR0_SCR_Pos         8           // Serial Clock Rate (divide)
#define SPI_CR0_SCR_Msk         (0xFF<<SPI_CR0_SCR_Pos)

#define SPI_CR0_SCR_DFLT        0x0300      // Serial Clock Rate (divide), default set at 3
#define SPI_CR0_FRF_MOT         0x0000      // Frame format, Motorola
#define SPI_CR0_DSS_8           0x0007      // Data packet size, 8bits
#define SPI_CR0_DSS_16          0x000F      // Data packet size, 16bits

// SPI_CR1 Control register 1
#define SPI_CR1_LBM_Pos         0           // Loop Back Mode
#define SPI_CR1_LBM_Msk         (1UL<<SPI_CR1_LBM_Pos)
#define SPI_CR1_SSE_Pos         1           // Serial port enable
#define SPI_CR1_SSE_Msk         (1UL<<SPI_CR1_SSE_Pos)
#define SPI_CR1_MS_Pos          2           // Master or Slave mode
#define SPI_CR1_MS_Msk          (1UL<<SPI_CR1_MS_Pos)
#define SPI_CR1_SOD_Pos         3           // Slave Output mode Disable
#define SPI_CR1_SOD_Msk         (1UL<<SPI_CR1_SOD_Pos)
#define SPI_CR1_WIDTH_Pos       4       // SPI Data Width[0]
#define SPI_CR1_WIDTH_Msk       (3UL<<SPI_CR1_WIDTH_Pos)


// SPI_SR Status register
#define SPI_SR_TFE_Pos          0           // Transmit FIFO empty
#define SPI_SR_TFE_Msk          (1UL<<SPI_SR_TFE_Pos)
#define SPI_SR_TNF_Pos          1           // Transmit FIFO not full
#define SPI_SR_TNF_Msk          (1UL<<SPI_SR_TNF_Pos)
#define SPI_SR_RNE_Pos          2           // Receive  FIFO not empty
#define SPI_SR_RNE_Msk          (1UL<<SPI_SR_RNE_Pos)
#define SPI_SR_RFF_Pos          3           // Receive  FIFO full
#define SPI_SR_RFF_Msk          (1UL<<SPI_SR_RFF_Pos)
#define SPI_SR_BSY_Pos          4           // Busy
#define SPI_SR_BSY_Msk          (1UL<<SPI_SR_BSY_Pos)
#define SPI_SR_BSY_TX_Pos       5           // Busy_TX
#define SPI_SR_BSY_TX_Msk       (1UL<<SPI_SR_BSY_TX_Pos)

// SPI_CPSR Clock prescale register
#define SPI_CPSR_CPD_Pos        0           // Clock prescale divisor
#define SPI_CPSR_CPD_Msk        (0xFF<<SPI_CPSR_CDP_Pos)

#define SPI_CPSR_DFLT        0x0008      // Clock prescale (use with SCR), default set at 8

// SSPIMSC Interrupt mask set and clear register
#define SPI_IMSC_RORIM_Pos         0           // Receive overrun not Masked
#define SPI_IMSC_RORIM_Msk         (1UL<<SPI_IMSC_RORIM_Pos)
#define SPI_IMSC_RTIM_Pos          1           // Receive timeout not Masked
#define SPI_IMSC_RTIM_Msk          (1UL<<SPI_IMSC_RTIM_Pos)
#define SPI_IMSC_RXIM_Pos          2           // Receive  FIFO not Masked
#define SPI_IMSC_RXIM_Msk          (1UL<<SPI_IMSC_RXIM_Pos)
#define SPI_IMSC_TXIM_Pos          3           // Transmit FIFO not Masked
#define SPI_IMSC_TXIM_Msk          (1UL<<SPI_IMSC_TXIM_Pos)
#define SPI_MISC_RXAFIM_Pos         4           // Masked Overrun  interrupt flag
#define SPI_MISC_RXAFIM_Msk         (1UL<<SPI_MISC_RXAFIM_Pos)

// SSPRIS Raw interrupt status register
#define SPI_RIS_RORRIS_Pos         0           // Raw Overrun  interrupt flag
#define SPI_RIS_RORRIS_Msk         (1UL<<SPI_RIS_RORRIS_Pos)
#define SPI_RIS_RTRIS_Pos          1           // Raw Timemout interrupt flag
#define SPI_RIS_RTRIS_Msk          (1UL<<SPI_RIS_RTRIS_Pos)
#define SPI_RIS_RXRIS_Pos          2           // Raw Receive  interrupt flag
#define SPI_RIS_RXRIS_Msk          (1UL<<SPI_RIS_RXRIS_Pos)
#define SPI_RIS_TXRIS_Pos          3           // Raw Transmit interrupt flag
#define SPI_RIS_TXRIS_Msk          (1UL<<SPI_RIS_TXRIS_Pos)

// SSPMIS Masked interrupt status register
#define SPI_MIS_RORMIS_Pos         0           // Masked Overrun  interrupt flag
#define SPI_MIS_RORMIS_Msk         (1UL<<SPI_MIS_RORMIS_Pos)
#define SPI_MIS_RTMIS_Pos          1           // Masked Timemout interrupt flag
#define SPI_MIS_RTMIS_Msk          (1UL<<SPI_MIS_RTMIS_Pos)
#define SPI_MIS_RXMIS_Pos          2           // Masked Receive  interrupt flag
#define SPI_MIS_RXMIS_Msk          (1UL<<SPI_MIS_RXMIS_Pos)
#define SPI_MIS_TXMIS_Pos          3           // Masked Transmit interrupt flag
#define SPI_MIS_TXMIS_Msk          (1UL<<SPI_MIS_TXMIS_Pos)
#define SPI_MIS_RXAFMIS_Pos        4           // Masked Overrun  interrupt flag
#define SPI_MIS_RXAFMIS_Msk        (1UL<<SPI_MIS_RXAFMIS_Pos)

// SSPICR Interrupt clear register
#define SPI_ICR_RORIC_Pos           0           // Clears Overrun  interrupt flag
#define SPI_ICR_RORIC_Msk           (1UL<<SPI_ICR_RORIC_Pos)
#define SPI_ICR_RTIC_Pos            1           // Clears Timemout interrupt flag
#define SPI_ICR_RTIC_Msk            (1UL<<SPI_ICR_RTIC_Pos)

// SSPDMACR DMA control register
#define SPI_DMACR_RXDMAE_Pos        0           // Enable Receive  FIFO DMA
#define SPI_DMACR_RXDMAE_Msk        (1UL<<SPI_DMACR_RXDMAE_Pos)
#define SPI_DMACR_TXDMAE_Pos        1           // Enable Transmit FIFO DMA
#define SPI_DMACR_TXDMAE_Msk        (1UL<<SPI_DMACR_TXDMAE_Pos)

/* --------------------  End of section using anonymous unions  ------------------- */




#if defined ( __CC_ARM   )
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Peripheral and SRAM base address */
#define CM3DS_MPS2_FLASH_BASE        (0x00000000UL)  /*!< (FLASH     ) Base Address */
#define CM3DS_MPS2_SRAM_BASE         (0x20000000UL)  /*!< (SRAM      ) Base Address */
#define CM3DS_MPS2_PERIPH_BASE       (0x40000000UL)  /*!< (Peripheral) Base Address */
#define CM3DS_MPS2_TARGEXP0_BASE     (0xA0000000UL)  /*!< (TARGEXP0  ) Base Address */
#define CM3DS_MPS2_TARGEXP1_BASE     (0xC0000000UL)  /*!< (TARGEXP1  ) Base Address */

#define CM3DS_MPS2_RAM_BASE          (0x20000000UL)
#define CM3DS_MPS2_APB_BASE          (0x40000000UL)
#define CM3DS_MPS2_AHB_BASE          (0x40010000UL)
#define AHB_TARGEXP0_BASE            (0xA0000000UL)

/* APB peripherals                                                           */
#define CM3DS_MPS2_TIMER0_BASE       (CM3DS_MPS2_APB_BASE + 0x0000UL)
#define CM3DS_MPS2_TIMER1_BASE       (CM3DS_MPS2_APB_BASE + 0x1000UL)
#define CM3DS_MPS2_DUALTIMER_BASE    (CM3DS_MPS2_APB_BASE + 0x2000UL)
#define CM3DS_MPS2_DUALTIMER_1_BASE  (CM3DS_MPS2_DUALTIMER_BASE)
#define CM3DS_MPS2_DUALTIMER_2_BASE  (CM3DS_MPS2_DUALTIMER_BASE + 0x20UL)
#define CM3DS_MPS2_UART0_BASE        (CM3DS_MPS2_APB_BASE + 0x4000UL)
#define CM3DS_MPS2_UART1_BASE        (CM3DS_MPS2_APB_BASE + 0x5000UL)
#define CM3DS_MPS2_PERI_RSTCTL_BASE  (CM3DS_MPS2_APB_BASE + 0x3000UL)
#define CM3DS_MPS2_I2C_BASE          (CM3DS_MPS2_APB_BASE + 0x6000UL)
#define CM3DS_MPS2_ADC_BASE          (CM3DS_MPS2_APB_BASE + 0x7000UL)
#define CM3DS_MPS2_WATCHDOG_BASE     (CM3DS_MPS2_APB_BASE + 0x8000UL)
#define CM3DS_MPS2_SPI0_BASE         (CM3DS_MPS2_APB_BASE + 0xB000UL)
#define CM3DS_MPS2_SPI1_BASE         (CM3DS_MPS2_APB_BASE + 0xC000UL)


/* added by gsl 2018-5-29  */

/* AHB peripherals                                                           */
#define CM3DS_MPS2_ZBT1_BASE         (0x00400000UL)
#define CM3DS_MPS2_ZBT2_BASE         (0x20400000UL)
#define CM3DS_MPS2_PSRAM_BASE        (0x21000000UL)
#define CM3DS_MPS2_GPIO0_BASE        (CM3DS_MPS2_AHB_BASE + 0x0000UL)
#define CM3DS_MPS2_SYSCTRL_BASE      (CM3DS_MPS2_AHB_BASE + 0xF000UL)
#define CM3DS_MPS2_EXTSPI_BASE       (0x40020000UL)
#define CM3DS_MPS2_CLCDSPI_BASE      (0x40021000UL)
#define CM3DS_MPS2_CLCDTOUCH_BASE    (0x40022000UL)
#define CM3DS_MPS2_AUDIOCFG_BASE     (0x40023000UL)
#define CM3DS_MPS2_AUDIO_BASE        (0x40024000UL)
#define CM3DS_MPS2_SPIADC_BASE       (0x40025000UL)
#define CM3DS_MPS2_SPISH0_BASE       (0x40026000UL)
#define CM3DS_MPS2_SPISH1_BASE       (0x40027000UL)
//#define CM3DS_MPS2_FPGASYS_BASE      (0x40028000UL)
#define CM3DS_MPS2_AUDIOSH0_BASE     (0x40029000UL)
#define CM3DS_MPS2_AUDIOSH1_BASE     (0x4002A000UL)

#define CM3DS_MPS2_SCC_BASE          (0x4002F000UL)
#define CM3DS_MPS2_GPIO4_BASE        (0x40030000UL)
#define CM3DS_MPS2_GPIO5_BASE        (0x40031000UL)
#define CM3DS_MPS2_ETH_BASE          (0x40200000UL)
#define CM3DS_MPS2_VGACON_BASE       (0x41000000UL)
#define CM3DS_MPS2_VGAIMAGE_BASE     (0x41100000UL)

/* Core peripherals                                                           */
#define CM3DS_MPS2_COREPERIP_BASE    (0xE0000000UL)
#define CM3DS_MPS2_COREAPB_BASE      (0xE0040000UL)
#define CM3DS_MPS2_COREROM_BASE      (0xE00FF000UL)

/* Peripheral and SRAM size */
#define CM3DS_MPS2_FLASH_SIZE        (0x20000UL)
#define CM3DS_MPS2_SRAM_SIZE         (0x8000UL)
#define CM3DS_MPS2_APB_SIZE          (0x10000UL)
#define CM3DS_MPS2_PSRAM_SIZE        (0x1000000UL)
#define CM3DS_MPS2_ZBT2_SIZE         (0x400000UL)
#define CM3DS_MPS2_ZBT1_SIZE         (0x400000UL)
#define CM3DS_MPS2_TARGEXP0_SIZE     (0x20000000UL)
#define CM3DS_MPS2_TARGEXP1_SIZE     (0x20000000UL)

/* Mixed Peripherals*/
#define CM3DS_MPS2_DMA_BASE (0x40009000UL)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define CM3DS_MPS2_UART0             ((UART_TypeDef   *) CM3DS_MPS2_UART0_BASE   )
#define CM3DS_MPS2_UART1             ((UART_TypeDef   *) CM3DS_MPS2_UART1_BASE   )
#define CM3DS_MPS2_TIMER0            ((TIMER_TypeDef  *) CM3DS_MPS2_TIMER0_BASE )
#define CM3DS_MPS2_TIMER1            ((TIMER_TypeDef  *) CM3DS_MPS2_TIMER1_BASE )
#define CM3DS_MPS2_DUALTIMER0         ((DUALTIMER_BOTH_TypeDef  *) CM3DS_MPS2_DUALTIMER_BASE )
//#define CM3DS_MPS2_DUALTIMER1        ((CM3DS_MPS2_DUALTIMER_SINGLE_TypeDef  *) CM3DS_MPS2_DUALTIMER_1_BASE )
//#define CM3DS_MPS2_DUALTIMER2        ((CM3DS_MPS2_DUALTIMER_SINGLE_TypeDef  *) CM3DS_MPS2_DUALTIMER_2_BASE )
#define CM3DS_MPS2_WATCHDOG          ((WATCHDOG_TypeDef  *) CM3DS_MPS2_WATCHDOG_BASE   )
#define CM3DS_MPS2_GPIO0             ((GPIO_TypeDef   *) CM3DS_MPS2_GPIO0_BASE )
#define CM3DS_MPS2_SYSCON            ((SYSCON_TypeDef *) CM3DS_MPS2_SYSCTRL_BASE )
#define CM3DS_MPS2_I2C               ((I2C_TypeDef *) CM3DS_MPS2_I2C_BASE )
#define CM3DS_MPS2_ADC               ((ADC_TypeDef *) CM3DS_MPS2_ADC_BASE )
#define CM3DS_MPS2_SPI0               ((SPI_TypeDef *) CM3DS_MPS2_SPI0_BASE )
#define CM3DS_MPS2_SPI1               ((SPI_TypeDef *) CM3DS_MPS2_SPI1_BASE )
#define APB_PERI_RSTCTL		        ((PERI_RSTCTL_TypeDef  *) CM3DS_MPS2_PERI_RSTCTL_BASE)
#define CM3DS_MPS2_DMA              ((DMA_TypeDef *) CM3DS_MPS2_DMA_BASE)

/*added by gsl 2018-5-29*/
#ifdef __cplusplus
}
#endif

#endif  /* CM3DS_MPS2_H */

