/*
 * $QNXtpLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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





/* yvals.h values header for conforming compilers on various systems */
#ifndef _YVALS
#define _YVALS
#include <sys/platform.h>

 #if defined(__clang__) && __GNUC_MINOR__ == 2	/* kludge */
  #define _CLANG	1

 #else	/* __clang__ */
  #define _CLANG	0
 #endif	/* __clang__ */

 #define _GCC43	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 3 <= __GNUC_MINOR__)	/* 4.3 or newer */
 #define _GCC44	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 4 <= __GNUC_MINOR__)	/* 4.4 or newer */
 #define _GCC45	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 5 <= __GNUC_MINOR__)	/* 4.5 or newer */
 #define _GCC46	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 6 <= __GNUC_MINOR__)	/* 4.6 or newer */
 #define _GCC47	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 7 <= __GNUC_MINOR__)	/* 4.7 or newer */
 #define _GCC0X	_GCC43	/* basic support for C++0X */

 #if __EDG__
#ifndef _DNK_RENAME
 #define _DNK_RENAME
#endif /* _DNK_RENAME */

 #define getenv_s	_Dnk_getenv_s

 #define iswalnum	_Dnk_iswalnum
 #define iswalpha	_Dnk_iswalpha
 #define iswcntrl	_Dnk_iswcntrl
 #define iswctype	_Dnk_iswctype
 #define iswdigit	_Dnk_iswdigit
 #define iswgraph	_Dnk_iswgraph
 #define iswlower	_Dnk_iswlower
 #define iswprint	_Dnk_iswprint
 #define iswpunct	_Dnk_iswpunct
 #define iswspace	_Dnk_iswspace
 #define iswupper	_Dnk_iswupper
 #define iswxdigit	_Dnk_iswxdigit

 #define localeconv	_Dnk_localeconv
 #define setlocale	_Dnk_setlocale

 #define strtol		_Dnk_strtol

 #define tolower	_Dnk_tolower
 #define toupper	_Dnk_toupper
 #endif /* __EDG__ */

#define _CPPLIB_VER	640

/* You can predefine (on the compile command line, for example):

_ADDED_C_LIB=0 -- to omit declarations for C extensions
_ALT_NS=1 -- to use namespace _Dinkum_std for C++
_ALT_NS=2 -- to use namespace _Dinkum_std for C++ and C
_ALT_NS=3 -- to use namespace _Dinkum_std for C++ and _Dinkum_std_c for C
_C_AS_CPP -- to compile C library as C++
_C_IN_NS -- to define C names in std/_Dinkum_std instead of global namespace
_C99 -- to turn ON C99 library support
_ABRCPP -- to turn ON Abridged C++ dialect (implies _ECPP)
_ECPP -- to turn ON Embedded C++ dialect
_HAS_ARRAY_OVERLOADS=0 -- to disable range testing for array parameters
_HAS_BACKWARD_COMPATIBILITY=1 -- to turn ON layout compatibility with old code
_HAS_CHAR16_T_LANUAGE_SUPPORT=1 -- to turn ON builtin char16_t/char32_t
_HAS_CPP0X=0 -- to turn OFF changes for C++0X (if present)
_HAS_DEBUG_COMPATIBILITY=1 -- to turn ON layout compatibility with debug code
_HAS_DELEGATING_CONSTRUCTORS=1 -- to turn ON use of delegating constructors
_HAS_EXPLICIT_OPERATORS=0 -- to turn OFF explicit keyword applied to operators
_HAS_FIXED_POINT=0 -- to turn OFF fixed-point extensions (if present)
_HAS_IMMUTABLE_SETS=0 -- to PERMIT alterable set elements
_HAS_NEW_SFINAE=1 -- to PERMIT use of template<class = test>
_HAS_NOEXCEPT=1 -- to PERMIT use of noexcept
_HAS_NULLPTR=1 -- to PERMIT use of nullptr_t
_HAS_REF_QUALIFIER=1 -- to PERMIT ref qualifiers
_HAS_SCOPED_ENUM=1 -- to PERMIT scoped enums
_HAS_STRICT_CONFORMANCE=1 -- to disable nonconforming extensions
_HAS_TEMPLATE_ALIAS=1 -- to PERMIT template aliases
_HAS_TEMPLATE_TEMPLATE=1 -- to PERMIT template templates
_HAS_TRADITIONAL_IOSTREAMS=0 -- to omit old iostreams functions
_HAS_TRADITIONAL_ITERATORS=1 -- for vector/string pointer iterators
_HAS_TRADITIONAL_POS_TYPE=1 -- for streampos same as streamoff
_HAS_TRADITIONAL_STL=0 -- to turn OFF old STL functions
_HAS_TR1=0 -- to turn OFF TR1 extensions (if present)
_HAS_TR1_IMPORTS=0 -- to turn OFF importing tr1 names (if present) into tr1
_HAS_VARIADIC_TEMPLATES=0 -- to turn OFF variadic templates (if present)
_NO_EX -- to turn OFF use of try/throw
_NO_LOCALES=1 -- to turn OFF named locales
_NO_MT -- to turn OFF thread synchronization
_NO_NS -- to turn OFF use of namespace declarations
__STDC_WANT_LIB_EXT1__=0 -- to disable C library extension 1
_STL_DB (or _STLP_DEBUG) -- to turn ON iterator/range debugging
_USE_EXISTING_SYSTEM_NAMES=0 -- to disable mappings (_Open to open)
__NO_LONG_LONG -- to define _Longlong as long, not long long

You can change (in this header AND ALL ITS COPIES):

_COMPILER_TLS -- from 0 to 1 if _TLS_QUAL is not nil
_EXFAIL -- from 1 to any nonzero value for EXIT_FAILURE
_FILE_OP_LOCKS -- from 0 to 1 for file atomic locks
_GLOBAL_LOCALE -- from 0 to 1 for shared locales instead of per-thread
_IOSTREAM_OP_LOCKS -- from 0 to 1 for iostream atomic locks
_TLS_QUAL -- from nil to compiler TLS qualifier, such as __declspec(thread)

Include directories needed to compile with Dinkum C:

C -- include/c
C99 -- include/c (define _C99)
Embedded C++ -- include/c include/embedded (define _ECPP)
Abridged C++ -- include/c include/embedded include (define _ABRCPP)
Standard C++ -- include/c include
Standard C++ with export -- include/c include/export include
	(--export --template_dir=lib/export)

Include directories needed to compile with native C:

C -- none
C99 -- N/A
Embedded C++ -- include/embedded (define _ECPP)
Abridged C++ -- include/embedded include (define _ABRCPP)
Standard C++ -- include
Standard C++ with export -- include/export include
	(--export --template_dir=lib/export)
 */


