/*
 * SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#ifndef __LOG_BUFFER_H__
#define __LOG_BUFFER_H__

#include "log.h"

void log_buffer_hex_internal(const char *tag, const void *buffer, uint16_t buff_len, log_level_t log_level);

void log_buffer_char_internal(const char *tag, const void *buffer, uint16_t buff_len, log_level_t log_level);

void log_buffer_hexdump_internal(const char *tag, const void *buffer, uint16_t buff_len, log_level_t log_level);

#endif
