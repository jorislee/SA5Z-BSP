
#ifndef STAR_H
#define STAR_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Configuration of the Cortex-M33 Processor and Core Peripherals */
#define __CM33_REV                 0x0201    /*!< Core Revision r2p1                             */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels        */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used   */
#define __MPU_PRESENT             1         /*!< MPU present or not                             */


/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,    /*!<  Cortex-M33 Non Maskable Interrupt                 */
  HardFault_IRQn                = -13,    /*!<  Cortex-M33 Hard Fault Interrupt                   */
  MemoryManagement_IRQn         = -12,    /*!<  Cortex-M33 Memory Management Interrupt            */
  BusFault_IRQn                 = -11,    /*!<  Cortex-M33 Bus Fault Interrupt                    */
  UsageFault_IRQn               = -10,    /*!<  Cortex-M33 Usage Fault Interrupt                  */
  SecureFault_IRQn				= -9,	  /*!<  Cortex-M33 Secure Fault Handler                   */
  SVCall_IRQn                   = -5,     /*!<  Cortex-M33 SV Call Interrupt                      */
  DebugMonitor_IRQn             = -4,     /*!<  Cortex-M33 Debug Monitor Interrupt                */
  PendSV_IRQn                   = -2,     /*!<  Cortex-M33 Pend SV Interrupt                      */
  SysTick_IRQn                  = -1,     /*!<  Cortex-M33 System Tick Interrupt                  */

/******  STAR Specific Interrupt Numbers *******************************************************/
  UART0_IRQn                    = 0,       /* UART 0 RX and TX Combined Interrupt   */
  ADC_IRQn                      = 1,       /* ADC Interrupt                         */
  UART1_IRQn                    = 2,       /* UART 1 RX and TX Combined Interrupt   */
  DMACINTERR_IRQn               = 3,       /* DMA Error Interrupt                             */
  DMACINTTC_IRQn                = 4,       /* DMA Transfer Complete Interrupt                             */
  DMACINTR_IRQn                 = 5,       /* DMA Interrupt                             */
  PORT0_ALL_IRQn                = 6,       /* GPIO combined Interrupt        		*/
  ADC1_IRQn                   	= 7,       /* ADC1 end of conversion interrupt     	*/
  TIMER0_IRQn                   = 8,       /* TIMER 0 Interrupt                     */
  TIMER1_IRQn                   = 9,       /* TIMER 1 Interrupt                     */
  DUALTIMER0_IRQn               = 10,      /* Dual Timer0 Interrupt                 */
  DUALTIMER1_IRQn               = 11,      /* Dual Timer1 Interrupt                 */
  UARTOVF_IRQn                  = 12,      /* UART 0,1,2  Overflow Interrupt     	*/
  EXT13_IRQn                    = 13,      /* External Interrupts                   */
  EXT14_IRQn                    = 14,      /* External Interrupts                   */
  EXT15_IRQn                    = 15,      /* External Interrupts                   */
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
  EXT12_IRQn                    = 63,
  UART2_IRQn                    = 64       /* UART 2 RX and TX Combined Interrupt   */
} IRQn_Type;


#include "core_cm33.h"                     /* Cortex-M33 processor and core peripherals   */
#include "system_ARMCM33.h"             /* CM33 System include file                      */
#include "STAR_conf.h"


/** @addtogroup Exported_types
  * @{
  */  

typedef enum {
	RESET = 0, 
	SET = !RESET
} FlagStatus, ITStatus;

/*!< CM33 Standard Peripheral Library old types (maintained for legacy purpose) */
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
/** @addtogroup STAR_Peripherals STAR Peripherals
  STAR Device Specific Peripheral registers structures
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


/*-------------------- General Purpose Input Output (GPIO) -------------------*/
 typedef struct
{
  __IO   uint32_t  DATA;                     /* Offset: 0x000 (R/W) DATA Register */
  __IO   uint32_t  DATAOUT;                  /* Offset: 0x004 (R/W) Data Output Latch Register */
         uint32_t  RESERVED0[2];
  __IO   uint32_t  OUTENSET;             /* Offset: 0x010 (R/W) Output Enable Set Register */
  __IO   uint32_t  OUTENCLR;             /* Offset: 0x014 (R/W) Output Enable Clear Register */
  __IO   uint32_t  ALTFUNCSET;               /* Offset: 0x018 (R/W) Alternate Function Set Register */
  __IO   uint32_t  ALTFUNCCLR;               /* Offset: 0x01C (R/W) Alternate Function Clear Register */
  __IO   uint32_t  INTENSET;                 /* Offset: 0x020 (R/W) Interrupt Enable Set Register */
  __IO   uint32_t  INTENCLR;                 /* Offset: 0x024 (R/W) Interrupt Enable Clear Register */
  __IO   uint32_t  INTTYPESET;               /* Offset: 0x028 (R/W) Interrupt Type Set Register */
  __IO   uint32_t  INTTYPECLR;               /* Offset: 0x02C (R/W) Interrupt Type Clear Register */
  __IO   uint32_t  INTPOLSET;                /* Offset: 0x030 (R/W) Interrupt Polarity Set Register */
  __IO   uint32_t  INTPOLCLR;                /* Offset: 0x034 (R/W) Interrupt Polarity Clear Register */
  union {
    __I    uint32_t  INTSTATUS;              /* Offset: 0x038 (R/ ) Interrupt Status Register */
    __O    uint32_t  INTCLEAR;               /* Offset: 0x038 ( /W) Interrupt Clear Register */
    };
         uint32_t RESERVED1[241];
  __IO   uint32_t MASKBYTE0[256];            /* Offset: 0x400 - 0x7FC Lower byte Masked Access Register (R/W) bits[7:0] masked access */
  __IO   uint32_t MASKBYTE1[256];            /* Offset: 0x800 - 0xBFC Upper byte Masked Access Register (R/W) bits[15:8] masked access */
  __IO   uint32_t MASKBYTE2[256];            /* Offset: 0xC00 - 0xFFC Lower byte Masked Access Register (R/W) bits[23:16] masked access */
  __IO   uint32_t MASKBYTE3[256];            /* Offset: 0x1000 - 0x13FC Upper byte Masked Access Register (R/W) bits[31:24] masked access*/		
}GPIO_TypeDef;


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
  __IO   uint32_t  BAUDDIV;       /*!< Offset: 0x010 Baudrate Divider Register (R/W). The minimum number is 16 */

}UART_TypeDef;