#ifdef __EXT_ANSIC_199901
#define _C99	1
#endif

#if defined(__GNUC__) && (2 <= __GNUC__) && (!__STRICT_ANSI__)
#define _C99 1
#endif

#ifdef _SOFT_FLOAT
 /* no FPU hardware support */
 #define _FPP_TYPE _FPP_NONE
#else 
		/* DETERMINE MACHINE TYPE */

 #if defined(i386) || defined(__i386) \
	|| defined(__i386__) || defined(_M_IX86)	/* Pentium */
  #define _FPP_TYPE	_FPP_X86	/* Pentium FPP */
 #elif defined(_MIPS) || defined(_MIPS_) || defined(_M_MRX000) \
    || defined(__MIPS__)		/* MIPS */
  #define _FPP_TYPE	_FPP_MIPS	/* MIPS FPP */
 #elif defined(__ppc__) || defined(_POWER) || defined(_M_PPC) \
    || defined(__PPC__)	/* PowerPC */
  #define _FPP_TYPE	_FPP_PPC	/* PowerPC FPP */
 #elif (defined(_ARM_) || defined(__ARM__)) && defined(__ARM_ARCH_7A__)	/* ARMv7 */
  #define _FPP_TYPE	_FPP_ARM
 #elif defined(_ARM_) || defined(__ARM__)	/* ARM */
  #define _FPP_TYPE	_FPP_NONE
 #elif defined(_SH4_) || defined(__SH__)	/* SH4 */
  #define _FPP_TYPE	_FPP_SH4	/* Hitachi SH4 FPP */
 #else /* system detector */
#error unknown compilation environment
 #endif /* system detector */
#endif

  #define _HAS_POSIX_C_LIB	1	/* use common Unix conventions */

#ifdef __QNX__
/* setting this will stop static and global definitions having a "= 0". */
#define _UNINITALIZED_IS_ZERO		1

/* set this to 1 to compile in atexit cleanup handlers */
#define _TERMINATION_CLEANUP		0

/* set this to 1 to add built-in support POSIX locales */
#define _ADD_POSIX					1

/* Search for locale file here if the LOCFILE envar is not set */
#define _DEFAULT_LOCFILE	"/usr/share/locale/locale.file"

#endif

 #if !defined(_RSIZE_MAX)
  #define _RSIZE_MAX    ((_Sizet)(-1) >> 1)     /* or sizeof largest object */
 #endif /* !defined(_RSIZE_MAX) */

 #if defined(_HAS_C9X)

 #elif defined(_C99)
  #define _HAS_C9X      1

 #else /* !defined(_HAS_C9X) */
  #define _HAS_C9X      0
 #endif /* !defined(_HAS_C9X) */

 #if !defined(_ECPP) && defined(_ABRCPP)
  #define _ECPP
 #endif /* !defined(_ECPP) && defined(_ABRCPP) */

 #if !defined(_IS_EMBEDDED) && defined(_ECPP)
  #define _IS_EMBEDDED	1	/* 1 for Embedded C++ */
 #endif /* _IS_EMBEDDED */

		/* EXCEPTION CONTROL */
#undef _HAS_EXCEPTIONS			/* @@@ qcc defines this when it shouldn't */
 #ifndef _HAS_EXCEPTIONS
  #ifndef _NO_EX	/* don't simplify */
   #define _HAS_EXCEPTIONS	1	/* 1 for try/throw logic */

  #else	/* _NO_EX */
   #define _HAS_EXCEPTIONS	0
  #endif /* _NO_EX */

 #endif /* _HAS_EXCEPTIONS */

		/* NAMING PROPERTIES */
/* #define _STD_LINKAGE	define C names as extern "C++" */
/* #define _STD_USING	define C names in one of three namespaces */

 #ifndef _HAS_NAMESPACE
  #ifndef _NO_NS	/* don't simplify */
   #define _HAS_NAMESPACE	1	/* 1 for C++ names in std */

  #else	/* _NO_NS */
   #define _HAS_NAMESPACE	0
  #endif /* _NO_NS */

 #endif /* _HAS_NAMESPACE */

 #if !defined(_STD_USING) && defined(__cplusplus) \
	&& (defined(_C_IN_NS) || 1 < _ALT_NS)
  #define _STD_USING	/* *.h headers export C names to global */

 #elif defined(_STD_USING) && !defined(__cplusplus)
  #undef _STD_USING	/* define only for C++ */
 #endif /* !defined(_STD_USING) */

 #if !defined(_HAS_STRICT_LINKAGE) \
	&& (__SUNPRO_CC \
		|| __EDG__ && !defined(__APPLE__) && !defined(_WIN32_C_LIB))
  #define _HAS_STRICT_LINKAGE	1	/* extern "C" in function type */
 #endif /* !defined(_HAS_STRICT_LINKAGE) */

		/* THREAD AND LOCALE CONTROL */
 #define _MULTI_THREAD	1	/* 0 for no thread locks */

