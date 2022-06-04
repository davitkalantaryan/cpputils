//
// file:			enums.hpp
// path:			include/cpputils/enums.hpp
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// warning:			for now CPPUTILS_ENUM01 works only if we have enumerated 0,1,...
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP

#include <cpputils/internal_header.h>
#include <cpputils/enums/fast.hpp>
//#include <cpputils/enums/full.hpp>
//#include <cpputils/enums/fullslow.hpp>


#define CPPUTILS_ENUM_RAW	CPPUTILS_ENUM_FAST_RAW
#define CPPUTILS_ENUM		CPPUTILS_ENUM_FAST

#ifndef CPPUTILS_ENUM_FULL
#define CPPUTILS_ENUM_FULL	CPPUTILS_ENUM
#endif

#ifndef CPPUTILS_ENUM_FULL_RAW
#define CPPUTILS_ENUM_FULL_RAW	CPPUTILS_ENUM_RAW
#endif


#ifndef CPPUTILS_ENUM_FULLSLOW
#define CPPUTILS_ENUM_FULLSLOW	CPPUTILS_ENUM
#endif

#ifndef CPPUTILS_ENUM_FULLSLOW_RAW
#define CPPUTILS_ENUM_FULLSLOW_RAW	CPPUTILS_ENUM_RAW
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP
