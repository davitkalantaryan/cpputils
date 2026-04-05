//
// repo:            cpputils
// file:			cpputils_hash_purehash.cpp
// path:			src/core/cpputils_hash_purehash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/purehash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace hash{


namespace ph{

static bh::Hash_p* CreateCollectionHash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

}


PureHash::PureHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    Base(ph::CreateCollectionHash_p(a_numberOfBaskets,a_allocator,a_deallocator))
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace ph {

static bh::Hash_p* CreateCollectionHash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
    if (!a_allocator) {
        a_allocator = &malloc;
    }
    bh::Hash_p* const pClHsData = (bh::Hash_p*)(a_allocator(sizeof(bh::Hash_p)));
    if (!pClHsData) {
        throw ::std::bad_alloc();
    }
    new(pClHsData) bh::Hash_p(a_numberOfBaskets, a_allocator, a_deallocator);
    return pClHsData;
}

}  //  namespace ph{


}}  //  namespace cpputils { namespace hash{
