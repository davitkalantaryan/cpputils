//
// file:			cpputils_internal_header.h
// path:			include/cpputils_internal_header.h
// created on:		2021 Mar 07
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_INTERNAL_HEADER_H
#define INCLUDE_CPPUTILS_INTERNAL_HEADER_H

#include <stddef.h>

#ifdef _MSC_VER
	#define CPPUTILS_UNREACHABLE_CODE(_code)
	//#if _MSC_FULL_VER
	#if (_MSC_VER>1900) // 1900 is VS2015
		#pragma warning (disable:5045)
	#endif
	// assignment within conditional expression (https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4706?view=msvc-160)
	#pragma warning (disable:4706) 
	// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-160
	#pragma warning (disable:4711)
	// Function not inlined althou defined to be inline. 
	// this can happen also with library functions, so this should be disabled
	// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-160
	#pragma warning (disable:4710)
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR
	#if defined(_MSVC_LANG) && (_MSVC_LANG>=201100L)
		#define CPPUTILS_CPP_11_DEFINED		1
	#endif
	#if defined(_MSVC_LANG) && (_MSVC_LANG>=201400L)
		#define CPPUTILS_CPP_14_DEFINED		1
	#endif
	#if defined(_MSVC_LANG) && (_MSVC_LANG>=201700L)
		#define CPPUTILS_CPP_17_DEFINED		1
	#endif
    #define CPPUTILS_DLL_PUBLIC		__declspec(dllexport)
    #define CPPUTILS_DLL_PRIVATE
    #define CPPUTILS_IMPORT_FROM_DLL	__declspec(dllimport)
	#define CPPUTILS_THREAD_LOCAL		__declspec(thread)
#elif defined(__GNUC__) || defined(__clang__)
	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
	#if defined(__cplusplus) && (__cplusplus>=201100L)
		#define CPPUTILS_CPP_11_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201400L)
		#define CPPUTILS_CPP_14_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201700L)
		#define CPPUTILS_CPP_17_DEFINED		1
	#endif
    //#define CPPUTILS_DLL_PUBLIC		__attribute__((visibility("default")))
    #define CPPUTILS_DLL_PUBLIC
    #define CPPUTILS_DLL_PRIVATE		__attribute__((visibility("hidden")))
    #define CPPUTILS_IMPORT_FROM_DLL
	#define CPPUTILS_THREAD_LOCAL		__thread
#elif defined(__CYGWIN__)
	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
	#if defined(__cplusplus) && (__cplusplus>=201100L)
		#define CPPUTILS_CPP_11_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201400L)
		#define CPPUTILS_CPP_14_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201700L)
		#define CPPUTILS_CPP_17_DEFINED		1
	#endif
    #define CPPUTILS_DLL_PUBLIC		__attribute__((dllexport))
    #define CPPUTILS_DLL_PRIVATE
    #define CPPUTILS_IMPORT_FROM_DLL	__attribute__((dllimport))
#elif defined(__MINGW64__) || defined(__MINGW32__)
	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
	#if defined(__cplusplus) && (__cplusplus>=201100L)
		#define CPPUTILS_CPP_11_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201400L)
		#define CPPUTILS_CPP_14_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201700L)
		#define CPPUTILS_CPP_17_DEFINED		1
	#endif
    #define CPPUTILS_DLL_PUBLIC		_declspec(dllexport)
    #define CPPUTILS_DLL_PRIVATE
    #define CPPUTILS_IMPORT_FROM_DLL	_declspec(dllimport)
#elif defined(__SUNPRO_CC)
	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	// #define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ; // ???
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR
	#if defined(__cplusplus) && (__cplusplus>=201100L)
		#define CPPUTILS_CPP_11_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201400L)
		#define CPPUTILS_CPP_14_DEFINED		1
	#endif
	#if defined(__cplusplus) && (__cplusplus>=201700L)
		#define CPPUTILS_CPP_17_DEFINED		1
	#endif
    #define CPPUTILS_DLL_PUBLIC
    #define CPPUTILS_DLL_PRIVATE		__hidden
    #define CPPUTILS_IMPORT_FROM_DLL
#endif  // #ifdef _MSC_VER

#if defined(CPPUTILS_COMPILING_SHARED_LIB)
    #define CPPUTILS_EXPORT CPPUTILS_DLL_PUBLIC
#elif defined(CPPUTILS_USING_STATIC_LIB_OR_OBJECTS)
    #define CPPUTILS_EXPORT
#else
    #define CPPUTILS_EXPORT CPPUTILS_IMPORT_FROM_DLL
#endif

#ifdef __cplusplus
#define CPPUTILS_STATIC_CAST(_type,_data)	static_cast<_type>(_data)
#define CPPUTILS_GLOBAL	   ::
#define CPPUTILS_BEGIN_C   extern "C" {
#define CPPUTILS_END_C     }
#define CPPUTILS_EXTERN_C  extern "C"
#else
#define CPPUTILS_STATIC_CAST(_type,_data)	((_type)(_data))
#define CPPUTILS_GLOBAL
#define CPPUTILS_BEGIN_C
#define CPPUTILS_END_C
#define CPPUTILS_EXTERN_C
#endif


#ifdef CPPUTILS_CPP_17_DEFINED
#define CPPUTILS_FALLTHROUGH	[[fallthrough]] ;
#else
#define CPPUTILS_FALLTHROUGH	CPPUTILS_BEFORE_CPP_17_FALL_THR 
//#define CPPUTILS_FALLTHROUGH	
#endif

#ifdef CPPUTILS_CPP_11_DEFINED
#define CPPUTILS_STD_MOVE_DEFINED   1
#define CPPUTILS_NOEXCEPT	noexcept
#define CPPUTILS_NULL		nullptr
#define CPPUTILS_OVERRIDE	override
#else
#define CPPUTILS_NOEXCEPT	throw()
#define CPPUTILS_NULL		NULL 
#define CPPUTILS_OVERRIDE
#endif

#ifdef __cplusplus
#define CPPUTILS_REGISTER
#else
#define CPPUTILS_REGISTER	register
#endif


#endif  // #ifndef INCLUDE_CPPUTILS_INTERNAL_HEADER_H
