/*
 * SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>

#include "log_color.h"

//#include "log_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Log level
 */
typedef enum {
    XS_LOG_NONE    = 0,    /*!< No log output */
    XS_LOG_ERROR   = 1,    /*!< Critical errors, software module can not recover on its own */
    XS_LOG_WARN    = 2,    /*!< Error conditions from which recovery measures have been taken */
    XS_LOG_INFO    = 3,    /*!< Information messages which describe normal flow of events */
    XS_LOG_DEBUG   = 4,    /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    XS_LOG_VERBOSE = 5,    /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
    XS_LOG_MAX     = 6,    /*!< Number of levels supported */
} log_level_t;

typedef int (*vprintf_like_t)(const char *, va_list);

/**
 * @brief Set function used to output log entries
 *
 * By default, log output goes to UART0. This function can be used to redirect log
 * output to some other destination, such as file or network. Returns the original
 * log handler, which may be necessary to return output to the previous destination.
 *
 * @note Please note that function callback here must be re-entrant as it can be
 * invoked in parallel from multiple thread context.
 *
 * @param func new Function used for output. Must have same signature as vprintf.
 *
 * @return func old Function used for output.
 */
vprintf_like_t log_set_vprintf(vprintf_like_t func);

/**
 * @brief Write message into the log
 *
 * This function is not intended to be used directly. Instead, use one of
 * XS_LOGE, XS_LOGW, XS_LOGI, XS_LOGD, XS_LOGV macros.
 *
 * This function or these macros should not be used from an interrupt.
 */
void log_write(log_level_t level, const char* tag, const char* format, ...) __attribute__((format(printf, 3, 4)));

/**
 * @brief Write message into the log, va_list variant
 * @see log_write()
 *
 * This function is provided to ease integration toward other logging framework,
 * so that log can be used as a log sink.
 */
void log_writev(log_level_t level, const char* tag, const char* format, va_list args);

uint32_t log_timestamp(void);

#include "log_buffers.h"

#ifndef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL  XS_LOG_DEBUG
#endif

/** @endcond */

/**
 * @brief Log a buffer of hex bytes at specified level, separated into 16 bytes each line.
 *
 * @param  tag      description tag
 * @param  buffer   Pointer to the buffer array
 * @param  buff_len length of buffer in bytes
 * @param  level    level of the log
 *
 */
#define XS_LOG_BUFFER_HEX_LEVEL(tag, buffer, buff_len, level ) \
    do {\
        if ( LOG_LOCAL_LEVEL >= (level) ) { \
            log_buffer_hex_internal(tag, buffer, buff_len, level ); \
        } \
    } while(0)

/**
 * @brief Log a buffer of characters at specified level, separated into 16 bytes each line. Buffer should contain only printable characters.
 *
 * @param  tag      description tag
 * @param  buffer   Pointer to the buffer array
 * @param  buff_len length of buffer in bytes
 * @param  level    level of the log
 *
 */
#define XS_LOG_BUFFER_CHAR_LEVEL(tag, buffer, buff_len, level ) \
    do {\
        if ( LOG_LOCAL_LEVEL >= (level) ) { \
            log_buffer_char_internal(tag, buffer, buff_len, level ); \
        } \
    } while(0)

/**
 * @brief Dump a buffer to the log at specified level.
 * 
 * The dump log shows just like the one below:
 * 
 *      W (195) log_example: 0x3ffb4280   45 53 50 33 32 20 69 73  20 67 72 65 61 74 2c 20  |ESP32 is great, |
 *      W (195) log_example: 0x3ffb4290   77 6f 72 6b 69 6e 67 20  61 6c 6f 6e 67 20 77 69  |working along wi|
 *      W (205) log_example: 0x3ffb42a0   74 68 20 74 68 65 20 49  44 46 2e 00              |th the IDF..|
 *      
 * It is highly recommend to use terminals with over 102 text width.
 * 
 * @param tag description tag
 * @param buffer Pointer to the buffer array
 * @param buff_len length of buffer in bytes
 * @param level level of the log
 */
#define XS_LOG_BUFFER_HEXDUMP_LEVEL(tag, buffer, buff_len, level ) \
    do { \
        if ( LOG_LOCAL_LEVEL >= (level) ) { \
            log_buffer_hexdump_internal(tag, buffer, buff_len, level); \
        } \
    } while(0)

