//
// file:			0005_macroses.cpp
// created on:		2021 Apr 11
//

#include "gtest/gtest.h"
#include <cpputils/macroses.h>
#include <string>
#include <stdarg.h>

static std::string SumAllArgs(int a_nargs,...);

#define ARGS_TO_NUM_AND_STRS(...)	CPPUTILS_NARGS(__VA_ARGS__), CPPUTILS_NAMES(__VA_ARGS__)

TEST(f_0005_macroses, t0000_nargs)
{
	ASSERT_EQ(CPPUTILS_NARGS(1,2,3,4,5,6),6);
	ASSERT_EQ(CPPUTILS_NARGS(a,b,1,4,3,""),6);
	ASSERT_EQ(CPPUTILS_NARGS(aaaa,bbb),2);
}


TEST(f_0005_macroses, t0001_names)
{
	ASSERT_EQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1,2,3,4,5,6)),std::string("123456"));
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(a,b,1,4,3,"")).c_str(),"ab143\"\"");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(aaaa,bbb)).c_str(),"aaaabbb");
}


static std::string SumAllArgs(int a_nargs,...)
{
	std::string retString;
	const char* nextArg;
	va_list aList;
	va_start(aList,a_nargs);
	
	for(int i(0);i<a_nargs;++i){
		nextArg = va_arg(aList,const char*);
		retString += nextArg;
	}
	
	return retString;
}
