//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include "gtest/gtest.h"
#include <stdio.h>
#include <common/functional_old.hpp>

static size_t SumStatic(int a_val1, int a_val2, int a_val3);

TEST(f_0003_function_old, t0000_first)
{
#ifdef CPPUTILS_CPP_11_DEFINED
		
	common::function_old< FUNC_ARGS_OLD(size_t,const int&) > aFn01([](const int& a_val){
		return static_cast<size_t>(a_val);
	});
	ASSERT_EQ(static_cast<size_t>(aFn01(1)),size_t(1));
	ASSERT_EQ(static_cast<size_t>(aFn01(2)),size_t(2));
	
#endif
	
	common::function_old< FUNC_ARGS_OLD(size_t,int,int,int) > aFn02;
	aFn02 = &SumStatic;
	
	ASSERT_EQ(static_cast<size_t>(aFn02(0,0,0)),size_t(0));
	ASSERT_EQ(static_cast<size_t>(aFn02(0,0,1)),size_t(1));
	ASSERT_EQ(static_cast<size_t>(aFn02(0,1,0)),size_t(1));
	ASSERT_EQ(static_cast<size_t>(aFn02(0,1,1)),size_t(2));
	
	ASSERT_EQ(static_cast<size_t>(aFn02(1,0,0)),size_t(1));
	ASSERT_EQ(static_cast<size_t>(aFn02(1,0,1)),size_t(2));
	ASSERT_EQ(static_cast<size_t>(aFn02(1,1,0)),size_t(2));
	ASSERT_EQ(static_cast<size_t>(aFn02(1,1,1)),size_t(3));
}


static size_t SumStatic(int a_val1, int a_val2, int a_val3)
{
	return static_cast<size_t>(a_val1+a_val2+a_val3);
}
