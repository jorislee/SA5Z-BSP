#include <stdio.h> 
#include <string.h> 
#include <time.h>

#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"
#include "CM3DS_uart.h"
#include "CM3DS_spi.h"
#include "CM3_retarget.h"
#include "CM3DS_rcc.h"
#include "CM3DS_gpio.h"
#include "CM3DS_MPS2.h"
#include "CM3DS_i2c.h"

#include "com.h"

#include "xs_uart.h"
#include "xs_flash.h"


#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

static const char * TAG = "xs.main";

#define TASK_PRORITY_UART   5

static int uart_fifo_printf(const char *format, va_list args)
{
	#define BUFFER_SIZE 256
	static char uart_fifo_buffer[BUFFER_SIZE];
    int send_len = vsnprintf(uart_fifo_buffer, BUFFER_SIZE, format, args);
	if(send_len > 0){
		xs_uart_fifo_send(UART_NUM0, (uint8_t *)uart_fifo_buffer, send_len, pdMS_TO_TICKS(10));
	}
    return send_len;
}

#if configSUPPORT_DYNAMIC_ALLOCATION == 1
/* Define the start address and size of the three RAM regions. */
#define HEAP_START_ADDRESS ( ( uint8_t * ) 0x20000000 )
#define HEAP_SIZE ( 32 * 1024 )

const HeapRegion_t xHeapRegions[] =
{
    { HEAP_START_ADDRESS, HEAP_SIZE },
    { NULL, 0 } /* Marks the end of the array. */
};
#endif

static void task_hello_world(void *pvParameters)
{
	while(1){
		XS_LOGI(TAG, "hello world");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

int main(void)
{
	#if configSUPPORT_DYNAMIC_ALLOCATION == 1
	vPortDefineHeapRegions( xHeapRegions );
	#endif

	GPIO_DeInit(CM3DS_MPS2_GPIO0);
	xs_uart_fifo_init(UART_NUM0, UART_CTRL_TX_EN|UART_CTRL_RX_EN, 115200);
    
	log_set_vprintf(uart_fifo_printf);

	xTaskCreate(task_hello_world,  "hello_world", 512, NULL, TASK_PRORITY_UART, NULL);

	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the idle task. */
	return 0;
}
