//------------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from Arm Technology (China) Co., Ltd.
// or its affiliates.
//
//            (C) COPYRIGHT 2019-2020 Arm Technology (China) Co., Ltd.
//                or its affiliates.
//            (C) COPYRIGHT 2017-2020 Arm Limited or its affiliates.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from Arm Technology (China) Co., Ltd. or its affiliates.
//
//  Release Information : STAR-r1p0-00eac0
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//
// Star Execution Testbench Configuration File
//
////////////////////////////////////////////////////////////////////////////////
//
//  Processor configuration options.
//  These must match the expected hardware configuration of the processor.
//
//  - EXPECTED_FPU           : Expected Floating Point Unit (0-1)
//  - EXPECTED_DSP           : Expected DSP Extension (0-1)
//  - EXPECTED_SECEXT        : Expected Security Extension (0-1)
//  - EXPECTED_CPIF          : Expected External Coprocessor interface (0-1)
//  - EXPECTED_MPU_NS        : Expected MPU non-secure regions (0,4,8,12,16)
//  - EXPECTED_MPU_S         : Expected MPU secure regions (0,4,8,12,16)
//  - EXPECTED_SAU           : Expected number of SAU regions (0,4,8)
//  - EXPECTED_NUMIRQ        : Expected number of IRQ lines (0-240)
//  - EXPECTED_IRQLVL        : Expected number of IRQ levels (3-8)
//  - EXPECTED_IRQLATENCY    : Expected split between high and low latency interrupts (NUMIRQ length vector)
//  - EXPECTED_IRQDIS        : Expected disable individual interrupts (NUMIRQ length vector)
//  - EXPECTED_DBGLVL        : Expected debug level (0-1)
//  - EXPECTED_ITM           : Expected CoreSight ITM trace config (0,1)
//  - EXPECTED_ETM           : Expected CoreSight ETM trace config (0,1)
//  - EXPECTED_MTB           : Expected CoreSight MTB trace config (0,1)
//  - EXPECTED_MTBAWIDTH     : Expected CoreSight MTB SRAM address width (5..32)
//  - EXPECTED_WIC           : Expected Wake-up interrupt controller support <0-1>
//  - EXPECTED_WICLINES      : Expected number of supported WIC lines <3-NUMIRQ+3>
//  - EXPECTED_CTI           : Expected Cross Trigger Interface Support (0,1)
//  - EXPECTED_QSPI          : Expected QSPI Unit (0-1)
//
//  Processor Tie-offs Static Config
//  - EXPECTED_BIGEND        : Expected Endianness (0-1)
//  - EXPECTED_SSTCALIB      : Expected value of SSTCALIB[25:0] <0x0-0x3FFFFFF>
//  - EXPECTED_NSSTCALIB     : Expected value of NSSTCALIB[25:0] <0x0-0x3FFFFFF>
//  - EXPECTED_CFGFPU        : Expected Floating Point Unit Enable (0-1)
//  - EXPECTED_CFGDSP        : Expected DSP Extension Enable(0-1)
//  - EXPECTED_CFGSECEXT     : Expected Security Extension Enable (0-1)
//  - EXPECTED_MPUNSDISABLE  : Expected MPU non-secure disable (0-1)
//  - EXPECTED_MPUSDISABLE   : Expected MPU secure disable (0-1)
//  - EXPECTED_SAUDISABLE    : Expected SAU disable (0-1)
//
//  Processor Tie-offs Reset Config
//  - EXPECTED_INITSVTOR     : Expected secure initialisation vector
//  - EXPECTED_INITNSVTOR    : Expected non-secure initialisation vector
//  - EXPECTED_RETENTION     : Expected retention support (0-1)
//
////////////////////////////////////////////////////////////////////////////////
//
//  DAP configuration options.
//  These must match the expected hardware configuration of the DAP.
//
//  - EXPECTED_MCUROMADDR    : Expected MCU ROM Address
//
//  DAP Tie-offs
//
//  - EXPECTED_INSTANCEID    : Expected DAP instance number (0-0xF)
//  - EXPECTED_TREVISION     : Expected Revision number (0-0xF)
//  - EXPECTED_TPARTNO       : Expected Part number (0-0xFFFF)
//  - EXPECTED_TDESIGNER     : Expected Designer code (0-0x7FF)
//  - EXPECTED_DPSEL         : Expected Debug Port Select (0,1,2)
//
////////////////////////////////////////////////////////////////////////////////
//
//  System ROM Table options.
//  These must match the values in the System ROM Table.
//
//  - EXPECTED_CUST_JEPID    : Expected JEDEC JEP-106 identity code (0-0x7F)
//  - EXPECTED_CUST_JEPCONT  : Expected JEDEC JEP-106 continuation code (0-0xF)
//  - EXPECTED_CUST_PART     : Expected Part number (0-0xFFF)
//  - EXPECTED_CUST_REV      : Expected Revision number (0-0xF)
//  - EXPECTED_CUST_REVAND   : Expected Manufacturer Revision number (0-0xF)
//
////////////////////////////////////////////////////////////////////////////////
//
//  Engineering Change Order and Revision Number Tie-off.
//
//  - EXPECTED_ECOREVNUM     : Expected Engineering Change Order and Revision number (0-0xFFFFF_FFFFFFFF)
//
////////////////////////////////////////////////////////////////////////////////

