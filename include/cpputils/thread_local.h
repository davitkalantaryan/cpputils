//
// file:			thread_local.h
// path:			include/cpputils/thread_local.h
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_THREAD_LOCAL_H
#define INCLUDE_CPPUTILS_THREAD_LOCAL_H

#include <cpputils/export_symbols.h>

#ifndef CPPUTILS_THREAD_LOCAL
#define CPPUTILS_THREAD_LOCAL
#endif

CINTERNAL_BEGIN_C

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
typedef DWORD			cpputils_thread_key_t;
#define cpputils_thread_getspecific		CINTERNAL_GLOBAL FlsGetValue
#define cpputils_thread_setspecific		CINTERNAL_GLOBAL FlsSetValue
#define cpputils_thread_key_delete		CINTERNAL_GLOBAL FlsFree
#define	CPPUTILS_TLS_OUT_OF_INDEXES		FLS_OUT_OF_INDEXES
#else
#include <pthread.h>
typedef pthread_key_t	cpputils_thread_key_t;
#define cpputils_thread_getspecific		CINTERNAL_GLOBAL pthread_getspecific
#define cpputils_thread_setspecific		CINTERNAL_GLOBAL pthread_setspecific
#define cpputils_thread_key_delete		CINTERNAL_GLOBAL pthread_key_delete
#define	CPPUTILS_TLS_OUT_OF_INDEXES		CINTERNAL_STATIC_CAST(cpputils_thread_key_t,-1)
#endif

extern CPPUTILS_EXPORT int   cpputils_thread_key_create(cpputils_thread_key_t*key, void (*destructor)(void*));

CINTERNAL_END_C

#endif  // #ifndef INCLUDE_CPPUTILS_THREAD_LOCAL_H