/*------------- APB peripherals soft reset control --------------------------------------*/
typedef struct
{
  __IO  uint32_t  RESETPERI;                /* Offset: 0x000 (R/W) Peripherals Reset Control Register */
	
} PERI_RSTCTL_TypeDef;

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


/*------------- Dual Timer  --------------------------------------------------*/
typedef struct
{
  __IO uint32_t Timer1Load;                  /* Offset: 0x000 (R/W) Timer1 Load */
  __I  uint32_t Timer1Value;                 /* Offset: 0x004 (R/ ) Timer1 Counter Current Value */
  __IO uint32_t Timer1Control;               /* Offset: 0x008 (R/W) Timer1 Control */
  __O  uint32_t Timer1IntClr;                /* Offset: 0x00C ( /W) Timer1 Interrupt Clear */
  __I  uint32_t Timer1RIS;                   /* Offset: 0x010 (R/ ) Timer1 Raw Interrupt Status */
  __I  uint32_t Timer1MIS;                   /* Offset: 0x014 (R/ ) Timer1 Masked Interrupt Status */
  __IO uint32_t Timer1BGLoad;                /* Offset: 0x018 (R/W) Background Load Register */
      uint32_t RESERVED0;
  __IO uint32_t Timer2Load;                  /* Offset: 0x020 (R/W) Timer2 Load */
  __I  uint32_t Timer2Value;                 /* Offset: 0x024 (R/ ) Timer2 Counter Current Value */
  __IO uint32_t Timer2Control;               /* Offset: 0x028 (R/W) Timer2 Control */
  __O  uint32_t Timer2IntClr;                /* Offset: 0x02C ( /W) Timer2 Interrupt Clear */
  __I  uint32_t Timer2RIS;                   /* Offset: 0x030 (R/ ) Timer2 Raw Interrupt Status */
  __I  uint32_t Timer2MIS;                   /* Offset: 0x034 (R/ ) Timer2 Masked Interrupt Status */
  __IO uint32_t Timer2BGLoad;                /* Offset: 0x038 (R/W) Background Load Register */
  	uint32_t RESERVED1[945];
  __IO uint32_t TimerITCR;                   /* Offset: 0xF00 (R/W) Integration Test Control Register */
  __O  uint32_t TimerITOP;                   /* Offset: 0xF04 ( /W) Integration Test Output Set Register */
} DUALTIMER_TypeDef;


/*------------------- Watchdog ----------------------------------------------*/
typedef struct
{
  __IO    uint32_t  WDOGLOAD;                   /* Offset: 0x000 (R/W) Watchdog Load Register */
  __I     uint32_t  WDOGVALUE;                  /* Offset: 0x004 (R/ ) Watchdog Value Register */
  __IO    uint32_t  WDOGCONTROL;                   /* Offset: 0x008 (R/W) Watchdog Control Register */
  __O     uint32_t  WDOGINTCLR;                 /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register */
  __I     uint32_t  WDOGRIS;             		/* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register */
  __I     uint32_t  WDOGMIS;            		/* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register */
		  uint32_t  RESERVED0[762];
  __IO    uint32_t  WDOGLOCK;                   /* Offset: 0xC00 (R/W) Watchdog Lock Register */
		uint32_t  RESERVED1[191];
  __IO    uint32_t  WDOGITCR;                   /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register */
  __O     uint32_t  WDOGITOP;                   /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register */
}WATCHDOG_TypeDef;


/******************************************************************************/
/*                        SPI Peripheral declaration                          */
/******************************************************************************/

