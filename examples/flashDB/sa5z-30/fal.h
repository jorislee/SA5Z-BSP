/*
 * Copyright (c) 2022, kaans, <https://github.com/kaans>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief configuration file
 */

#ifndef _FDB_PARTITION_H_
#define _FDB_PARTITION_H_

/* FAL flash and partition device name max length */
#ifndef FAL_DEV_NAME_MAX
#define FAL_DEV_NAME_MAX 24
#endif

#ifndef FAL_DEV_NAME_MAX
#define FAL_DEV_NAME_MAX 24
#endif

struct fal_flash_dev
{
    char name[FAL_DEV_NAME_MAX];

    /* flash device start address and len  */
    uint32_t addr;
    size_t len;
    /* the block size in the flash for erase minimum granularity */
    size_t blk_size;

    struct
    {
        int (*init)(void);
        int (*read)(long offset, uint8_t *buf, size_t size);
        int (*write)(long offset, const uint8_t *buf, size_t size);
        int (*erase)(long offset, size_t size);
    } ops;

    /* write minimum granularity, unit: bit. 
       1(nor flash)/ 8(stm32f2/f4)/ 32(stm32f1)/ 64(stm32l4)
       0 will not take effect. */
    size_t write_gran;
};
typedef struct fal_flash_dev *fal_flash_dev_t;

/**
 * FAL partition
 */
struct fal_partition
{
    uint32_t magic_word;

    /* partition name */
    char name[FAL_DEV_NAME_MAX];
    /* flash device name for partition */
    char flash_name[FAL_DEV_NAME_MAX];

    /* partition offset address on flash device */
    long offset;
    size_t len;

    uint32_t reserved;
};
typedef struct fal_partition *fal_partition_t;

int fal_init(void);

int fal_partition_write(const struct fal_partition *part, uint32_t addr, const uint8_t *buf, size_t size);

int fal_partition_read(const struct fal_partition *part, uint32_t addr, uint8_t *buf, size_t size);

int fal_partition_erase(const struct fal_partition *part, uint32_t addr, size_t size);

const struct fal_partition *fal_partition_find(const char *name);

#endif /* _FDB_PARTITION_H_ */
