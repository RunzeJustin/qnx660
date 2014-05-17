/* xtgmath.h internal header */
#ifndef _XTGMATH
#define _XTGMATH

 #if defined(__cplusplus)
#include <xtr1common>

_STD_BEGIN
template<class _Ty>
	struct _Promote_to_float
	{	// promote integral to double
	typedef typename conditional<is_integral<_Ty>::value,
		double, _Ty>::type type;
	};

template<class _Ty1,
	class _Ty2>
	struct _Common_float_type
	{	// find type for two-argument math function
	typedef typename _Promote_to_float<_Ty1>::type _Ty1f;
	typedef typename _Promote_to_float<_Ty2>::type _Ty2f;
	typedef typename conditional<is_same<_Ty1f, long double>::value
		|| is_same<_Ty2f, long double>::value, long double,
		typename conditional<is_same<_Ty1f, double>::value
			|| is_same<_Ty2f, double>::value, double,
			float>::type>::type type;
	};
_STD_END

#define _CRTDEFAULT
#define _CRTSPECIAL

#define _GENERIC_MATH1(FUN, CRTTYPE) \
extern "C" CRTTYPE double FUN(double); \
template<class _Ty> inline \
	typename _STD enable_if< _STD is_integral<_Ty>::value, double>::type \
	FUN(_Ty _Left) \
	{ \
	return (_CSTD FUN((double)_Left)); \
	}

#define _GENERIC_MATH1X(FUN, ARG2, CRTTYPE) \
extern "C" CRTTYPE double FUN(double, ARG2); \
template<class _Ty> inline \
	typename _STD enable_if< _STD is_integral<_Ty>::value, double>::type \
	FUN(_Ty _Left, ARG2 _Arg2) \
	{ \
	return (_CSTD FUN((double)_Left, _Arg2)); \
	}

#define _GENERIC_MATH2(FUN, CRTTYPE) \
extern "C" CRTTYPE double FUN(double, double); \
template<class _Ty1, \
	class _Ty2> inline \
	typename _STD enable_if< _STD _Is_numeric<_Ty1>::value \
		&& _STD _Is_numeric<_Ty2>::value, \
			typename _STD _Common_float_type<_Ty1, _Ty2>::type>::type \
	FUN(_Ty1 _Left, _Ty2 _Right) \
	{ \
	typedef typename _STD _Common_float_type<_Ty1, _Ty2>::type type; \
	return (_CSTD FUN((type)_Left, (type)_Right)); \
	}

_C_STD_BEGIN
extern "C" double pow(double, double);
float pow(float, float);
long double pow(long double, long double);

template<class _Ty1,
	class _Ty2> inline
	typename _STD enable_if< _STD _Is_numeric<_Ty1>::value
		&& _STD _Is_numeric<_Ty2>::value,
		typename _STD _Common_float_type<_Ty1, _Ty2>::type>::type
	pow(const _Ty1 _Left, const _Ty2 _Right)
	{	// bring mixed types to a common type
	typedef typename _STD _Common_float_type<_Ty1, _Ty2>::type type;
	return (_CSTD pow(type(_Left), type(_Right)));
	}

//_GENERIC_MATH1(abs, _CRTDEFAULT)	// has integer overloads
_GENERIC_MATH1(acos, _CRTDEFAULT)
_GENERIC_MATH1(asin, _CRTDEFAULT)
_GENERIC_MATH1(atan, _CRTDEFAULT)
_GENERIC_MATH2(atan2, _CRTDEFAULT)
_GENERIC_MATH1(ceil, _CRTSPECIAL)
_GENERIC_MATH1(cos, _CRTDEFAULT)
_GENERIC_MATH1(cosh, _CRTDEFAULT)
_GENERIC_MATH1(exp, _CRTDEFAULT)
//_GENERIC_MATH1(fabs, _CRT_JIT_INTRINSIC)	// not required
_GENERIC_MATH1(floor, _CRTSPECIAL)
_GENERIC_MATH2(fmod, _CRTDEFAULT)
_GENERIC_MATH1X(frexp, int *, _CRTSPECIAL)
_GENERIC_MATH1X(ldexp, int, _CRTSPECIAL)
_GENERIC_MATH1(log, _CRTDEFAULT)
_GENERIC_MATH1(log10, _CRTDEFAULT)
//_GENERIC_MATH1(modf, _CRTDEFAULT)		// types must match
//_GENERIC_MATH2(pow, _CRTDEFAULT)	// hand crafted
_GENERIC_MATH1(sin, _CRTDEFAULT)
_GENERIC_MATH1(sinh, _CRTDEFAULT)
_GENERIC_MATH1(sqrt, _CRTDEFAULT)
_GENERIC_MATH1(tan, _CRTDEFAULT)
_GENERIC_MATH1(tanh, _CRTDEFAULT)

		// C99 MATH FUNCTIONS
