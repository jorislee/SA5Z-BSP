#include "STAR.h"
#include "STAR_rcc.h"
#include "STAR_watchdog.h"

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
	STAR_WATCHDOG->WDOGLOAD = counter;
}

/**
  *
  * @brief: 读取WatchDog计数器当前值。
  * 
  * @retVal: wdogvalue,读取到的WatchDog计数器当前值。
  */
uint32_t WatchDog_Get_CurrentCounter(void)
{
	return STAR_WATCHDOG->WDOGVALUE; 
	
}

/**
  *
  * @brief: WatchDog配置。
  *
  * @param: rsten,是否使能WatchDog复位输出；使能时，不喂狗就会进行系统复位；
  *					可设置的值包括：WDG_RST_Output_Enable - 使能;WDG_RST_Output_Disable - 不使能。
  * @param: conuter_int_en, 是否使能WatchDog计数器和中断；需使能WatchDog计数器WatchDog才会工作。
  *					可设置的值包括：WDG_CNT_INT_Enable -使能；WDG_CNT_INT_Disable -不使能。
  * 
  * @retVal: void
  */
void WatchDog_Config(uint8_t rsten, uint8_t conuter_int_en)
{
	uint32_t tmpval;
	
	assert_param(IS_WDG_RST_Output(rsten)); 
	assert_param(IS_WDG_CNT_INT(conuter_int_en));
	
	tmpval = STAR_WATCHDOG->WDOGCONTROL;
	tmpval &= 0xfffffffc;
	tmpval |= (rsten|conuter_int_en);
	
	STAR_WATCHDOG->WDOGCONTROL = tmpval;
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
	STAR_WATCHDOG->WDOGINTCLR = Watchdog_INTCLR_Msk;
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
	STAR_WATCHDOG->WDOGLOCK = 0;
}

/**
  *
  * @brief: 解锁WatchDog，允许对WatchDog寄存器的写访问。
  * 
  * @retVal: void
  */
void WatchDog_Unlock(void)
{
	STAR_WATCHDOG->WDOGLOCK = 0x1ACCE551;
}

/**
  *
  * @brief: 读取WatchDog中断状态。
  * 
  * @retVal: 获取到的状态，SET - 发生了WatchDog中断；RESET - 未发生WatchDog中断。
  */      
ITStatus WatchDog_InterruptStatus_Get(void)
{
	if(STAR_WATCHDOG->WDOGMIS&0x01)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}
