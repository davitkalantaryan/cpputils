//
// repo:			cpputils
// file:			main_collection_map_test.cpp
// path:			src/tests/main_collection_map_test.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#define CPPUTILS_TEST_TEMPLATE_HASH



//

class A {
    public:
        typedef const int& TypeSomeFuncRet;
        static constexpr bool is_some_funcs_noexcept = true;
        int val;
        const int& some_func() noexcept
        {
            return val;
        }
};


class B {
public:
    typedef int TypeSomeFuncRet;
    static constexpr bool is_some_funcs_noexcept = false;
    int some_func()
    {
        return 1;
    }
};

template <typename TypeCls>
class TC {
    TypeCls m_memb;
public:
    using TypeSomeFuncRet = typename TypeCls::TypeSomeFuncRet;
    static constexpr bool is_some_funcs_noexcept = TypeCls::is_some_funcs_noexcept;
    TypeSomeFuncRet some_func() noexcept(is_some_funcs_noexcept) {
        return m_memb.some_func();
    }
};

//

#include <cpputils/hash/mt/listhash.hpp>
#include <cpputils/hash/mt/purehash.hpp>
#include <cpputils/hash/mt/vecthash.hpp>
#include <cpputils/hash/mt/base.hpp>

#include <cpputils/hash/templ/base.hpp>

#ifdef CPPUTILS_TEST_TEMPLATE_HASH
#include <cpputils/hash/templ/nl/purehash.hpp>
#include <cpputils/hash/templ/nl/listhash.hpp>
#include <cpputils/hash/templ/nl/vecthash.hpp>
#include <cpputils/hash/templ/mt/purehash.hpp>
#include <cpputils/hash/templ/mt/listhash.hpp>
#include <cpputils/hash/templ/mt/vecthash.hpp>
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <type_traits>
#include <cinternal/undisable_compiler_warnings.h>


template <typename TypeHash>
static void TestHash(void);
#ifdef CPPUTILS_TEST_TEMPLATE_HASH
template <typename TypeTemplHash>  // , typename TypeData, typename TypeKey -> int,int
static void TestTemplHash(void);
#endif


int main(void)
{
    TestHash<::cpputils::hash::nl::ListHash>();
    TestHash<::cpputils::hash::nl::PureHash>();
    TestHash<::cpputils::hash::nl::VectHash>();
    TestHash<::cpputils::hash::mt::ListHash>();
    TestHash<::cpputils::hash::mt::PureHash>();
    TestHash<::cpputils::hash::mt::VectHash>();

    TC<A> a;
    TC<B> b;
    a.some_func();
    b.some_func();

#ifdef CPPUTILS_TEST_TEMPLATE_HASH
    TestTemplHash<::cpputils::hash::templ::mt::PureHash<int, CPPUTILS_HASH_CHI(int)> >();
    TestTemplHash<::cpputils::hash::templ::mt::ListHash<int, int> >();
    TestTemplHash<::cpputils::hash::templ::mt::VectHash<int, int> >();
    TestTemplHash<::cpputils::hash::templ::nl::PureHash<int,int> >();
    TestTemplHash<::cpputils::hash::templ::nl::ListHash<int, int> >();
    TestTemplHash<::cpputils::hash::templ::nl::VectHash<int, int> >();
#endif

	return 0;
}


