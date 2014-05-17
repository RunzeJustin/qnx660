/* stdalign.h standard header */
#ifndef _STDALIGN
#define _STDALIGN
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN
 #define __alignas_is_defined	1

 #ifndef __cplusplus
 #define alignas	_Alignas;
 #endif /* __cplusplus */
_C_STD_END
#endif /* _STDALIGN */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/c/public/stdalign.h $ $Rev: 735298 $")
#endif
