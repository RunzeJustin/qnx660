/*
******************************************************************************
*
*   Copyright (C) 2009-2012, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
******************************************************************************
*/

#ifndef __ICU_DATA_VER_H__
#define __ICU_DATA_VER_H__

#include "unicode/utypes.h"

#ifndef U_HIDE_DRAFT_API
/**
 * @draft ICU 49
 */
#define U_ICU_VERSION_BUNDLE "icuver"

/**
 * @draft ICU 49
 */
#define U_ICU_DATA_KEY "DataVersion"

/**
 * Retrieves the data version from icuver and stores it in dataVersionFillin.
 * 
 * @param dataVersionFillin icuver data version information to be filled in if not-null
 * @param status stores the error code from the calls to resource bundle
 * 
 * @draft ICU 49
 */
U_DRAFT void U_EXPORT2 u_getDataVersion(UVersionInfo dataVersionFillin, UErrorCode *status);
#endif  /* U_HIDE_DRAFT_API */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/icu/dist/source/common/unicode/icudataver.h $ $Rev: 680336 $")
#endif