// RealView MDK GUI Support
// <<< Use Configuration Wizard in Context Menu >>>
//
// <h> Processor configuration options
// <o.0> EXPECTED_FPU: Expected Floating Point Unit
#define EXPECTED_FPU            1

// <o.0> EXPECTED_DSP: Expected DSP Extension
#define EXPECTED_DSP            1

// <o.0> EXPECTED_SECEXT: Expected Security Extension
#define EXPECTED_SECEXT         1

// <o.0> EXPECTED_CPIF: Expected External Coprocessor interface Unit
#define EXPECTED_CPIF           1

// <o> EXPECTED_MPU_NS: Expected MPU non-secure regions <0=> Absent <4=> 4 Regions <8=> 8 Regions <12=> 12 Regions <16=> 16 Regions
#define EXPECTED_MPU_NS         8

// <o> EXPECTED_MPU_S: Expected MPU secure regions <0=> Absent <4=> 4 Regions <8=> 8 Regions <12=> 12 Regions <16=> 16 Regions
#define EXPECTED_MPU_S          8

// <o> EXPECTED_SAU: Expected number SAU regions <0=> Absent <4=> 4 Regions <8=> 8 Regions
#define EXPECTED_SAU            4

// <o> EXPECTED_NUMIRQ: Expected number of IRQ lines <1-480>
#define EXPECTED_NUMIRQ         32

// <o> EXPECTED_IRQLVL: Expected number of exception levels <3-8>
#define EXPECTED_IRQLVL         3

// <h> EXPECTED_IRQLATENCY: Expected split between high and low latency interrupts <NUMIRQ length vector>
// <o0 >IRQLATENCY for IRQ number 479 - 448
// <o1 >IRQLATENCY for IRQ number 447 - 416
// <o1 >IRQLATENCY for IRQ number 415 - 384
// <o1 >IRQLATENCY for IRQ number 383 - 352
// <o2 >IRQLATENCY for IRQ number 351 - 320
// <o3 >IRQLATENCY for IRQ number 319 - 288
// <o4 >IRQLATENCY for IRQ number 287 - 256
// <o5 >IRQLATENCY for IRQ number 255 - 224
// <o6 >IRQLATENCY for IRQ number 223 - 192
// <o7 >IRQLATENCY for IRQ number 191 - 160
// <o8 >IRQLATENCY for IRQ number 159 - 128
// <o9 >IRQLATENCY for IRQ number 127 - 96
// <o10>IRQLATENCY for IRQ number 95 - 64
// <o11>IRQLATENCY for IRQ number 63 - 32
// <o12>IRQLATENCY for IRQ number 31 - 0
#define EXPECTED_IRQLATENCY_479_448 0x00000000
#define EXPECTED_IRQLATENCY_447_416 0x00000000
#define EXPECTED_IRQLATENCY_415_384 0x00000000
#define EXPECTED_IRQLATENCY_383_352 0x00000000
#define EXPECTED_IRQLATENCY_351_320 0x00000000
#define EXPECTED_IRQLATENCY_319_288 0x00000000
#define EXPECTED_IRQLATENCY_287_256 0x00000000
#define EXPECTED_IRQLATENCY_255_224 0x00000000
#define EXPECTED_IRQLATENCY_223_192 0x00000000
#define EXPECTED_IRQLATENCY_191_160 0x00000000
#define EXPECTED_IRQLATENCY_159_128 0x00000000
#define EXPECTED_IRQLATENCY_127_96  0x00000000
#define EXPECTED_IRQLATENCY_95_64   0x00000000
#define EXPECTED_IRQLATENCY_63_32   0x00000000
#define EXPECTED_IRQLATENCY_31_0    0xFFFFFFFF
// </h>

