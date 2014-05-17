/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef __TIMER_UTILS_H
#define __TIMER_UTILS_H

#include <time.h>
#include <sys/types.h>
#include <inttypes.h>
#include <signal.h>

typedef void (*timer_expiry_callback)(void * udata);

typedef struct timer_info
{
    clockid_t clock_id;
    struct sigevent event;
    timer_t  timerid;
    pthread_t tid;
    int32_t chid;
    int32_t coid;
    void * udata;
    timer_expiry_callback cb;
    int32_t status;
} timer_info_t;

timer_info_t * timer_create_callback( clockid_t clock_id, struct itimerspec * duration, timer_expiry_callback cb, void * udata );
int32_t timer_destroy_callback( timer_info_t * timerInfo );
#endif /* __TIMER_UTILS_H */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/timer-utils/public/include/sys/timer_utils.h $ $Rev: 732568 $")
#endif