#define _GLOBAL_LOCALE	1	/* 0 for per-thread locales, 1 for shared */
#define _FILE_OP_LOCKS	1	/* 0 for no FILE locks, 1 for atomic */
#define _IOSTREAM_OP_LOCKS	1	/* 0 for no iostream locks, 1 for atomic */

		/* THREAD-LOCAL STORAGE */
#define _COMPILER_TLS	0	/* 1 if compiler supports TLS directly */
#define _TLS_QUAL	/* TLS qualifier, such as __declspec(thread), if any */

 #if !defined(_ADDED_C_LIB)
  #define _ADDED_C_LIB	1	/* include declarations for C extensions */
 #endif /* !defined(_ADDED_C_LIB) */

 #if defined(_HAS_TR1)

 #elif !_IS_EMBEDDED && (1310 <= _MSC_VER || __EDG__ || 3 <= __GNUC__)
  #define _HAS_TR1	1	/* enable TR1 */

 #else /* _HAS_TR1 */
  #define _HAS_TR1	0	/* disable TR1 */
 #endif /* _HAS_TR1 */

 #if !defined(_HAS_TR1_DECLARATIONS)
  #define _HAS_TR1_DECLARATIONS	0	/* disable special math functions */
 #endif /* !defined(_HAS_TR1_DECLARATIONS */

 #if !defined(_HAS_TR1_IMPORTS)
  #define _HAS_TR1_IMPORTS	_HAS_TR1
 #endif /* !defined(_HAS_TR1_IMPORTS) */

 #if defined(_HAS_CPP0X)

 #elif _HAS_TR1 && (1400 <= _MSC_VER || __EDG__ || __GNUC__) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103)
  #define _HAS_CPP0X	1	/* enable C++0X changes */

 #if _HAS_CPP0X

 #else /* _HAS_CPP0X */
  #undef _HAS_CPP0X	/* don't ask */
  #define _HAS_CPP0X	0	/* enable C++0X changes */
 #endif /* _HAS_CPP0X */

 #else /* !defined(_HAS_CPP0X) */
  #define _HAS_CPP0X	0	/* disable C++0X changes */
 #endif /* !defined(_HAS_CPP0X) */

 #ifndef _MULTI_THREAD

  #ifdef __CYGWIN__
   #define _MULTI_THREAD	0	/* Cygwin has dummy thread library */

  #else /* __CYGWIN__ */

   #if defined(_NO_MT) || defined(_DEBUG) && 1310 == _MSC_VER
    #define _MULTI_THREAD	0	/* 0 for no thread locks */

   #else /* defined(_NO_MT) || defined(_DEBUG) */
    #define _MULTI_THREAD	1
   #endif /* defined(_NO_MT) || defined(_DEBUG) */

  #endif /* __CYGWIN__ */
 #endif /* _MULTI_THREAD */

 #if defined(_HAS_CHAR16_T_LANGUAGE_SUPPORT)

 #elif _CLANG || _HAS_CPP0X && (_GCC44 || 403 <= __EDG_VERSION__)
  #define _HAS_CHAR16_T_LANGUAGE_SUPPORT	1	/* char16/32_t are keywords */

 #else /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */
  #define _HAS_CHAR16_T_LANGUAGE_SUPPORT	0	/* char16/32_t not keywords */
 #endif /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */

 #if !defined(_HAS_FIXED_POINT)
  #define _HAS_FIXED_POINT	0	/* enable fixed-point extensions */
 #endif /* !defined(_HAS_FIXED_POINT) */

 #if !defined(_HAS_DELEGATING_CONSTRUCTORS)

  #if _HAS_CPP0X && (1800 <= _MSC_VER && !__EDG__ || _CLANG || _GCC47)
   #define _HAS_DELEGATING_CONSTRUCTORS	1	/* enable explicit operators */

  #else /* 1800 <= _MSC_VER */
   #define _HAS_DELEGATING_CONSTRUCTORS	0	/* disable explicit operators */
  #endif /* 1800 <= _MSC_VER */

 #endif /* !defined(_HAS_EXPLICIT_OPERATORS) */

 #if !defined(_HAS_NEW_SFINAE)

  #if 1800 <= _MSC_VER || __EDG__ || _CLANG
   #define _HAS_NEW_SFINAE	1	/* enable template<class = test> */

  #else /* 1800 <= _MSC_VER, etc. */
   #define _HAS_NEW_SFINAE	0	/* disable template<class = test> */
  #endif /* 1800 <= _MSC_VER, etc. */

 #endif /* !defined(_HAS_NEW_SFINAE) */

 #if !defined(_HAS_EXPLICIT_OPERATORS)
  #define _HAS_EXPLICIT_OPERATORS	0	/* disable explicit operators */
 #endif /* !defined(_HAS_EXPLICIT_OPERATORS) */

 #if !defined(_HAS_IMMUTABLE_SETS)
  #define _HAS_IMMUTABLE_SETS	1	/* disallow alterable set elements */
 #endif /* !defined(_HAS_IMMUTABLE_SETS) */

 #if !defined(_HAS_ITERATOR_DEBUGGING) \
	&& (defined(_STL_DB) || defined(_STLP_DEBUG))
  #define _HAS_ITERATOR_DEBUGGING	1	/* enable range checks, etc. */
 #endif /* define _HAS_ITERATOR_DEBUGGING */

 #if !defined(_HAS_ARRAY_OVERLOADS)
  #define _HAS_ARRAY_OVERLOADS	1	/* enable array range checking */
 #endif /* define _HAS_ARRAY_OVERLOADS */

 #if !defined(_HAS_NOEXCEPT)

  #if _HAS_CPP0X && (404 <= __EDG_VERSION__)
   #define _HAS_NOEXCEPT	1

  #else /* _HAS_CPP0X && (404 <= __EDG_VERSION__) */
	/* disabled in gcc due to GCC PR52869 [DR1207] */
   #define _HAS_NOEXCEPT	0
  #endif /* _HAS_CPP0X && (404 <= __EDG_VERSION__) */

 #endif /* !defined(_HAS_NOEXCEPT) */

 #if _HAS_NOEXCEPT == 0 || !defined(__cplusplus)
  #define _NOEXCEPT
  #define _NOEXCEPT_OP(x)

 #else /* _HAS_NOEXCEPT == 0, etc. */
  #define _NOEXCEPT			noexcept
  #define _NOEXCEPT_OP(x)	noexcept(x)
 #endif /* _HAS_NOEXCEPT == 0, etc. */

 #if !defined(_HAS_NULLPTR_T)
  #define _HAS_NULLPTR_T	(_HAS_CPP0X && (_GCC46 || 403 < __EDG_VERSION__))
 #endif /* !defined(_HAS_NULLPTR_T) */

 #if !defined(_HAS_STRICT_CONFORMANCE)
  #define _HAS_STRICT_CONFORMANCE	0	/* enable nonconforming extensions */
 #endif /* !defined(_HAS_STRICT_CONFORMANCE) */

 #if !defined(_HAS_TRADITIONAL_IOSTREAMS)
  #define _HAS_TRADITIONAL_IOSTREAMS	\
	(!_HAS_STRICT_CONFORMANCE)	/* enable old iostreams stuff */
 #endif /* !defined(_HAS_TRADITIONAL_IOSTREAMS) */

 #if !defined(_HAS_TRADITIONAL_ITERATORS)
  #define _HAS_TRADITIONAL_ITERATORS	0	/* don't use pointer iterators */
 #endif /* !defined(_HAS_TRADITIONAL_ITERATORS) */

 #if !defined(_HAS_TRADITIONAL_POS_TYPE)
  #define _HAS_TRADITIONAL_POS_TYPE	0	/* make streampos same as streamoff */
 #endif /* !defined(_HAS_TRADITIONAL_POS_TYPE) */

 #if !defined(_HAS_TRADITIONAL_STL)
  #define _HAS_TRADITIONAL_STL	\
	(!_HAS_STRICT_CONFORMANCE)	/* enable older STL extensions */
 #endif /* !defined(_HAS_TRADITIONAL_STL) */

 #if !defined(_HAS_CONSTEXPR)

 #elif _HAS_CPP0X && (_GCC45 || 405 <= __EDG_VERSION__)
  #define _HAS_CONSTEXPR	1	/* enable constexpr */

 #else /* !defined(_HAS_CONSTEXPR) */
  #define _HAS_CONSTEXPR	0	/* disable constexpr */
 #endif /* !defined(_HAS_CONSTEXPR) */

 #if _HAS_CONSTEXPR
  #define _CONST_DATA	constexpr
  #define _CONST_FUN	constexpr

 #else /* _HAS_CONSTEXPR */
  #define _CONST_DATA	const
  #define _CONST_FUN
 #endif /* _HAS_CONSTEXPR */

 #if defined(_HAS_DECLTYPE)

 #elif _HAS_CPP0X && (1600 <= _MSC_VER || _GCC44 || 403 <= __EDG_VERSION__)
  #define _HAS_DECLTYPE	1	/* enable decltype */

 #else /* _HAS_DECLTYPE */
  #define _HAS_DECLTYPE	0	/* disable decltype */
 #endif /* _HAS_DECLTYPE */

 #if defined(_HAS_FUNCTION_DELETE)

 #elif _HAS_CPP0X && _GCC44 && !defined(__clang__)
  #define _HAS_FUNCTION_DELETE	1	/* enable =delete/default */

 #else /* _HAS_FUNCTION_DELETE */
  #define _HAS_FUNCTION_DELETE	0	/* disable =delete/default */
 #endif /* _HAS_FUNCTION_DELETE */

 #if defined(_HAS_INITIALIZER_LISTS)

 #elif _HAS_CPP0X
  #define _HAS_INITIALIZER_LISTS	1	/* enable initializer_list */

 #else /* _HAS_INITIALIZER_LISTS */
  #define _HAS_INITIALIZER_LISTS	0	/* disable initializer_list */
 #endif /* _HAS_INITIALIZER_LISTS */

 #if defined(_HAS_REF_QUALIFIER)

 #else /* _HAS_REF_QUALIFIER */
  #define _HAS_REF_QUALIFIER	0	/* disable reference qualifiers */
 #endif /* _HAS_REF_QUALIFIER */

 #if defined(_HAS_RVALUE_REFERENCES)

 #elif _HAS_CPP0X && (1600 <= _MSC_VER || 400 <= __EDG_VERSION__ || _GCC0X)
  #define _HAS_RVALUE_REFERENCES	1	/* enable rvalue references */

 #else /* _HAS_RVALUE_REFERENCES */
  #define _HAS_RVALUE_REFERENCES	0	/* disable rvalue references */
 #endif /* _HAS_RVALUE_REFERENCES */

 #if defined(_HAS_NEW_RVALUE_REFERENCES)

 #elif _HAS_RVALUE_REFERENCES \
	&& (1600 <= _MSC_VER || 400 <= __EDG_VERSION__ || _GCC45)
  #define _HAS_NEW_RVALUE_REFERENCES	1	/* enable new style rvalues */

 #else /* 400 <= __EDG_VERSION__ */
  #define _HAS_NEW_RVALUE_REFERENCES	0	/* disable new style rvalues */
 #endif /* defined(_HAS_NEW_RVALUE_REFERENCES) */

 #if _HAS_RVALUE_REFERENCES
  #define _REFREF	&&
  #define _LVALREF	&&
  #define _VALREF	&&

 #else /* _HAS_RVALUE_REFERENCES */
  #define _REFREF	const&
  #define _LVALREF	&
  #define _VALREF
 #endif /* _HAS_RVALUE_REFERENCES */

 #if defined(_HAS_SCOPED_ENUM)

 #elif _HAS_CPP0X && (_GCC44 || 403 <= __EDG_VERSION__)
  #define _HAS_SCOPED_ENUM	1	/* enable scoped enums */

 #else /* _HAS_SCOPED_ENUM */
  #define _HAS_SCOPED_ENUM	0	/* disable scoped enums */
 #endif /* _HAS_SCOPED_ENUM */

 #if defined(_HAS_STATIC_ASSERT)

 #elif _HAS_CPP0X && (1600 <= _MSC_VER || _GCC0X || 403 <= __EDG_VERSION__)
  #define _HAS_STATIC_ASSERT	1	/* enable static_assert */

 #else /* _HAS_STATIC_ASSERT */
  #define _HAS_STATIC_ASSERT	0	/* disable static_assert */
 #endif /* _HAS_STATIC_ASSERT */

 #if _HAS_STATIC_ASSERT
  #define _STATIC_ASSERT2(test, mesg)	\
	static_assert(test, mesg)

 #else /* _HAS_STATIC_ASSERT */
  #define _STATIC_ASSERT2(test, mesg)	typedef int _Dummy_static_assert
 #endif /* _HAS_STATIC_ASSERT */

 #if defined(_HAS_TEMPLATE_ALIAS)

 #elif _HAS_CPP0X && (_GCC47 || 402 <= __EDG_VERSION__)
  #define _HAS_TEMPLATE_ALIAS	1	/* enable template aliases */
  #define _OTHER

 #else /* _HAS_TEMPLATE_ALIAS */
  #define _HAS_TEMPLATE_ALIAS	0	/* disable template aliases */
  #define _OTHER	:: other	/* [sic] */
 #endif /* _HAS_TEMPLATE_ALIAS */

 #if defined(_HAS_TEMPLATE_TEMPLATE)

 #elif _HAS_CPP0X && _GCC44
  #define _HAS_TEMPLATE_TEMPLATE	1	/* enable template templates */

 #else /* _HAS_TEMPLATE_TEMPLATE */
  #define _HAS_TEMPLATE_TEMPLATE	0	/* disable template templates */
 #endif /* _HAS_TEMPLATE_TEMPLATE */

 #if defined(_HAS_VARIADIC_TEMPLATES)

 #elif _HAS_CPP0X && (_GCC0X || 403 <= __EDG_VERSION__)
  #define _HAS_VARIADIC_TEMPLATES	1	/* enable variadics */

 #else /* _HAS_VARIADIC_TEMPLATES */
  #define _HAS_VARIADIC_TEMPLATES	0	/* disable variadics */
 #endif /* _HAS_VARIADIC_TEMPLATES */

 #if _HAS_EXPLICIT_OPERATORS
  #define _EXP_OP	explicit

 #else /* _HAS_EXPLICIT_OPERATORS */
  #define _EXP_OP
 #endif /* _HAS_EXPLICIT_OPERATORS */

 #if !defined(_USE_EXISTING_SYSTEM_NAMES)
  #define _USE_EXISTING_SYSTEM_NAMES	1	/* _Open => open, etc. */
 #endif /* !defined(_USE_EXISTING_SYSTEM_NAMES) */

 #if __STDC_WANT_SAFER_LIB__
  #define __STDC_SAFER_LIB__	200510L
 #endif /* __STDC_WANT_SAFER_LIB__ */

		/* NAMESPACE CONTROL */

 #if defined(__cplusplus)

 #if _HAS_NAMESPACE