// <h> EXPECTED_IRQDIS Expected disable individual interrupts <NUMIRQ length vector>
// <o0 >IRQDIS for IRQ number 479 - 448
// <o1 >IRQDIS for IRQ number 447 - 416
// <o1 >IRQDIS for IRQ number 415 - 384
// <o1 >IRQDIS for IRQ number 383 - 352
// <o2 >IRQDIS for IRQ number 351 - 320
// <o3 >IRQDIS for IRQ number 319 - 288
// <o4 >IRQDIS for IRQ number 287 - 256
// <o5 >IRQDIS for IRQ number 255 - 224
// <o6 >IRQDIS for IRQ number 223 - 192
// <o7 >IRQDIS for IRQ number 191 - 160
// <o8 >IRQDIS for IRQ number 159 - 128
// <o9 >IRQDIS for IRQ number 127 - 96
// <o10>IRQDIS for IRQ number 95 - 64
// <o11>IRQDIS for IRQ number 63 - 32
// <o12>IRQDIS for IRQ number 31 - 0
#define EXPECTED_IRQDIS_479_448   0x00000000
#define EXPECTED_IRQDIS_447_416   0x00000000
#define EXPECTED_IRQDIS_415_384   0x00000000
#define EXPECTED_IRQDIS_383_352   0x00000000
#define EXPECTED_IRQDIS_351_320   0x00000000
#define EXPECTED_IRQDIS_319_288   0x00000000
#define EXPECTED_IRQDIS_287_256   0x00000000
#define EXPECTED_IRQDIS_255_224   0x00000000
#define EXPECTED_IRQDIS_223_192   0x00000000
#define EXPECTED_IRQDIS_191_160   0x00000000
#define EXPECTED_IRQDIS_159_128   0x00000000
#define EXPECTED_IRQDIS_127_96    0x00000000
#define EXPECTED_IRQDIS_95_64     0x00000000
#define EXPECTED_IRQDIS_63_32     0x00000000
#define EXPECTED_IRQDIS_31_0      0x00000000

#define EXPECTED_CFGITCMSZ        0x0000000f
#define EXPECTED_CFGDTCMSZ        0x0000000f
#define EXPECTED_ICACHESZ         0x00000007
#define EXPECTED_DCACHESZ         0x00000007
#define EXPECTED_TCM              1
#define EXPECTED_ITGU             0
#define EXPECTED_ITGUBLKSZ        3
#define EXPECTED_ITGUMAXBLKS      0
#define EXPECTED_DTGU             0
#define EXPECTED_DTGUBLKSZ        3
#define EXPECTED_DTGUMAXBLKS      0
// </h>

// <o> EXPECTED_DBGLVL: Expected debug level
//                      <0=> No halting debug or memory access
//                      <1=> 2 WPT and 4 BKPT
//                      <2=> 4 WPT and 8 BKPT
#define EXPECTED_DBGLVL         2

// <o.0> EXPECTED_ITM: Expected CoreSight ITM config
#define EXPECTED_ITM            1

// <o.0> EXPECTED_ETM: Expected CoreSight ETM config
#define EXPECTED_ETM            0

// <o.0> EXPECTED_MTB: Expected CoreSight MTB config
#define EXPECTED_MTB            0

// <o> EXPECTED_MTBAWIDTH: Expected MTB RAM address width <5-32>
#define EXPECTED_MTBAWIDTH      32

// <o.0> EXPECTED_WIC: Expected Wake-up interrupt controller support <0-1>
#define EXPECTED_WIC            1

// <o> EXPECTED_WICLINES : Expected number of supported WIC lines <4-483>
#define EXPECTED_WICLINES       35

// <o.0> EXPECTED_CTI: Expected Cross Trigger Interface
#define EXPECTED_CTI            1

