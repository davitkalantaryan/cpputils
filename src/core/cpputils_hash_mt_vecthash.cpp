//
// repo:            cpputils
// file:			cpputils_hash_listhash.cpp
// path:			src/core/cpputils_hash_listhash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/mt/vecthash.hpp>


namespace cpputils { namespace hash{ namespace mt{


void VectHash::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        m_nsHash.AllocateListsInAdvance(a_numberOfLists);
    }  //  lock guard ends
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{