namespace std {}
 #if defined(_C_AS_CPP)
  #define _NO_CPP_INLINES	/* just for compiling C library as C++ */
 #endif /* _C_AS_CPP */

 #if 0 < _ALT_NS

  #if defined(_C_AS_CPP)	/* define library in _Dinkum_std */
   #define _STD_BEGIN	namespace _Dinkum_std {_C_LIB_DECL
   #define _STD_END		_END_C_LIB_DECL }

  #else /* _C_AS_CPP */
   #define _STD_BEGIN	namespace _Dinkum_std {
   #define _STD_END		}
  #endif /* _C_AS_CPP */

  #if _ALT_NS == 1	/* define C library in global namespace */
    #define _C_STD_BEGIN
    #define _C_STD_END
    #define _CSTD		::
    #define _STD			::_Dinkum_std::

  #elif _ALT_NS == 2	/* define both C and C++ in namespace _Dinkum_std */
    #define _C_STD_BEGIN	namespace _Dinkum_std {
    #define _C_STD_END	}
    #define _CSTD		::_Dinkum_std::
    #define _STD			::_Dinkum_std::

  #else	/* define C in namespace _Dinkum_std_c and C++ in _Dinkum_std */
    #define _C_STD_BEGIN	namespace _Dinkum_std_c {
    #define _C_STD_END	}
    #define _CSTD		::_Dinkum_std_c::
    #define _STD			::_Dinkum_std::
  #endif /* _ALT_NS */
