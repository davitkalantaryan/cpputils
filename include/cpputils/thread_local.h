//
// file:			thread_local.h
// path:			include/cpputils/thread_local.h
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_THREAD_LOCAL_H
#define INCLUDE_CPPUTILS_THREAD_LOCAL_H

#include <cpputils/internal_header.h>

#ifndef CPPUTILS_THREAD_LOCAL
#define CPPUTILS_THREAD_LOCAL
#endif

CPPUTILS_BEGIN_C

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
typedef DWORD			cpputils_thread_key_t;
#define cpputils_thread_getspecific		CPPUTILS_GLOBAL FlsGetValue
#define cpputils_thread_setspecific		CPPUTILS_GLOBAL FlsSetValue
#define cpputils_thread_key_delete		CPPUTILS_GLOBAL FlsFree
#define	CPPUTILS_TLS_OUT_OF_INDEXES		FLS_OUT_OF_INDEXES
#else
#include <pthread.h>
typedef pthread_key_t	cpputils_thread_key_t;
#define cpputils_thread_getspecific		CPPUTILS_GLOBAL pthread_getspecific
#define cpputils_thread_setspecific		CPPUTILS_GLOBAL pthread_setspecific
#define cpputils_thread_key_delete		CPPUTILS_GLOBAL pthread_key_delete
#define	CPPUTILS_TLS_OUT_OF_INDEXES		CPPUTILS_STATIC_CAST(cpputils_thread_key_t,-1)
#endif

extern CPPUTILS_EXPORT int   cpputils_thread_key_create(cpputils_thread_key_t*key, void (*destructor)(void*));

CPPUTILS_END_C

#endif  // #ifndef INCLUDE_CPPUTILS_THREAD_LOCAL_H