// <h> Processor port Tie-offs Static Config
// <o> EXPECTED_BIGEND: Expected Endianness <0=> Little Endian <1=> Big Endian
#define EXPECTED_BIGEND         0

// <o> EXPECTED_SSTCALIB: Expected value of SSTCALIB[25:0] Secure Systick calibration <0x0-0x3FFFFFF>
#define EXPECTED_SSTCALIB       0x107A11F

// <o> EXPECTED_NSSTCALIB: Expected value of NSSTCALIB[25:0] Non-secure Systick calibration <0x0-0x3FFFFFF>
#define EXPECTED_NSSTCALIB      0x107A11F

// <o.0> EXPECTED_CFGFPU: Expected Floating Point Unit Enable
#define EXPECTED_CFGFPU         1

// <o.0> EXPECTED_CFGDSP: Expected DSP Extension Enable
#define EXPECTED_CFGDSP         1

// <o.0> EXPECTED_CFGSECEXT: Expected Security Extension Enable
#define EXPECTED_CFGSECEXT      1

// <o> EXPECTED_MPUNSDISABLE: Expected value of MPUNSDISABLE <0-1>
#define EXPECTED_MPUNSDISABLE   0

// <o> EXPECTED_MPUSDISABLE: Expected value of MPUSDISABLE <0-1>
#define EXPECTED_MPUSDISABLE    0

// <o> EXPECTED_SAUDISABLE: Expected value of SAUDISABLE <0-1>
#define EXPECTED_SAUDISABLE     0

// <h> Processor port Tie-offs Static Config
// <o> EXPECTED_INITSVTOR:  Expected default secure initialisation vector
#define EXPECTED_INITSVTOR      0x00000000

// <o> EXPECTED_INITNSVTOR:  Expected default non-secure initialisation vector
#define EXPECTED_INITNSVTOR     0x00000000

// <o> EXPECTED_RETENTION: Expected retention support <0-1>
#define EXPECTED_RETENTION      1

// </h>

// <h> DAP configuration options

#if (EXPECTED_ETM == 1) && (EXPECTED_DBGLVL != 0) || (EXPECTED_ITM==1)
// <o> EXPECTED_MCUROMADDR : Expected MCU ROM Address
  #define EXPECTED_MCUROMADDR 0xE00FE000
#else
  #define EXPECTED_MCUROMADDR 0xE00FF000
#endif

// </h>

// <h> DAP Tie-offs
// <o> EXPECTED_INSTANCEID: Expected DAP instance number (0-0xF)
#define EXPECTED_INSTANCEID     0x0

// <o> EXPECTED_TREVISION: Expected Revision number (0-0xF)
#define EXPECTED_TREVISION      0x7

// <o> EXPECTED_TPARTNO: Expected Part number (0-0xFFFF)
#define EXPECTED_TPARTNO        0xf15f

// <o> EXPECTED_TDESIGNER: Expected Designer code (0-0x7FF)
#define EXPECTED_TDESIGNER      0x67f

// <o> EXPECTED_DPSEL: Debug Port Select (0-JTAG ,1-SW ,2-JTAG&SW)
#define EXPECTED_DPSEL          2

// </h>

// <h> CoreSight Debug configuration options
// <o> EXPECTED_CUST_JEPID: Expected JEDEC JEP-106 identity code (0-0x7F)
#define EXPECTED_CUST_JEPID     0x2

// <o> EXPECTED_CUST_JEPCONT: Expected JEDEC JEP-106 continuation code (0-0xF)
#define EXPECTED_CUST_JEPCONT   0xe

// <o> EXPECTED_CUST_PART: Expected Part number (0-0xFFF)
#define EXPECTED_CUST_PART      0x4ca

// <o> EXPECTED_CUST_REV: Expected Revision number (0-0xF)
#define EXPECTED_CUST_REV       0x0

// <o> EXPECTED_CUST_REVAND: Expected Manufacturer Revision number (0-0xF)
#define EXPECTED_CUST_REVAND    0x0

// <h> EXPECTED_ECOREVNUM
// <o> EXPECTED_ECOREVNUM: Expected Engineering Change Order and Revision number (0-0xFFFFF_FFFFFFFF)
#define EXPECTED_ECOREVNUM      0x0000000000000LL

// </h>