namespace _Dinkum_std {}
namespace _Dinkum_std_c {}
namespace std {
	using namespace _Dinkum_std;
	using namespace _Dinkum_std_c;
	}
using namespace _Dinkum_std_c;

 #elif defined(_STD_USING)

  #if defined(_C_AS_CPP)	/* define library in std */
   #define _STD_BEGIN	namespace std {_C_LIB_DECL
   #define _STD_END		_END_C_LIB_DECL }

  #else /* _C_AS_CPP */
   #define _STD_BEGIN	namespace std {
   #define _STD_END		}
  #endif /* _C_AS_CPP */

   #define _C_STD_BEGIN	namespace std {
   #define _C_STD_END	}
   #define _CSTD		::std::
   #define _STD			::std::

 #else /* _ALT_NS == 0 && !defined(_STD_USING) */

  #if defined(_C_AS_CPP)	/* define C++ library in std, C in global */
   #define _STD_BEGIN	_C_LIB_DECL
   #define _STD_END		_END_C_LIB_DECL

  #else /* _C_AS_CPP */
   #define _STD_BEGIN	namespace std {
   #define _STD_END		}
  #endif /* _C_AS_CPP */

   #define _C_STD_BEGIN
   #define _C_STD_END
   #define _CSTD		::
   #define _STD			::std::
 #endif /* _ALT_NS etc. */

  #define _X_STD_BEGIN	namespace std {
  #define _X_STD_END	}
  #define _XSTD			::std::

  #if defined(_STD_USING) && _ALT_NS < 3
   #undef _GLOBAL_USING		/* C names in std namespace */

  #elif !defined(_MSC_VER) || 1300 <= _MSC_VER
   #define _GLOBAL_USING	1	/* c* headers import C names to std */
  #endif /* defined(_STD_USING) */

  #if defined(_STD_LINKAGE)
   #define _C_LIB_DECL		extern "C++" {	/* C has extern "C++" linkage */
  #else /* defined(_STD_LINKAGE) */
   #define _C_LIB_DECL		extern "C" {	/* C has extern "C" linkage */
  #endif /* defined(_STD_LINKAGE) */
  #define _END_C_LIB_DECL	}
  #define _EXTERN_C			extern "C" {
  #define _END_EXTERN_C		}

 #else /* _HAS_NAMESPACE */
  #define _STD_BEGIN
  #define _STD_END
  #define _STD	::

  #define _X_STD_BEGIN
  #define _X_STD_END
  #define _XSTD	::

  #define _C_STD_BEGIN
  #define _C_STD_END
  #define _CSTD	::

  #define _C_LIB_DECL		extern "C" {
  #define _END_C_LIB_DECL	}
  #define _EXTERN_C			extern "C" {
  #define _END_EXTERN_C		}
 #endif /* _HAS_NAMESPACE */

 #ifndef _NO_LOCALES
  #define _NO_LOCALES	0	/* define as 1 to disable named locales */
 #endif /* _NO_LOCALES */

 #else /* __cplusplus */
  #define _STD_BEGIN
  #define _STD_END
  #define _STD

  #define _X_STD_BEGIN
  #define _X_STD_END
  #define _XSTD

  #define _C_STD_BEGIN
  #define _C_STD_END
  #define _CSTD

  #define _C_LIB_DECL
  #define _END_C_LIB_DECL
  #define _EXTERN_C
  #define _END_EXTERN_C
 #endif /* __cplusplus */

 #ifdef __cplusplus