typedef struct                   // Document DDI0194G_ssp_pl022_r1p3_trm.pdf
{
  __IO uint32_t SSPCR0;             // Offset: 0x000 (R/W)  Control register 0
                                 //                        [31:16] : Reserved
                                 //                         [15:8] : Serial clock rate
                                 //                            [7] : SSPCLKOUT phase,    applicable to Motorola SPI frame format only
                                 //                            [6] : SSPCLKOUT polarity, applicable to Motorola SPI frame format only
                                 //                          [5:4] : Frame format
                                 //                          [3:0] : Data Size Select
  __IO uint32_t SSPCR1;             // Offset: 0x004 (R/W)  Control register 1
                                 //                         [31:4] : Reserved
                                 //                            [3] : Slave-mode output disable
                                 //                            [2] : Master or slave mode select
                                 //                            [1] : Synchronous serial port enable
                                 //                            [0] : Loop back mode
  __IO uint32_t SSPDR;              // Offset: 0x008 (R/W)  Data register
                                 //                        [31:16] : Reserved
                                 //                         [15:0] : Transmit/Receive FIFO
  __I  uint32_t SSPSR;              // Offset: 0x00C (R/ )  Status register
                                 //                         [31:5] : Reserved
                                 //                            [4] : PrimeCell SSP busy flag
                                 //                            [3] : Receive FIFO full
                                 //                            [2] : Receive FIFO not empty
                                 //                            [1] : Transmit FIFO not full
                                 //                            [0] : Transmit FIFO empty
  __IO uint32_t SSPCPSR;            // Offset: 0x010 (R/W)  Clock prescale register
                                 //                         [31:8] : Reserved
                                 //                          [8:0] : Clock prescale divisor
  __IO uint32_t SSPIMSC;            // Offset: 0x014 (R/W)  Interrupt mask set or clear register
                                 //                         [31:4] : Reserved
                                 //                            [3] : Transmit FIFO interrupt mask
                                 //                            [2] : Receive FIFO interrupt mask
                                 //                            [1] : Receive timeout interrupt mask
                                 //                            [0] : Receive overrun interrupt mask
  __I  uint32_t SSPRIS;             // Offset: 0x018 (R/ )  Raw interrupt status register
                                 //                         [31:4] : Reserved
                                 //                            [3] : raw interrupt state, prior to masking, of the SSPTXINTR interrupt
                                 //                            [2] : raw interrupt state, prior to masking, of the SSPRXINTR interrupt
                                 //                            [1] : raw interrupt state, prior to masking, of the SSPRTINTR interrupt
                                 //                            [0] : raw interrupt state, prior to masking, of the SSPRORINTR interrupt
  __I  uint32_t SSPMIS;             // Offset: 0x01C (R/ )  Masked interrupt status register
                                 //                         [31:4] : Reserved
                                 //                            [3] : transmit FIFO masked interrupt state, after masking, of the SSPTXINTR interrupt
                                 //                            [2] : receive FIFO masked interrupt state, after masking, of the SSPRXINTR interrupt
                                 //                            [1] : receive timeout masked interrupt state, after masking, of the SSPRTINTR interrupt
                                 //                            [0] : receive over run masked interrupt status, after masking, of the SSPRORINTR interrupt
  __O  uint32_t SSPICR;             // Offset: 0x020 ( /W)  Interrupt clear register
                                 //                         [31:2] : Reserved
                                 //                            [1] : Clears the SSPRTINTR interrupt
                                 //                            [0] : Clears the SSPRORINTR interrupt
  __IO uint32_t SSPDMACR;           // Offset: 0x024 (R/W)  DMA control register
                                 //                         [31:2] : Reserved
                                 //                            [1] : Transmit DMA Enable
                                 //                            [0] : Receive DMA Enable
  __IO uint32_t rev;  
  __IO uint32_t SSP_RX_CNT_MSB;      // Offset: 0x02c (R/W)  rx_cnt_msb register
 
  __IO uint32_t SSP_RX_CNT_LSB;           // Offset: 0x030 (R/W)  rx_cnt_lsb register

} SPI_TypeDef;

/*---------------------- Analog Digital Convertion (ADC) ---------------------*/
typedef struct
{
	__I		uint32_t  ADC_DBR_1_0;              /* Offset: 0x000 (R/ ) DATA Buffer Register1 and Register0 */
	__I    	uint32_t  ADC_DBR_3_2;              /* Offset: 0x004 (R/ ) DATA Buffer Register3 and Register2 */
	__I    	uint32_t  ADC_DBR_5_4;              /* Offset: 0x008 (R/ ) DATA Buffer Register5 and Register4 */	
	__I    	uint32_t  ADC_DBR_7_6;              /* Offset: 0x00C (R/ ) DATA Buffer Register7 and Register6 */
	__I    	uint32_t  ADC_DBR_9_8;              /* Offset: 0x010 (R/ ) DATA Buffer Register9 and Register8 */
	__I    	uint32_t  ADC_DBR_11_10;            /* Offset: 0x014 (R/ ) DATA Buffer Register11 and Register10 */
	__I    	uint32_t  ADC_DBR_13_12;            /* Offset: 0x018 (R/ ) DATA Buffer Register13 and Register12 */
	__I    	uint32_t  ADC_DBR_15_14;            /* Offset: 0x01C (R/ ) DATA Buffer Register15 and Register14 */
	__IO   	uint32_t  ADC_CSR_0;                /* Offset: 0x020 (R/W) Control and Status Register0 */	
	__IO   	uint32_t  ADC_CSR_1;                /* Offset: 0x024 (R/W) Control and Status Register1 */		
	__IO   	uint32_t  ADC_CR_1;                 /* Offset: 0x028 (R/W) Configuration Register1 */		
	__IO   	uint32_t  ADC_CR_2;               	/* Offset: 0x02C (R/W) Configuration Register2 and Register3 */		
			uint32_t  RESERVED0[3];	
	__I    	uint32_t  ADC_DR;   			    /* Offset: 0x03C	(R/ ) DATA Register */		

}ADC_TypeDef;

