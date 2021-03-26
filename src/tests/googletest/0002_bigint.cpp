//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include "gtest/gtest.h"
#include <common/bigint.hpp>

template <uint64_t BiSize>
static void TestBigInteger();

TEST(f_0002_bigint, t0000_basic)
{
	common::BigInt<1> a1(2);
	
	// let's declare very big integer
#ifdef CPPUTILS_CPP_11_DEFINED
	common::BigInt<1> a4 = 100000000000000000000_bi01; // = 10^20
	ASSERT_EQ(a4, 100000000000000000000_bi01);
#else
	common::BigInt<1> a4 = 10000000000;
	a4 *= 10000000000;
	ASSERT_EQ(static_cast<int64_t>(a4/ 10000000000), 10000000000);
#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
	
	ASSERT_EQ(static_cast<int64_t>(a4/1000000000000000), 100000);

}

TEST(f_0002_bigint, t0000_test_different_sizes)
{
	TestBigInteger<1>();
	TestBigInteger<2>();
	TestBigInteger<3>();
	TestBigInteger<4>();
	TestBigInteger<5>();
	TestBigInteger<6>();
	TestBigInteger<7>();
	TestBigInteger<8>();
}


template <uint64_t BiSize>
static void TestBigInteger()
{
	common::BigInt<BiSize> bi1(2);
	ASSERT_EQ(sizeof(bi1), 8*(1<< BiSize));

	bi1 *= 2;
	ASSERT_EQ(static_cast<int64_t>(bi1), 4);

	bi1 -= 5;
	ASSERT_EQ(static_cast<int64_t>(bi1), -1);

	common::BigInt<BiSize> bi2 = 2000;
	ASSERT_EQ(static_cast<int64_t>(bi1+2* bi2), 3999);

}
