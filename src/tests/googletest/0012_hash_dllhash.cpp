//
// file:			0012_hash_dllhash.cpp
// created on:		2022 Sep 25
//

#include "gtest/gtest.h"
#include <cpputils/export_symbols.h>

#ifdef CPPUTILS_CPP_11_DEFINED

#include <cpputils/hash/dllhash.hpp>
#include <string>


TEST(f_0012_hash_dllhash, t0001)
{
	::cpputils::hash::DllHash<int, int> aHash;

	aHash.AddEntryIfNotExistC(::std::pair<int,int>(1,1));
	aHash.AddEntryIfNotExistC(::std::pair<int, int>(1, 1));

	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_EQ(aHash.find(1)->second,1);
	aHash.RemoveEntryRaw(aHash.begin());
	ASSERT_EQ(aHash.size(), size_t(1));
}


TEST(f_0012_hash_dllhash, t0002)
{
	typedef ::cpputils::hash::DllHash<int,::std::string> TypeHash1;
	TypeHash1 aHash;
	size_t unHash0, unHash;

	const TypeHash1::const_iterator iter1 = aHash.find(1,&unHash0);
	if (iter1 == TypeHash1::s_constNullIter) {
		// we have to create ::std::string object
		aHash.AddEntryWithKnownHashMv(::std::pair<int, ::std::string>(1, "One"), unHash0);
	}

	
	const TypeHash1::const_iterator iter2 = aHash.find(1, &unHash);
	ASSERT_FALSE(iter2== TypeHash1::s_constNullIter);
	ASSERT_EQ(unHash, unHash0);
	ASSERT_STREQ("One", iter2->second.c_str());
}


#endif  //  #ifdef CPPUTILS_CPP_11_DEFINED