/*-------------------- DMA(Direct Memory Access) -------------------*/
typedef struct
{
  __I  uint32_t DMACIntStatus;                 //Offset 0x000
                                                               //[31:2] : Read undefined
									//[1]: IntStatus1 Channel1 interrupt status after masking
									//[0]: IntStatus0 Channel0 interrupt status after masking
  										
  __I  uint32_t DMACIntTCStatus;             //Offset 0x004
									//[31:2] : Read undefined
                                                               //[1] : IntTCStatus1 Channel1 terminal count interrupt status after masking
                                                               //[0] : IntTCStatus0 Channel0 terminal count interrupt status after masking
                                                               
  __O uint32_t DMACIntTCClear;              //Offset 0x008
									//[31:2] : Read undefined 
                                                               //[1] : IntTCClear1 Clear terminal count interrupt request of channel 1
                                                               //[0] : IntTCClear0 Clear terminal count interrupt request of channel 0
                                                               
  __I  uint32_t DMACIntErrorStatus;        //Offset 0x00C
									//[31:2] : Read undefined
                                                               //[1] : IntErrorStatus1 Channel1 error interrupt status after masking
                                                               //[0] : IntErrorStatus0 Channel0 error interrupt status after masking
                                                               
  __O uint32_t DMACIntErrClr;                 //Offset 0x010
									//[31:2] : Read undefined
                                                               //[1] : IntErrClear1 Clear error interrupt request of channel 1
                                                               //[0] : IntErrClear0 Clear error interrupt request of channel 0
                                                               
  __I  uint32_t DMACRawIntTCStatus;      //Offset 0x014
									//[31:2] : Read undefined
                                                               //[1] : RawIntTCStatus1 Channel1 terminal count interrupt status prior to masking
                                                               //[0] : RawIntTCStatus0 Channel0 terminal count interrupt status prior to masking
                                                               
  __I  uint32_t DMACRawIntErrorStatus;  //Offset 0x018
									//[31:2] : Read undefined
                                                                //[1] : RawIntEerrStatus1 Channel1 error interrupt status prior to masking
                                                                //[0] RawIntEerrStatus0 Channel0 error interrupt status prior to masking
                                                                
  __I  uint32_t DMACEnbldChns;               //Offset 0x01c
									//[31:2] : Read undefined
                                                              //[1] :EnabledChannel1 Channel1 enable status
                                                              //[0] : EnabledChannel0 Channel0 enable status
                                                                
 __IO uint32_t DMACSoftBReq;                //Offset 0x020
								      //[31:16] : Read undefined
                                                              //[15:0] : SoftBReq Software burst request
                                                                
 __IO uint32_t DMACSoftSReq;                //Offset 0x024
								      //[31:16] : Read undefined
                                                              //[15:0] : SoftSReq Software single request
                                                                
 __IO uint32_t DMACSoftLBReq;               //Offset 0x028
									//[31:16] : Read undefined
                                                               //[15:0] : SoftLBReq Software last burst request
                                                                
 __IO uint32_t DMACSoftLSReq;               //Offset 0x02C
									//[31:16] : Read undefined
                                                                //[15:0]: SoftLSReq Software last single request
                                                               
 __IO uint32_t DMACConfiguration;         //Offset 0x030
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
                                                                
 __IO uint32_t DMACSync;                        //Offset 0x034
									//[31:16] : Read undefined
                                                                //[15:0] : DMACSync

         uint32_t RESERVED[50];																
                                                               
 __IO uint32_t DMACC0SrcAddr;              //Offset 0x100 
                                                               //[31:0]:SrcAddr DMA source address
                                                                
 __IO uint32_t DMACC0DestAddr;           //Offset 0x104 
                                                              //[31:0]: DesAddr DMA destination address
                                                                
 __IO uint32_t DMACC0LLI;                      //Offset 0x108
                                                              //[31:2] LLI Linked list item. Bits [31:2] of the address for the next LLI. Address bits [1:0] are 0.
                                                              //[1:0] : Read undefined. Write as zero.
                                                               
 __IO uint32_t DMACC0Control;               //Offset 0x10C 
                                                                
 __IO uint32_t DMACC0Configuration;    //Offset 0x110
                                                             //
 
 	  uint32_t RESERVED1[3]; 
                                                                
 __IO uint32_t DMACC1SrcAddr;             //Offset 0x120               
                                                                
 __IO uint32_t DMACC1DestAddr;          //Offset 0x124             
                                                                
 __IO uint32_t DMACC1LLI;                    //Offset 0x128   
                                                                
 __IO uint32_t DMACC1Control;             //Offset 0x12C       
                                                                
 __IO uint32_t DMACC1Configuration;  //Offset 0x130   
                                                                
}DMA_TypeDef;

/* STAR DATA Register Definitions */

#define UART_DATA_Pos               0                                      	/*!< UART_DATA_Pos: DATA Position */
#define UART_DATA_Msk              (0xFFul << UART_DATA_Pos)               	/*!< UART DATA: Data value */
        
#define UART_STATE_RXOR_Pos         3                                 	   	/*!< UART STATE: RXOR Position */
#define UART_STATE_RXOR_Msk         (0x1ul << UART_STATE_RXOR_Pos)         	/*!< UART STATE: RX buffer overrun, write 1 to clear */

#define UART_STATE_TXOR_Pos         2                                 	   	/*!< UART STATE: TXOR Position */
#define UART_STATE_TXOR_Msk         (0x1ul << UART_STATE_TXOR_Pos)         	/*!< UART STATE: TX buffer overrun, write 1 to clear */

#define UART_STATE_RXBF_Pos         1                                 		/*!< UART STATE: RXBF Position */
#define UART_STATE_RXBF_Msk         (0x1ul << UART_STATE_RXBF_Pos)         	/*!< UART STATE: RX buffer full, read-only */

#define UART_STATE_TXBF_Pos         0                                 		/*!< UART STATE: TXBF Position */
#define UART_STATE_TXBF_Msk         (0x1ul << UART_STATE_TXBF_Pos )        	/*!< UART STATE: TX buffer full, read-only */

#define UART_CTRL_HSTM_Pos          6                                       /*!< UART CTRL: HSTM Position */
#define UART_CTRL_HSTM_Msk          (0x01ul << UART_CTRL_HSTM_Pos)         	/*!< UART CTRL: High-speed test mode for TX only */

#define UART_CTRL_RXORIRQEN_Pos     5                                 		/*!< UART CTRL: RXORIRQEN Position */
#define UART_CTRL_RXORIRQEN_Msk     (0x01ul << UART_CTRL_RXORIRQEN_Pos)    	/*!< UART CTRL: RX overrun interrupt enable */

#define UART_CTRL_TXORIRQEN_Pos     4                                 		/*!< UART CTRL: TXORIRQEN Position */
#define UART_CTRL_TXORIRQEN_Msk     (0x01ul << UART_CTRL_TXORIRQEN_Pos)    	/*!< UART CTRL: TX overrun interrupt enable */

