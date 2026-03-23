//
// repo:            cpputils
// file:			cpputils_hash_ListHash.cpp
// path:			src/core/cpputils_hash_ListHash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash2/listhash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace hash{


namespace lh{

static size_t HasherStatic(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static bool IsKeysTheSameStatic(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool StoreKeyStatic(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void UnstoreStatic(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static Hash_p* CreateCollectionHash_p(TypeCinternalAllocator a_allocator);


}  //  namespace ph{


ListHash::~ListHash() noexcept
{
    const TypeCinternalDeallocator aDeallocator = m_clhash_data_p->m_hash->deallocator;
    m_clhash_data_p->~Hash_p();
    (*aDeallocator)(m_clhash_data_p);
}


ListHash::ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_clhash_data_p(lh::CreateCollectionHash_p(a_allocator))
{
    new(m_clhash_data_p) lh::Hash_p(a_numberOfBaskets,a_allocator,a_deallocator);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


namespace lh{


Hash_p::~Hash_p() noexcept
{
    ItemVoid* pItemNext, * pItem;

    for (size_t i(0); i < m_numberOfAllocatedTables; ++i) {
        pItem = m_dataFncs[i].m_first;
        while (pItem) {
            pItemNext = static_cast<ItemVoid*>(pItem->next);
            CInternalHashRemoveDataEx(m_hash, pItem->hashIter);
            (*(m_dataFncs[i].callDestructFnc))(pItem->data_p);
            (*(m_hash->deallocator))(pItem->data_p);
            pItem->~ItemVoid();
            (*(m_hash->deallocator))(pItem);
            pItem = pItemNext;
        }  //  while(pItem){
    }  //  for (size_t i(0); i < m_clmp_data_p->m_numberOfTypes; ++i) {

    (*(m_hash->deallocator))(m_dataFncs);
    CInternalHashDestroy(m_hash);
}


Hash_p::Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_hash(CPPUTILS_NULL),
    m_numberOfAllocatedTables(0),
    m_numberOfDataTypes(0),
    m_counterOfKeyAndHashTypes(-1),
    m_dataFncs(CPPUTILS_NULL)
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

    m_dataFncs = (lh::SDataFunctions*)(*(m_hash->allocator))(sizeof(lh::SDataFunctions));
    if (!m_dataFncs) {
        throw ::std::bad_alloc();
    }
    m_numberOfAllocatedTables = 1;
}


int32_t Hash_p::GetNextDataIndex(const lh::TypeCallDestructFnc& a_callDestructFnc)
{
    const size_t cunThisFuncIndex = (size_t)(m_numberOfDataTypes++);
    if(cunThisFuncIndex>=m_numberOfAllocatedTables){
        const size_t numberOfAllocatedTablesNew = 2 * m_numberOfAllocatedTables;
        lh::SDataFunctions* const dataFncs = m_dataFncs;
        m_dataFncs = (lh::SDataFunctions*)(*(m_hash->allocator))(numberOfAllocatedTablesNew * sizeof(lh::SDataFunctions));
        if (!m_dataFncs) {
            throw ::std::bad_alloc();
        }
        memcpy(m_dataFncs,dataFncs,m_numberOfAllocatedTables * sizeof(lh::SDataFunctions));
        for(size_t i(m_numberOfAllocatedTables); i<numberOfAllocatedTablesNew; ++i){
            m_dataFncs[i].callDestructFnc = [](void*){};
            m_dataFncs[i].isReal = false;
            m_dataFncs[i].m_first = m_dataFncs[i].m_last = 0;
            m_dataFncs[i].m_count = 0;
        }  //  for(size_t i(m_numberOfAllocatedTables); i<numberOfAllocatedTablesNew; ++i){
    }  //  if(cunThisFuncIndex>=m_numberOfAllocatedTables){

    m_dataFncs[cunThisFuncIndex].callDestructFnc = a_callDestructFnc;
    m_dataFncs[cunThisFuncIndex].isReal = true;
    return (int32_t)cunThisFuncIndex;
}


int32_t Hash_p::getNextKeyAndHasherIndex(void) const noexcept
{
    return (++m_counterOfKeyAndHashTypes);
}


void Hash_p::AddItemExtraPart(int32_t a_dataIndex, lh::ItemVoid* CPPUTILS_ARG_NN a_item) noexcept
{
    if(m_dataFncs[a_dataIndex].m_first){
        m_dataFncs[a_dataIndex].m_first->prev = a_item;
    }
    else{
        m_dataFncs[a_dataIndex].m_last = a_item;
    }
    a_item->next = m_dataFncs[a_dataIndex].m_first;
    a_item->prev = CPPUTILS_NULL;
    m_dataFncs[a_dataIndex].m_first = a_item;
    ++(m_dataFncs[a_dataIndex].m_count);
}


void Hash_p::AddItemToEndOfList(int32_t a_dataIndex, lh::ItemVoid* CPPUTILS_ARG_NN a_item) noexcept
{
    if(m_dataFncs[a_dataIndex].m_last){
        m_dataFncs[a_dataIndex].m_last->next = a_item;
    }
    else{
        m_dataFncs[a_dataIndex].m_first = a_item;
    }
    a_item->prev = m_dataFncs[a_dataIndex].m_last;
    a_item->next = CPPUTILS_NULL;
    m_dataFncs[a_dataIndex].m_last = a_item;
    ++(m_dataFncs[a_dataIndex].m_count);
}


void Hash_p::RemoveItemExtraPart(int32_t a_dataIndex, lh::ItemVoid* CPPUTILS_ARG_NN a_item) noexcept
{
    if(a_item->prev){
        a_item->prev->next = a_item->next;
    }
    else{
        m_dataFncs[a_dataIndex].m_first = (lh::ItemVoid*)a_item->next;
    }

    if(a_item->next){
        a_item->next->prev = a_item->prev;
    }
    else{
        m_dataFncs[a_dataIndex].m_last = (lh::ItemVoid*)a_item->prev;
    }

    --(m_dataFncs[a_dataIndex].m_count);
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


CKeyBase::~CKeyBase()
{
}


CKeyBase::CKeyBase(int32_t a_dataIndex, int32_t a_keyAndHashIndex)
:
    dataIndex(a_dataIndex),
    keyAndHashIndex(a_keyAndHashIndex)
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

static size_t HasherStatic(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    const CKeyBase* const pKeyExt = (const CKeyBase*)a_key;
    (void)a_keySize;
    const uint64_t hashByRawKey = pKeyExt->hash();
    const uint64_t typeIndex = (uint64_t)(pKeyExt->dataIndex);
    const uint64_t wholeHash = (typeIndex << 32) | ((uint64_t)((uint32_t)hashByRawKey));
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
