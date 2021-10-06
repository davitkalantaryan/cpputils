//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include "gtest/gtest.h"
#include <cpputils/bigint.hpp>
#include <stdio.h>

template <uint64_t BiSize>
static void TestBigInteger();

TEST(f_0002_bigint, t0000_basic)
{
    //printf("press any key ken enter to continue");fflush(stdout);
    //getchar();

	cpputils::BigInt<1> a1(2);
	
	// let's declare very big integer
#ifdef CPPUTILS_CPP_11_DEFINED
	cpputils::BigInt<1> a4 = 100000000000000000000_bi01; // = 10^20
	
	ASSERT_EQ(static_cast<int64_t>(a4/100000000000),static_cast<int64_t>(100000000000000000000_bi01/100000000000));	
	
#ifdef _WIN32
	ASSERT_EQ(a4, 100000000000000000000_bi01);
#endif
	
#else
	cpputils::BigInt<1> a4 = 10000000000;
	a4 *= 10000000000;
	ASSERT_EQ(static_cast<int64_t>(a4/ 10000000000), 10000000000);
#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
	
	ASSERT_EQ(static_cast<int64_t>(a4/1000000000000000), 100000);


    cpputils::BigInt<2> bi3(-4);
    cpputils::BigInt<2> bi4(4);
    cpputils::BigInt<2> bi5(2);
    cpputils::BigInt<2> bi6(-2);

    ASSERT_EQ(::std::to_string(bi4/bi5),::std::string("2"));
    ASSERT_EQ(::std::to_string(-bi3),::std::string("4"));
    ASSERT_EQ(::std::to_string(bi3*bi5),::std::string("-8"));
    ASSERT_EQ(::std::to_string(bi3*bi6), ::std::string("8"));
    ASSERT_EQ(::std::to_string(bi3/bi5),::std::string("-2"));
    ASSERT_EQ(::std::to_string(bi3/bi6), ::std::string("2"));


}



TEST(f_0002_bigint, t0001_test_different_sizes)
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


TEST(f_0002_bigint, t0002_test_arithmetic)
{
#ifdef CPPUTILS_CPP_11_DEFINED

	cpputils::BigInt<2> bi1 = 1000000000000000000000000000000_bi02; // 10^30
    ASSERT_EQ(bi1.to_stringS<char>(), std::string("1000000000000000000000000000000"));

	bi1 /= 100;  // 10^28
    ASSERT_EQ(bi1.to_stringS<char>(), std::string("10000000000000000000000000000"));

	bi1 /= 100000000000000000000_bi02; // we divide to 10^20, so remains 10^8
    ASSERT_EQ(bi1.to_stringS<char>(), std::string("100000000"));

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
}


template <uint64_t BiSize>
static void TestBigInteger()
{
	cpputils::BigInt<BiSize> bi1(2);
	ASSERT_EQ(size_t(sizeof(bi1)), size_t(8*(1<< BiSize)));

	bi1 *= 2;
	ASSERT_EQ(static_cast<int64_t>(bi1), 4);

	bi1 -= 5;
	ASSERT_EQ(static_cast<int64_t>(bi1), -1);

	cpputils::BigInt<BiSize> bi2 = 2000;
	ASSERT_EQ(static_cast<int64_t>(bi1+2* bi2), 3999);

}
