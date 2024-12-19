//
// file:			0008_bigint_double.cpp
// created on:		2021 Oct 10
//

#include <cinternal/unit_test.h>
#include <cpputils/bigint.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <stdio.h>
#include <cinternal/undisable_compiler_warnings.h>


TEST(f_0008_bigint_double, t0001_double_to_int)
{
    //printf("press any key ken enter to continue");fflush(stdout);
    //getchar();

    //double lfV01 = 1e30;
    //cpputils::BigInt<2> a01(lfV01);
    //ASSERT_EQ( ::std::to_string(a01),::std::string("1000000000000000000000000000000"));

    double lfV01 = 1e33;
    cpputils::BigInt<2> a01(lfV01);
    ::std::cout << "!!!!!!!!!!!!!!!!"<<::std::to_string(a01) <<::std::endl;
    //ASSERT_EQ( ::std::to_string(a01),::std::string("100000000000000000000"));
    double lfV02 = static_cast<double>(a01);
    ASSERT_NEAR(lfV01,lfV02,5.0);
}


TEST(f_0008_bigint_double, t0002_double_int_to_double)
{
    cpputils::BigInt<2> a01 = 1000000000000000000000000000000_bi02;
    double lfV01 = static_cast<double>(a01);

    ASSERT_NEAR(lfV01,1e30,0.01);
}
