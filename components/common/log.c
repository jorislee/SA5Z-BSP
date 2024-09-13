
/*
 * SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "compiler.h"
#include "log.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Maximum time to wait for the mutex in a logging statement.
//
// We don't expect this to happen in most cases, as contention is low. The most likely case is if a
// log function is called from an ISR (technically caller should use the ISR-friendly logging macros but
// possible they use the normal one instead and disable the log type by tag).
#define MAX_MUTEX_WAIT_MS 10
#define MAX_MUTEX_WAIT_TICKS ((MAX_MUTEX_WAIT_MS + portTICK_PERIOD_MS - 1) / portTICK_PERIOD_MS)

static SemaphoreHandle_t s_log_mutex = NULL;
#if configSUPPORT_STATIC_ALLOCATION == 1
static StaticSemaphore_t s_xMutexBuffer;
#endif

static vprintf_like_t s_log_print_func = &vprintf;

void log_impl_lock(void)
{
    
    if (unlikely(!s_log_mutex)) {
        #if configSUPPORT_STATIC_ALLOCATION == 1
        s_log_mutex = xSemaphoreCreateMutexStatic(&s_xMutexBuffer);
        #else
        s_log_mutex = xSemaphoreCreateMutex();
        #endif
    }
    if (unlikely(xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)) {
        return;
    }
    xSemaphoreTake(s_log_mutex, portMAX_DELAY);
}

void log_impl_unlock(void)
{
    
    if (unlikely(xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)) {
        return;
    }
    xSemaphoreGive(s_log_mutex);
}

vprintf_like_t log_set_vprintf(vprintf_like_t func)
{
    log_impl_lock();
    vprintf_like_t orig_func = s_log_print_func;
    s_log_print_func = func;
    log_impl_unlock();
    return orig_func;
}

void log_writev(log_level_t level,
                    const char *tag,
                    const char *format,
                    va_list args)
{
    log_impl_lock();
   (*s_log_print_func)(format, args);
    log_impl_unlock();
}

void log_write(log_level_t level,
                   const char *tag,
                   const char *format, ...)
{
    va_list list;
    va_start(list, format);
    log_writev(level, tag, format, list);
    va_end(list);
}

uint32_t log_timestamp(void)
{
    //TickType_t tick_count = xTaskGetTickCountFromISR();
    TickType_t tick_count = xTaskGetTickCount();
    return tick_count * (1000 / configTICK_RATE_HZ);
}
