//
// file:            disable_compiler_warnings.h
// path:			include/cpputils/disable_compiler_warnings.h
// created on:		2021 Nov 15
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_DISABLE_COMPILER_WARNINGS_H
#define CPPUTILS_INCLUDE_DISABLE_COMPILER_WARNINGS_H

#include <cpputils/internal_header.h>

#if defined(_MSC_VER)

#pragma warning(disable:4710)
#pragma warning(disable:4711)
#if (_MSC_VER>=1929) && (_MSC_FULL_VER>192930100)
#pragma warning(disable:5246)
#endif

#elif defined(__GNUC__) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


#endif  // #ifndef CPPUTILS_INCLUDE_DISABLE_COMPILER_WARNINGS_H
