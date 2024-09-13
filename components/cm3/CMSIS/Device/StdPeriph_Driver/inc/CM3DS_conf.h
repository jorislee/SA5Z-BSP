
#ifndef  __CM3DS_CONF_H
#define  __CM3DS_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
//#include "CM3DS_gpio.h"
//#include "CM3DS_uart.h"
//#include "CM3DS_i2c.h"
//#include "CM3DS_adc.h"
//#include "CM3DS_spi.h"
//#include "CM3DS_timer.h"
//#include "CM3DS_dualtimer.h"

/* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_CONF_H */
