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

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "com.h"

#include "xs_uart.h"
#include "xs_flash.h"

#include "sm234.h"

static const char * TAG = "xs.main";

#define TASK_PRORITY_SM4   5

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

static void task_sm4_test(void *pvParameters)
{
	uint8_t sm4_cbc_data[32] = {0x80, 0x7A, 0x2A, 0xEC, 0x9E, 0x6D, 0x61, 0xDF, 
							   0x91, 0x07, 0x5B, 0x2C, 0xD0, 0xA8, 0x68, 0xB5, 
							   0xCD, 0xD9, 0x1F, 0xA7, 0xE6, 0x97, 0x8A, 0x4A, 
							   0x19, 0xB6, 0xD5, 0x20, 0x6E, 0xCD, 0x25, 0x57};
	uint8_t sm4_cbc_key[16] = {0x4C, 0x35, 0xE3, 0x76, 0x9A, 0x4C, 0x2E, 0x67, 
							   0x22, 0xB7, 0xC5, 0xC5, 0x4B, 0x45, 0x78, 0x25};
	uint8_t sm4_cbc_iv[16] = {0x2C, 0xB7, 0xB3, 0x00, 0x60, 0xB1, 0x3E, 0xB0, 
							  0x80, 0x79, 0xB1, 0x5D, 0x9D, 0x64, 0xCE, 0xDC};
	uint8_t sm4_cbc_en[32] = {0x66, 0x65, 0xE8, 0xD2, 0x72, 0x2A, 0x19, 0x02, 
							  0xCB, 0xA9, 0xFF, 0x5F, 0x45, 0xE9, 0xC7, 0x33, 
							  0xFF, 0xBA, 0x90, 0x36, 0x1E, 0x80, 0xA2, 0xEB, 
							  0xD2, 0x7D, 0xC8, 0x20, 0x12, 0x9D, 0x79, 0x9D};
	uint8_t sm4_cbc_buf[32] = {0};
	while(1){
		sm4_cbc_crypt(SM4_ENCRYPT, sm4_cbc_key, sm4_cbc_iv, sm4_cbc_data, sm4_cbc_buf, 32);
		if(memcmp(sm4_cbc_buf, sm4_cbc_en, 32) == 0){
			XS_LOGI(TAG, "sm4 cbc encrypt success");
		}else{
			XS_LOGE(TAG, "sm4 cbc encrypt failed");
		}
		vTaskDelay(pdMS_TO_TICKS(100000));
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

	xTaskCreate(task_sm4_test,  "sm4_test", 512, NULL, TASK_PRORITY_SM4, NULL);

	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the idle task. */
	return 0;
}
