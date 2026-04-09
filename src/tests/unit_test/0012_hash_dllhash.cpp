//
// file:			0012_hash_dllhash.cpp
// created on:		2022 Sep 25
//

#include <cinternal/unit_test.h>
#include <cpputils/export_symbols.h>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <cinternal/undisable_compiler_warnings.h>

#define TRY_LISTHASH

#ifdef CPPUTILS_CPP_11_DEFINED

#ifdef TRY_LISTHASH
#include <cpputils/hash/listhash.hpp>
#else
#include <cpputils/hash/purehash.hpp>
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <string>
#include <cinternal/undisable_compiler_warnings.h>


#ifdef TRY_LISTHASH

typedef ::cpputils::hash::ListHash  MapToTest;

#else

typedef ::cpputils::hash::PureHash  MapToTest;

#endif


TEST(f_0012_hash_dllhash, t0001)
{
    MapToTest aMap(1024);
    size_t unHash;

    MapToTest::Iterator<int> iter;
    MapToTest::Iterator<double> iterD;

    const ConstCinternalHash_t rawHash = aMap.getHash();
    ::std::cout << "rawHash: " << rawHash << ::std::endl;
    ASSERT_TRUE(rawHash);

    iter = aMap.findEx<int, int>(1, &unHash);
    ::std::cout << "iter_01: " << iter << ::std::endl;
    ASSERT_FALSE(iter);

    iter = aMap.AddWithKnownHash<int, int>(unHash,1, 1);
    ::std::cout << "iter_02: " << iter << ::std::endl;

    iter = aMap.findEx<int, int>(1, &unHash);
    ::std::cout << "iter_03: " << iter << ::std::endl;
    ASSERT_TRUE(iter);

    iter = aMap.find<int, int>(1);
    ::std::cout << "iter_04: " << iter << ::std::endl;

    if (iter) {
        iter = aMap.findNextTheSame<int>(iter);
        ::std::cout << "iter_05: " << iter << ::std::endl;
    }

    // CPPUTILS_CHI
    iter = aMap.findEx<int, CPPUTILS_HASH_CHI(int) >(1, &unHash);
    ::std::cout << "iter_06: " << iter << ::std::endl;

    iter = aMap.AddEvenIfExist<int, int>(1, 1);
    ::std::cout << "iter_07: " << iter << ::std::endl;

    iter = aMap.AddIfNotExist<int, int>(1, 1);
    ::std::cout << "iter_08: " << iter << ::std::endl;

    iterD = aMap.findEx<double, int>(1, &unHash);
    ::std::cout << "iterD_09: " << iterD << ::std::endl;

    iter = aMap.find<int, int>(1);
    ::std::cout << "iter_10: " << iter << ::std::endl;
    int i = 0;
    while (iter) {
        iter = aMap.findNextTheSame<int>(iter);
        ::std::cout << "iter_11: " << (++i) << "  " << iter << ::std::endl;
    }  //  while(iter){

    iter = aMap.find<int, int>(1);
    ::std::cout << "iter_12: " << iter << ::std::endl;

    if (iter) {
#ifdef TRY_LISTHASH

        iter = aMap.first<int>();
        ::std::cout << "iter_13: " << iter << ::std::endl;

        iter = aMap.last<int>();
        ::std::cout << "iter_13: " << iter << ::std::endl;

        aMap.MoveToStart(iter);
        aMap.MoveToEnd(iter);
#endif
        aMap.RemoveEx(iter);
    }
}


#endif  //  #ifdef CPPUTILS_CPP_11_DEFINED