template <typename TypeHash>
static void TestHash()
{
    typedef typename TypeHash::template Iterator<int> TypeIterInt;
    typedef typename TypeHash::template Iterator<double> TypeIterDouble;

    TypeHash aMap(1024);
    size_t unHash;

    TypeIterInt iter;
    TypeIterDouble iterD;

    const int32_t reserveResult = aMap.template reserveUniqueIdForDataInline<double>();
    ::std::cout << "reserveResult: " << reserveResult << ::std::endl;

    iter = aMap.template findEx<int, int>(1, &unHash);
    ::std::cout << "iter_01: " << iter << ::std::endl;

    iter = aMap.template find<int, int>(1);
    ::std::cout << "iter_01b: " << iter << ::std::endl;

    iter = aMap.template AddWithKnownHash<int, int>(unHash, 1, 1);
    ::std::cout << "iter_02: " << iter << ::std::endl;

    if (iter) {
        bool isValid;
        const int cnkey = aMap.template key<int, int>(iter, &isValid);
        ::std::cout << "cnkey: " << cnkey << ::std::endl;
        iter = aMap.template findNextTheSame<int>(iter);
        ::std::cout << "iter_01c: " << iter << ::std::endl;
    }

    iter = aMap.template AddEvenIfExist<int, int>(1, 1);
    ::std::cout << "iter_02b: " << iter << ::std::endl;

    iter = aMap.template AddIfNotExist<int, int>(1, 1);
    ::std::cout << "iter_02c: " << iter << ::std::endl;

    iter = aMap.template AddOrReturnExisting<int, int>(1, 1);
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

    const CinternalHashConstBasic_t rawHashBasic = aMap.getConstHashBase();
    ::std::cout << "rawHashBasic: " << rawHashBasic << ::std::endl;

    if constexpr (
        ::std::is_same<TypeHash, ::cpputils::hash::nl::PureHash>::value ||
        ::std::is_same<TypeHash, ::cpputils::hash::nl::ListHash>::value || 
        ::std::is_same<TypeHash, ::cpputils::hash::nl::VectHash>::value )
    {
        const CinternalHashConst_t rawHash = aMap.getConstHash();
        ::std::cout << "rawHash: " << rawHash << ::std::endl;
    }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {

    if constexpr ( ::std::is_same<TypeHash, ::cpputils::hash::nl::ListHash>::value ){
        const size_t countOfTheType = aMap.template count<int>();
        ::std::cout << "countOfTheTypeList: " << countOfTheType << ::std::endl;
        iter = aMap.template first<int>();
        int i = 0;
        while (iter) {
            ::std::cout << "iter_list: " << (++i) << "  " << iter << ::std::endl;
            iter = (TypeIterInt)iter->next;
        }  //  while (iter) {
    }  //  if constexpr ( ::std::is_same<TypeHash, ::cpputils::hash::ListHash>::value ){

    if constexpr (::std::is_same<TypeHash, ::cpputils::hash::nl::VectHash>::value) {
        const size_t countOfTheType = aMap.template count<int>();
        const ::cpputils::hash::nl::vh::SVectData& vectData = aMap.getVectDataForTypeDataRaw(aMap.template reserveUniqueIdForDataInline<int>());
        ::std::cout << "countOfTheTypeVect: " << countOfTheType << ::std::endl;
        size_t i;
        for (i = 0; i < countOfTheType; ++i) {
            iter = aMap.template at<int>(i);
            ::std::cout << "iter_vect: " << "  iter:" << iter << ", vectData.m_items_p[" << i << "]:"<<vectData.m_items_p[i] << ::std::endl;
        }  //  for (i = 0; i < countOfTheType; ++i) {

    }  //  if constexpr ( ::std::is_same<TypeHash, ::cpputils::hash::VectHash>::value ){
    
    if constexpr ( 
        ::std::is_same<TypeHash, ::cpputils::hash::mt::ListHash>::value ||
        ::std::is_same<TypeHash, ::cpputils::hash::mt::VectHash>::value  )
    {
        int nIter = 0;
        aMap.template iterateBegToEnd<int,int>([&nIter](int& a_data, const int& a_key)->bool {
            ::std::cout << "dataBegToEnd(iter:" << (++nIter) << "): key:" << a_key << ", data: "<< a_data << ::std::endl;
            return true;
        });
        
        nIter = 0;
        aMap.template iterateEndToBeg<int,int>([&nIter](int& a_data, const int& a_key)->bool {
            ::std::cout << "dataEndToBeg(iter:" << (++nIter) << "): key:" << a_key << ", data: " << a_data << ::std::endl;
            return true;
        });

        nIter = 0;
        aMap.template IterateBegToEnd<int>([&nIter,&aMap](const TypeIterInt& a_iter)->bool {
            ::std::cout << "dataBegToEnd(iter:" << (++nIter) << "):" << a_iter << ::std::endl;
            aMap.template MoveToStart<int>(a_iter);
            aMap.template MoveToEnd<int>(a_iter);
            return false;
        });
        
        nIter = 0;
        aMap.template IterateEndToBeg<int>([&nIter](const TypeIterInt& a_iter)->bool {
            ::std::cout << "dataEndToBeg(iter:" << (++nIter) << "):" << a_iter << ::std::endl;
            return true;
        });
    }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {

    iter = aMap.template find<int, int>(1);
    ::std::cout << "iter_12: " << iter << ::std::endl;

    if (iter) {
        if constexpr (
            ::std::is_same<TypeHash, ::cpputils::hash::nl::ListHash>::value ||
            ::std::is_same<TypeHash, ::cpputils::hash::nl::VectHash>::value ||
            ::std::is_same<TypeHash, ::cpputils::hash::mt::ListHash>::value  ||  
            ::std::is_same<TypeHash, ::cpputils::hash::mt::VectHash>::value   )
        {
            aMap.MoveToStart(iter);
            aMap.MoveToEnd(iter);
        }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {
        aMap.RemoveEx(iter);
    }  //  if (iter) {
}


#ifdef CPPUTILS_TEST_TEMPLATE_HASH

template <typename TypeTemplHash>
static void TestTemplHash(void)
{
    typedef typename TypeTemplHash::Iterator TypeIterInt;
    size_t unHash;
    typedef typename TypeTemplHash::TypeRawHash TypeHash;
    TypeHash aMap2(1024);
    TypeTemplHash aMapTemp(&aMap2);
    typename TypeTemplHash::Iterator iter;

    iter = aMapTemp.findEx(1, &unHash);
    ::std::cout << "iter_01: " << iter << ::std::endl;

    iter = aMapTemp.find(1);
    ::std::cout << "iter_01b: " << iter << ::std::endl;

    iter = aMapTemp.AddWithKnownHash(unHash, 1, 1);
    ::std::cout << "iter_02: " << iter << ::std::endl;

    if (iter) {
        bool isValid;
        const int cnkey = aMapTemp.key(iter, &isValid);
        ::std::cout << "cnkey: " << cnkey << ::std::endl;
        iter = aMapTemp.findNextTheSame(iter);
        ::std::cout << "iter_01c: " << iter << ::std::endl;
    }

    iter = aMapTemp.AddEvenIfExist(1, 1);
    ::std::cout << "iter_02b: " << iter << ::std::endl;

    iter = aMapTemp.AddIfNotExist(1, 1);
    ::std::cout << "iter_02c: " << iter << ::std::endl;

    iter = aMapTemp.AddOrReturnExisting(1, 1);
    ::std::cout << "iter_02c: " << iter << ::std::endl;

    iter = aMapTemp.findEx(1, &unHash);
    ::std::cout << "iter_03: " << iter << ::std::endl;

    iter = aMapTemp.find(1);
    ::std::cout << "iter_04: " << iter << ::std::endl;

    if (iter) {
        iter = aMapTemp.findNextTheSame(iter);
        ::std::cout << "iter_05: " << iter << ::std::endl;
    }

    iter = aMapTemp.findEx(1, &unHash);
    ::std::cout << "iter_06: " << iter << ::std::endl;

    iter = aMapTemp.AddEvenIfExist(2, 1);
    ::std::cout << "iter_07: " << iter << ::std::endl;

    iter = aMapTemp.AddIfNotExist(1, 1);
    ::std::cout << "iter_08: " << iter << ::std::endl;

    iter = aMapTemp.findEx(1, &unHash);
    ::std::cout << "iterD_09: " << iter << ::std::endl;

    iter = aMapTemp.find(1);
    ::std::cout << "iter_10: " << iter << ::std::endl;
    int i = 0;
    while (iter) {
        iter = aMapTemp.findNextTheSame(iter);
        ::std::cout << "iter_11: " << (++i) << "  " << iter << ::std::endl;
    }  //  while(iter){

    const CinternalHashConstBasic_t rawHashBasic = aMapTemp.getConstHashBase();
    ::std::cout << "rawHashBasic: " << rawHashBasic << ::std::endl;

    if constexpr (
        ::std::is_same<TypeHash, ::cpputils::hash::nl::PureHash>::value ||
        ::std::is_same<TypeHash, ::cpputils::hash::nl::ListHash>::value || 
        ::std::is_same<TypeHash, ::cpputils::hash::nl::VectHash>::value )
    {
        const CinternalHashConst_t rawHash = aMapTemp.getConstHash();
        ::std::cout << "rawHash: " << rawHash << ::std::endl;
    }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {

    if constexpr ( ::std::is_same<TypeHash, ::cpputils::hash::nl::ListHash>::value ){
        const size_t countOfTheType = aMapTemp.count();
        ::std::cout << "countOfTheTypeList: " << countOfTheType << ::std::endl;
        iter = aMapTemp.first();
        int i = 0;
        while (iter) {
            ::std::cout << "iter_list: " << (++i) << "  " << iter << ::std::endl;
            iter = (TypeIterInt)iter->next;
        }  //  while (iter) {
    }  //  if constexpr ( ::std::is_same<TypeHash, ::cpputils::hash::ListHash>::value ){

    if constexpr (::std::is_same<TypeHash, ::cpputils::hash::nl::VectHash>::value) {
        const size_t countOfTheType = aMapTemp.count();
        const ::cpputils::hash::nl::vh::SVectData& vectData = aMapTemp.getVectDataForTypeData();
        ::std::cout << "countOfTheTypeVect: " << countOfTheType << ::std::endl;
        size_t i;
        for (i = 0; i < countOfTheType; ++i) {
            iter = aMapTemp.at(i);
            ::std::cout << "iter_vect: " << "  iter:" << iter << ", vectData.m_items_p[" << i << "]:" << vectData.m_items_p[i] << ::std::endl;
        }  //  for (i = 0; i < countOfTheType; ++i) {
    }  //  if constexpr ( ::std::is_same<TypeHash, ::cpputils::hash::VectHash>::value ){
    
    if constexpr ( 
        ::std::is_same<TypeHash, ::cpputils::hash::mt::ListHash>::value ||
        ::std::is_same<TypeHash, ::cpputils::hash::mt::VectHash>::value  )
    {
        int nIter = 0;
        aMapTemp.iterateBegToEnd([&nIter](int& a_data, const int& a_key)->bool {
            ::std::cout << "dataBegToEnd(iter:" << (++nIter) << "): key:" << a_key << ", data: "<< a_data << ::std::endl;
            return true;
        });
        
        nIter = 0;
        aMapTemp.iterateEndToBeg([&nIter](int& a_data, const int& a_key)->bool {
            ::std::cout << "dataEndToBeg(iter:" << (++nIter) << "): key:" << a_key << ", data: " << a_data << ::std::endl;
            return true;
        });

        nIter = 0;
        aMapTemp.IterateBegToEnd([&nIter,&aMapTemp](const TypeIterInt& a_iter)->bool {
            ::std::cout << "dataBegToEnd(iter:" << (++nIter) << "):" << a_iter << ::std::endl;
            aMapTemp.MoveToStart(a_iter);
            aMapTemp.MoveToEnd(a_iter);
            return false;
        });
        
        nIter = 0;
        aMapTemp.IterateEndToBeg([&nIter](const TypeIterInt& a_iter)->bool {
            ::std::cout << "dataEndToBeg(iter:" << (++nIter) << "):" << a_iter << ::std::endl;
            return true;
        });
    }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {

    iter = aMapTemp.find(1);
    ::std::cout << "iter_12: " << iter << ::std::endl;

    if (iter) {
        if constexpr (
            ::std::is_same<TypeHash, ::cpputils::hash::nl::ListHash>::value ||
            ::std::is_same<TypeHash, ::cpputils::hash::nl::VectHash>::value ||
            ::std::is_same<TypeHash, ::cpputils::hash::mt::ListHash>::value  ||  
            ::std::is_same<TypeHash, ::cpputils::hash::mt::VectHash>::value   )
        {
            aMapTemp.MoveToStart(iter);
            aMapTemp.MoveToEnd(iter);
        }  //  if constexpr ( ::std::is_same_v<TypeHash, ::cpputils::hash::mt::MtListHash>) {
        aMapTemp.RemoveEx(iter);
    }  //  if (iter) {

}

#endif  //  #ifdef CPPUTILS_TEST_TEMPLATE_HASH
