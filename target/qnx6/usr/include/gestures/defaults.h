/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems.
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

/**
 * @file defaults.h
 *
 * @brief Global settings for gesture timings
 *
 * The defaults.h header file provides global settings
 * for hold delay, move tolerance, touch interval and tap delay.
 *
 */  
#include <sys/cdefs.h>
 
#ifndef DEFAULTS_H_
#define DEFAULTS_H_

__BEGIN_DECLS

/** 
 * The amount of time the finger must remain touching the screen to qualify as
 * a hold. 
 *
 */
#define GESTURE_MIN_HOLD_DELAY_MS 400 


/**
 * The maximum number of pixels in any direction a touch gesture can move before
 * failing.
 * 
 */
#define GESTURE_MAX_MOVE_TOLERANCE_PIX 16 

/**
 * The maximum time interval between two fingers touching the screen for the
 * gesture to be considered a two-finger touch, as opposed to two single-finger touches.
 *
 */
#define GESTURE_TWO_FINGER_INTERVAL_MS 100

/**
 * The maximum delay between taps for a double-tap or triple-tap gesture. A longer
 * delay results in multiple single taps.
 *
 */
#define GESTURE_MAX_TAP_DELAY_MS 300

__END_DECLS

#endif /* DEFAULTS_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/gestures/public/gestures/defaults.h $ $Rev: 680336 $")
#endif
