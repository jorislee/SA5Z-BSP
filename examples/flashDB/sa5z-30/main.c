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

static const char *TAG = "xs.main";

#include "flashdb.h"

static uint32_t boot_count = 0;
static time_t boot_time[10] = {0, 1, 2, 3};

/* KVDB object */
static struct fdb_kvdb kvdb = { 0 };
/* TSDB object */
struct fdb_tsdb tsdb = { 0 };
/* counts for simulated timestamp */
static int counts = 0;
static SemaphoreHandle_t s_lock = NULL;

extern void kvdb_basic_sample(fdb_kvdb_t kvdb);
extern void kvdb_type_string_sample(fdb_kvdb_t kvdb);
extern void kvdb_type_blob_sample(fdb_kvdb_t kvdb);
extern void tsdb_sample(fdb_tsdb_t tsdb);

static void lock(fdb_db_t db)
{
    xSemaphoreTake(s_lock, portMAX_DELAY);
}

static void unlock(fdb_db_t db)
{
    xSemaphoreGive(s_lock);
}

static fdb_time_t get_time(void)
{
    /* Using the counts instead of timestamp.
     * Please change this function to return RTC time.
     */
    return ++counts;
}

#define FDB_LOG_TAG "[sample][tsdb]"

#ifdef FDB_USING_TIMESTAMP_64BIT
#define __PRITS "lld"
#else
#define __PRITS "d"
#endif

struct env_status {
    int temp;
    int humi;
};

static bool query_by_time_cb(fdb_tsl_t tsl, void *arg);

void tsdb_sample(fdb_tsdb_t tsdb)
{
    struct fdb_blob blob;

    FDB_INFO("==================== tsdb_sample ====================\n");

    { /* APPEND new TSL (time series log) */
        struct env_status status;
        time_t now_time = 6000;

        /* append new log to TSDB */
        status.temp = 36;
        status.humi = 85;
        fdb_tsl_append_with_ts(tsdb, fdb_blob_make(&blob, &status, sizeof(status)), now_time);
        FDB_INFO("append the new status.temp (%d) and status.humi (%d)\n", status.temp, status.humi);
    }

    
    { /* QUERY the TSDB by time */
        time_t from_time = 3000;
        time_t to_time = 10000;
        size_t count;
        /* query all TSL in TSDB by time */
        fdb_tsl_iter_by_time(tsdb, from_time, to_time, query_by_time_cb, tsdb);
        /* query all FDB_TSL_WRITE status TSL's count in TSDB by time */
        count = fdb_tsl_query_count(tsdb, from_time, to_time, FDB_TSL_WRITE);
        FDB_INFO("query count is: %zu\n", count);
    }
    FDB_INFO("===========================================================\n");
}

static bool query_by_time_cb(fdb_tsl_t tsl, void *arg)
{
    struct fdb_blob blob;
    struct env_status status;
    fdb_tsdb_t db = arg;

    fdb_blob_read((fdb_db_t) db, fdb_tsl_to_blob(tsl, fdb_blob_make(&blob, &status, sizeof(status))));
    FDB_INFO("[query_by_time_cb] queried a TSL: time: %" __PRITS ", temp: %d, humi: %d\n", tsl->time, status.temp, status.humi);

    return false;
}

int flashdb_demo(void)
{
    fdb_err_t result;

    if (s_lock == NULL) {
        s_lock = xSemaphoreCreateCounting(1, 1);
    }

#ifdef FDB_USING_KVDB
    { /* KVDB Sample */
        /* set the lock and unlock function if you want */
        fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_LOCK, lock);
        fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_UNLOCK, unlock);
        result = fdb_kvdb_init(&kvdb, "env", "fdb_kvdb", NULL, NULL);

        if (result != FDB_NO_ERR) {
            return -1;
        }
        /* run basic KV samples */
        kvdb_basic_sample(&kvdb);
        /* run string KV samples */
        kvdb_type_string_sample(&kvdb);
        /* run blob KV samples */
        kvdb_type_blob_sample(&kvdb);
    }
#endif /* FDB_USING_KVDB */

#ifdef FDB_USING_TSDB
    { /* TSDB Sample */
        /* set the lock and unlock function if you want */
        fdb_tsdb_control(&tsdb, FDB_TSDB_CTRL_SET_LOCK, lock);
        fdb_tsdb_control(&tsdb, FDB_TSDB_CTRL_SET_UNLOCK, unlock);
        result = fdb_tsdb_init(&tsdb, "key", "fdb_tsdb", get_time, 128, NULL);
        /* read last saved time for simulated timestamp */
        fdb_tsdb_control(&tsdb, FDB_TSDB_CTRL_GET_LAST_TIME, &counts);

        if (result != FDB_NO_ERR) {
            return -1;
        }
        tsdb_sample(&tsdb);
    }
#endif /* FDB_USING_TSDB */

    return 0;
}

#define TASK_PRORITY_FLASH   5

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

static void task_flashDB_test(void *pvParameters)
{
	xs_flash_init();
	xs_flash_dma_init();

	while(1){
		flashdb_demo();
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

	xTaskCreate(task_flashDB_test,  "flashDB_test", 2024, NULL, TASK_PRORITY_FLASH, NULL);

	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the idle task. */
	return 0;
}
