/*
 * Copyright 2003, QNX Software Systems Ltd. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems Ltd.  (QSSL) and its licensors. Any use, reproduction,
 * modification, disclosure, distribution or transfer of this software,
 * or any software which includes or is based upon any of this code, is
 * prohibited unless expressly authorized by QSSL by written agreement. For
 * more information (including whether this source code file has been
 * published) please email licensing@qnx.com.
 */

/*
 *  dcmd_sim_umass.h   Non-portable low-level devctl definitions
 *
*/

#ifndef __DCMD_SIM_UMASS_H_INCLUDED
#define __DCMD_SIM_UMASS_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#ifndef __DCMD_CAM_H_INCLUDED
 #include <sys/dcmd_cam.h>
#endif

#include <_pack64.h>

typedef struct _umass_set_priority {
	_Uint32t		prio_usb;
	_Uint32t		prio_umass;
} umass_set_priority_t;


#define DCMD_SIM_UMASS_SET_PRIORITY      __DIOT(_DCMD_CAM, _SIM_UMASS + 0, struct _umass_set_priority )


#include <_packpop.h>

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/devb/umass/public/hw/dcmd_sim_umass.h $ $Rev: 680332 $")
#endif
