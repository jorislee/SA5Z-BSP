/*
 * SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "err.h"

#define ERR_TBL_IT(err)    {err, #err}

typedef struct {
    xs_err_t code;
    const char *msg;
} xs_err_msg_t;

static const xs_err_msg_t xs_err_msg_table[] = {
    // components/mcommon/include/mdf_err.h
#   ifdef      XS_FAIL
    ERR_TBL_IT(XS_FAIL),                             /**<      -1 Generic xs_err_t code indicating failure */
#   endif
#   ifdef      XS_OK
    ERR_TBL_IT(XS_OK),                               /**<       0 xs_err_t value indicating success (no error) */
#   endif
#   ifdef      XS_ERR_NO_MEM
    ERR_TBL_IT(XS_ERR_NO_MEM),                       /**< 257    0x101 Out of memory */
#   endif
#   ifdef      XS_ERR_INVALID_ARG
    ERR_TBL_IT(XS_ERR_INVALID_ARG),                  /**< 258    0x102 Invalid argument */
#   endif
#   ifdef      XS_ERR_INVALID_STATE
    ERR_TBL_IT(XS_ERR_INVALID_STATE),                /**< 259    0x103 Invalid state */
#   endif
#   ifdef      XS_ERR_INVALID_SIZE
    ERR_TBL_IT(XS_ERR_INVALID_SIZE),                 /**< 260    0x104 Invalid size */
#   endif
#   ifdef      XS_ERR_NOT_FOUND
    ERR_TBL_IT(XS_ERR_NOT_FOUND),                    /**< 261    0x105 Requested resource not found */
#   endif
#   ifdef      XS_ERR_NOT_SUPPORTED
    ERR_TBL_IT(XS_ERR_NOT_SUPPORTED),                /**< 262    0x106 Operation or feature not supported */
#   endif
#   ifdef      XS_ERR_TIMEOUT
    ERR_TBL_IT(XS_ERR_TIMEOUT),                      /**< 263    0x107 Operation timed out */
#   endif
#   ifdef      XS_ERR_INVALID_RESPONSE
    ERR_TBL_IT(XS_ERR_INVALID_RESPONSE),             /**< 264    0x108 Received response was invalid */
#   endif
#   ifdef      XS_ERR_INVALID_CRC
    ERR_TBL_IT(XS_ERR_INVALID_CRC),                  /**< 265    0x109 CRC or checksum was invalid */
#   endif
#   ifdef      XS_ERR_INVALID_VERSION
    ERR_TBL_IT(XS_ERR_INVALID_VERSION),              /**< 266    0x10a Version was invalid */
#   endif
#   ifdef      XS_ERR_NOT_INIT
    ERR_TBL_IT(XS_ERR_NOT_INIT),                     /**< 267    0x10b */
#   endif
#   ifdef      XS_ERR_BUF
    ERR_TBL_IT(XS_ERR_BUF),                          /**< 268    0x10d The buffer is too small */
#   endif
};

const char *xs_err_to_name(xs_err_t code)
{
    int i;
    for (i = 0; i < sizeof(xs_err_msg_table) / sizeof(xs_err_msg_table[0]); ++i) {
        if (xs_err_msg_table[i].code == code) {
            return xs_err_msg_table[i].msg;
        }
    }
    return NULL;
}
