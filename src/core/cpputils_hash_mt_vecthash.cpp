//
// repo:            cpputils
// file:			cpputils_hash_listhash.cpp
// path:			src/core/cpputils_hash_listhash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/mt/vecthash.hpp>


namespace cpputils { namespace hash{ namespace mt{


VectHash::VectHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    Base<hash::VectHash>(a_numberOfBaskets,a_allocator,a_deallocator)
{
}


void VectHash::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        m_nsHash.AllocateListsInAdvance(a_numberOfLists);
    }  //  lock guard ends
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{