// <h> CDE configuration options
// <o> EXPECTED_CDEMAPPEDONCP0: Expected value of CDE mapped on CP0 <0-1>
#define EXPECTED_CDEMAPPEDONCP0           0

// <o> EXPECTED_CDEMAPPEDONCP1: Expected value of CDE mapped on CP1 <0-1>
#define EXPECTED_CDEMAPPEDONCP1           0

// <o> EXPECTED_CDEMAPPEDONCP2: Expected value of CDE mapped on CP2 <0-1>
#define EXPECTED_CDEMAPPEDONCP2           0

// <o> EXPECTED_CDEMAPPEDONCP3: Expected value of CDE mapped on CP3 <0-1>
#define EXPECTED_CDEMAPPEDONCP3           0

// <o> EXPECTED_CDEMAPPEDONCP4: Expected value of CDE mapped on CP4 <0-1>
#define EXPECTED_CDEMAPPEDONCP4           0

// <o> EXPECTED_CDEMAPPEDONCP5: Expected value of CDE mapped on CP5 <0-1>
#define EXPECTED_CDEMAPPEDONCP5           0

// <o> EXPECTED_CDEMAPPEDONCP6: Expected value of CDE mapped on CP6 <0-1>
#define EXPECTED_CDEMAPPEDONCP6           0

// <o> EXPECTED_CDEMAPPEDONCP7: Expected value of CDE mapped on CP7 <0-1>
#define EXPECTED_CDEMAPPEDONCP7           0

// <o> EXPECTED_CDERTLID: Expected value of RTL ID code present in the customisable CDE module <0-255>
#define EXPECTED_CDERTLID       0

// </h>

// <h> QSPI configuration options
// <o> EXPECTED_QSPI: Expected QSPI
#define EXPECTED_QSPI           0

// <o> EXPECTED_QSPI_FMSIZE: Expected Maximum size of flash memory if EXPECTED_QSPI is present
#define EXPECTED_QSPIFMSIZE              1

// <o> EXPECTED_QSPI_FIFO_DEPTH: Expected RX/TX FIFO depth in QSPI if EXPECTED_QSPI is present
#define EXPECTED_QSPIFIFODEPTH           2

// </h>

// <<< end of configuration section >>>

////////////////////////////////////////////////////////////////////////////////
//
// Define whether the execution_tb tests and the DebugDriver code should display messages
// using the chracter output device in the testbench.
//
////////////////////////////////////////////////////////////////////////////////
#define EXECTB_PRINTF
//#define DEBUGDRIVER_PRINTF
//#define DEBUGTRACE_PRINTF

// These values are used for TRACE ID when testing trace.
// Allows the formatter output to be associated with the generating source

#define EXECTB_ETM_ID 0x22
#define EXECTB_ITM_ID 0x59


////////////////////////////////////////////////////////////////////////////////
//
// ID values - DO NOT MODIFY
//
////////////////////////////////////////////////////////////////////////////////

// Used by the Dhrystone benchmark
#define EXPECTED_SYST           1

#define STAR_CPUID              (0x631F1320 ^ (EXPECTED_ECOREVNUM & 0x0000000FLL))

// CoreSight Component Identifier for Peripheral classes
#define CORESIGHT_CID0          0x0D
#define CORESIGHT_CID1_tbl      0x10
#define CORESIGHT_CID1_dbg      0x90
#define CORESIGHT_CID1_mem      0xE0
#define CORESIGHT_CID1_prm      0xF0
#define CORESIGHT_CID2          0x05
#define CORESIGHT_CID3          0xB1

#define ARM_JEP_ID              0x3B
#define ARM_JEP_CONT            0x4

#define ARMCHINA_JEP_ID         0x75
#define ARMCHINA_JEP_CONT       0xA

#define ETM_JEP_ID              0x75
#define ETM_JEP_CONT            0xA

#define ITM_JEP_ID              0x75
#define ITM_JEP_CONT            0xA

// Component Part Numbers
#define STAR_CPU_PART           0x132
#define STAR_PART               0x132
#define STAR_CSI_PART           0x4C8
#define STAR_DAP_DP_PART        0xBD

// ARCHID codes
#define STAR_ITM_ARCHID         0x1A01
#define STAR_DWT_ARCHID         0x1A02
#define STAR_FPB_ARCHID         0x1A03
#define STAR_DBG_ARCHID         0x2A04
#define STAR_ETM_ARCHID         0x4A13
#define STAR_CTI_ARCHID         0x1A14
#define STAR_MTB_ARCHID         0x0A31
#define STAR_TPIU_ARCHID        0x0000

