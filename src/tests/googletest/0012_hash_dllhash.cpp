//
// file:			0012_hash_dllhash.cpp
// created on:		2022 Sep 25
//

#include "gtest/gtest.h"
#include <cpputils/hash/dllhash.hpp>
#ifdef CPPUTILS_CPP_11_DEFINED
#include <utility>
#endif


TEST(f_0012_hash_dllhash, t0001_base)
{
	::cpputils::hash::DllHash<int, int> aHash;

	aHash.AddEntryIfNotExistC(::std::pair<int,int>(1,1));
	aHash.AddEntryIfNotExistC(::std::pair<int, int>(1, 1));

	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_EQ((aHash.find(1)->second),1);
	aHash.RemoveEntryRaw(aHash.begin());
	ASSERT_EQ(aHash.size(), size_t(1));
}

