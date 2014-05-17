/* xtimec.h -- header for high-resolution time functions */
#ifndef _THREADS_XTIMEC_H
#define _THREADS_XTIMEC_H
#include <Dinkum/threads/xthrcommon.h>
#include <time.h>


#ifdef __cplusplus
extern "C" {	// C linkage
#endif /* __cplusplus */

enum {	/* define TIME_UTC */
	TIME_UTC = 1
	};

typedef struct xtime
	{	/* store time with nanosecond resolution */
	long sec;
	long nsec;
	} xtime;

int xtime_get(xtime*, int);

 #if _WIN32_C_LIB
long _Xtime_diff_to_millis(const xtime *);
long _Xtime_diff_to_millis2(const xtime*, const xtime *);
_LONGLONG _Xtime_get_ticks();
#define _XTIME_NSECS_PER_TICK	100
#define _XTIME_TICKS_PER_TIME_T	(_LONGLONG)10000000

 #elif _HAS_POSIX_C_LIB
struct timespec _Xtime_to_ts(const xtime *xt);
struct timespec _Xtime_diff_to_ts(const xtime *xt);
_LONGLONG _Xtime_get_ticks();
#define _XTIME_NSECS_PER_TICK	1000
#define _XTIME_TICKS_PER_TIME_T	(_LONGLONG)1000000

 #else /* library type */
  #error Unknown platform
 #endif	/* library type */

#ifdef __cplusplus
} // extern "C"
#endif
#endif	/* _THREADS_XTIMEC_H */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * (c) Copyright William E. Kempf 2001
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation. William E. Kempf makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/cpp/public/cpp/Dinkum/threads/xtimec.h $ $Rev: 735298 $")
#endif
