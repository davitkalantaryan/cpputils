//
// repo:			cpputils
// file:			main_collection_map_test.cpp
// path:			src/tests/main_collection_map_test.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cpputils/collectionmap.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>


#define CPPUTILS_COLLECTION_MAP_UNIQUE_ID   __COUNTER__

//static inline int& GetNextUniqueId() noexcept {
//    static int counter = 0;
//    return counter;
//}


CPPUTILS_EXPORT int GetNextIndex(void) noexcept;

template <typename TypeData>
static inline int GetUniqueIdInline(void) noexcept {
    static int dataIndex = GetNextIndex();
    return dataIndex;
}


class A {};
class B {};


int main(void)
{	
    ::std::cout << "GetUniqueIdInline<int>():" << GetUniqueIdInline<int>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<int>():" << GetUniqueIdInline<int>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<float>():" << GetUniqueIdInline<float>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<int32_t>():" << GetUniqueIdInline<int32_t>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<A>():" << GetUniqueIdInline<A>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<double>():" << GetUniqueIdInline<double>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<float>():" << GetUniqueIdInline<float>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<int>():" << GetUniqueIdInline<int>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<A>():" << GetUniqueIdInline<A>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<B>():" << GetUniqueIdInline<B>() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<::std::shared_ptr<A> >():" << GetUniqueIdInline<::std::shared_ptr<A> >() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<::std::shared_ptr<B> >():" << GetUniqueIdInline<::std::shared_ptr<B> >() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<::std::shared_ptr<A> >():" << GetUniqueIdInline<::std::shared_ptr<A> >() << ::std::endl;
    ::std::cout << "GetUniqueIdInline<::std::shared_ptr<B> >():" << GetUniqueIdInline<::std::shared_ptr<B> >() << ::std::endl;

    ::cpputils::CollectionMap aMap(1024);

    aMap.AddBegWithKnownHash<int>(1, 1, 1);
    
    ::cpputils::CollectionMap::Iterator<int> iter1 =  aMap.first<int>();
    ::std::cout << "iter1:" << (const void*)iter1 << ::std::endl;

    ::cpputils::CollectionMap::Iterator<int> iter2 = aMap.last<int>();
    ::std::cout << "iter2:" << (const void*)iter2 << ::std::endl;

    ::cpputils::CollectionMap::Iterator<double> iter3 = aMap.first<double>();
    ::std::cout << "iter3:" << (const void*)iter3 << ::std::endl;

    ::cpputils::CollectionMap::Iterator<double> iter4 = aMap.last<double>();
    ::std::cout << "iter4:" << (const void*)iter4 << ::std::endl;

	return 0;
}


CPPUTILS_EXPORT int GetNextIndex(void) noexcept
{
    static int snCounter = 0;
    return (snCounter++);
}
