//------------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from Arm Technology (China) Co., Ltd.
// or its affiliates.
//
//            (C) COPYRIGHT 2018-2020 Arm Technology (China) Co., Ltd.
//                or its affiliates.
//            (C) COPYRIGHT 2017-2020 Arm Limited or its affiliates.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from Arm Technology (China) Co., Ltd. or its affiliates.
//
//  Release Information : STAR-r1p0-00eac0
//------------------------------------------------------------------------------

#ifndef __SYSTEM_EXECTBMCU_H
#define __SYSTEM_EXECTBMCU_H

extern uint32_t SystemFrequency;                   /*!< System Clock Frequency (Core Clock) */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system
 *         Initialise GPIO directions and values
 */
extern                   void SystemInit     (void);

#endif
