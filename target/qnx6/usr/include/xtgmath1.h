/* xtgmath1.h header for clang */

 #ifndef _Tg_promote
#define _Tg_promote(From, To) \
	static To __attribute__((__overloadable__)) __tg_promote(From)

_Tg_promote(int, double);
_Tg_promote(unsigned int, double);
_Tg_promote(long, double);
_Tg_promote(unsigned long, double);
_Tg_promote(long long, double);
_Tg_promote(unsigned long long, double);
_Tg_promote(float, float);
_Tg_promote(double, double);
_Tg_promote(long double, long double);

_Tg_promote(float _Complex, float _Complex);
_Tg_promote(double _Complex, double _Complex);
_Tg_promote(long double _Complex, long double _Complex);

static void __tg_promote(...)
	__attribute__((__overloadable__, __unavailable__));

#define _Tg_overload	__attribute__((__overloadable__, __always_inline__))

#define _Prom1(x)	(__typeof__(__tg_promote(x)))
#define _Prom2(x, y)	(__typeof__(__tg_promote(x) + __tg_promote(y)))
#define _Prom3(x, y, z)	(__typeof__(__tg_promote(x) + __tg_promote(y) \
	+ __tg_promote(z)))
 #endif /* _Tg_promote */

#define _Tg_r(fn) \
static float _Tg_overload _Tg_##fn(float _Left) \
	{return (fn##f(_Left));} \
static double _Tg_overload _Tg_##fn(double _Left) \
	{return (fn(_Left));} \
static long double _Tg_overload _Tg_##fn(long double _Left) \
	{return (fn##l(_Left));}
#define _Tg_c(fn) \
static float _Complex _Tg_overload _Tg_##fn(float _Complex _Left) \
	{return (fn##f(_Left));} \
static double _Complex _Tg_overload _Tg_##fn(double _Complex _Left) \
	{return (fn(_Left));} \
static long double _Complex _Tg_overload \
		_Tg_##fn(long double _Complex _Left) \
	{return (fn##l(_Left));}
#define _Tg_r2(fn) \
static float _Tg_overload _Tg_##fn(float _Left, float _Right) \
	{return (fn##f(_Left, _Right));} \
static double _Tg_overload _Tg_##fn(double _Left, double _Right) \
	{return (fn(_Left, _Right));} \
static long double _Tg_overload \
		_Tg_##fn(long double _Left, long double _Right) \
	{return (fn##l(_Left, _Right));}
#define _Tg_c2(fn) \
static float _Complex _Tg_overload \
		_Tg_##fn(float _Complex _Left, float _Complex _Right) \
	{return (fn##f(_Left, _Right));} \
static double _Complex _Tg_overload \
		_Tg_##fn(double _Complex _Left, double _Complex _Right) \
	{return (fn(_Left, _Right));} \
static long double _Complex _Tg_overload \
		_Tg_##fn(long double _Complex _Left, long double _Complex _Right) \
	{return (fn##l(_Left, _Right));}
#define _Tg_ri(fn, rty) \
static rty _Tg_overload _Tg_##fn(float _Left) \
	{return (fn##f(_Left));} \
static rty _Tg_overload _Tg_##fn(double _Left) \
	{return (fn(_Left));} \
static rty _Tg_overload \
		_Tg_##fn(long double _Left) \
	{return (fn##l(_Left));}
#define _Tg_rx(fn, rty) \
static float _Tg_overload _Tg_##fn(float _Left, rty _Right) \
	{return (fn##f(_Left, _Right));} \
static double _Tg_overload _Tg_##fn(double _Left, rty _Right) \
	{return (fn(_Left, _Right));} \
static long double _Tg_overload \
		_Tg_##fn(long double _Left, rty _Right) \
	{return (fn##l(_Left, _Right));}
#define _Tg_r3(fn) \
static float _Tg_overload _Tg_##fn(float _Left, float _Mid, float _Right) \
	{return (fn##f(_Left, _Mid, _Right));} \
static double _Tg_overload \
		_Tg_##fn(double _Left, double _Mid, double _Right) \
	{return (fn(_Left, _Mid, _Right));} \
static long double _Tg_overload \
		_Tg_##fn(long double _Left, long double _Mid, long double _Right) \
	{return (fn##l(_Left, _Mid, _Right));}
#define _Tg_r3x(fn, rty) \
static float _Tg_overload _Tg_##fn(float _Left, float _Mid, rty _Right) \
	{return (fn##f(_Left, _Mid, _Right));} \
static double _Tg_overload \
		_Tg_##fn(double _Left, double _Mid, rty _Right) \
	{return (fn(_Left, _Mid, _Right));} \
static long double _Tg_overload \
		_Tg_##fn(long double _Left, long double _Mid, rty _Right) \
	{return (fn##l(_Left, _Mid, _Right));}
#define _Tg_c0(fn) \
static float _Tg_overload _Tg_##fn(float _Complex _Left) \
	{return (fn##f(_Left));} \
static double _Tg_overload _Tg_##fn(double _Complex _Left) \
	{return (fn(_Left));} \
static long double _Tg_overload \
		_Tg_##fn(long double _Complex _Left) \
	{return (fn##l(_Left));}
#define _Tg_rc(fn) \
	_Tg_r(fn) \
static float _Complex _Tg_overload _Tg_##fn(float _Complex _Left) \
	{return (c##fn##f(_Left));} \
static double _Complex _Tg_overload _Tg_##fn(double _Complex _Left) \
	{return (c##fn(_Left));} \
static long double _Complex _Tg_overload \
	_Tg_##fn(long double _Complex _Left) \
	{return (c##fn##l(_Left));}
_C_STD_BEGIN
_Tg_rc(acos)
#undef acos
#define acos(x) _Tg_acos(_Prom1(x)(x))

_Tg_rc(acosh)
#undef acosh
#define acosh(x) _Tg_acosh(_Prom1(x)(x))

_Tg_rc(asin)
#undef asin
#define asin(x) _Tg_asin(_Prom1(x)(x))

_Tg_rc(asinh)
#undef asinh
#define asinh(x) _Tg_asinh(_Prom1(x)(x))

_Tg_rc(atan)
#undef atan
#define atan(x) _Tg_atan(_Prom1(x)(x))

_Tg_rc(atanh)
#undef atanh
#define atanh(x) _Tg_atanh(_Prom1(x)(x))

_Tg_r2(atan2)
#undef atan2
#define atan2(y, x) _Tg_atan2(_Prom2(y, x)(y), _Prom2(y, x)(x))

_Tg_c0(carg)
#undef carg
#define carg(x) _Tg_carg(_Prom1(x)(x))

_Tg_r(cbrt)
#undef cbrt
#define cbrt(x) _Tg_cbrt(_Prom1(x)(x))

_Tg_r(ceil)
#undef ceil
#define ceil(x) _Tg_ceil(_Prom1(x)(x))

_Tg_c0(cimag)
#undef cimag
#define cimag(x) _Tg_cimag(_Prom1(x)(x))

_Tg_r(conj)
_Tg_c(conj)
#undef conj
#define conj(x) _Tg_conj(_Prom1(x)(x))

_Tg_r2(copysign)
#undef copysign
#define copysign(y, x) _Tg_copysign(_Prom2(y, x)(y), _Prom2(y, x)(x))

_Tg_rc(cos)
#undef cos
#define cos(x) _Tg_cos(_Prom1(x)(x))

_Tg_rc(cosh)
#undef cosh
#define cosh(x) _Tg_cosh(_Prom1(x)(x))

_Tg_r(cproj)
_Tg_c(cproj)
#undef cproj
#define cproj(x) _Tg_cproj(_Prom1(x)(x))

_Tg_c0(creal)
#undef creal
#define creal(x) _Tg_creal(_Prom1(x)(x))

_Tg_r(erf)
#undef erf
#define erf(x) _Tg_erf(_Prom1(x)(x))

_Tg_r(erfc)
#undef erfc
#define erfc(x) _Tg_erfc(_Prom1(x)(x))

_Tg_rc(exp)
#undef exp
#define exp(x) _Tg_exp(_Prom1(x)(x))

_Tg_r(exp2)
#undef exp2
#define exp2(x) _Tg_exp2(_Prom1(x)(x))

_Tg_r(expm1)
#undef expm1
#define expm1(x) _Tg_expm1(_Prom1(x)(x))

_Tg_r(fabs)
_Tg_c(cabs)
#undef fabs
#define fabs(x) _Tg_fabs(_Prom1(x)(x))

_Tg_r2(fdim)
#undef fdim
#define fdim(x, y) _Tg_fdim(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_r(floor)
#undef floor
#define floor(x) _Tg_floor(_Prom1(x)(x))

_Tg_r3(fma)
#undef fma
#define fma(x, y, z) \
	_Tg_fma(_Prom3(x, y, z)(x), _Prom3(x, y, z)(y), _Prom3(x, y, z)(z))

_Tg_r2(fmax)
#undef fmax
#define fmax(x, y) _Tg_fmax(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_r2(fmin)
#undef fmin
#define fmin(x, y) _Tg_fmin(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_r2(fmod)
#undef fmod
#define fmod(x, y) _Tg_fmod(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_rx(frexp, int *)
#undef frexp
#define frexp(x, y) _Tg_frexp(_Prom1(x)(x), y)

_Tg_r2(hypot)
#undef hypot
#define hypot(x, y) _Tg_hypot(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_ri(ilogb, int)
#undef ilogb
#define ilogb(x) _Tg_ilogb(_Prom1(x)(x))

_Tg_rx(ldexp, int)
#undef ldexp
#define ldexp(x, y) _Tg_ldexp(_Prom1(x)(x), y)

_Tg_r(lgamma)
#undef lgamma
#define lgamma(x) _Tg_lgamma(_Prom1(x)(x))

_Tg_ri(llrint, long long)
#undef llrint
#define llrint(x) _Tg_llrint(_Prom1(x)(x))

_Tg_ri(llround, long long)
#undef llround
#define llround(x) _Tg_llround(_Prom1(x)(x))

_Tg_rc(log)
#undef log
#define log(x) _Tg_log(_Prom1(x)(x))

_Tg_r(log1p)
#undef log1p
#define log1p(x) _Tg_log1p(_Prom1(x)(x))

_Tg_r(log10)
#undef log10
#define log10(x) _Tg_log10(_Prom1(x)(x))

_Tg_r(log2)
#undef log2
#define log2(x) _Tg_log2(_Prom1(x)(x))

_Tg_r(logb)
#undef logb
#define logb(x) _Tg_logb(_Prom1(x)(x))

_Tg_ri(lrint, long)
#undef lrint
#define lrint(x) _Tg_lrint(_Prom1(x)(x))

_Tg_ri(lround, long)
#undef lround
#define lround(x) _Tg_lround(_Prom1(x)(x))

_Tg_r(nearbyint)
#undef nearbyint
#define nearbyint(x) _Tg_nearbyint(_Prom1(x)(x))

_Tg_r2(nextafter)
#undef nextafter
#define nextafter(x, y) _Tg_nextafter(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_rx(nexttoward, long double)
#undef nexttoward
#define nexttoward(x, y) _Tg_nexttoward(_Prom1(x)(x), y)

_Tg_r2(pow)
_Tg_c2(pow)
#undef pow
#define pow(x, y) _Tg_pow(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_r2(remainder)
#undef remainder
#define remainder(x, y) _Tg_remainder(_Prom2(x, y)(x), _Prom2(x, y)(y))

_Tg_r3x(remquo, int *)
#undef remquo
#define remquo(x, y, z) \
	_Tg_remquo(_Prom2(x, y)(x), _Prom2(x, y)(y), z)

_Tg_r(rint)
#undef rint
#define rint(x) _Tg_rint(_Prom1(x)(x))

_Tg_r(round)
#undef round
#define round(x) _Tg_round(_Prom1(x)(x))

_Tg_rx(scalbln, long)
#undef scalbln
#define scalbln(x, y) _Tg_scalbln(_Prom1(x)(x), y)

_Tg_rx(scalbn, int)
#undef scalbn
#define scalbn(x, y) _Tg_scalbn(_Prom1(x)(x), y)

_Tg_rc(sin)
#undef sin
#define sin(x) _Tg_sin(_Prom1(x)(x))

_Tg_rc(sinh)
#undef sinh
#define sinh(x) _Tg_sinh(_Prom1(x)(x))

_Tg_rc(sqrt)
#undef sqrt
#define sqrt(x) _Tg_sqrt(_Prom1(x)(x))

_Tg_rc(tan)
#undef tan
#define tan(x) _Tg_tan(_Prom1(x)(x))

_Tg_rc(tanh)
#undef tanh
#define tanh(x) _Tg_tanh(_Prom1(x)(x))

_Tg_r(tgamma)
#undef tgamma
#define tgamma(x) _Tg_tgamma(_Prom1(x)(x))

_Tg_r(trunc)
#undef trunc
#define trunc(x) _Tg_trunc(_Prom1(x)(x))

 #if _HAS_CPP0X
#undef proj
#define proj(x) _Tg_cproj(_Prom1(x)(x))
 #endif /* _HAS_CPP0X */
_C_STD_END

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/m/public/xtgmath1.h $ $Rev: 735298 $")
#endif