#define _GENERIC_MATH1R(FUN, RET, CRTTYPE) \
extern "C" CRTTYPE RET FUN(double); \
template<class _Ty> inline \
	typename _STD enable_if< _STD is_integral<_Ty>::value, RET>::type \
	FUN(_Ty _Left) \
	{ \
	return (_CSTD FUN((double)_Left)); \
	}

		// TEMPLATE FUNCTION fma
template<class _Ty1,
	class _Ty2,
	class _Ty3> inline
	typename _STD _Common_float_type<_Ty1,
		typename _STD _Common_float_type<_Ty2, _Ty3>::type>::type
	fma(_Ty1 _Left, _Ty2 _Middle, _Ty3 _Right)
	{	// bring mixed types to a common type
	typedef typename _STD _Common_float_type<_Ty1,
		typename _STD _Common_float_type<_Ty2, _Ty3>::type>::type type;
	return (_CSTD fma((type)_Left, (type)_Right));
	}

		// TEMPLATE FUNCTION remquo
template<class _Ty1,
	class _Ty2> inline
	typename _STD _Common_float_type<_Ty1, _Ty2>::type
	remquo(_Ty1 _Left, _Ty2 _Right, int *_Pquo)
	{	// bring mixed types to a common type
	typedef typename _STD _Common_float_type<_Ty1, _Ty2>::type type;
	return (_CSTD remquo((type)_Left, (type)_Right, _Pquo));
	}

_GENERIC_MATH1(acosh, _CRTDEFAULT)
_GENERIC_MATH1(asinh, _CRTDEFAULT)
_GENERIC_MATH1(atanh, _CRTDEFAULT)
_GENERIC_MATH1(cbrt, _CRTDEFAULT)
_GENERIC_MATH2(copysign, _CRTDEFAULT)
_GENERIC_MATH1(erf, _CRTDEFAULT)
_GENERIC_MATH1(erfc, _CRTDEFAULT)
_GENERIC_MATH1(expm1, _CRTDEFAULT)
_GENERIC_MATH1(exp2, _CRTDEFAULT)
_GENERIC_MATH1(fabs, _CRTDEFAULT)
_GENERIC_MATH2(fdim, _CRTDEFAULT)
//_GENERIC_MATH3(fma, _CRTDEFAULT)	// hand crafted
_GENERIC_MATH2(fmax, _CRTDEFAULT)
_GENERIC_MATH2(fmin, _CRTDEFAULT)
_GENERIC_MATH2(hypot, _CRTDEFAULT)
_GENERIC_MATH1R(ilogb, int, _CRTDEFAULT)
_GENERIC_MATH1(lgamma, _CRTDEFAULT)
_GENERIC_MATH1R(llrint, long long, _CRTDEFAULT)
_GENERIC_MATH1R(llround, long long, _CRTDEFAULT)
_GENERIC_MATH1(log1p, _CRTDEFAULT)
_GENERIC_MATH1(log2, _CRTDEFAULT)
_GENERIC_MATH1(logb, _CRTDEFAULT)
_GENERIC_MATH1R(lrint, long, _CRTDEFAULT)
_GENERIC_MATH1R(lround, long, _CRTDEFAULT)
_GENERIC_MATH1(nearbyint, _CRTDEFAULT)
_GENERIC_MATH2(nextafter, _CRTDEFAULT)
_GENERIC_MATH1X(nexttoward, long double, _CRTDEFAULT)
_GENERIC_MATH2(remainder, _CRTDEFAULT)
//_GENERIC_MATH2X(remquo, _CRTDEFAULT)	// hand crafted
_GENERIC_MATH1(rint, _CRTDEFAULT)
_GENERIC_MATH1(round, _CRTDEFAULT)
_GENERIC_MATH1X(scalbln, long, _CRTDEFAULT)
_GENERIC_MATH1X(scalbn, int, _CRTDEFAULT)
_GENERIC_MATH1(tgamma, _CRTDEFAULT)
_GENERIC_MATH1(trunc, _CRTDEFAULT)
_C_STD_END
 #endif /* defined(__cplusplus) */

#endif /* _XTGMATH */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/m/public/xtgmath.h $ $Rev: 735298 $")
#endif
