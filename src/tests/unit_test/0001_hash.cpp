//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include <cinternal/unit_test.h>
#include <cpputils/hash/listhash.hpp>


TEST(f_0001_hash, t0001_base)
{
    cpputils::hash::ListHash aHash(1024);

    aHash.AddIfNotExist<int,int>(1, 1);
    aHash.AddEvenIfExist<int,int>(1, 1);

    ASSERT_EQ((aHash.find<int,int>(1)->data),1);
}
