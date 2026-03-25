//
// repo:            cpputils
// file:			cpputils_hash_mt_purehash.cpp
// path:			src/core/cpputils_hash_mt_purehash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/mt/purehash.hpp>


namespace cpputils { namespace hash{ namespace mt{


MtPureHash::MtPureHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_nsHash(a_numberOfBaskets,a_allocator,a_deallocator)
{
}


ConstCinternalHash_t MtPureHash::getHash()const
{
        return m_nsHash.getHash();
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{
