/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems.
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

/*
 *  dcmd_sim_eide.h   Non-portable low-level devctl definitions
 *
*/

#ifndef __DCMD_SIM_EIDE_H_INCLUDED
#define __DCMD_SIM_EIDE_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#ifndef __DCMD_CAM_H_INCLUDED
 #include <sys/dcmd_cam.h>
#endif

#include <_pack64.h>

#define EIDE_APM_LEVEL				0x00     /* Set apm level */
#define EIDE_APM_CPM				0x01     /* Check Power Mode */
	#define EIDE_CPM_STANDBY		0x00     /* drive in standby (returned) */
	#define EIDE_CPM_STANDBY_MEDIA	0x01     /* drive in standby media (qnx specific) */
	#define EIDE_CPM_IDLE			0x80     /* drive idle (returned) */
	#define EIDE_CPM_ACTIVE			0xff     /* drive active (returned) */
	#define EIDE_CPM_IDLE_ACTIVE	0xff     /* drive idle or active (returned) */
#define EIDE_APM_MODE				0x02     /* Set apm mode */
	#define EIDE_MODE_ACTIVE		0x01
	#define EIDE_MODE_IDLE			0x02
	#define EIDE_MODE_STANDBY		0x03
	#define EIDE_MODE_SLEEP			0x05
	#define EIDE_MODE_STANDBY_MEDIA	0x80     /* Standby media (fail media access) */
#define EIDE_APM_STANDBY_INTERVAL	0x03     /* Set apm standby interval */
   /* level         timeout period */
   /* 0           timeout disabled */
   /* 1-240       ( value * 5 ) seconds */
   /* 241-251     ( ( value - 240 ) * 30 )  minutes */
   /* 252         21 minutes */
   /* 253         8 to 12 hours */
   /* 254         reserved */
   /* 255         21 minutes 15 seconds */
   /* Note:  times are approximate ) */

typedef struct _eide_apm {
	_Uint32t		action;
	_Uint32t		level;
} eide_apm_t;

#define EIDE_NOTIFY_ACTION_REMOVE		0x00
#define EIDE_NOTIFY_ACTION_ADD			0x01

#define EIDE_NOTIFY_TYPE_MEDIUM_ERROR	0x00
typedef struct _eide_notify {
	_Uint32t		action;
	_Uint32t		type;
	struct sigevent	sigev;
} eide_notify_t;

#define EIDE_DEVICE_STATE_DISABLE       0
#define EIDE_DEVICE_STATE_ENABLE        1
typedef struct _eide_device_state {
	_Uint32t		state;
} eide_device_state_t;

#define DCMD_SIM_EIDE_APM                __DIOTF(_DCMD_CAM, _SIM_EIDE + 1, struct _eide_apm)
#define DCMD_SIM_EIDE_NOTIFY             __DIOT(_DCMD_CAM, _SIM_EIDE + 2, struct _eide_notify)
#define DCMD_SIM_EIDE_DEVICE_STATE       __DIOT(_DCMD_CAM, _SIM_EIDE + 3, struct _eide_device_state)

#include <_packpop.h>

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/devb/eide/public/hw/dcmd_sim_eide.h $ $Rev: 736751 $")
#endif
