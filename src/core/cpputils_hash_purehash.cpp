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
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace hash{


namespace ph{

static size_t HasherStatic(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static bool IsKeysTheSameStatic(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool StoreKeyStatic(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void UnstoreStatic(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static Hash_p* CreateCollectionHash_p(TypeCinternalAllocator a_allocator);

static int32_t s_dataIndexCounter = -1;


}  //  namespace ph{


PureHash::~PureHash() noexcept
{
    const TypeCinternalDeallocator aDeallocator = m_clhash_data_p->m_hash->deallocator;
    m_clhash_data_p->~Hash_p();
    (*aDeallocator)(m_clhash_data_p);
}


PureHash::PureHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_clhash_data_p(ph::CreateCollectionHash_p(a_allocator))
{
    new(m_clhash_data_p) ph::Hash_p(a_numberOfBaskets,a_allocator,a_deallocator);
}


ConstCinternalHash_t PureHash::getHash()const
{
        return m_clhash_data_p->m_hash;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


namespace ph{


Hash_p::~Hash_p() noexcept
{
    CInternalHashDestroy(m_hash);
}


Hash_p::Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_hash(CPPUTILS_NULL)
{
    m_hash = CInternalHashCreateAnyEx(
        a_numberOfBaskets,
        &HasherStatic,
        &IsKeysTheSameStatic,
        &StoreKeyStatic,
        &UnstoreStatic,
        a_allocator, a_deallocator);
    if (!m_hash) {
        throw ::std::bad_alloc();
    }
}


int32_t Hash_p::getNextDataIndex(void) noexcept
{
    return (++s_dataIndexCounter);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

CKeyBase::CKeyBase(int32_t a_dataIndex)
:
    dataIndex(a_dataIndex)
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

static size_t HasherStatic(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    const CKeyBase* const pKeyExt = (const CKeyBase*)a_key;
    (void)a_keySize;
    const uint64_t hashByRawKey = pKeyExt->hash();
    const uint64_t typeIndex = (uint64_t)(pKeyExt->dataIndex);
    const uint64_t wholeHash = typeIndex | (hashByRawKey<<8);
    return (size_t)wholeHash;
}


static bool IsKeysTheSameStatic(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
    const CKeyBase* const pKey1Ext = (const CKeyBase*)a_key1;
    const CKeyBase* const pKey2Ext = (const CKeyBase*)a_key2;
    (void)a_keySize1;
    (void)a_keySize2;
    return pKey1Ext->areTheKeysSame(*pKey2Ext);
}


static bool StoreKeyStatic(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    const CKeyBase* const pKeyExt = (const CKeyBase*)a_key;
    CKeyBase* const pKeyToStoreExt = pKeyExt->clone(a_allocator);
    *a_pKeyStore = (void*)pKeyToStoreExt;
    (void)a_pKeySizeStore;
    (void)a_keySize;
    return true;
}


static void UnstoreStatic(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    CKeyBase* const pKeyExt = (CKeyBase*)a_key;
    pKeyExt->~CKeyBase();
    (*a_deallocator)(pKeyExt);
    (void)a_keySize;
}


static Hash_p* CreateCollectionHash_p(TypeCinternalAllocator a_allocator)
{
    if (!a_allocator) {
        a_allocator = &malloc;
    }
    Hash_p* const pClHsData = (Hash_p*)(a_allocator(sizeof(Hash_p)));
    if (!pClHsData) {
        throw ::std::bad_alloc();
    }
    return pClHsData;
}


}  //  namespace lh{


}}  //  namespace cpputils { namespace hash{
