//
// file:            flagshelper.h
// path:			include/cpputils/flagshelper.h
// created on:		2021 Nov 13
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_FLAGSHELPER_H
#define CPPUTILS_INCLUDE_CPPUTILS_FLAGSHELPER_H

#include <cpputils/internal_header.h>
#include <cpputils/macroses02.h>

#define CPPUTILS_MAKE_BITS_POSITIVE     1
#define CPPUTILS_MAKE_BITS_NEGATIVE     2
#define CPPUTILS_MAKE_BITS_TRUE         1
#define CPPUTILS_MAKE_BITS_FALSE        2
#define CPPUTILS_INIT_BITS              0xaaaaaaaaaaaaaaaa

#define CPPUTILS_POS_NEG_BITS_RAW(_type,_name) \
    _type  _name ## _true : 1; \
    _type  _name ## _false : 1

#define CPPUTILS_POS_NEG_BITS(_name)  CPPUTILS_POS_NEG_BITS_RAW(uint64_t,_name)
#define CPPUTILS_POS_NEG_BITS2(_a,_name)  CPPUTILS_POS_NEG_BITS(_name) ;


#define CPPUTILS_BOTH_BITS_RAW(_type,_name) \
    _type  _name ## _both : 2
#define CPPUTILS_BOTH_BITS(_name)  CPPUTILS_BOTH_BITS_RAW(uint64_t,_name)
#define CPPUTILS_BOTH_BITS2(_a,_name)  CPPUTILS_BOTH_BITS(_name) ;


#define CPPUTILS_BITS_B(...) CPPUTILS_MACRO02_APPY(CPPUTILS_POS_NEG_BITS2,;,__VA_ARGS__)
#define CPPUTILS_BITS_B2(...) CPPUTILS_MACRO02_APPY(CPPUTILS_BOTH_BITS2,;,__VA_ARGS__)


#define CPPUTILS_FLAGS_UN_RAW(_name, _numberOfReserved,...)  \
    union _name {  \
        uint64_t  all; \
        struct{ \
            CPPUTILS_BITS_B(__VA_ARGS__)                \
            uint64_t    reserved01 : _numberOfReserved; \
        }b; \
        struct{ \
            CPPUTILS_BITS_B2(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }b2;    \
    }

#define CPPUTILS_FLAGS_UN(...)    CPPUTILS_FLAGS_UN_RAW(,64-2*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)
#define CPPUTILS_FLAGS_UN_NM(_name,...)    CPPUTILS_FLAGS_UN_RAW(_name,64-2*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_FLAGSHELPER_H
