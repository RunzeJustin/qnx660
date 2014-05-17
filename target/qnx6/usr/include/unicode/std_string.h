/*
*******************************************************************************
*
*   Copyright (C) 2009-2011, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
*******************************************************************************
*   file name:  std_string.h
*   encoding:   US-ASCII
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2009feb19
*   created by: Markus W. Scherer
*/

#ifndef __STD_STRING_H__
#define __STD_STRING_H__

/**
 * \file 
 * \brief C++ API: Central ICU header for including the C++ standard &lt;string&gt;
 *                 header and for related definitions.
 */

#include "unicode/utypes.h"

#if U_HAVE_STD_STRING

#include <string>

#endif  // U_HAVE_STD_STRING

#endif  // __STD_STRING_H__

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/icu/dist/source/common/unicode/std_string.h $ $Rev: 680336 $")
#endif
