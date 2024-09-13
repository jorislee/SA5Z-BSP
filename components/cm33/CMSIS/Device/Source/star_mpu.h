//crate at 22.3.1 by sdfu
//for arm core STAR
 #include "exectb_mcu.h"
#include "EXECTB_tests.h"
#include <stdio.h>
#include <inttypes.h>
#ifndef STAR_MPU_H
#define STAR_MPU_H
#define MPU_CTRL_ENABLE_SHITF       0UL
#define MPU_CTRL_ENABLE_MASK        (1UL << MPU_CTRL_ENABLE_SHITF)

#define MPU_CTRL_HFNMIENA_SHIFT     1UL
#define MPU_CTRL_HFNMIENA_MASK      (1UL << MPU_CTRL_HFNMIENA_SHIFT)

#define MPU_CTRL_PRIVDEFENA_SHIFT   2UL
#define MPU_CTRL_PRIVDEFENA_MASK    (1UL << MPU_CTRL_PRIVDEFENA_SHIFT)

#define MPU_RNR_REGION_SHIFT        0UL
#define MPU_RNR_REGION_MASK         (0xFFUL << MPU_RNR_REGION_SHIFT)

#define MPU_CTRL_RBAR_BASE_SHIFT    0x5UL
#define MPU_CTRL_RBAR_BASE_MASK     0xFFFFFFE0UL

#define MPU_CTRL_RBAR_SH_SHIFT      3UL
#define MPU_CTRL_RBAR_SH_MASK       (0x3UL << MPU_CTRL_RBAR_SH_SHIFT)

#define MPU_CTRL_RBAR_AP_SHIFT      1UL
#define MPU_CTRL_RBAR_AP_MASK       (0x3UL << MPU_CTRL_RBAR_AP_SHIFT)

#define MPU_CTRL_RBAR_XN_SHIFT      0UL
#define MPU_CTRL_RBAR_XN_MASK       (1UL << MPU_CTRL_RBAR_XN_SHIFT)

#define MPU_CTRL_RLAR_LIMIT_SHIFT   5UL
#define MPU_CTRL_RLAR_LIMIT_MASK    0xFFFFFFE0UL

#define MPU_CTRL_RLAR_ATTRIDX_SHIFT 1UL
#define MPU_CTRL_RLAR_ATTRIDX_MASK  (0x7UL << MPU_CTRL_RLAR_ATTRIDX_SHIFT)

#define MPU_CTRL_RLAR_EN_SHIFT      0UL
#define MPU_CTRL_RLAR_EN_MASK       (1UL << MPU_CTRL_RLAR_EN_SHIFT)
#define REGION_NON_SHAREABLE        0
#define REGION_UNPREDICTABLE        1
#define REGION_OUTER_SHAREABLE      2
#define REGION_INNER_SHAREABLE      3

#define REGION_RW_PRIV_ONLY         0
#define REGION_RW_ANY               1
#define REGION_RO_PRIV_ONLY         2
#define REGION_RO_ANY               3

#define REGION_X                    0
#define REGION_XN                   1

#define REGION_DISABLE              0
#define REGION_EN                   1

void set_region_base(uint32_t base,uint8_t share_att,uint8_t ap_att, uint8_t xn);
void set_region_limit(uint32_t limit, uint32_t att_num ,uint32_t en);
void set_mair(uint8_t idx,uint8_t att);
void mpu_enable();
#endif