#define UART_CTRL_RXIRQEN_Pos       3                                 		/*!< UART CTRL: RXIRQEN Position */
#define UART_CTRL_RXIRQEN_Msk       (0x01ul << UART_CTRL_RXIRQEN_Pos)      	/*!< UART CTRL: RX interrupt enable */

#define UART_CTRL_TXIRQEN_Pos       2                                 		/*!< UART CTRL: TXIRQEN Position */
#define UART_CTRL_TXIRQEN_Msk       (0x01ul << UART_CTRL_TXIRQEN_Pos)      	/*!< UART CTRL: TX interrupt enable */

#define UART_CTRL_RXEN_Pos          1                                 		/*!< UART CTRL: RXEN Position */
#define UART_CTRL_RXEN_Msk          (0x01ul << UART_CTRL_RXEN_Pos)         	/*!< UART CTRL: RX enable */

#define UART_CTRL_TXEN_Pos          0                                 		/*!< UART CTRL: TXEN Position */
#define UART_CTRL_TXEN_Msk          (0x01ul << UART_CTRL_TXEN_Pos)         	/*!< UART CTRL: TX enable */

#define UART_INTSTATUS_RXORIRQ_Pos  3                                 		/*!< UART CTRL: RXORIRQ Position */
#define UART_CTRL_RXORIRQ_Msk       (0x01ul << UART_INTSTATUS_RXORIRQ_Pos) 	/*!< UART CTRL: RX overrun interrupt. Write 1 to clear */

#define UART_CTRL_TXORIRQ_Pos       2                                 		/*!< UART CTRL: TXORIRQ Position */
#define UART_CTRL_TXORIRQ_Msk       (0x01ul << UART_CTRL_TXORIRQ_Pos)      	/*!< UART CTRL: TX overrun interrupt. Write 1 to clear */

#define UART_CTRL_RXIRQ_Pos         1                                 		/*!< UART CTRL: RXIRQ Position */
#define UART_CTRL_RXIRQ_Msk         (0x01ul << UART_CTRL_RXIRQ_Pos)        	/*!< UART CTRL: RX interrupt. Write 1 to clear */

#define UART_CTRL_TXIRQ_Pos         0                                 		/*!< UART CTRL: TXIRQ Position */
#define UART_CTRL_TXIRQ_Msk         (0x01ul << UART_CTRL_TXIRQ_Pos)        	/*!< UART CTRL: TX interrupt. Write 1 to clear */

#define UART_BAUDDIV_Pos            0                                       /*!< UART BAUDDIV: BAUDDIV Position */
#define UART_BAUDDIV_Msk            (0xFFFFFul << UART_BAUDDIV_Pos)        	/*!< UART BAUDDIV: BAUDDIV Mask */



#define DUALTIMER1_LOAD_Pos            0                                           /* STAR_DUALTIMER1 LOAD: LOAD Position */
#define DUALTIMER1_LOAD_Msk            (0xFFFFFFFFul << DUALTIMER1_LOAD_Pos) 	/* STAR_DUALTIMER1 LOAD: LOAD Mask */
                                                                                                   
#define DUALTIMER1_VALUE_Pos           0                                           /* STAR_DUALTIMER1 VALUE: VALUE Position */
#define DUALTIMER1_VALUE_Msk           (0xFFFFFFFFul << DUALTIMER1_VALUE_Pos)	/* STAR_DUALTIMER1 VALUE: VALUE Mask */
                                                                                                   
#define DUALTIMER1_CTRL_EN_Pos         7                                           /* STAR_DUALTIMER1 Timer Enable: Timer Enable Position */
#define DUALTIMER1_CTRL_EN_Msk         (0x1ul << DUALTIMER1_CTRL_EN_Pos)     	/* STAR_DUALTIMER1 Timer Enable: Timer Enable Mask */
                                                                                              
#define DUALTIMER1_CTRL_MODE_Pos       6                                           /* STAR_DUALTIMER1 Timer Mode: Timer Mode Position */
#define DUALTIMER1_CTRL_MODE_Msk       (0x1ul << DUALTIMER1_CTRL_MODE_Pos)   	/* STAR_DUALTIMER1 Timer Mode: Timer Mode Mask */
                                                                                              
#define DUALTIMER1_CTRL_INTEN_Pos      5                                           /* STAR_DUALTIMER1 Interrupt Enable: Interrupt Enable Position */
#define DUALTIMER1_CTRL_INTEN_Msk      (0x1ul << DUALTIMER1_CTRL_INTEN_Pos)  	/* STAR_DUALTIMER1 Interrupt Enable: Interrupt Enable Mask */
                                                                                              
#define DUALTIMER1_CTRL_PRESCALE_Pos   2                                             /* STAR_DUALTIMER1 Prescale bits: Prescale bits Position */
#define DUALTIMER1_CTRL_PRESCALE_Msk   (0x3ul << DUALTIMER1_CTRL_PRESCALE_Pos)  /* STAR_DUALTIMER1 Prescale bits: Prescale bits Mask */
                                                                                              
#define DUALTIMER1_CTRL_SIZE_Pos       1                                             /* STAR_DUALTIMER1 Timer Size: Timer Size Position */
#define DUALTIMER1_CTRL_SIZE_Msk       (0x1ul << DUALTIMER1_CTRL_SIZE_Pos)      /* STAR_DUALTIMER1 Timer Size: Timer Size Mask */
                                                                                              
#define DUALTIMER1_CTRL_ONESHOOT_Pos   0                                             /* STAR_DUALTIMER1 One-shot Count: One-shot Count Position */
#define DUALTIMER1_CTRL_ONESHOOT_Msk   (0x1ul << DUALTIMER1_CTRL_ONESHOOT_Pos)  /* STAR_DUALTIMER1 One-shot Count: One-shot Count Mask */
                                                                                              
