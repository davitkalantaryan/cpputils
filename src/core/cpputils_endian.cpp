//
// file:			cpputils_endian.cpp
// path:			src/core/cpputils_endian.cpp
// created on:		2021 Aug 01
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/endian.hpp>


#ifndef CPPUTILS_ENDIAN_COMPILETIME
#include <stdlib.h>

static bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

CPPUTILS_BEGIN_C

CPPUTILS_EXPORT uint64_t htole64(uint64_t a_host_64bits)
{
    if(is_big_endian()){return _byteswap_uint64 (a_host_64bits);}
    return a_host_64bits;
}
CPPUTILS_EXPORT uint64_t le64toh(uint64_t a_little_endian_64bits)
{
    if(is_big_endian()){return _byteswap_uint64 (a_little_endian_64bits);}
    return a_little_endian_64bits;
}

CPPUTILS_END_C

#endif  // #ifndef CPPUTILS_ENDIAN_COMPILETIME


//namespace __private { namespace __implementation {
//}}  // namespace __private { namespace __implementation {
//
//
//namespace cpputils {
//
//InScopeCleaner::InScopeCleaner(TypeDeleteFunc a_func, void* a_pClbkData)
//	:
//	  m_func(a_func),
//	  m_clbkData(a_pClbkData)
//{
//}
//
//
//InScopeCleaner::~InScopeCleaner()
//{
//	m_func(m_clbkData);
//}
//
//}  // namespace cpputils {
