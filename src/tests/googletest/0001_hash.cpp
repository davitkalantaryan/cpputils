//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include "gtest/gtest.h"
#include <common/hashtbl.hpp>
#ifdef CPPUTILS_CPP_11_DEFINED
#include <utility>
#endif


TEST(f_0001_hash, t0001_base)
{
	common::hashtbl::Base<int, int> aHash;

	aHash.AddEntry(1, 1);
	aHash.AddEntryEvenIfExists(1, 1);

	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_EQ(aHash[1],1);
	aHash.RemoveEntry(aHash.begin());
	ASSERT_EQ(aHash.size(), size_t(1));
}

TEST(f_0001_hash, t0002_key_is_any_void_ptr)
{
	int a = 1;
	common::hashtbl::HashTbl<int> aHash;

	aHash.AddEntry({ &a,4 }, 1);
	aHash.AddEntryEvenIfExists({ &a,4 }, 1);
	common::hashtbl::HashTbl<int>::iterator iter = aHash.FindEntry({ &a,4 });
	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_FALSE(iter== common::hashtbl::HashTbl<int>::s_endIter);
	ASSERT_EQ(iter->second, 1);
}


TEST(f_0001_hash, t0003_map)
{
	common::hashtbl::Set<int> aHash;

	size_t unHash;
	aHash.AddEntry(1);
	ASSERT_EQ(aHash.size(), size_t(1));

	common::hashtbl::Set<int>::iterator iter = aHash.FindEntry(2, &unHash);
	ASSERT_TRUE(iter == common::hashtbl::Set<int>::s_endIter);
	aHash.AddEntryWithKnownHash(2, unHash);
	ASSERT_EQ(aHash.size(),size_t(2));
}


TEST(f_0001_hash, t0004_map_with_any_void_ptr_key)
{
	int a = 1;
	common::hashtbl::SetHash aHash;

	aHash.AddEntry({ &a,4 });
	aHash.AddEntryEvenIfExists({ &a,4 });
	common::hashtbl::SetHash::iterator iter = aHash.FindEntry({ &a,4 });
	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_FALSE(iter == common::hashtbl::SetHash::s_endIter);
}

#define NUMBER_OF_ENTRIES	10

TEST(f_0001_hash, t0005_testing_copy_constructor_and_operator_eq)
{
#ifdef ARG_FROM
#undef ARG_FROM
#endif
#define ARG_FROM(_i)	(_i),(_i)
#ifdef OP_SQ_BR_DEF
#undef OP_SQ_BR_DEF
#endif
#define OP_SQ_BR_DEF(_exp)	_exp
	typedef common::hashtbl::Base<int, int> HashType;

	int i;
	HashType aHashIn;
	const HashType::iterator endIter = HashType::s_endIter;

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashIn.AddEntry(ARG_FROM(i)) == endIter);
	}
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	//
	HashType aHashFn1(aHashIn);
	ASSERT_EQ(aHashFn1.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn1.FindEntry(i)== endIter);
		ASSERT_FALSE(aHashIn.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn1[i],i));
		OP_SQ_BR_DEF(ASSERT_EQ(aHashIn[i], i));
	}

	HashType aHashFn2(aHashIn,1);
	ASSERT_EQ(aHashFn2.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(0));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn2.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn2[i], i));
	}

	/*///////////////////////////*/
	aHashIn.ReplaceWithOther(aHashFn2);
	ASSERT_EQ(aHashFn2.size(), size_t(0));
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashIn.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashIn[i], i));
	}

	//
	aHashFn1=aHashIn;
	ASSERT_EQ(aHashFn1.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn1.FindEntry(i) == endIter);
		ASSERT_FALSE(aHashIn.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn1[i], i));
		OP_SQ_BR_DEF(ASSERT_EQ(aHashIn[i], i));
	}

#ifdef CPPUTILS_CPP_11_DEFINED
	aHashFn2 = std::move(aHashIn);
	ASSERT_EQ(aHashFn2.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(0));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn2.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn2[i], i));
	}
#endif
}


TEST(f_0001_hash, t0006_testing_copy_constructor_and_operator_eq_set)
{
#ifdef ARG_FROM
#undef ARG_FROM
#endif
#define ARG_FROM(_i)	(_i)
#ifdef OP_SQ_BR_DEF
#undef OP_SQ_BR_DEF
#endif
#define OP_SQ_BR_DEF(_exp) 
	typedef common::hashtbl::Base<int, void> HashType;

	int i;
	HashType aHashIn;
	const HashType::iterator endIter = HashType::s_endIter;

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashIn.AddEntry(ARG_FROM(i)) == endIter);
	}
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	//
	HashType aHashFn1(aHashIn);
	ASSERT_EQ(aHashFn1.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn1.FindEntry(i)== endIter);
		ASSERT_FALSE(aHashIn.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn1[i],i));
		OP_SQ_BR_DEF(ASSERT_EQ(aHashIn[i], i));
	}

	HashType aHashFn2(aHashIn,1);
	ASSERT_EQ(aHashFn2.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(0));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn2.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn2[i], i));
	}

	/*///////////////////////////*/
	aHashIn.ReplaceWithOther(aHashFn2);
	ASSERT_EQ(aHashFn2.size(), size_t(0));
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashIn.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashIn[i], i));
	}

	//
	aHashFn1=aHashIn;
	ASSERT_EQ(aHashFn1.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(NUMBER_OF_ENTRIES));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn1.FindEntry(i) == endIter);
		ASSERT_FALSE(aHashIn.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn1[i], i));
		OP_SQ_BR_DEF(ASSERT_EQ(aHashIn[i], i));
	}

#ifdef CPPUTILS_CPP_11_DEFINED
	aHashFn2 = std::move(aHashIn);
	ASSERT_EQ(aHashFn2.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(0));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn2.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn2[i], i));
	}
#endif
}
