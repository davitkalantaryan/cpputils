//
// file:            disable_compiler_warnings.h
// path:			include/cpputils/disable_compiler_warnings.h
// created on:		2021 Nov 15
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_DISABLE_COMPILER_WARNINGS_H
#define CPPUTILS_INCLUDE_DISABLE_COMPILER_WARNINGS_H

#include <cpputils_internal_header.h>

#if defined(_MSC_VER)

#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:5246)

#elif defined(__GNUC__) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


#endif  // #ifndef CPPUTILS_INCLUDE_DISABLE_COMPILER_WARNINGS_H
