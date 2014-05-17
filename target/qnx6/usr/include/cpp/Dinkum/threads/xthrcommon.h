/* xthrcommon.h -- common header for C/C++ threads libraries */
#ifndef _THREADS_XTHRCOMMON_H
#define _THREADS_XTHRCOMMON_H
#include <yvals.h>


 #if defined(_THREAD_CHECK) || defined(_DEBUG)
  #define _THREAD_CHECKX	1

 #else /* defined(_THREAD_CHECK) || defined(_DEBUG) */
  #define _THREAD_CHECKX	0
 #endif /* defined(_THREAD_CHECK) || defined(_DEBUG) */

 #if defined(__BORLANDC__)
  #pragma warn -par
 #endif /* defined(__BORLANDC__) */

_EXTERN_C

 #if _WIN32_C_LIB

 #if defined(__EDG__) \
	|| defined(_X86_EMUL) && _420 == _WIN32_WCE \
	|| defined(_X86_) && 300 <= _WIN32_WCE
  #define _STDCALL
 #else /* defined(_X86_EMUL) etc. */
  #define _STDCALL	__stdcall
 #endif /* defined(_X86_EMUL) etc. */

typedef struct
	{	/* thread identifier for Win32 */
	void *_Hnd;	/* Win32 HANDLE */
	unsigned int _Id;
	} _Thrd_imp_t;

#define _Thr_val(thr) thr._Id
#define _Thr_set_null(thr) (thr._Id = 0)
#define _Thr_is_null(thr) (thr._Id == 0)

typedef unsigned int (_STDCALL *_Thrd_callback_t)(void *);
typedef struct _Mtx_internal_imp_t *_Mtx_imp_t;

typedef struct
	{	/* saved state for Win32 mutex */
	int _Count;
	} _Mtx_state;

int _Save_state(struct _Mtx_internal_imp_t **, _Mtx_state *);
int _Restore_state(struct _Mtx_internal_imp_t **, _Mtx_state *);

typedef struct _Cnd_internal_imp_t *_Cnd_imp_t;
typedef int _Tss_imp_t;

typedef char _Once_flag_imp_t;
  #define _ONCE_FLAG_INIT_IMP	0

 #elif _HAS_POSIX_C_LIB
  #include <limits.h>
  #include <time.h>
  #include <errno.h>
  #include <pthread.h>

  #define _STDCALL

  #ifdef ETIMEDOUT
  #elif defined(sparc) || defined(__sparc)
   #define ETIMEDOUT	0x0091
  #else /* assume Linux */
   #define ETIMEDOUT	0x006E
  #endif /* library type */

  #ifndef EBUSY
   #define EBUSY	0x0010
  #endif /* EBUSY */

typedef pthread_t _Thrd_imp_t;

#define _Thr_val(thr) thr
#define _Thr_set_null(thr) (thr = 0)
#define _Thr_is_null(thr) (thr == 0)

typedef void *(*_Thrd_callback_t)(void *);
typedef struct _Mtx_internal_imp_t *_Mtx_imp_t;

typedef struct
	{	/* saved state for POSIX mutex */
	pthread_t _Owner;
	int _Count;
	} _Mtx_state;

pthread_mutex_t *_Save_state(struct _Mtx_internal_imp_t *, _Mtx_state *);
int _Restore_state(struct _Mtx_internal_imp_t *, _Mtx_state *);

  #if _THREAD_CHECKX
typedef struct _Cnd_internal_imp_t *_Cnd_imp_t;

  #else /* THREAD_CHECKX */
typedef pthread_cond_t _Cnd_imp_t;
  #endif /* THREAD_CHECKX */

typedef pthread_key_t _Tss_imp_t;

  #define _TSS_CREATE(key, dtor)	pthread_key_create(key, dtor)
  #define _TSS_DELETE(key)			pthread_key_delete(key)
  #define _TSS_SET(key, value)		pthread_setspecific(key, value)
  #define _TSS_GET(key)				pthread_getspecific(key)

typedef pthread_once_t _Once_flag_imp_t;

  #define _ONCE_FLAG_INIT_IMP	PTHREAD_ONCE_INIT

 #else /* library type */
  #error Unknown platform
 #endif	/* library type */

	/* internal */
void _Thrd_abort(const char *);
int _Thrd_start(_Thrd_imp_t *, _Thrd_callback_t, void *);
void _Tss_destroy(void);

 #if _THREAD_CHECKX
  #define _THREAD_QUOTX(x)	#x
  #define _THREAD_QUOT(x)	_THREAD_QUOTX(x)
	/* CAUTION -- some compilers require this all one one line: */
  #define _THREAD_ASSERT(expr, msg)	((expr) \
	? (void)0 : _Thrd_abort(__FILE__ "(" _THREAD_QUOT(__LINE__) "): " msg))

 #else /* _THREAD_CHECKX */
  #define _THREAD_ASSERT(expr, msg)	((void)0)
 #endif	/* _THREAD_CHECKX */

_END_EXTERN_C

/*	platform-specific properties */
 #if _WIN32_C_LIB
  #define _THREAD_EMULATE_TSS	1

 #elif _HAS_POSIX_C_LIB
  #if defined(sparc) || defined(__sparc)
   #define _THREAD_EMULATE_TSS	1
   #define _THREAD_HAS_NANOSLEEP	0
   #define _THREAD_HAS_SCHED_YIELD	0

  #elif !defined(PTHREAD_DESTRUCTOR_ITERATIONS)
   #define _THREAD_EMULATE_TSS	1
   #define _THREAD_HAS_NANOSLEEP	1
   #define _THREAD_HAS_SCHED_YIELD	1

  #else /* defined(sparc) || defined(__sparc) */
   #define _THREAD_EMULATE_TSS	0
   #define _THREAD_HAS_NANOSLEEP	1
   #define _THREAD_HAS_SCHED_YIELD	1
  #endif /* defined(sparc) || defined(__sparc) */

 #else /* library type */
  #error Unknown platform
 #endif /* library type */

 #if _THREAD_EMULATE_TSS
  #define _TSS_USE_MACROS	0
  #define _TSS_DTOR_ITERATIONS_IMP	4

 #elif _HAS_POSIX_C_LIB
  #define _TSS_USE_MACROS	1
  #define _TSS_DTOR_ITERATIONS_IMP	PTHREAD_DESTRUCTOR_ITERATIONS
 #endif /* _THREAD_EMULATE_TSS */

#endif	/* _THREADS_XTHRCOMMON_H */

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
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/cpp/public/cpp/Dinkum/threads/xthrcommon.h $ $Rev: 735298 $")
#endif