#define DUALTIMER1_INTCLR_Pos          0                                             /* STAR_DUALTIMER1 INTCLR: INT Clear Position */
#define DUALTIMER1_INTCLR_Msk          (0x1ul << DUALTIMER1_INTCLR_Pos)         /* STAR_DUALTIMER1 INTCLR: INT Clear  Mask */
                                                                                              
#define DUALTIMER1_RAWINTSTAT_Pos      0                                             /* STAR_DUALTIMER1 RAWINTSTAT: Raw Int Status Position */
#define DUALTIMER1_RAWINTSTAT_Msk      (0x1ul << DUALTIMER1_RAWINTSTAT_Pos)     /* STAR_DUALTIMER1 RAWINTSTAT: Raw Int Status Mask */
                                                                                              
#define DUALTIMER1_MASKINTSTAT_Pos     0                                             /* STAR_DUALTIMER1 MASKINTSTAT: Mask Int Status Position */
#define DUALTIMER1_MASKINTSTAT_Msk     (0x1ul << DUALTIMER1_MASKINTSTAT_Pos)    /* STAR_DUALTIMER1 MASKINTSTAT: Mask Int Status Mask */
                                                                                              
#define DUALTIMER1_BGLOAD_Pos          0                                             /* STAR_DUALTIMER1 BGLOAD: Background Load Position */
#define DUALTIMER1_BGLOAD_Msk          (0xFFFFFFFFul << DUALTIMER1_BGLOAD_Pos)  /* STAR_DUALTIMER1 BGLOAD: Background Load Mask */
                                                                                              
#define DUALTIMER2_LOAD_Pos            0                                             /* STAR_DUALTIMER2 LOAD: LOAD Position */
#define DUALTIMER2_LOAD_Msk            (0xFFFFFFFFul << DUALTIMER2_LOAD_Pos)    /* STAR_DUALTIMER2 LOAD: LOAD Mask */
                                                                                              
#define DUALTIMER2_VALUE_Pos           0                                             /* STAR_DUALTIMER2 VALUE: VALUE Position */
#define DUALTIMER2_VALUE_Msk           (0xFFFFFFFFul << DUALTIMER2_VALUE_Pos)   /* STAR_DUALTIMER2 VALUE: VALUE Mask */
                                                                                                   
#define DUALTIMER2_CTRL_EN_Pos         7                                             /* STAR_DUALTIMER2 Timer Enable: Timer Enable Position */
#define DUALTIMER2_CTRL_EN_Msk         (0x1ul << DUALTIMER2_CTRL_EN_Pos)        /* STAR_DUALTIMER2 Timer Enable: Timer Enable Mask */
                                                                                              
#define DUALTIMER2_CTRL_MODE_Pos       6                                             /* STAR_DUALTIMER2 Timer Mode: Timer Mode Position */
#define DUALTIMER2_CTRL_MODE_Msk       (0x1ul << DUALTIMER2_CTRL_MODE_Pos)      /* STAR_DUALTIMER2 Timer Mode: Timer Mode Mask */
                                                                                              
#define DUALTIMER2_CTRL_INTEN_Pos      5                                             /* STAR_DUALTIMER2 Interrupt Enable: Interrupt Enable Position */
#define DUALTIMER2_CTRL_INTEN_Msk      (0x1ul << DUALTIMER2_CTRL_INTEN_Pos)     /* STAR_DUALTIMER2 Interrupt Enable: Interrupt Enable Mask */
                                                                                              
#define DUALTIMER2_CTRL_PRESCALE_Pos   2                                             /* STAR_DUALTIMER2 Prescale bits: Prescale bits Position */
#define DUALTIMER2_CTRL_PRESCALE_Msk   (0x3ul << DUALTIMER2_CTRL_PRESCALE_Pos)  /* STAR_DUALTIMER2 Prescale bits: Prescale bits Mask */
                                                                                              
#define DUALTIMER2_CTRL_SIZE_Pos       1                                             /* STAR_DUALTIMER2 Timer Size: Timer Size Position */
#define DUALTIMER2_CTRL_SIZE_Msk       (0x1ul << DUALTIMER2_CTRL_SIZE_Pos)      /* STAR_DUALTIMER2 Timer Size: Timer Size Mask */
                                                                                              
#define DUALTIMER2_CTRL_ONESHOOT_Pos   0                                             /* STAR_DUALTIMER2 One-shot Count: One-shot Count Position */
#define DUALTIMER2_CTRL_ONESHOOT_Msk   (0x1ul << DUALTIMER2_CTRL_ONESHOOT_Pos)  /* STAR_DUALTIMER2 One-shot Count: One-shot Count Mask */
                                                                                              
#define DUALTIMER2_INTCLR_Pos          0                                             /* STAR_DUALTIMER2 INTCLR: INT Clear Position */
#define DUALTIMER2_INTCLR_Msk          (0x1ul << DUALTIMER2_INTCLR_Pos)         /* STAR_DUALTIMER2 INTCLR: INT Clear  Mask */
                                                                                              
#define DUALTIMER2_RAWINTSTAT_Pos      0                                             /* STAR_DUALTIMER2 RAWINTSTAT: Raw Int Status Position */
#define DUALTIMER2_RAWINTSTAT_Msk      (0x1ul << DUALTIMER2_RAWINTSTAT_Pos)     /* STAR_DUALTIMER2 RAWINTSTAT: Raw Int Status Mask */
                                                                                              
