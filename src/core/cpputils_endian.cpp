//
// file:			cpputils_endian.cpp
// path:			src/core/cpputils_endian.cpp
// created on:		2021 Aug 01
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/endian.hpp>


#ifndef CPPUTILS_ENDIAN_COMPILETIME
#include <stdlib.h>
#include <stdint.h>

static inline bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

#if defined(_MSC_VER)
#define byteswap_uint64_new     _byteswap_uint64
#else
uint64_t byteswap_uint64_new ( uint64_t a_val )
{
    uint64_t retVal;
    const char* pcInpVal = reinterpret_cast<const char*>(&a_val);
    char* pcRetVal = reinterpret_cast<char*>(&retVal);

    pcRetVal[3] = pcInpVal[0];
    pcRetVal[0] = pcInpVal[3];

    pcRetVal[2] = pcInpVal[1];
    pcRetVal[1] = pcInpVal[2];
    return retVal;
}
#endif

CPPUTILS_BEGIN_C

CPPUTILS_EXPORT uint64_t htole64(uint64_t a_host_64bits)
{
    if(is_big_endian()){return byteswap_uint64_new (a_host_64bits);}
    return a_host_64bits;
}
CPPUTILS_EXPORT uint64_t le64toh(uint64_t a_little_endian_64bits)
{
    if(is_big_endian()){return byteswap_uint64_new (a_little_endian_64bits);}
    return a_little_endian_64bits;
}

CPPUTILS_END_C

#endif  // #ifndef CPPUTILS_ENDIAN_COMPILETIME
