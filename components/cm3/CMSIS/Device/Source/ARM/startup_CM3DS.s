;/**************************************************************************//**
; * @file     startup_CM3DS_MPS2.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           Device CM3DS_MPS2
; * @version  V3.01
; * @date     06. March 2012
; *
; * @note
; * Copyright (C) 2012,2017 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000C00

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     UART0_Handler             ; UART 0 RX and TX Handler
                DCD     ADC_Handler               ; ADC Handler, modified by gsl 2018-5-29
                DCD     UART1_Handler             ; UART 1 RX and TX Handler
                DCD     DMACINTERR_Handler        ; DMA Error Interrupt Handler
                DCD     DMACINTTC_Handler         ; DMA Count Interrupt Handler
                DCD     DMACINTR_Handler          ; DMA Interrupt Handler
                DCD     PORT0_COMB_Handler        ; GPIO Port 0 Combined Handler
                DCD     Spare7_Handler            ; Not Used
                DCD     TIMER0_Handler            ; TIMER 0 handler
                DCD     TIMER1_Handler            ; TIMER 1 handler
                DCD     DUALTIMER_HANDLER         ; Dual timer handler
                DCD     Spare11_Handler           ; Not Used
                DCD     UARTOVF_Handler           ; UART 0,1,2 Overflow Handler
                DCD     EXT13_Handler             ; External Interrupts					
                DCD     EXT14_Handler             ; External Interrupts
                DCD     EXT15_Handler             ; External Interrupts	
                DCD     PORT0_0_Handler           ; GPIO Port 0 pin 0 Handler
                DCD     PORT0_1_Handler           ; GPIO Port 0 pin 1 Handler
                DCD     PORT0_2_Handler           ; GPIO Port 0 pin 2 Handler
                DCD     PORT0_3_Handler           ; GPIO Port 0 pin 3 Handler
                DCD     PORT0_4_Handler           ; GPIO Port 0 pin 4 Handler
                DCD     PORT0_5_Handler           ; GPIO Port 0 pin 5 Handler
                DCD     PORT0_6_Handler           ; GPIO Port 0 pin 6 Handler
                DCD     PORT0_7_Handler           ; GPIO Port 0 pin 7 Handler
                DCD     PORT0_8_Handler           ; GPIO Port 0 pin 8 Handler
                DCD     PORT0_9_Handler           ; GPIO Port 0 pin 9 Handler
                DCD     PORT0_10_Handler          ; GPIO Port 0 pin 10 Handler
                DCD     PORT0_11_Handler          ; GPIO Port 0 pin 11 Handler
                DCD     PORT0_12_Handler          ; GPIO Port 0 pin 12 Handler
                DCD     PORT0_13_Handler          ; GPIO Port 0 pin 13 Handler
                DCD     PORT0_14_Handler          ; GPIO Port 0 pin 14 Handler
                DCD     PORT0_15_Handler          ; GPIO Port 0 pin 15 Handler
                DCD     PORT0_16_Handler          ; GPIO Port 0 pin 16 Handler
                DCD     PORT0_17_Handler          ; GPIO Port 0 pin 17 Handler
                DCD     PORT0_18_Handler          ; GPIO Port 0 pin 18 Handler
                DCD     PORT0_19_Handler          ; GPIO Port 0 pin 19 Handler
                DCD     PORT0_20_Handler          ; GPIO Port 0 pin 20 Handler
                DCD     PORT0_21_Handler          ; GPIO Port 0 pin 21 Handler
                DCD     PORT0_22_Handler          ; GPIO Port 0 pin 22 Handler
                DCD     PORT0_23_Handler          ; GPIO Port 0 pin 23 Handler
                DCD     PORT0_24_Handler          ; GPIO Port 0 pin 24 Handler
                DCD     PORT0_25_Handler          ; GPIO Port 0 pin 25 Handler
                DCD     PORT0_26_Handler          ; GPIO Port 0 pin 16 Handler
                DCD     PORT0_27_Handler          ; GPIO Port 0 pin 17 Handler
                DCD     PORT0_28_Handler          ; GPIO Port 0 pin 18 Handler
                DCD     PORT0_29_Handler          ; GPIO Port 0 pin 19 Handler
                DCD     PORT0_30_Handler          ; GPIO Port 0 pin 20 Handler
                DCD     PORT0_31_Handler          ; GPIO Port 0 pin 21 Handler					
                DCD     I2C_Handler               ; I2C Handler
                DCD     MPS2_SSP0_Handler         ; SPI0 Handler 
                DCD     MPS2_SSP1_Handler         ; SPI1 Handler 
                DCD     EXT0_Handler              ; External Interrupts
                DCD     EXT1_Handler              ; External Interrupts
                DCD     EXT2_Handler              ; External Interrupts
                DCD     EXT3_Handler              ; External Interrupts
                DCD     EXT4_Handler              ; External Interrupts
                DCD     EXT5_Handler              ; External Interrupts
                DCD     EXT6_Handler              ; External Interrupts
                DCD     EXT7_Handler              ; External Interrupts
                DCD     EXT8_Handler              ; External Interrupts
                DCD     EXT9_Handler              ; External Interrupts
                DCD     EXT10_Handler             ; External Interrupts
                DCD     EXT11_Handler             ; External Interrupts
                DCD     EXT12_Handler             ; External Interrupts
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT UART0_Handler              [WEAK]
                EXPORT ADC_Handler                [WEAK]
                EXPORT UART1_Handler              [WEAK]
                EXPORT DMACINTERR_Handler         [WEAK]
                EXPORT DMACINTTC_Handler          [WEAK]
                EXPORT DMACINTR_Handler           [WEAK]
                EXPORT PORT0_COMB_Handler         [WEAK]
                EXPORT Spare7_Handler             [WEAK]
                EXPORT TIMER0_Handler             [WEAK]
                EXPORT TIMER1_Handler             [WEAK]
                EXPORT DUALTIMER_HANDLER          [WEAK]
                EXPORT Spare11_Handler            [WEAK]
                EXPORT UARTOVF_Handler            [WEAK]
                EXPORT Spare13_Handler            [WEAK]
                EXPORT Spare14_Handler            [WEAK]
                EXPORT Spare15_Handler            [WEAK]
                EXPORT PORT0_0_Handler            [WEAK]
                EXPORT PORT0_1_Handler            [WEAK]
                EXPORT PORT0_2_Handler            [WEAK]
                EXPORT PORT0_3_Handler            [WEAK]
                EXPORT PORT0_4_Handler            [WEAK]
                EXPORT PORT0_5_Handler            [WEAK]
                EXPORT PORT0_6_Handler            [WEAK]
                EXPORT PORT0_7_Handler            [WEAK]
                EXPORT PORT0_8_Handler            [WEAK]
                EXPORT PORT0_9_Handler            [WEAK]
                EXPORT PORT0_10_Handler           [WEAK]
                EXPORT PORT0_11_Handler           [WEAK]
                EXPORT PORT0_12_Handler           [WEAK]
                EXPORT PORT0_13_Handler           [WEAK]
                EXPORT PORT0_14_Handler           [WEAK]
                EXPORT PORT0_15_Handler           [WEAK]
                EXPORT PORT0_16_Handler           [WEAK]
                EXPORT PORT0_17_Handler           [WEAK]
                EXPORT PORT0_18_Handler           [WEAK]
                EXPORT PORT0_19_Handler           [WEAK]
                EXPORT PORT0_20_Handler           [WEAK]
                EXPORT PORT0_21_Handler           [WEAK]
                EXPORT PORT0_22_Handler           [WEAK]
                EXPORT PORT0_23_Handler           [WEAK]		
                EXPORT PORT0_24_Handler           [WEAK]
                EXPORT PORT0_25_Handler           [WEAK]
                EXPORT PORT0_26_Handler           [WEAK]
                EXPORT PORT0_27_Handler           [WEAK]
                EXPORT PORT0_28_Handler           [WEAK]
                EXPORT PORT0_29_Handler           [WEAK]
                EXPORT PORT0_30_Handler           [WEAK]
                EXPORT PORT0_31_Handler           [WEAK]
                EXPORT I2C_Handler                [WEAK]
                EXPORT MPS2_SSP0_Handler          [WEAK]
                EXPORT MPS2_SSP1_Handler          [WEAK]
                EXPORT Spare51_Handler            [WEAK]
                EXPORT Spare52_Handler            [WEAK]
                EXPORT Spare53_Handler            [WEAK]
                EXPORT Spare54_Handler            [WEAK]
                EXPORT Spare55_Handler            [WEAK]
                EXPORT Spare56_Handler            [WEAK]
                EXPORT Spare57_Handler            [WEAK]
                EXPORT Spare58_Handler            [WEAK]
                EXPORT Spare59_Handler            [WEAK]
                EXPORT Spare60_Handler            [WEAK]
                EXPORT Spare61_Handler            [WEAK]
                EXPORT Spare62_Handler            [WEAK]
                EXPORT Spare63_Handler            [WEAK]					
                EXPORT EXT0_Handler               [WEAK]
                EXPORT EXT1_Handler               [WEAK]
                EXPORT EXT2_Handler               [WEAK]
                EXPORT EXT3_Handler               [WEAK]
                EXPORT EXT4_Handler               [WEAK]
                EXPORT EXT5_Handler               [WEAK]
                EXPORT EXT6_Handler               [WEAK]
                EXPORT EXT7_Handler               [WEAK]
                EXPORT EXT8_Handler               [WEAK]
                EXPORT EXT9_Handler               [WEAK]
                EXPORT EXT10_Handler              [WEAK]
                EXPORT EXT11_Handler              [WEAK]
                EXPORT EXT12_Handler              [WEAK]
                EXPORT EXT13_Handler              [WEAK]
                EXPORT EXT14_Handler              [WEAK]
                EXPORT EXT15_Handler              [WEAK]

UART0_Handler
ADC_Handler
UART1_Handler
DMACINTERR_Handler
DMACINTTC_Handler
DMACINTR_Handler
PORT0_COMB_Handler
Spare7_Handler
TIMER0_Handler
TIMER1_Handler
DUALTIMER_HANDLER
Spare11_Handler
UARTOVF_Handler
Spare13_Handler
Spare14_Handler
Spare15_Handler
PORT0_0_Handler
PORT0_1_Handler
PORT0_2_Handler
PORT0_3_Handler
PORT0_4_Handler
PORT0_5_Handler
PORT0_6_Handler
PORT0_7_Handler
PORT0_8_Handler
PORT0_9_Handler
PORT0_10_Handler
PORT0_11_Handler
PORT0_12_Handler
PORT0_13_Handler
PORT0_14_Handler
PORT0_15_Handler
PORT0_16_Handler
PORT0_17_Handler
PORT0_18_Handler
PORT0_19_Handler
PORT0_20_Handler
PORT0_21_Handler
PORT0_22_Handler
PORT0_23_Handler
PORT0_24_Handler
PORT0_25_Handler
PORT0_26_Handler
PORT0_27_Handler
PORT0_28_Handler
PORT0_29_Handler
PORT0_30_Handler
PORT0_31_Handler
I2C_Handler
MPS2_SSP0_Handler
MPS2_SSP1_Handler
Spare51_Handler
Spare52_Handler
Spare53_Handler
Spare54_Handler
Spare55_Handler
Spare56_Handler
Spare57_Handler
Spare58_Handler
Spare59_Handler
Spare60_Handler
Spare61_Handler
Spare62_Handler
Spare63_Handler
EXT0_Handler 
EXT1_Handler 
EXT2_Handler 
EXT3_Handler 
EXT4_Handler 
EXT5_Handler 
EXT6_Handler 
EXT7_Handler 
EXT8_Handler 
EXT9_Handler 
EXT10_Handler
EXT11_Handler
EXT12_Handler
EXT13_Handler
EXT14_Handler
EXT15_Handler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