#define DUALTIMER2_MASKINTSTAT_Pos     0                                             /* STAR_DUALTIMER2 MASKINTSTAT: Mask Int Status Position */
#define DUALTIMER2_MASKINTSTAT_Msk     (0x1ul << DUALTIMER2_MASKINTSTAT_Pos)    /* STAR_DUALTIMER2 MASKINTSTAT: Mask Int Status Mask */
                                                                                              
#define DUALTIMER2_BGLOAD_Pos          0                                             /* STAR_DUALTIMER2 BGLOAD: Background Load Position */
#define DUALTIMER2_BGLOAD_Msk          (0xFFFFFFFFul << DUALTIMER2_BGLOAD_Pos)  /* STAR_DUALTIMER2 BGLOAD: Background Load Mask */

#define Watchdog_INTCLR_Pos             0                                              /* STAR_Watchdog INTCLR: Int Clear Position */
#define Watchdog_INTCLR_Msk            (0x1ul << Watchdog_INTCLR_Pos)             /* STAR_Watchdog INTCLR: Int Clear Mask */

// SPI_SR Status register
#define SPI_SR_TFE_Pos          0           			// Transmit FIFO empty
#define SPI_SR_TFE_Msk          (1UL<<SPI_SR_TFE_Pos)
#define SPI_SR_TNF_Pos          1           			// Transmit FIFO not full
#define SPI_SR_TNF_Msk          (1UL<<SPI_SR_TNF_Pos)
#define SPI_SR_RNE_Pos          2           			// Receive  FIFO not empty
#define SPI_SR_RNE_Msk          (1UL<<SPI_SR_RNE_Pos)
#define SPI_SR_RFF_Pos          3           			// Receive  FIFO full
#define SPI_SR_RFF_Msk          (1UL<<SPI_SR_RFF_Pos)
#define SPI_SR_BSY_Pos          4           			// PrimeCell SPI busy flag
#define SPI_SR_BSY_Msk          (1UL<<SPI_SR_BSY_Pos)
#define SPI_SR_BSY_TX_Pos       5           			// SPI TX busy flag
#define SPI_SR_BSY_TX_Msk       (1UL<<SPI_SR_BSY_TX_Pos)


/*------------------- I2C ----------------------------------------------*/
typedef struct
{
	__IO    uint32_t  CONTROL;
	__IO    uint32_t  FREQDIV;
	__IO    uint32_t  OWNADDR;
	__IO    uint32_t  SLVADDR;
	__IO    uint32_t  TXDATA;
	__O     uint32_t  RXDATA;
	__O     uint32_t  STATUS1;
	__O     uint32_t  STATUS2;
	
}I2C_TypeDef;


#define I2C_TX_ENA_Pos  0
#define I2C_TX_ENA_Msk  (1UL<<I2C_TX_ENA_Pos)


#define I2C_TX_BUFFER_LEVEL_Pos  2
#define I2C_TX_BUFFER_LEVEL_Msk  (0x3UL<<I2C_TX_BUFFER_LEVEL_Pos)

#define I2C_START_SET_Pos  4
#define I2C_START_SET_Msk  (0x1UL<<I2C_START_SET_Pos)

#define I2C_STOP_SET_Pos  5
#define I2C_STOP_SET_Msk  (0x1UL<<I2C_STOP_SET_Pos)

#define I2C_RX_ENA_Pos  8
#define I2C_RX_ENA_Msk  (1UL<<I2C_RX_ENA_Pos)

#define I2C_RX_BUFFER_LEVEL_Pos  10
#define I2C_RX_BUFFER_LEVEL_Msk  (0x3UL<<I2C_RX_BUFFER_LEVEL_Pos)

#define I2C_TX_NUM_Pos  16
#define I2C_TX_NUM_Msk  (0xFUL<<I2C_TX_NUM_Pos)

#define I2C_SWRST_Pos 31
#define I2C_SWRST_Msk (1UL<<I2C_SWRST_Pos)

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Peripheral and SRAM base address */
#define STAR_FLASH_BASE        (0x00000000UL)  /*!< (FLASH     ) Base Address */
#define STAR_SRAM_BASE         (0x20000000UL)  /*!< (SRAM      ) Base Address */
#define STAR_PERIPH_BASE       (0x40000000UL)  /*!< (Peripheral) Base Address */
#define STAR_TARGEXP0_BASE     (0x60000000UL)  /*!< (TARGEXP0  ) Base Address */
#define STAR_TARGEXP1_BASE     (0xA0000000UL)  /*!< (TARGEXP1  ) Base Address */

#define STAR_RAM_BASE          (0x20000000UL)
#define STAR_APB_BASE          (0x40000000UL)
#define STAR_AHB_BASE          (0x40010000UL)
#define AHB_TARGEXP0_BASE            (0x60000000UL)

/* APB peripherals                                                           */
#define STAR_TIMER0_BASE       (STAR_APB_BASE + 0x0000UL)
#define STAR_TIMER1_BASE       (STAR_APB_BASE + 0x1000UL)
//#define STAR_DUALTIMER_BASE    (STAR_APB_BASE + 0x2000UL)
#define STAR_DUALTIMER0_BASE  (STAR_APB_BASE + 0x2000UL)
#define STAR_DUALTIMER1_BASE  (STAR_APB_BASE + 0xD000UL)
#define STAR_UART0_BASE        (STAR_APB_BASE + 0x4000UL)
#define STAR_UART1_BASE        (STAR_APB_BASE + 0x5000UL)
#define STAR_UART2_BASE        (STAR_APB_BASE + 0xF000UL)
#define STAR_PERI_RSTCTL_BASE  (STAR_APB_BASE + 0x3000UL)
#define STAR_I2C_BASE          (STAR_APB_BASE + 0x6000UL)
#define STAR_ADC0_BASE         (STAR_APB_BASE + 0x7000UL)
#define STAR_ADC1_BASE         (STAR_APB_BASE + 0xE000UL)
#define STAR_WATCHDOG_BASE     (STAR_APB_BASE + 0x8000UL)
#define STAR_SPI0_BASE         (STAR_APB_BASE + 0xB000UL)
#define STAR_SPI1_BASE         (STAR_APB_BASE + 0xC000UL)