_STD_BEGIN
typedef bool _Bool;
_STD_END
 #endif /* __cplusplus */

 #ifndef _HAS_OPENCL
  #define _HAS_OPENCL	0
 #endif /* _HAS_OPENCL */

#define _FINVERT(x)	(FLIT(1.0) / (x))
#define _FDIV(x, y)	((x) / (y))

 #if defined(__OXILI_CLRUNTIME)	/* compiler test */
 typedef char *va_list;	/* Oxili does not allow variable arguments */

#define _PASTE(a, b)	__cl__internal__##a##b
#define _STATIC_CONST	static const \
	__attribute__((address_space(2)))
#define _EXTERN_CONST	/* extern */ const \
	__attribute__((address_space(2)))
#define _EXTERN_CONST_DECL	extern const \
	__attribute__((address_space(2)))
#define _EXTERN_CONST_DEF	/* extern */ const \
	__attribute__((address_space(2)))

void *__attribute__((overloadable)) __qcom_memcpy_DW(void *dest,
	const __attribute__((address_space(2))) void *src, int num);
void *__attribute__((overloadable)) __qcom_memcpy_DW(void *dest,
	const void *src, int num);

 #else /* defined(__OXILI_CLRUNTIME) */
#ifndef __QNXNTO__
#include <stdarg.h>
#endif

#define _PASTE(a, b)	a##b
#define _STATIC_CONST	static const

  #if !defined(_EXTERN_CONST)
#define _EXTERN_CONST	/* extern */ const
#define _EXTERN_CONST_DECL	extern const

   #if defined(__cplusplus)
#define _EXTERN_CONST_DEF	extern const

   #else /* defined(__cplusplus) */
