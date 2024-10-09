/*
 * Copyright (c) 2022, kaans, <https://github.com/kaans>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "log.h"
#include "xs_flash.h"

#include <string.h>
#include <fal.h>

#define LOCKER_ENABLE
#ifdef LOCKER_ENABLE

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* partition magic word */
#define FAL_PART_MAGIC_WORD         0x45503130
#define FAL_PART_MAGIC_WORD_H       0x4550L
#define FAL_PART_MAGIC_WORD_L       0x3130L

#define FLASH_ERASE_MIN_SIZE        (4096)

static SemaphoreHandle_t s_lock = NULL;

#define LOCK()                                 \
    do                                         \
    {                                          \
        xSemaphoreTake(s_lock, portMAX_DELAY); \
    } while (0)

#define UNLOCK()                \
    do                          \
    {                           \
        xSemaphoreGive(s_lock); \
    } while (0)
#else
#define LOCK()
#define UNLOCK()
#endif

static struct fal_partition g_partition_table[2] = {0};
static struct fal_flash_dev g_flash_table = {0};

int fal_init(void)
{
    g_flash_table.blk_size = 4096;

#ifdef LOCKER_ENABLE
    if (s_lock == NULL)
    {
        s_lock = xSemaphoreCreateCounting(1, 1);
    }
#endif
    memset(g_partition_table, 0, sizeof(g_partition_table));
    
    g_partition_table[0].magic_word = FAL_PART_MAGIC_WORD;
    memcpy(g_partition_table[0].name, "fdb_kvdb", sizeof("fdb_kvdb"));
    memcpy(g_partition_table[0].flash_name, "norflash0", sizeof("norflash0"));
    g_partition_table[0].offset = 0x400000;
    g_partition_table[0].len = 128 * 1024;

    g_partition_table[1].magic_word = FAL_PART_MAGIC_WORD;
    memcpy(g_partition_table[1].name, "fdb_tsdb", sizeof("fdb_tsdb"));
    memcpy(g_partition_table[1].flash_name, "norflash0", sizeof("norflash0"));
    g_partition_table[1].offset = 0x500000;
    g_partition_table[1].len = 1024 * 1024;

    return 0;
}

int fal_partition_write(const struct fal_partition *part, uint32_t addr, const uint8_t *buf, size_t size)
{
    LOCK();
    xs_flash_write(part->offset + addr, (uint8_t*)buf, size);
    UNLOCK();
    return 0;
}

int fal_partition_read(const struct fal_partition *part, uint32_t addr, uint8_t *buf, size_t size)
{
    LOCK();
    xs_flash_read(part->offset + addr, buf, size);
    UNLOCK();
    return 0;
}

int fal_partition_erase(const struct fal_partition *part, uint32_t addr, size_t size)
{
    LOCK();
    for (int i = 0; i < size; i = i + FLASH_ERASE_MIN_SIZE)
    {
        xs_flash_erase(part->offset + addr + i);
    }
    UNLOCK();
    return 0;
}

const struct fal_partition *fal_partition_find(const char *name)
{
    size_t i;
    for (i = 0; i < 2; i++)
    {
        if (!strcmp(name, g_partition_table[i].name))
        {
            return &g_partition_table[i];
        }
    }
    return NULL;
}

const struct fal_flash_dev *fal_flash_device_find(const char *name)
{
    return &g_flash_table;
}
