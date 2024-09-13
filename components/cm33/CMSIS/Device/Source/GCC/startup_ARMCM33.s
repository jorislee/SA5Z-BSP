;/**************************************************************************//**
; * @file     startup_ARMCM33.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM33 Device
; * @version  V1.0.1
; * @date     23. July 2019
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------


;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>	
Stack_Size      EQU      0x00000c00   ;0x00000400

                AREA     STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE    Stack_Size
__initial_sp


;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Heap_Size       EQU      0x00000C00

                IF       Heap_Size != 0                      ; Heap is provided
                AREA     HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE    Heap_Size
__heap_limit
                ENDIF


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA     RESET, DATA, READONLY
                EXPORT   __Vectors
                EXPORT   __Vectors_End
                EXPORT   __Vectors_Size

__Vectors       DCD      __initial_sp                        ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      MemManage_Handler                   ; -12 MPU Fault Handler
                DCD      BusFault_Handler                    ; -11 Bus Fault Handler
                DCD      UsageFault_Handler                  ; -10 Usage Fault Handler
                DCD      SecureFault_Handler                 ;  -9 Secure Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      DebugMon_Handler                    ;  -4 Debug Monitor Handler
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
;                DCD      Interrupt0_Handler                  ;   0 Interrupt 0  ;modeified sdfu
;                DCD      Interrupt1_Handler                  ;   1 Interrupt 1
;                DCD      Interrupt2_Handler                  ;   2 Interrupt 2
;                DCD      Interrupt3_Handler                  ;   3 Interrupt 3
;                DCD      Interrupt4_Handler                  ;   4 Interrupt 4
;                DCD      Interrupt5_Handler                  ;   5 Interrupt 5
;                DCD      Interrupt6_Handler                  ;   6 Interrupt 6
;                DCD      Interrupt7_Handler                  ;   7 Interrupt 7
;                DCD      Interrupt8_Handler                  ;   8 Interrupt 8
;                DCD      Interrupt9_Handler                  ;   9 Interrupt 9
				DCD     UART0_Handler             ; UART 0 RX and TX Handler
                DCD     ADC_Handler               ; ADC Handler, modified by gsl 2018-5-29
                DCD     UART1_Handler             ; UART 1 RX and TX Handler
                DCD     DMACINTERR_Handler                ;
                DCD     DMACINTTC_Handler                 ; 
                DCD     DMACINTR_Handler                  ; 
                DCD     PORT0_COMB_Handler        ; GPIO Port 0 Combined Handler
                DCD     ADC1_Handler                 ; Not Used
                DCD     TIMER0_Handler            ; TIMER 0 handler
                DCD     TIMER1_Handler            ; TIMER 1 handler
                DCD     DUALTIMER0_Handler        ; Dual timer0 handler
                DCD     DUALTIMER1_Handler        ; Dual timer1 handler
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
				DCD     UART2_Handler
					
                SPACE    (470 * 4)                           ; Interrupts 10 .. 480 are left out
__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors


                AREA     |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT   Reset_Handler             [WEAK]
                IMPORT   SystemInit
                IMPORT   __main

                LDR      R0, =__stack_limit
                MSR      MSPLIM, R0                          ; Non-secure version of MSPLIM is RAZ/WI

                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__main
                BX       R0
                ENDP

; The default macro is not used for HardFault_Handler
; because this results in a poor debug illusion.
HardFault_Handler PROC
                EXPORT   HardFault_Handler         [WEAK]
                B        .
                ENDP

; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND


; Default exception/interrupt handler

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SecureFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

;                Set_Default_Handler  Interrupt0_Handler    ;mod sdfu
;                Set_Default_Handler  Interrupt1_Handler
;                Set_Default_Handler  Interrupt2_Handler
;                Set_Default_Handler  Interrupt3_Handler
;                Set_Default_Handler  Interrupt4_Handler
;                Set_Default_Handler  Interrupt5_Handler
;                Set_Default_Handler  Interrupt6_Handler
;                Set_Default_Handler  Interrupt7_Handler
;                Set_Default_Handler  Interrupt8_Handler
;                Set_Default_Handler  Interrupt9_Handler
				Set_Default_Handler  UART0_Handler
				Set_Default_Handler  ADC_Handler
				Set_Default_Handler  UART1_Handler
				Set_Default_Handler  DMACINTERR_Handler
				Set_Default_Handler  DMACINTTC_Handler
				Set_Default_Handler  DMACINTR_Handler
				Set_Default_Handler  PORT0_COMB_Handler
				Set_Default_Handler  ADC1_Handler
				Set_Default_Handler  TIMER0_Handler
				Set_Default_Handler  TIMER1_Handler
				Set_Default_Handler  DUALTIMER0_Handler
				Set_Default_Handler  DUALTIMER1_Handler
				Set_Default_Handler  UARTOVF_Handler
				Set_Default_Handler  EXT13_IRQn
				Set_Default_Handler  EXT14_IRQn
				Set_Default_Handler  EXT15_IRQn
				Set_Default_Handler  PORT0_0_Handler
				Set_Default_Handler  PORT0_1_Handler
				Set_Default_Handler  PORT0_2_Handler
				Set_Default_Handler  PORT0_3_Handler
				Set_Default_Handler  PORT0_4_Handler
				Set_Default_Handler  PORT0_5_Handler
				Set_Default_Handler  PORT0_6_Handler
				Set_Default_Handler  PORT0_7_Handler
				Set_Default_Handler  PORT0_8_Handler
				Set_Default_Handler  PORT0_9_Handler
				Set_Default_Handler  PORT0_10_Handler
				Set_Default_Handler  PORT0_11_Handler
				Set_Default_Handler  PORT0_12_Handler
				Set_Default_Handler  PORT0_13_Handler
				Set_Default_Handler  PORT0_14_Handler
				Set_Default_Handler  PORT0_15_Handler
				Set_Default_Handler  PORT0_16_Handler
				Set_Default_Handler  PORT0_17_Handler
				Set_Default_Handler  PORT0_18_Handler
				Set_Default_Handler  PORT0_19_Handler
				Set_Default_Handler  PORT0_20_Handler
				Set_Default_Handler  PORT0_21_Handler
				Set_Default_Handler  PORT0_22_Handler
				Set_Default_Handler  PORT0_23_Handler
				Set_Default_Handler  PORT0_24_Handler
				Set_Default_Handler  PORT0_25_Handler
				Set_Default_Handler  PORT0_26_Handler
				Set_Default_Handler  PORT0_27_Handler
				Set_Default_Handler  PORT0_28_Handler
				Set_Default_Handler  PORT0_29_Handler
				Set_Default_Handler  PORT0_30_Handler
				Set_Default_Handler  PORT0_31_Handler
				Set_Default_Handler  I2C_Handler
				Set_Default_Handler  MPS2_SSP0_Handler
				Set_Default_Handler  MPS2_SSP1_Handler
				Set_Default_Handler  Spare51_Handler
				Set_Default_Handler  Spare52_Handler
				Set_Default_Handler  Spare53_Handler
				Set_Default_Handler  Spare54_Handler
				Set_Default_Handler  Spare55_Handler
				Set_Default_Handler  Spare56_Handler
				Set_Default_Handler  Spare57_Handler
				Set_Default_Handler  Spare58_Handler
				Set_Default_Handler  Spare59_Handler
				Set_Default_Handler  Spare60_Handler
				Set_Default_Handler  Spare61_Handler
				Set_Default_Handler  Spare62_Handler
				Set_Default_Handler  Spare63_Handler
				Set_Default_Handler  EXT0_Handler 
				Set_Default_Handler  EXT1_Handler 
				Set_Default_Handler  EXT2_Handler 
				Set_Default_Handler  EXT3_Handler 
				Set_Default_Handler  EXT4_Handler 
				Set_Default_Handler  EXT5_Handler 
				Set_Default_Handler  EXT6_Handler 
				Set_Default_Handler  EXT7_Handler 
				Set_Default_Handler  EXT8_Handler 
				Set_Default_Handler  EXT9_Handler 
				Set_Default_Handler  EXT10_Handler
				Set_Default_Handler  EXT11_Handler
				Set_Default_Handler  EXT12_Handler
				Set_Default_Handler  EXT13_Handler
				Set_Default_Handler  EXT14_Handler
				Set_Default_Handler  EXT15_Handler
				Set_Default_Handler  UART2_Handler
				
                ALIGN


; User setup Stack & Heap

                IF       :LNOT::DEF:__MICROLIB
                IMPORT   __use_two_region_memory
                ENDIF

                EXPORT   __stack_limit
                EXPORT   __initial_sp
                IF       Heap_Size != 0                      ; Heap is provided
                EXPORT   __heap_base
                EXPORT   __heap_limit
                ENDIF

                END
