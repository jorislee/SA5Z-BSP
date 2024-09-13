/*
 *  Copyright 2014-2022 The GmSSL Project. All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the License); you may
 *  not use this file except in compliance with the License.
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <gmssl/rand.h>
#include <gmssl/error.h>

#include "FreeRTOS.h"
#include "task.h"

int rand_bytes(uint8_t *buf, size_t buflen)
{
	srand(xTaskGetTickCount() +1 );
	do {
		*(uint8_t *)buf = rand() & 0xff;
		buf = (uint8_t *)buf + 1;
	} while (--buflen);
	return 1;
}
