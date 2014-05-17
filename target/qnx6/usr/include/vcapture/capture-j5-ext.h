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

#ifndef INCL__VCAPTURE_J5_EXT__H
#define INCL__VCAPTURE_J5_EXT__H

#include <vcapture/capture.h>

#define CAPTURE_PROPERTY_J5_SYNC_TYPE CAPTURE_PROPERTY('5','S','N','T')
	/* R/W  int          Sets the sync. signal type (0 to 15; */
	/*                   or -1 for default). */

#define CAPTURE_PROPERTY_J5_USE_ACTVID_HSYNC CAPTURE_PROPERTY('5','U','A','H')
	/* R/W  int          If 1, use ACTVID style line capture */
	/*                   (0 or 1; or -1 for default). */

#define CAPTURE_PROPERTY_J5_EDMA_CHANNEL CAPTURE_PROPERTY( '5', 'E', 'C', 'N' )
	/* R/W  int          Sets the edma channel, for weave2 de-interlacing */
	/*                   (0~63, board specific; or -1 for default) */
	/*                   The default edma channel number is bound to the */
	/*                   specific device and source: */
	/*                   channel 6 for device 0 + source 0 */
	/*                   channel 7 for device 1 + source 0 */
	/*                   channel 62 for device 0 + source 1 */
	/*                   channel 63 for device 1 + source 1 */

#define CAPTURE_PROPERTY_J5_ADAPTIVE_DEI_INT_MODE CAPTURE_PROPERTY( '5', 'D', 'I', 'M' )
	/*  R/W int          Set the interpolation mode for the adaptive (hardware) de-interlacer */
        /*                   0: The interpolated field is created by line averaging from the YUV */
        /*                      data. That is, the interpolated line is created by averaging its */
        /*                      top and bottom lines. */
        /*                   1: The interpolated field is created by averaging pixels from fields */
        /*                      before and after the current field. For instance, if the current */
        /*                      field is a top field, the interpolated bottom field  is created by */
        /*                      averaging pixels from bottom field pictures before and after the */
        /*                      current field. */
        /*                   2: This is an edge assisted interlace mode with edges detected from */
        /*                      the Luma information in the frame window. Luma for missing lines */
        /*                      are interpolated using original Luma along the detected edge. MV */
        /*                      from the MDT module is used to select coefficients from a LUT on */
        /*                      how 2D interpolation from the current field  and 3D interpolation */
        /*                      from two fields adjacent to the current fields are blended. */
        /*                   3: The edge detection method used in this mode is similar to */
        /*                      interpolation mode 2. The only difference is that the edge-directed */
        /*                      interpolation is performed on both Luma and Chroma. Chroma is */
        /*                      interpolated similarly according to the edge vectors obtained */
        /*                      based on Luma information. */

enum j5_adaptive_dei_interpolation_mode {
		J5_ADAPTIVE_DEI_INT_MODE_0 = 0,
		J5_ADAPTIVE_DEI_INT_MODE_1,
		J5_ADAPTIVE_DEI_INT_MODE_2,
		J5_ADAPTIVE_DEI_INT_MODE_3
};

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/wfd/jacinto5/caplib/public/vcapture/capture-j5-ext.h $ $Rev: 732568 $")
#endif
