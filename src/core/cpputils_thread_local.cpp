//
// file:			cpputils_thread_local.cpp
// path:			src/core/cpputils_thread_local.cpp
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/thread_local.h>


CPPUTILS_BEGIN_C

CPPUTILS_EXPORT int cpputils_thread_key_create(cpputils_thread_key_t* a_key, void (*a_destructor)(void*))
{
#ifdef _WIN32
	*a_key = FlsAlloc(a_destructor);
	if((*a_key)==FLS_OUT_OF_INDEXES){
		return static_cast<int>(GetLastError());
	}
	return 0;
#else
	return pthread_key_create(a_key,a_destructor);
#endif
}


CPPUTILS_END_C