#define _EXTERN_CONST_DEF	const
   #endif /* defined(__cplusplus) */

  #endif /* defined(_EXTERN_CONST) */
 #endif /* defined(__OXILI_CLRUNTIME) */

		/* VC++ COMPILER PARAMETERS */
#define _CDECL
#define _THROW_N(x, y)	_THROW_NCEE(x, y)

 #if defined(_WIN32_C_LIB)
  #ifndef _VA_LIST_DEFINED

   #if defined(__BORLANDC__)

   #elif defined(_M_ALPHA)
typedef struct
	{	/* define va_list for Alpha */
	char *a0;
	int offset;
	} va_list;

   #else /* defined(_M_ALPHA) */
typedef char *va_list;
   #endif /* defined(_M_ALPHA) */

   #define _VA_LIST_DEFINED
  #endif /* _VA_LIST_DEFINED */

 #endif /* defined(_WIN32_C_LIB) */

 #ifdef __NO_LONG_LONG

 #elif defined(_MSC_VER)
  #define _LONGLONG	__int64
  #define _ULONGLONG	unsigned __int64
  #define _LLONG_MAX	0x7fffffffffffffff
  #define _ULLONG_MAX	0xffffffffffffffff

 #else /* defined(__NO_LONG_LONG) && !defined (_MSC_VER) */
  #define _LONGLONG	long long
  #define _ULONGLONG	unsigned long long
  #define _LLONG_MAX	0x7fffffffffffffffLL
  #define _ULLONG_MAX	0xffffffffffffffffULL
 #endif /* __NO_LONG_LONG */

		/* MAKE MINGW LOOK LIKE WIN32 HEREAFTER */

 #if defined(__MINGW32__) || defined(__CYGWIN__)
  #define _WIN32_C_LIB	1
 #endif /* defined(__MINGW32__) etc. */

 #if _WIN32_C_LIB && !defined(__BORLANDC__)
  #undef _HAS_POSIX_C_LIB

  #if !defined(_SIZE_T) && !defined(_SIZET) \
	&& !defined(_BSD_SIZE_T_DEFINED_) \
	&& !defined(_SIZE_T_DEFINED)
   #define _SIZE_T
   #define _SIZET
   #define _BSD_SIZE_T_DEFINED_
   #define _STD_USING_SIZE_T
   #define _SIZE_T_DEFINED

typedef _Sizet size_t;

   #ifdef __cplusplus
namespace _Dinkum_std {
	using ::size_t;
	}
namespace _Dinkum_std_c {
	using ::size_t;
	}
   #endif /* __cplusplus */

  #endif /* !defined(_SIZE_T) etc. */

  #if !defined(_WCHAR_T_DEFINED)
   #define _WCHAR_T_DEFINED
   #define _WCHAR_T_
   #undef __need_wchar_t

   #ifndef __cplusplus
typedef unsigned short wchar_t;
   #endif /* __cplusplus */

  #endif /* !defined(_WCHAR_T) etc. */
 #endif /* _WIN32_C_LIB */

		/* FLOATING-POINT PROPERTIES */
#define _DBIAS	0x3fe	/* IEEE format double and float */
#define _DOFF	4
#define _FBIAS	0x7e
#define _FOFF	7

		/* INTEGER PROPERTIES */
#define _BITS_BYTE	8
#define _C2			1	/* 0 if not 2's complement */
#define _MBMAX		8	/* MB_LEN_MAX */
#define _ILONG		1	/* 0 if 16-bit int */

 #if defined(__s390__) || defined(__CHAR_UNSIGNED__) \
	|| defined(_CHAR_UNSIGNED)
  #define _CSIGN	0	/* 0 if char is not signed */

 #else /* defined(__s390__) etc. */
  #define _CSIGN	1
 #endif /* defined(__s390__) etc. */

#define _MAX_EXP_DIG	8	/* for parsing numerics */
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	48

 #if _HAS_TR1

 #ifdef __cplusplus
_STD_BEGIN
namespace tr1 { // TR1 ADDITIONS
using ::_Longlong;
using ::_ULonglong;
}       // namespace tr1
_STD_END
 #endif /* __cplusplus */

 #endif /* _HAS_TR1 */

                /* wchar_t AND wint_t PROPERTIES */

 #if defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) \
        || defined (_MSL_WCHAR_T_TYPE)
  #define _WCHART
 #endif /* defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) */

 #if defined(_WINT_T)
  #define _WINTT
 #endif /* _WINT_T */

 #ifdef __cplusplus
  #define _WCHART
typedef wchar_t _Wchart;
typedef wchar_t _Wintt;
 #endif /* __cplusplus */

_C_STD_BEGIN
		/* stdlib PROPERTIES */
#define _EXFAIL	1	/* EXIT_FAILURE */

		/* stdio PROPERTIES */
#define _FNAMAX	260
#define _FOPMAX	20
#define _TNAMAX	16

  #define _FD_NO(str) ((str)->_Handle)
 #define _FD_VALID(fd)	(0 <= (fd))	/* fd is signed integer */
 #define _FD_INVALID	(-1)
 #define _SYSCH(x)	x

#ifndef _SYSCH_T
typedef char _Sysch_t;
#define _SYSCH_T
#endif

		/* STORAGE ALIGNMENT PROPERTIES */

 #if defined(_LP64) || defined(__x86_64)	/* compiler test */
  #define _MEMBND	4U /* 16-byte boundaries (2^^4) */

 #else /* defined(_LP64) etc. */
  #define _MEMBND	3U /* eight-byte boundaries (2^^3) */
 #endif /* defined(_LP64) etc. */

		/* time PROPERTIES */
