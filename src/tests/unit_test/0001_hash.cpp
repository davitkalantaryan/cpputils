//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include <cinternal/unit_test.h>
#include <cpputils/hashtbl.hpp>
#ifdef CPPUTILS_CPP_11_DEFINED
#include <utility>
#endif

// todo: get rid of this
#define DEF_SIZE	10


TEST(f_0001_hash, t0001_base)
{
	cpputils::hashtbl::Base<int, int> aHash;

	aHash.AddEntryIfNotExist(1, 1);
	aHash.AddEntryEvenIfExists(1, 1);

	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_EQ(aHash[1],1);
	aHash.RemoveEntry(aHash.begin());
	ASSERT_EQ(aHash.size(), size_t(1));
}

TEST(f_0001_hash, t0002_key_is_any_void_ptr)
{
	int a = 1;
	cpputils::hashtbl::VoidPtrHash<int> aHash;

	aHash.AddEntryIfNotExist({ &a,4 }, 1);
	aHash.AddEntryEvenIfExists({ &a,4 }, 1);
	cpputils::hashtbl::VoidPtrHash<int>::iterator iter = aHash.FindEntry({ &a,4 });
	ASSERT_EQ(aHash.size(), size_t(2));
	ASSERT_FALSE(iter== cpputils::hashtbl::VoidPtrHash<int>::s_endIter);
	ASSERT_EQ(iter->second, 1);
}


TEST(f_0001_hash, t0003_map)
{
	cpputils::hashtbl::Set<int> aHash;

	size_t unHash;
	aHash.AddEntryIfNotExist(1);
	ASSERT_EQ(aHash.size(), size_t(1));

	cpputils::hashtbl::Set<int>::iterator iter = aHash.FindEntry(2, &unHash);
	ASSERT_TRUE(iter == cpputils::hashtbl::Set<int>::s_endIter);
	aHash.AddEntryWithKnownHash(2, unHash);
	ASSERT_EQ(aHash.size(),size_t(2));
}


TEST(f_0001_hash, t0004_map_with_any_void_ptr_key)
{
	int a = 1;
	const cpputils::hashtbl::Base< cpputils::hashtbl::VoidPtrKey,void,cpputils::hashtbl::FHashVoidPtr>::iterator endIter = 
	        cpputils::hashtbl::Base< cpputils::hashtbl::VoidPtrKey,void,cpputils::hashtbl::FHashVoidPtr>::s_endIter;
	
	cpputils::hashtbl::VoidPtrSet<DEF_SIZE> aHash;
	// template <typename KeyType,typename DataType,typename Hash=FHash<KeyType>>
	//cpputils::hashtbl::Base< cpputils::hashtbl::VoidPtrKey,void,cpputils::hashtbl::FHashVoidPtr> aHash; 

	aHash.AddEntryIfNotExist({ &a,4 });
	aHash.AddEntryEvenIfExists({ &a,4 });
	//cpputils::hashtbl::SetHash::iterator iter = aHash.FindEntry({ &a,4 });
	cpputils::hashtbl::Base< cpputils::hashtbl::VoidPtrKey,void,cpputils::hashtbl::FHashVoidPtr>::iterator iter = aHash.FindEntry({ &a,4 });
	ASSERT_EQ(aHash.size(), size_t(2));
	//ASSERT_FALSE(iter == cpputils::hashtbl::SetHash::s_endIter);
	ASSERT_FALSE(iter == endIter);
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
	typedef cpputils::hashtbl::Base<int, int> HashType;

	int i;
	HashType aHashIn;
	const HashType::iterator endIter = HashType::s_endIter;

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashIn.AddEntryIfNotExist(ARG_FROM(i)) == endIter);
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

	HashType aHashFn2(&aHashIn);
	ASSERT_EQ(aHashFn2.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(0));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn2.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn2[i], i));
	}

	/*///////////////////////////*/
	aHashIn.ReplaceWithOther(&aHashFn2);
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
	typedef cpputils::hashtbl::Base<int, void> HashType;

	int i;
	HashType aHashIn;
	const HashType::iterator endIter = HashType::s_endIter;

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashIn.AddEntryIfNotExist(ARG_FROM(i)) == endIter);
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

	HashType aHashFn2(&aHashIn);
	ASSERT_EQ(aHashFn2.size(), size_t(NUMBER_OF_ENTRIES));
	ASSERT_EQ(aHashIn.size(), size_t(0));

	for (i = 0; i < NUMBER_OF_ENTRIES; ++i) {
		ASSERT_FALSE(aHashFn2.FindEntry(i) == endIter);
		OP_SQ_BR_DEF(ASSERT_EQ(aHashFn2[i], i));
	}

	/*///////////////////////////*/
	aHashIn.ReplaceWithOther(&aHashFn2);
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
