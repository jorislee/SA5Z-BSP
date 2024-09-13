#include "CM3DS_MPS2.h"
#include  "CM3DS_rcc.h"
#include "CM3DS_watchdog.h"


/**
  *
  * @brief: 将Watchdog初始化为默认配置。
  * 
  * @retVal: void
  */
void WatchDog_DeInit(void)
{
	RCC_APBPeriphReset_Ctr(RCC_APBPeriph_Wdog, ENABLE);
	RCC_APBPeriphReset_Ctr(RCC_APBPeriph_Wdog, DISABLE);
}


/**
  *
  * @brief: 设置WatchDog的计数器值。
  *
  * @param: counter,要设置的计数器值。
  * 
  * @retVal: void
  */
void WatchDog_Set_Counter(uint32_t counter)
{
	CM3DS_MPS2_WATCHDOG->LOAD = counter;
}


/**
  *
  * @brief: 读取WatchDog计数器当前值。
  *
  * 
  * @retVal:读取到的WatchDog计数器当前值。
  */
uint32_t WatchDog_Get_CurrentCounter(void)
{
	return CM3DS_MPS2_WATCHDOG->VALUE; 
}

/**
  *
  * @brief: WatchDog控制寄存器设置。
  *
  * @param: rsten,是否使能WatchDog复位输出；使能时，不喂狗就会进行系统复位；
  *					可设置的值包括：WDG_RST_Output_Enable - 使能;WDG_RST_Output_Disable - 不使能。
  * @param: en,是否使能WatchDog计数器和中断；需使能WatchDog计数器WatchDog才会工作；
  *					可设置的值包括：WDG_CNT_INT_Enable -使能；WDG_CNT_INT_Disable -不使能。
  * 
  * @retVal: void
  */
void WatchDog_Config(int rsten, int conuter_int_en)
{
	uint32_t tmpval;
	
	assert_param(IS_WDG_RST_Output(rsten)); 
	assert_param(IS_WDG_CNT_INT(conuter_int_en));
	
	tmpval = CM3DS_MPS2_WATCHDOG->CTRL;
	tmpval &= 0xfffffffc;
	tmpval |= (rsten|conuter_int_en);
	
	CM3DS_MPS2_WATCHDOG->CTRL = tmpval;
	
}


/**
  *
  * @brief: 清除WatchDog中断。
  * 
  * @retVal: void
  */
void WatchDog_Interrupt_Clear(void)
{
	WatchDog_Unlock();
	CM3DS_MPS2_WATCHDOG->INTCLR = Watchdog_INTCLR_Msk;
	WatchDog_Lock();
}

/**
  *
  * @brief: 锁定WatchDog，禁止对WatchDog寄存器的写访问。
  * 
  * @retVal: void
  */
void WatchDog_Lock(void)
{
	CM3DS_MPS2_WATCHDOG->LOCK = 0;
}

/**
  *
  * @brief: 解锁WatchDog，允许对WatchDog寄存器的写访问。
  * 
  * @retVal: void
  */
void WatchDog_Unlock(void)
{
	CM3DS_MPS2_WATCHDOG->LOCK = 0x1ACCE551;;
}


/**
  *
  * @brief: 获取WatchDog中断状态。
  *
  * 
  * @retVal: 获取到的状态，SET - 发生了WatchDog中断；RESET - 未发生WatchDog中断。
  */      
ITStatus WatchDog_InterruptStatus_Get(void)
{
	if(CM3DS_MPS2_WATCHDOG->MASKINTSTAT&0x01)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}
