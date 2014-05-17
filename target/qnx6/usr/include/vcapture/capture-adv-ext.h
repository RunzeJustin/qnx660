/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef INCL__VCAPTURE_ADV_EXT__H
#define INCL__VCAPTURE_ADV_EXT__H

#include <vcapture/capture.h>

#define CAPTURE_PROPERTY_ADV_SRC_TYPE		CAPTURE_PROPERTY( 'A', 'S', 'T', 'P' )
		/* R/W	uint32_t	the input type of ADV decoder (0 ~ 3) */
		/*			0: sing-ended CVBS */
		/*			1: S-Video */
		/*			2: PCbCr */
		/*			3: differential CVBS */

#define CAPTURE_PROPERTY_ADV_LOCK_STATUS	CAPTURE_PROPERTY( 'A', 'L', 'C', 'K' )
		/* R	uint32_t	lock indicator */
		/*			0: unlocked */
		/*			1: locked */

#define CAPTURE_PROPERTY_ADV_FSCLOCK_STATUS	CAPTURE_PROPERTY( 'A', 'F', 'S', 'C' )
		/* R	uint32_t	Fsc lock indicator */
		/*			0: unlocked */
		/*			1: locked */

#define CAPTURE_PROPERTY_ADV_OUTPUT_FREQ	CAPTURE_PROPERTY( 'A', 'O', 'P', 'F' )
		/* R	uint32_t	indicate whether 50Hz or 60Hz is present at output */
		/*			0: 60Hz */
		/*			1: 50Hz */

#define CAPTURE_PROPERTY_ADV_WSS_STATUS		CAPTURE_PROPERTY( 'A', 'W', 'S', 'S' )
		/* R	uint32_t	indicate whether Wide Screen Signaling is available */
		/*			0: unavailable */
		/*			1: available */

/*
 * The following norms (video standards) can be set via CAPTURE_PROPERTY_NORM, with
 * the case of the characters being ignored:
 * "AUTO_PAL_BGHID_NTSC_J_SECAM"
 * "AUTO_PAL_BGHID_NTSC_M_SECAM"
 * "AUTO_PAL_N_NTSC_J_SECAM"
 * "AUTO_PAL_N_NTSC_M_SECAM"
 * "NTSC_J"
 * "NTSC_M"
 * "PAL_60"
 * "NTSC_4_43"
 * "PAL_BGHID"
 * "PAL_N"
 * "PAL_M_NO_PEDESTAL"
 * "PAL_M"
 * "PAL_COMBINATION_N"
 * "PAL_COMBINATION_N_PEDESTAL"
 * "SECAM"
 * "SECAM_PEDESTAL"
 *
 * The available norms (video standards), which can be get via CAPTURE_PROPERTY_CURRENT_NORM,
 * are listed as below:
 * "NTSC_M_J"
 * "NTSC_4_43"
 * "PAL_M"
 * "PAL_60"
 * "PAL_B_G_H_I_D"
 * "SECAM"
 * "PAL_COMBINATION_N"
 * "SECAM_525"
 * */

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/capture/adv7281ma/public/vcapture/capture-adv-ext.h $ $Rev: 732568 $")
#endif
