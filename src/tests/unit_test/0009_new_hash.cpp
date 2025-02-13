//
// file:			0009_new_hash.cpp
// created on:		2022 Jan 29
//

#include <cpputils/export_symbols.h>

#ifdef CPPUTILS_CPP_11_DEFINED

#include <cinternal/unit_test.h>
#include <cpputils/hash/hash.hpp>
#include <cpputils/hash/lhash.hpp>
#include <cpputils/hash/vhash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <utility>
#include <cinternal/undisable_compiler_warnings.h>



TEST(f_0009_new_hash, t0001_Hash)
{
	cpputils::hash::Hash<int, int> aHash;

	cpputils::hash::Hash<int, int>::iterator iter = aHash.AddEntryEvenIfExistsC(::std::pair<int,int>(1,1));
	aHash.AddEntryEvenIfExistsC(::std::pair<int,int>(1,1));

	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_EQ(aHash.find(1)->second,1);
	aHash.RemoveEntryRaw(iter);
	ASSERT_EQ(aHash.size(), size_t(1));
}


TEST(f_0009_new_hash, t0002_LHash)
{
	cpputils::hash::LSet<int> aHash;
    aHash.AddEntryEvenIfExistsC(1);
    aHash.AddEntryIfNotExistC(1);
    ASSERT_EQ(aHash.size(), size_t(1));
}


TEST(f_0009_new_hash, t0003_VHash)
{
    cpputils::hash::VSet<int> aHash;
    aHash.AddEntryEvenIfExistsC(1);
    aHash.AddEntryIfNotExistC(1);
    ASSERT_EQ(aHash.size(), size_t(1));
}



#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
