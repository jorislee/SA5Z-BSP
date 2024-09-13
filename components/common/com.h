#ifndef __COM_H__
#define __COM_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#include "log.h"
#include "err.h"

#include "bit.h"
#include "byte.h"
#include "crc32.h"
#include "CM3DS_MPS2.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions for error constants. */
#define XS_OK                      0        /**< ks_err_t value indicating success (no error) */
#define XS_FAIL                    -1       /**< Generic ks_err_t code indicating failure */
#define XS_TRUE                    1       
#define XS_FALSE                   0 

#define WORD_MASK 0xFFFFFFFC
#define WORD_ROUNDUP(x) (((x) + 3) & WORD_MASK)

#define SM4_MASK 0xFFFFFFF0
#define SM4_ROUNDUP(x) (((x) + 15) & SM4_MASK)

#ifndef ARMCM3

// 将 16 位数从主机字节序转换为网络字节序（大端）
static inline uint32_t htons(uint32_t value) {
    uint32_t result;
    __asm {
        REV16 result, value
    }
    return result;
}

// 将 32 位数从网络字节序转换为主机字节序（小端）
static inline uint32_t htonl(uint32_t value) {
    uint32_t result;
    __asm {
        REV result, value
    }
    return result;
}

// 将 16 位数从网络字节序转换为主机字节序（小端）
#define ntohs htons

// 将 32 位数从网络字节序转换为主机字节序（小端）
#define ntohl htonl

#else
// 将 16 位数从主机字节序转换为网络字节序（大端）
static inline uint16_t htons(uint16_t hostshort) {
    return (hostshort << 8) | (hostshort >> 8);
}

// 将 32 位数从主机字节序转换为网络字节序（大端）
static inline uint32_t htonl(uint32_t hostlong) {
    return ((hostlong & 0xFF000000) >> 24) |
           ((hostlong & 0x00FF0000) >> 8) |
           ((hostlong & 0x0000FF00) << 8) |
           ((hostlong & 0x000000FF) << 24);
}

// 将 16 位数从网络字节序转换为主机字节序（小端）
#define ntohs htons

// 将 32 位数从网络字节序转换为主机字节序（小端）
#define ntohl htonl
#endif

static inline int is_little_endian() {
    uint32_t num = 0x01020304;
    uint8_t *ptr = (uint8_t *)&num;
    return (*ptr == 0x04);
}

#ifdef __cplusplus
}
#endif

#endif /* __COM_H__ */
