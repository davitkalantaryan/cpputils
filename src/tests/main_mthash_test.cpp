//
// repo:			cpputils
// file:			main_collection_map_test.cpp
// path:			src/tests/main_collection_map_test.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/mt/listhash.hpp>
#include <cpputils/hash/mt/purehash.hpp>
#include <cpputils/hash/mt/vecthash.hpp>
#include <cpputils/hash/mt/base.hpp>
#include <cpputils/hash/templ/purehash.hpp>
#include <cpputils/hash/templ/listhash.hpp>
#include <cpputils/hash/templ/vecthash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <type_traits>
#include <cinternal/undisable_compiler_warnings.h>


template <typename TypeHash>
static void TestHash(void);
template <typename TypeTemplHash, typename TypeData, typename TypeKey>
static void TestTemplHash(void);


int main(void)
{
    size_t unHash;
    cpputils::hash::mt::Base<cpputils::hash::PureHash> aBase(1024);
    aBase.findEx<int, int>(1, &unHash);

    TestHash<::cpputils::hash::ListHash>();
    TestHash<::cpputils::hash::PureHash>();
    TestHash<::cpputils::hash::VectHash>();
    //TestHash<::cpputils::hash::mt::ListHash>();
    //TestHash<::cpputils::hash::mt::PureHash>();

#ifndef _MSC_VER2
    TestTemplHash<::cpputils::hash::templ::MtPureHash<int,int>,int,int >();
    TestTemplHash<::cpputils::hash::templ::MtListHash<int, int>, int, int >();
    TestTemplHash<::cpputils::hash::templ::MtVectHash<int, int>, int, int >();
#endif
    TestTemplHash<::cpputils::hash::templ::PureHash<int,int>,int,int >();
    TestTemplHash<::cpputils::hash::templ::ListHash<int, int>, int, int >();
    TestTemplHash<::cpputils::hash::templ::VectHash<int, int>, int, int >();

	return 0;
}


