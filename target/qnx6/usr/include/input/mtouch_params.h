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
 * @file mtouch_params.h
 *
 * @brief Enumerations and Structures for mtouch parameters
 *
 *        The mtouch_params.h header file provides type definitions related to
 *        mtouch parameters.
 *
 */

#include <inttypes.h>
#include <sys/types.h>
#include "input/calib.h"

#ifndef MTOUCH_PARAMS_H_
#define MTOUCH_PARAMS_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

 /**
 * Maximum number of filters used by Screen.
 *
 * This is somewhat arbitrary and is defined only so Screen knows how big to
 * make its filters parameter array. There is no libinputevents limit to how
 * many filters can be chained.
 */
#define MTOUCH_MAX_FILTERS 8

/* Internal use only. */
#define MTOUCH_PARAMS_VENDOR_SZ      64
#define MTOUCH_PARAMS_PRODUCT_ID_SZ  64
#define MTOUCH_PARAMS_SENSOR_ID_SZ   64

/**
* @brief Touch driver parameters
*/
typedef struct mtouch_driver_params {
	/**
	* The capabilities supported by the driver. Valid capabilities are:
	* - @c MTOUCH_CAPABILITIES_CONTACT_ID
	* - @c MTOUCH_CAPABILITIES_COORDS
	* - @c MTOUCH_CAPABILITIES_CONTACT_COUNT
	* - @c MTOUCH_CAPABILITIES_WIDTH
	* - @c MTOUCH_CAPABILITIES_HEIGHT
	* - @c MTOUCH_CAPABILITIES_ORIENTATION
	* - @c MTOUCH_CAPABILITIES_PRESSURE
	* - @c MTOUCH_CAPABILITIES_RATE_SET
	* - @c MTOUCH_CAPABILITIES_SEQ_ID
	* - @c MTOUCH_CAPABILITIES_CONTACT_TYPE
	* - @c MTOUCH_CAPABILITIES_SELECT
	*/
	_Uint32t capabilities;

	/**
	* Device flags. Valid flags are:
	* - @c MTOUCH_FLAGS_INCONSISTENT_DIGIT_ORDER
	* - @c MTOUCH_FLAGS_INCONSISTENT_CONTACT_IDS
	*/
	_Uint32t flags;

	/**
	* The maximum number of touchpoints supported by the driver.
	*/
	_Uint8t max_touchpoints;

	/**
	* The width, in touch units, of the touch area.
	*/
	_Uint32t width;

	/**
	* The height, in touch units,  of the touch area.
	*/
	_Uint32t height;

	/**
	* Internal use only.
	*/
	 char    vendor[MTOUCH_PARAMS_VENDOR_SZ];

	/**
	* Internal use only.
	*/
	 char    product_id[MTOUCH_PARAMS_PRODUCT_ID_SZ];

	/**
	* Internal use only.
	*/
	 char    sensor_id[MTOUCH_PARAMS_SENSOR_ID_SZ];

	/**
	* Internal use only.
	*/
	_Uint32t sensor_sz_x;

	/**
	* Internal use only.
	*/
	_Uint32t sensor_sz_y;

	/**
	* Internal use only.
	*/
	_Uint32t max_refresh;
} mtouch_driver_params_t;

/**
* @brief Types of filters
*/
typedef enum {
	/**
	* No filter.
	*/
	MTOUCH_FILTER_NONE = 0,

	/**
	* Ballistic filter. Minimizes the noise normally seen on successive touch
	* events that follow a low-speed ballistic trajectory. The lower the speed
	* of the ballistic movement, the more gain reduction is applied to the
	* speed of the movement. By doing so, the result is a solid touch with no
	* noise.
	*/
	MTOUCH_FILTER_BALLISTIC,

	/**
	* Edge-swipe filter. Detects the passing of a finger over the edge of the
	* touch surface. This lets you get swipe gestures starting from outside the
	* screen.
	*/
	MTOUCH_FILTER_EDGE_SWIPE,

	/**
	* Kalman filter. Minimizes the tracking noise of a moving finger on a given
	* touch surface by use of the Kalman filter algorithm.
	*/
	MTOUCH_FILTER_KALMAN,

	/**
	* Bezel-touch filter.
	*/
	MTOUCH_FILTER_BEZEL_TOUCH,
#ifdef HAVE_MTOUCH_FILTER_DOA
	/**
	* DOA touch filter.
	*/
	MTOUCH_FILTER_DOA,
#endif
} mtouch_filter_e;

/**
* @brief Touch filter configuration
*/
typedef struct mtouch_filter_config {
	/**
	* Filter type
	*/
	mtouch_filter_e type;

	/**
	* Filter specific options. The available filter options depend on the filter
	* type.
	*/
	char * options;
} mtouch_filter_config_t;

/**
* @brief Touch client parameters
*/
typedef struct mtouch_client_params {
	/**
	* The sampling period (in microseconds) of the touch driver. You will not
	* get two touch samples within a time less than that configured here. The
	* effectiveness of this configuration is driver-dependent.
	*/
	_Uint32t min_event_interval;

	/**
	* The parameters for scaling touch coordinates.
	*/
	mtouch_scaling_params_t scaling;
} mtouch_client_params_t;

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* MTOUCH_PARAMS_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/inputevents/public/input/mtouch_params.h $ $Rev: 731258 $")
#endif