// Revision Codes
#define STAR_ITM_REV            0x0
#define STAR_ETM_REV            0x0

// Revand
#define STAR_SYSROM_ECO         ((EXPECTED_ECOREVNUM & 0xF000000000000LL) >> 48)
#define STAR_TPIU_ECO           ((EXPECTED_ECOREVNUM & 0x0F00000000000LL) >> 44)
#define STAR_DAP_DP_ECO         ((EXPECTED_ECOREVNUM & 0x00F0000000000LL) >> 40)
#define STAR_DAP_AP_ECO         ((EXPECTED_ECOREVNUM & 0x000F000000000LL) >> 36)
#define STAR_MTB_ECO            ((EXPECTED_ECOREVNUM & 0x0000F00000000LL) >> 32)
#define STAR_ETM_ECO            ((EXPECTED_ECOREVNUM & 0x00000F0000000LL) >> 28)
#define STAR_CTI_ECO            ((EXPECTED_ECOREVNUM & 0x000000F000000LL) >> 24)
#define STAR_ROM_ECO            ((EXPECTED_ECOREVNUM & 0x0000000F00000LL) >> 20)
#define STAR_ITM_ECO            ((EXPECTED_ECOREVNUM & 0x00000000F0000LL) >> 16)
#define STAR_SCS_ECO            ((EXPECTED_ECOREVNUM & 0x000000000F000LL) >> 12)
#define STAR_DWT_ECO            ((EXPECTED_ECOREVNUM & 0x0000000000F00LL) >>  8)
#define STAR_BPU_ECO            ((EXPECTED_ECOREVNUM & 0x00000000000F0LL) >>  4)

// DAP Registers
#define STAR_DAP_JTAG_TAPID     (0x0BA04AEB | (STAR_DAP_DP_ECO << 28))
#define STAR_DAP_JTAG_DPIDR     (0x0BE11AEB | (STAR_DAP_DP_ECO << 28))
#define STAR_DAP_SW_DPIDR       (0x1BE11AEB | (STAR_DAP_DP_ECO << 28))
#define STAR_DAP_SWMD_DPIDR     (0x1BE12AEB | (STAR_DAP_DP_ECO << 28))
#define STAR_DAP_APIDR          (0x0AEB0051 | (STAR_DAP_AP_ECO << 28))

// CTI Registers
#define DEV_TYPE_VALUE          0x00000014

//GPIO Interrupt
#define GPIO_IRQn               0


////////////////////////////////////////////////////////////////////////////////
//
// Defines used in execution_tb - Do not modify
//
////////////////////////////////////////////////////////////////////////////////

#define SYSROMTABLE_BASE        0xE00FD000
#define PILROMTABLE_BASE        0xE00FE000
#define STARROMTABLE_BASE       0xE00FF000

#define DEVARCH_Offset          0xFBC
#define MEMTYPE_Offset          0xFCC
#define PID4_Offset             0xFD0
#define PID5_Offset             0xFD4
#define PID6_Offset             0xFD8
#define PID7_Offset             0xFDC
#define PID0_Offset             0xFE0
#define PID1_Offset             0xFE4
#define PID2_Offset             0xFE8
#define PID3_Offset             0xFEC
#define CID0_Offset             0xFF0
#define CID1_Offset             0xFF4
#define CID2_Offset             0xFF8
#define CID3_Offset             0xFFC

#define STAR_SCB_MVFR0          0x10110021
#define STAR_SCB_MVFR1          0x11000011

#define STAR_SCB_ID_PRF1_SEC    0x00000010
#define STAR_SCB_ID_PRF1_NO_SEC 0x00000000

#define STAR_SCB_ISAR2_DSP      0x20232232
#define STAR_SCB_ISAR2_NODSP    0x20112232

#define STAR_SCB_ISAR0_COPRO    0x01141110
#define STAR_SCB_ISAR0_NOCOPRO  0x01101110

/*SCB */
#define SCB_CPACR_FPU           (0xF << 20)   /*!< cp10 and cp11 set in CPACR  */
////////////////////////////////////////////////////////////////////////////////
