//
// file:			0009_new_hash.cpp
// created on:		2022 Jan 29
//

#include <cpputils/export_symbols.h>

#ifdef CPPUTILS_CPP_11_DEFINED

#include <cinternal/unit_test.h>
#include <cpputils/hash/purehash.hpp>
#include <cpputils/hash/listhash.hpp>


TEST(f_0009_new_hash, t0001_Hash)
{
	cpputils::hash::PureHash aHash(1024);

	cpputils::hash::PureHash::Iterator<int> iter = aHash.AddEvenIfExist(1,1);

	ASSERT_EQ(*(aHash.find<int,int>(1)->data_p),1);
	
    aHash.RemoveEx(iter);
    iter = aHash.find<int, int>(1);
	ASSERT_EQ(iter, CPPUTILS_NULL);
}


TEST(f_0009_new_hash, t0002_LHash)
{
    cpputils::hash::ListHash aHash(1024);

    cpputils::hash::ListHash::Iterator<int> iter = aHash.AddEvenIfExist(1, 1);
    aHash.AddEvenIfExist(1, 1);

    ASSERT_EQ(aHash.count<int>(), size_t(2));
    ASSERT_EQ(aHash.count<double>(), size_t(0));
    ASSERT_EQ(*(aHash.find<int, int>(1)->data_p), 1);
    aHash.RemoveEx(iter);
    ASSERT_EQ(aHash.count<int>(), size_t(1));
}


#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