#define _CPS	1000
#define _TBIAS	((70 * 365LU + 17) * 86400)
_C_STD_END

		/* uchar PROPERTIES */

 #if !defined(_CHAR16T) && defined(__cplusplus)
  #define _CHAR16T

 #if !_HAS_CHAR16_T_LANGUAGE_SUPPORT	// sic
typedef unsigned short char16_t;
typedef unsigned int char32_t;
 #endif /* !_HAS_CHAR16_T_LANGUAGE_SUPPORT */

 #endif /* !defined(_CHAR16T) etc. */

		/* MULTITHREAD PROPERTIES */

 #if _MULTI_THREAD
 #define _BEGIN_LOCK(kind)	{_STD _Lockit _Lock(kind);
 #define _END_LOCK()		}

_EXTERN_C
void _Locksyslock(int);
void _Unlocksyslock(int);
_END_EXTERN_C

 #else /* _MULTI_THREAD */
 #define _BEGIN_LOCK(kind)	{
 #define _END_LOCK()		}

  #define _Locksyslock(x)	(void)0
  #define _Unlocksyslock(x)	(void)0
 #endif /* _MULTI_THREAD */

		/* LOCK MACROS */
 #define _LOCK_LOCALE	0
 #define _LOCK_MALLOC	1
 #define _LOCK_STREAM	2
 #define _LOCK_DEBUG	3
 #define _MAX_LOCK		4	/* one more than highest lock number */

 #if _IOSTREAM_OP_LOCKS
  #define _MAYBE_LOCK

 #else /* _IOSTREAM_OP_LOCKS */
  #define _MAYBE_LOCK	\
	if (_Locktype == _LOCK_MALLOC || _Locktype == _LOCK_DEBUG)
 #endif /* _IOSTREAM_OP_LOCKS */

 #ifdef __cplusplus
_STD_BEGIN
enum _Uninitialized
	{	// tag for suppressing initialization
	_Noinit
	};

extern "C++" {	// in case of _C_AS_CPP
		// CLASS _Lockit
class _Lockit
	{	// lock while object in existence -- MUST NEST
public:
  #if !_MULTI_THREAD
	_Lockit()
		{	// do nothing
		}

	explicit _Lockit(int)
		{	// do nothing
		}

	~_Lockit() _NOEXCEPT
		{	// do nothing
		}

  #else /* !_MULTI_THREAD */
	_Lockit()
		: _Locktype(_LOCK_MALLOC)
		{	// set default lock
		_MAYBE_LOCK
			_Locksyslock(_Locktype);
		}

	explicit _Lockit(int _Kind)
		: _Locktype(_Kind)
		{	// set the lock
		_MAYBE_LOCK
			_Locksyslock(_Locktype);
		}

	~_Lockit() _NOEXCEPT
		{	// clear the lock
		_MAYBE_LOCK
			_Unlocksyslock(_Locktype);
		}
  #endif /* _MULTI_THREAD */

//private:
	_Lockit(const _Lockit&);			// not defined
	_Lockit& operator=(const _Lockit&);	// not defined

private:
	int _Locktype;
	};

  #if !_MULTI_THREAD || !_IOSTREAM_OP_LOCKS
class _Mutex
	{	// lock under program control
public:
	_Mutex(_Uninitialized)
	    {	// do nothing
	    }

	_Mutex()
	    {	// do nothing
	    }

	void _Lock()
		{	// do nothing
		}

	void _Unlock()
		{	// do nothing
		}
	};

  #else /* !_MULTI_THREAD || !_IOSTREAM_OP_LOCKS */
class _Mutex
	{	// lock under program control
public:
	_Mutex(_Uninitialized)
	    {	// do nothing
	    }

	_Mutex();
	~_Mutex() _NOEXCEPT;
	void _Lock();
	void _Unlock();

private:
	_Mutex(const _Mutex&);				// not defined
	_Mutex& operator=(const _Mutex&);	// not defined
	void *_Mtx;
	};
  #endif /* !_MULTI_THREAD || !_IOSTREAM_OP_LOCKS */
}	// extern "C++"
_STD_END
 #endif /* __cplusplus */

  #define _NO_RET(fun)	void fun

#ifndef _NO_RETURN

 #if _HAS_EXCEPTIONS

 #if 0 < __GNUC__
  #define _NO_RETURN(fun)	void fun __attribute__((__noreturn__))

 #else /* 0 < __GNUC__ */
  #define _NO_RETURN(fun)	void fun
 #endif /* 0 < __GNUC__ */

 #else /* _HAS_EXCEPTIONS */

 #if 0 < __GNUC__ && !defined(__cplusplus)
  #define _NO_RETURN(fun)	void fun __attribute__((__noreturn__))

 #else /* 0 < __GNUC__ */
  #define _NO_RETURN(fun)	void fun
 #endif /* 0 < __GNUC__ */
 #endif /* _HAS_EXCEPTIONS */

#endif /* _NO_RETURN */

  #define _NO_RETURN_MEMBER(fun)	void fun

#define _STRINGIZEX(x)	#x
#define _STRINGIZE(x)	_STRINGIZEX(x)

 #if _HAS_CPP0X
  #define _POINTER_TO(x)	_STD pointer_traits<pointer>::pointer_to(x)

 #else /* _HAS_CPP0X */
  #define _POINTER_TO(x)	&(x)
 #endif /* _HAS_CPP0X */

#endif /* _YVALS */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/c/public/yvals.h $ $Rev: 736604 $")
#endif
