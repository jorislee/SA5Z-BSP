#ifndef __CM3DS_WATCHDOG_H
#define __CM3DS_WATCHDOG_H

#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "CM3DS_MPS2.h"
	 
	  
#define IS_WatchDog_ALL_PERIPH(PERIPH)  ((PERIPH) == CM3DS_MPS2_WATCHDOG))

	 
#define WDG_RST_Output_Enable							2
#define WDG_RST_Output_Disable							0
#define IS_WDG_RST_Output(WDG_RST_OUTPUT)						(((WDG_RST_OUTPUT) == WDG_RST_Output_Enable ) || \
															     ((WDG_RST_OUTPUT) == WDG_RST_Output_Disable ))

#define WDG_CNT_INT_Enable						1
#define WDG_CNT_INT_Disable						0
#define IS_WDG_CNT_INT(INTEN) 				 (((INTEN) ==  WDG_CNT_INT_Enable ) || \
															    ((INTEN) ==  WDG_CNT_INT_Disable ))

void WatchDog_DeInit(void);
void WatchDog_Set_Counter(uint32_t counter);
uint32_t WatchDog_Get_CurrentCounter(void);
void WatchDog_Config(int rsten, int conuter_int_en);
void WatchDog_Interrupt_Clear(void);
void WatchDog_Lock(void);
void WatchDog_Unlock(void);
ITStatus WatchDog_InterruptStatus_Get(void);


#ifdef __cplusplus
}
#endif

#endif

