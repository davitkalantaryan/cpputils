//
// file:			0011_multifor.cpp
// created on:		2022 May 24
//

#include <cpputils_internal_header.h>
#include "gtest/gtest.h"
#include <cpputils/multifor.hpp>

//#ifdef CPPUTILS_CPP_11_DEFINED

//typedef ::cpputils::function<void(const void*, size_t,const ::std::vector<int64_t>&)> TypeIter;
//typedef ::cpputils::function<int64_t(const void*, size_t,const ::std::vector<int64_t>&)> TypeLimit;
//MultiFor(size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max);


static uint64_t PowByMFor(uint64_t a_val, uint64_t a_pow)
{
    uint64_t ullnRet = 0;
    cpputils::MultiFor aMFor(size_t(a_pow),
                             [&ullnRet](const void*,size_t,const ::std::vector<int64_t>&){++ullnRet},
                             [](const void*, size_t,const ::std::vector<int64_t>&){return 0;},
                             [](const void*, size_t,const ::std::vector<int64_t>&){return int64_t(a_val);});

    return ullnRet;
}



TEST(f_0011_multifor, t0001)
{
    uint64_t retVal;

    retVal = PowByMFor(5,3);
    ASSERT_EQ(retVal, uint64_t(125));

}


//#endif  //#ifdef CPPUTILS_CPP_11_DEFINED
