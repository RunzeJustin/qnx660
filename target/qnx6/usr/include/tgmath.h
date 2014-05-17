/* tgmath.h standard header */
#ifndef _TGMATH
#define _TGMATH
#include <complex.h>
#include <math.h>

#ifndef __cplusplus

 #if __clang__ && __GNUC_MINOR__ == 2	/* compiler test */
#include <xtgmath1.h>

 #else /* __clang__ */
#include <xtgmath0.h>
 #endif /* __clang__ */

#endif /* __cplusplus */
#endif /* _TGMATH */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/m/public/tgmath.h $ $Rev: 735298 $")
#endif
