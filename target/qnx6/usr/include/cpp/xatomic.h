/* xatomic.h internal header */
#ifndef _XATOMIC_H
#define _XATOMIC_H
#include <xatomic0.h>
#include <stddef.h>	// for size_t
#include <stdlib.h>
#include <string.h>

 #ifndef _CONCAT
  #define _CONCATX(x, y)	x ## y
  #define _CONCAT(x, y)		_CONCATX(x, y)
 #endif /* _CONCAT */

#define ATOMIC_BOOL_LOCK_FREE	\
	(1 <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_CHAR_LOCK_FREE	\
	(1 <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_CHAR16_T_LOCK_FREE	\
	(2 <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_CHAR32_T_LOCK_FREE	\
	(2 <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_WCHAR_T_LOCK_FREE	\
	(_WCHAR_T_SIZE <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_SHORT_LOCK_FREE	\
	(_SHORT_SIZE <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_INT_LOCK_FREE	\
	(_INT_SIZE <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_LONG_LOCK_FREE	\
	(_LONG_SIZE <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define _ATOMIC_LLONG_LOCK_FREE	\
	(_LONGLONG_SIZE <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)
#define ATOMIC_POINTER_LOCK_FREE	\
	(_ADDR_SIZE <= _ATOMIC_MAXBYTES_LOCK_FREE ? 2 : 0)

_STD_BEGIN
		/* TYPEDEFS FOR INTERNAL ARITHMETIC TYPES */
typedef unsigned char _Uint1_t;
typedef unsigned short _Uint2_t;
//typedef _Uint32t _Uint4_t;
typedef unsigned _LONGLONG _Uint8_t;

  #define _ATOMIC_FLAG_TEST_AND_SET _Atomic_flag_test_and_set
  #define _ATOMIC_FLAG_CLEAR _Atomic_flag_clear

  #define _ATOMIC_THREAD_FENCE _Atomic_thread_fence
  #define _ATOMIC_SIGNAL_FENCE _Atomic_signal_fence

_EXTERN_C
void _Atomic_store_1(volatile _Uint1_t *_Tgt, _Uint1_t _Value,
	memory_order _Order);
_Uint1_t _Atomic_load_1(volatile _Uint1_t *_Tgt,
	memory_order _Order);
_Uint1_t _Atomic_exchange_1(volatile _Uint1_t *_Tgt,
	_Uint1_t _Value, memory_order _Order);
int _Atomic_compare_exchange_strong_1(
	volatile _Uint1_t *_Tgt, _Uint1_t *_Exp, _Uint1_t _Value,
	memory_order _Order1, memory_order _Order2);
int _Atomic_compare_exchange_weak_1(
	volatile _Uint1_t *_Tgt, _Uint1_t *_Exp, _Uint1_t _Value,
	memory_order _Order1, memory_order _Order2);
_Uint1_t _Atomic_fetch_add_1(
	volatile _Uint1_t *_Tgt, _Uint1_t _Value, memory_order _Order);
_Uint1_t _Atomic_fetch_sub_1(
	volatile _Uint1_t *_Tgt, _Uint1_t _Value, memory_order _Order);
_Uint1_t _Atomic_fetch_and_1(
	volatile _Uint1_t *_Tgt, _Uint1_t _Value, memory_order _Order);
_Uint1_t _Atomic_fetch_or_1(
	volatile _Uint1_t *_Tgt, _Uint1_t _Value, memory_order _Order);
_Uint1_t _Atomic_fetch_xor_1(
	volatile _Uint1_t *_Tgt, _Uint1_t _Value, memory_order _Order);
void _Atomic_store_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
_Uint2_t _Atomic_load_2(
	volatile _Uint2_t *_Tgt, memory_order _Order);
_Uint2_t _Atomic_exchange_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
int _Atomic_compare_exchange_weak_2(
	volatile _Uint2_t *_Tgt, _Uint2_t *_Exp, _Uint2_t _Value,
	memory_order _Order1, memory_order _Order2);
int _Atomic_compare_exchange_strong_2(
	volatile _Uint2_t *_Tgt, _Uint2_t *_Exp, _Uint2_t _Value,
	memory_order _Order1, memory_order _Order2);
_Uint2_t _Atomic_fetch_add_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
_Uint2_t _Atomic_fetch_sub_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
_Uint2_t _Atomic_fetch_and_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
_Uint2_t _Atomic_fetch_or_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
_Uint2_t _Atomic_fetch_xor_2(
	volatile _Uint2_t *_Tgt, _Uint2_t _Value, memory_order _Order);
void _Atomic_store_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
_Uint4_t _Atomic_load_4(
	volatile _Uint4_t *_Tgt, memory_order _Order);
_Uint4_t _Atomic_exchange_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
int _Atomic_compare_exchange_strong_4(
	volatile _Uint4_t *_Tgt, _Uint4_t *_Exp, _Uint4_t _Value,
	memory_order _Order1, memory_order _Order2);
int _Atomic_compare_exchange_weak_4(
	volatile _Uint4_t *_Tgt, _Uint4_t *_Exp, _Uint4_t _Value,
	memory_order _Order1, memory_order _Order2);
_Uint4_t _Atomic_fetch_add_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
_Uint4_t _Atomic_fetch_sub_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
_Uint4_t _Atomic_fetch_and_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
_Uint4_t _Atomic_fetch_or_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
_Uint4_t _Atomic_fetch_xor_4(
	volatile _Uint4_t *_Tgt, _Uint4_t _Value, memory_order _Order);
void _Atomic_store_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
_Uint8_t _Atomic_load_8(
	volatile _Uint8_t *_Tgt, memory_order _Order);
_Uint8_t _Atomic_exchange_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
int _Atomic_compare_exchange_strong_8(
	volatile _Uint8_t *_Tgt, _Uint8_t *_Exp, _Uint8_t _Value,
	memory_order _Order1, memory_order _Order2);
int _Atomic_compare_exchange_weak_8(
	volatile _Uint8_t *_Tgt, _Uint8_t *_Exp, _Uint8_t _Value,
	memory_order _Order1, memory_order _Order2);
_Uint8_t _Atomic_fetch_add_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
_Uint8_t _Atomic_fetch_sub_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
_Uint8_t _Atomic_fetch_and_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
_Uint8_t _Atomic_fetch_or_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
_Uint8_t _Atomic_fetch_xor_8(
	volatile _Uint8_t *_Tgt, _Uint8_t _Value, memory_order _Order);
int _Atomic_flag_test_and_set(volatile _Atomic_flag_t *_Flag,
	memory_order _Order);
void _Atomic_flag_clear(volatile _Atomic_flag_t *_Flag,
	memory_order _Order);
void _Atomic_thread_fence(memory_order _Order);
void _Atomic_signal_fence(memory_order _Order);
_END_EXTERN_C

 #ifdef __cplusplus
  #define _INLINE	inline

 #else /* __cplusplus */
  #define _INLINE	static
 #endif /* __cplusplus */

 #if defined(_M_ARM)
 #define _YIELD_PROCESSOR __yield()

 #else
 #define _YIELD_PROCESSOR
 #endif

		/* SPIN LOCK FOR LOCKING VERSIONS OF OPERATIONS */
		/* Use acquire semantics on lock and release on unlock. Given our
			current atomic_flag implementation, this ensures not just
			atomicity but also sequential consistency. */

_INLINE void _Lock_spin_lock(
	volatile _Atomic_flag_t *_Flag)
	{	/* spin until _Flag successfully set */
	while (_ATOMIC_FLAG_TEST_AND_SET(_Flag, memory_order_acquire))
		_YIELD_PROCESSOR;
	}

_INLINE void _Unlock_spin_lock(
	volatile _Atomic_flag_t *_Flag)
	{	/* release previously obtained lock */
	_ATOMIC_FLAG_CLEAR(_Flag, memory_order_release);
	}

		/* ATOMIC OPERATIONS FOR OBJECTS WITH SIZES THAT
			DON'T MATCH THE SIZE OF ANY INTEGRAL TYPE */
_INLINE void _Atomic_copy(
	volatile _Atomic_flag_t *_Flag, size_t _Size,
		volatile void *_Tgt, volatile const void *_Src,
			memory_order _Order)
	{	/* atomically copy *_Src to *_Tgt with memory ordering */
	_Lock_spin_lock(_Flag);
	memcpy((void *)_Tgt, (void *)_Src, _Size);
	_Unlock_spin_lock(_Flag);
	}

_INLINE void _Atomic_exchange(
	volatile _Atomic_flag_t *_Flag, size_t _Size,
		volatile void *_Tgt, volatile void *_Src,
			memory_order _Order)
	{	/* atomically swap *_Src and *_Tgt with memory ordering */
	unsigned char *_Left = (unsigned char *)_Tgt;
	unsigned char *_Right = (unsigned char *)_Src;

	_Lock_spin_lock(_Flag);
	for (; 0 < _Size; --_Size)
		{	/* copy bytes */
		unsigned char _Tmp = *_Left;
		*_Left++ = *_Right;
		*_Right++ = _Tmp;
		}
	_Unlock_spin_lock(_Flag);
	}

_INLINE int _Atomic_compare_exchange_weak(
	volatile _Atomic_flag_t *_Flag, size_t _Size,
		volatile void *_Tgt, volatile void *_Exp, const volatile void *_Src,
			memory_order _Order1, memory_order _Order2)
	{	/* atomically compare and exchange with memory ordering */
	int _Result;

	_Lock_spin_lock(_Flag);
	_Result = memcmp((const void *)_Tgt, (const void *)_Exp, _Size) == 0;
	if (_Result != 0)
		memcpy((void *)_Tgt, (void *)_Src, _Size);
	else
		memcpy((void *)_Exp, (void *)_Tgt, _Size);
	_Unlock_spin_lock(_Flag);
	return (_Result);
	}

_INLINE int _Atomic_compare_exchange_strong(
	volatile _Atomic_flag_t *_Flag, size_t _Size,
	volatile void *_Tgt, volatile void *_Exp, const volatile void *_Src,
	memory_order _Order1, memory_order _Order2)
	{	/* atomically compare and exchange with memory ordering */
	return (_Atomic_compare_exchange_weak(_Flag, _Size, _Tgt, _Exp, _Src,
	  _Order1, _Order2));
	}

		/* LOCK-FREE PROPERTY FOR INTEGRAL TYPES */
_INLINE int _Atomic_is_lock_free_1(void)
	{	/* return true if 1-byte atomic values are lock-free */
	return (1 <= _ATOMIC_MAXBYTES_LOCK_FREE);
	}

_INLINE int _Atomic_is_lock_free_2(void)
	{	/* return true if 2-byte atomic values are lock-free */
	return (2 <= _ATOMIC_MAXBYTES_LOCK_FREE);
	}

_INLINE int _Atomic_is_lock_free_4(void)
	{	/* return true if 4-byte atomic values are lock-free */
	return (4 <= _ATOMIC_MAXBYTES_LOCK_FREE);
	}

_INLINE int _Atomic_is_lock_free_8(void)
	{	/* return true if 8-byte atomic values are lock-free */
	return (8 <= _ATOMIC_MAXBYTES_LOCK_FREE);
	}
_STD_END
#endif /* _XATOMIC_H */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/cpp/public/cpp/xatomic.h $ $Rev: 735298 $")
#endif