/* added by gsl 2018-5-29  */

/* AHB peripherals                                                           */
//#define STAR_ZBT1_BASE         (0x00400000UL)
//#define STAR_ZBT2_BASE         (0x20400000UL)
//#define STAR_PSRAM_BASE        (0x21000000UL)
#define STAR_GPIO0_BASE        (STAR_AHB_BASE + 0x0000UL)
#define STAR_SYSCTRL_BASE      (STAR_AHB_BASE + 0xF000UL)
//#define STAR_EXTSPI_BASE       (0x40020000UL)
//#define STAR_CLCDSPI_BASE      (0x40021000UL)
//#define STAR_CLCDTOUCH_BASE    (0x40022000UL)
//#define STAR_AUDIOCFG_BASE     (0x40023000UL)
//#define STAR_AUDIO_BASE        (0x40024000UL)
//#define STAR_SPIADC_BASE       (0x40025000UL)
//#define STAR_SPISH0_BASE       (0x40026000UL)
//#define STAR_SPISH1_BASE       (0x40027000UL)
//#define STAR_FPGASYS_BASE      (0x40028000UL)
//#define STAR_AUDIOSH0_BASE     (0x40029000UL)
//#define STAR_AUDIOSH1_BASE     (0x4002A000UL)

//#define STAR_SCC_BASE          (0x4002F000UL)
//#define STAR_GPIO4_BASE        (0x40030000UL)
//#define STAR_GPIO5_BASE        (0x40031000UL)
//#define STAR_ETH_BASE          (0x40200000UL)
//#define STAR_VGACON_BASE       (0x41000000UL)
//#define STAR_VGAIMAGE_BASE     (0x41100000UL)

/* Core peripherals                                                           */
#define STAR_COREPERIP_BASE    (0xE0000000UL)
#define STAR_COREAPB_BASE      (0xE0040000UL)
#define STAR_COREROM_BASE      (0xE00FF000UL)

/* Peripheral and SRAM size */
#define STAR_FLASH_SIZE        (0x40000UL)
#define STAR_SRAM_SIZE         (0x30000UL)
#define STAR_APB_SIZE          (0x10000UL)
//#define STAR_PSRAM_SIZE        (0x1000000UL)
//#define STAR_ZBT2_SIZE         (0x400000UL)
//#define STAR_ZBT1_SIZE         (0x400000UL)
#define STAR_TARGEXP0_SIZE     (0x40000000UL)
#define STAR_TARGEXP1_SIZE     (0x40000000UL)

/* Mixed Peripherals*/
#define STAR_DMA_BASE (0x40009000UL)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define STAR_UART0             ((UART_TypeDef   *) STAR_UART0_BASE   )
#define STAR_UART1             ((UART_TypeDef   *) STAR_UART1_BASE   )
#define STAR_UART2             ((UART_TypeDef   *) STAR_UART2_BASE   )
#define STAR_TIMER0            ((TIMER_TypeDef  *) STAR_TIMER0_BASE )
#define STAR_TIMER1            ((TIMER_TypeDef  *) STAR_TIMER1_BASE )
#define STAR_DUALTIMER0        ((DUALTIMER_TypeDef  *) STAR_DUALTIMER0_BASE )
#define STAR_DUALTIMER1        ((DUALTIMER_TypeDef  *) STAR_DUALTIMER1_BASE )
#define STAR_WATCHDOG          ((WATCHDOG_TypeDef  *) STAR_WATCHDOG_BASE   )
#define STAR_GPIO0             ((GPIO_TypeDef   *) STAR_GPIO0_BASE )
//#define STAR_GPIO1             ((STAR_GPIO_TypeDef   *) STAR_GPIO1_BASE )
//#define STAR_GPIO2             ((STAR_GPIO_TypeDef   *) STAR_GPIO2_BASE )
//#define STAR_GPIO3             ((STAR_GPIO_TypeDef   *) STAR_GPIO3_BASE )
//#define STAR_GPIO4             ((STAR_GPIO_TypeDef   *) STAR_GPIO4_BASE )
//#define STAR_GPIO5             ((STAR_GPIO_TypeDef   *) STAR_GPIO5_BASE )
#define STAR_SYSCON            ((SYSCON_TypeDef *) STAR_SYSCTRL_BASE )
#define STAR_I2C               ((I2C_TypeDef *) STAR_I2C_BASE )
//#define STAR_I2S               ((I2S_TypeDef     *) STAR_AUDIO_BASE )
//#define STAR_FPGASYS           ((FPGASYS_TypeDef *) STAR_FPGASYS_BASE )
//#define STAR_SCC               ((SCC_TypeDef *) STAR_SCC_BASE )
#define STAR_ADC0               ((ADC_TypeDef *) STAR_ADC0_BASE )
#define STAR_ADC1               ((ADC_TypeDef *) STAR_ADC1_BASE )
#define STAR_SPI0               ((SPI_TypeDef  *) STAR_SPI0_BASE )
#define STAR_SPI1               ((SPI_TypeDef  *) STAR_SPI1_BASE )
#define GPIO_TUBE               ((GPIO_TUBE_TypeDef *) AHB_TARGEXP0_BASE)
#define APB_PERI_RSTCTL		    ((PERI_RSTCTL_TypeDef  *) STAR_PERI_RSTCTL_BASE)
#define STAR_DMA              	((DMA_TypeDef *) STAR_DMA_BASE)




#ifdef __cplusplus
}
#endif

#endif  /* STAR_H */