/**
 * @brief Dump a buffer to the log at Info level.
 * 
 * The dump log shows just like the one below:
 * 
 *      W (195) log_example: 0x3ffb4280   45 53 50 33 32 20 69 73  20 67 72 65 61 74 2c 20  |ESP32 is great, |
 *      W (195) log_example: 0x3ffb4290   77 6f 72 6b 69 6e 67 20  61 6c 6f 6e 67 20 77 69  |working along wi|
 *      W (205) log_example: 0x3ffb42a0   74 68 20 74 68 65 20 49  44 46 2e 00              |th the IDF..|
 *      
 * It is highly recommend to use terminals with over 102 text width.
 * 
 * @param tag description tag
 * @param buffer Pointer to the buffer array
 * @param buff_len length of buffer in bytes
 */
#define XS_LOG_BUFFER_HEXDUMP(tag, buffer, buff_len ) \
    do { \
        if ( LOG_LOCAL_LEVEL >= XS_LOG_INFO ) { \
            log_buffer_hexdump_internal(tag, buffer, buff_len, XS_LOG_INFO); \
        } \
    } while(0)

/**
 * @brief Log a buffer of hex bytes at Info level
 *
 * @param  tag      description tag
 * @param  buffer   Pointer to the buffer array
 * @param  buff_len length of buffer in bytes
 *
 * @see ``KS_log_buffer_hex_level``
 *
 */
#define XS_LOG_BUFFER_HEX(tag, buffer, buff_len) \
    do { \
        if (LOG_LOCAL_LEVEL >= XS_LOG_INFO) { \
            XS_LOG_BUFFER_HEX_LEVEL( tag, buffer, buff_len, XS_LOG_INFO ); \
        }\
    } while(0)

/**
 * @brief Log a buffer of characters at Info level. Buffer should contain only printable characters.
 *
 * @param  tag      description tag
 * @param  buffer   Pointer to the buffer array
 * @param  buff_len length of buffer in bytes
 *
 * @see ``KS_log_buffer_char_level``
 *
 */
#define XS_LOG_BUFFER_CHAR(tag, buffer, buff_len) \
    do { \
        if (LOG_LOCAL_LEVEL >= XS_LOG_INFO) { \
            XS_LOG_BUFFER_CHAR_LEVEL(tag, buffer, buff_len, XS_LOG_INFO ); \
        }\
    } while(0)

//#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%" PRIu32 ") %s: " format LOG_RESET_COLOR "\n"
#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%" PRIu32 ") %s: " format LOG_RESET_COLOR "\r\n"

#define XS_LOGE( tag, format, ... ) XS_LOG_LEVEL_LOCAL(XS_LOG_ERROR,   tag, format, ##__VA_ARGS__)
#define XS_LOGW( tag, format, ... ) XS_LOG_LEVEL_LOCAL(XS_LOG_WARN,    tag, format, ##__VA_ARGS__)
#define XS_LOGI( tag, format, ... ) XS_LOG_LEVEL_LOCAL(XS_LOG_INFO,    tag, format, ##__VA_ARGS__)
#define XS_LOGD( tag, format, ... ) XS_LOG_LEVEL_LOCAL(XS_LOG_DEBUG,   tag, format, ##__VA_ARGS__)
#define XS_LOGV( tag, format, ... ) XS_LOG_LEVEL_LOCAL(XS_LOG_VERBOSE, tag, format, ##__VA_ARGS__)

#define XS_LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==XS_LOG_ERROR )          { log_write(XS_LOG_ERROR,      tag, LOG_FORMAT(E, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==XS_LOG_WARN )      { log_write(XS_LOG_WARN,       tag, LOG_FORMAT(W, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==XS_LOG_DEBUG )     { log_write(XS_LOG_DEBUG,      tag, LOG_FORMAT(D, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==XS_LOG_VERBOSE )   { log_write(XS_LOG_VERBOSE,    tag, LOG_FORMAT(V, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else                               { log_write(XS_LOG_INFO,       tag, LOG_FORMAT(I, format), log_timestamp(), tag, ##__VA_ARGS__); } \
    } while(0)

#define XS_LOG_LEVEL_LOCAL(level, tag, format, ...) do {               \
        if ( LOG_LOCAL_LEVEL >= level ) XS_LOG_LEVEL(level, tag, format, ##__VA_ARGS__); \
    } while(0)

#ifdef __cplusplus
}
#endif
