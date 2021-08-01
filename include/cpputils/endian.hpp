//
// file:			endian.hpp
// path:			include/cpputils/endian.hpp
// created on:		2021 Mar 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_ENDIAN_H
#define INCLUDE_CPPUTILS_ENDIAN_H

#include "cpputils_internal_header.h"
#include <stdbool.h>
#include <stdint.h>


//#if defined(__GCC__)
#ifndef _MSC_VER
#include <endian.h>
#define CPPUTILS_ENDIAN_COMPILETIME		1
#endif

#ifndef CPPUTILS_ENDIAN_COMPILETIME
CPPUTILS_BEGIN_C

CPPUTILS_EXPORT uint64_t htole64(uint64_t host_64bits);
CPPUTILS_EXPORT uint64_t le64toh(uint64_t little_endian_64bits);

CPPUTILS_END_C
#endif  // #ifndef CPPUTILS_ENDIAN_COMPILETIME


#endif  // #ifndef INCLUDE_CPPUTILS_ENDIAN_H
