//
// file:			endian.hpp
// path:			include/cpputils/endian.hpp
// created on:		2021 Mar 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_ENDIAN_H
#define INCLUDE_CPPUTILS_ENDIAN_H

#include "cpputils_internal_header.h"


//#if defined(__GCC__)
#include <endian.h>
#define CPPUTILS_ENDIAN_COMPILETIME		1
//#endif

#ifndef CPPUTILS_ENDIAN_COMPILETIME
#endif


#endif  // #ifndef INCLUDE_CPPUTILS_ENDIAN_H
