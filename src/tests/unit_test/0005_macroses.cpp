//
// file:			0005_macroses.cpp
// created on:		2021 Apr 11
//

#include <cinternal/unit_test.h>
#include <cinternal/macroses.h>
#include <stdarg.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string>
#include <cinternal/undisable_compiler_warnings.h>

#define ARGS_TO_NUM_AND_STRS(...)	CPPUTILS_NARGS(__VA_ARGS__), CPPUTILS_NAMES(__VA_ARGS__)


TEST(f_0005_macroses, t0000_nargs)
{
	ASSERT_EQ(CPPUTILS_NARGS(1,2,3,4,5,6),6);
	ASSERT_EQ(CPPUTILS_NARGS(a,b,1,4,3,""),6);
	ASSERT_EQ(CPPUTILS_NARGS(aaaa,bbb),2);

	ASSERT_EQ(CPPUTILS_NARGS(anySymbol),1);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2), 2);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2,3), 3);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4), 4);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4, 5), 5);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4, 5, 6), 6);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4, 5, 6, 7), 7);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4, 5, 6, 7, 8), 8);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4, 5, 6, 7, 8, 9), 9);
	ASSERT_EQ(CPPUTILS_NARGS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10), 10);
	// up to 99 args will be properly calculated
	// range [1..99]  (0 args is not handled properly)
}


static std::string SumAllArgs(int a_nargs, ...);

static std::string SumAllArgs(int a_nargs, ...);

TEST(f_0005_macroses, t0001_names)
{
	ASSERT_EQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1,2,3,4,5,6)),std::string("123456"));
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(a,b,1,4,3,"")).c_str(),"ab143\"\"");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(aaaa,bbb)).c_str(),"aaaabbb");

	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(anySymbol)).c_str(), "anySymbol");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2)).c_str(), "12");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3)).c_str(), "123");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4)).c_str(), "1234");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4, 5)).c_str(), "12345");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4, 5, 6)).c_str(), "123456");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4, 5, 6, 7)).c_str(), "1234567");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4, 5, 6, 7, 8)).c_str(), "12345678");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4, 5, 6, 7, 8, 9)).c_str(), "123456789");
	ASSERT_STREQ(SumAllArgs(ARGS_TO_NUM_AND_STRS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)).c_str(), "12345678910");
	// up to 99 args will be properly calculated
	// range [1..99]  (0 args is not handled properly)
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