template <typename TypeHash>
static void TestHash()
{
    TypeHash aMap(1024);
    size_t unHash;

    typename TypeHash::template Iterator<int> iter;
    typename TypeHash::template Iterator<double> iterD;

    int32_t reserveResult = aMap.template reserveUniqueIdForDataInline<double>();
    ::std::cout << "reserveResult: " << reserveResult << ::std::endl;

    const ConstCinternalHash_t rawHash = aMap.getHash();
    ::std::cout << "rawHash: " << rawHash << ::std::endl;

    iter = aMap.template findEx<int, int>(1, &unHash);
    ::std::cout << "iter_01: " << iter << ::std::endl;

    iter = aMap.template find<int, int>(1);
    ::std::cout << "iter_01b: " << iter << ::std::endl;

    if (iter) {
        iter = aMap.template findNextTheSame<int>(iter);
        ::std::cout << "iter_01c: " << iter << ::std::endl;
    }

    iter = aMap.template AddWithKnownHash<int, int>(1, 1, unHash);
    ::std::cout << "iter_02: " << iter << ::std::endl;

    iter = aMap.template AddEvenIfExist<int, int>(1, 1);
    ::std::cout << "iter_02b: " << iter << ::std::endl;

    iter = aMap.template AddIfNotExist<int, int>(1, 1);
    ::std::cout << "iter_02c: " << iter << ::std::endl;

    iter = aMap.template findEx<int, int>(1, &unHash);
    ::std::cout << "iter_03: " << iter << ::std::endl;

    iter = aMap.template find<int, int>(1);
    ::std::cout << "iter_04: " << iter << ::std::endl;

    if (iter) {
        iter = aMap.template findNextTheSame<int>(iter);
        ::std::cout << "iter_05: " << iter << ::std::endl;
    }

    iter = aMap.template findEx<int, CPPUTILS_HASH_CHI(int) >(1, &unHash);
    ::std::cout << "iter_06: " << iter << ::std::endl;

    iter = aMap.template AddEvenIfExist<int, int>(2, 1);
    ::std::cout << "iter_07: " << iter << ::std::endl;

    iter = aMap.template AddIfNotExist<int, int>(1, 1);
    ::std::cout << "iter_08: " << iter << ::std::endl;

    iterD = aMap.template findEx<double, int>(1, &unHash);
    ::std::cout << "iterD_09: " << iterD << ::std::endl;

    iter = aMap.template find<int, int>(1);
    ::std::cout << "iter_10: " << iter << ::std::endl;
    int i = 0;
    while (iter) {
        iter = aMap.template findNextTheSame<int>(iter);
        ::std::cout << "iter_11: " << (++i) << "  " << iter << ::std::endl;
    }  //  while(iter){

    iter = aMap.template find<int, int>(1);
    ::std::cout << "iter_12: " << iter << ::std::endl;

    if (iter) {

        if constexpr (::std::is_same<TypeHash, ::cpputils::hash::mt::ListHash>::value) {
            int nIter = 0;
            aMap.template iterateBegToEnd<int>([&nIter](int& a_data)->bool {
                ::std::cout << "dataBegToEnd(iter:" << (++nIter) << "):" << a_data << ::std::endl;
                return true;
            });
            
            nIter = 0;
            aMap.template iterateEndToBeg<int>([&nIter](int& a_data)->bool {
                ::std::cout << "dataEndToBeg(iter:" << (++nIter) << "):" << a_data << ::std::endl;
                return true;
            });
            
            aMap.MoveToStart(iter);
            aMap.MoveToEnd(iter);
        }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {

        aMap.RemoveEx(iter);
    }  //  if (iter) {
}


template <typename TypeTemplHash, typename TypeData, typename TypeKey>
static void TestTemplHash(void)
{
    size_t unHash;
    typename TypeTemplHash::TypeRawHash aHashBase(1024);
    TypeTemplHash aHash(&aHashBase);

    typename TypeTemplHash::TypeRawHash::template Iterator<int> iter;
    iter = aHash.findEx(1, &unHash);
    ::std::cout << "iter_01: " << iter << ::std::endl;

    iter = aHash.find(1);
    ::std::cout << "iter_02: " << iter << ::std::endl;

    if constexpr (
        (::std::is_same<TypeTemplHash, ::cpputils::hash::PureHash>::value) ||
        (::std::is_same<TypeTemplHash, ::cpputils::hash::ListHash>::value)  ||  
        (::std::is_same<TypeTemplHash, ::cpputils::hash::VectHash>::value)   )
    {
        if (iter) {
            iter = aHash.findNextTheSame(iter);
            ::std::cout << "iter_03: " << iter << ::std::endl;
        }
    }

    iter = aHash.AddWithKnownHash(1, 1, unHash);
    ::std::cout << "iter_04: " << iter << ::std::endl;

    iter = aHash.AddEvenIfExist(1, 1);
    ::std::cout << "iter_05: " << iter << ::std::endl;

    iter = aHash.AddIfNotExist(1, 1);
    ::std::cout << "iter_06: " << iter << ::std::endl;

    if constexpr (
        (::std::is_same<TypeTemplHash, ::cpputils::hash::PureHash>::value) ||
        (::std::is_same<TypeTemplHash, ::cpputils::hash::ListHash>::value) ||
        (::std::is_same<TypeTemplHash, ::cpputils::hash::VectHash>::value))
    {
        if (iter) {
            aHash.RemoveEx(iter);
        }
    }

    iter = aHash.findEx(1, &unHash);
    if constexpr (
        (::std::is_same<TypeTemplHash, ::cpputils::hash::PureHash>::value) ||
        (::std::is_same<TypeTemplHash, ::cpputils::hash::ListHash>::value) ||
        (::std::is_same<TypeTemplHash, ::cpputils::hash::VectHash>::value))
    {
        if (iter) {
            aHash.RemoveEx(iter);
        }
    }

    const bool removeResult = aHash.Remove(1);
    ::std::cout << "removeResult: " << removeResult << ::std::endl;
}
