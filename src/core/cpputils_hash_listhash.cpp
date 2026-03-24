//
// repo:            cpputils
// file:			cpputils_hash_ListHash.cpp
// path:			src/core/cpputils_hash_ListHash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/listhash.hpp>
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

static int32_t s_dataIndexCounter = -1;


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


ConstCinternalHash_t ListHash::getHash()const
{
        return m_clhash_data_p->m_hash;
}


void ListHash::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    m_clhash_data_p->MakeSureHasEnoughLists(a_numberOfLists);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


namespace lh{


Hash_p::~Hash_p() noexcept
{
    ItemBool* pItemNext, * pItem;

    for (int32_t i(0); i < m_numberOfAllocatedDataTypes; ++i) {
        pItem = m_lists_p[i].m_first;
        while (pItem) {
            pItemNext = pItem->next;
            ItemBase* const pItemBaseToDelete = (ItemBase*)pItem;
            CInternalHashRemoveDataEx(m_hash, pItem->hashIter);
            pItemBaseToDelete->~ItemBase();
            (*(m_hash->deallocator))(pItem);
            pItem = pItemNext;
        }  //  while(pItem){
    }  //  for (size_t i(0); i < m_clmp_data_p->m_numberOfTypes; ++i) {

    (*(m_hash->deallocator))(m_lists_p);
    CInternalHashDestroy(m_hash);
}


Hash_p::Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_hash(CPPUTILS_NULL),
    m_numberOfAllocatedDataTypes(0),
    m_lists_p(CPPUTILS_NULL)
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


void Hash_p::AddItemExtraPart(int32_t a_dataIndex, ItemBase* CPPUTILS_ARG_NN a_item) noexcept
{
    ItemBool* const pItemBool = (ItemBool*)a_item;
    if(m_lists_p[a_dataIndex].m_first){
        m_lists_p[a_dataIndex].m_first->prev = pItemBool;
    }
    else{
        m_lists_p[a_dataIndex].m_last = pItemBool;
    }
    pItemBool->next = m_lists_p[a_dataIndex].m_first;
    pItemBool->prev = CPPUTILS_NULL;
    m_lists_p[a_dataIndex].m_first = pItemBool;
    ++(m_lists_p[a_dataIndex].m_count);
}


void Hash_p::AddItemToEndOfList(int32_t a_dataIndex, ItemBase* CPPUTILS_ARG_NN a_item) noexcept
{
    ItemBool* const pItemBool = (ItemBool*)a_item;
    if(m_lists_p[a_dataIndex].m_last){
        m_lists_p[a_dataIndex].m_last->next = pItemBool;
    }
    else{
        m_lists_p[a_dataIndex].m_first = pItemBool;
    }
    pItemBool->prev = m_lists_p[a_dataIndex].m_last;
    pItemBool->next = CPPUTILS_NULL;
    m_lists_p[a_dataIndex].m_last = pItemBool;
    ++(m_lists_p[a_dataIndex].m_count);
}


void Hash_p::RemoveItemExtraPart(int32_t a_dataIndex, ItemBase* CPPUTILS_ARG_NN a_item) noexcept
{
    ItemBool* const pItemBool = (ItemBool*)a_item;
    if(pItemBool->prev){
        pItemBool->prev->next = pItemBool->next;
    }
    else{
        m_lists_p[a_dataIndex].m_first = pItemBool->next;
    }

    if(pItemBool->next){
        pItemBool->next->prev = pItemBool->prev;
    }
    else{
        m_lists_p[a_dataIndex].m_last = pItemBool->prev;
    }

    --(m_lists_p[a_dataIndex].m_count);
}


void Hash_p::MakeSureHasEnoughLists(int32_t a_dataIndex) noexcept
{
    if (a_dataIndex >= m_numberOfAllocatedDataTypes) {
        const int32_t numberOfAllocatedTablesNew = a_dataIndex+1;
        lh::SListData* const lists_p = m_lists_p;
        m_lists_p = (lh::SListData*)(*(m_hash->allocator))((size_t)(numberOfAllocatedTablesNew * sizeof(lh::SListData)));
        if (!m_lists_p) {
            m_lists_p = lists_p;
            return;
        }
        memcpy(m_lists_p, lists_p, (size_t)(m_numberOfAllocatedDataTypes * sizeof(lh::SListData)));
        for (int32_t i(m_numberOfAllocatedDataTypes); i < numberOfAllocatedTablesNew; ++i) {
            m_lists_p[i].m_first = m_lists_p[i].m_last = CPPUTILS_NULL;
            m_lists_p[i].m_count = 0;
        }  //  for(size_t i(m_numberOfAllocatedTables); i<numberOfAllocatedTablesNew; ++i){
        m_numberOfAllocatedDataTypes = numberOfAllocatedTablesNew;
    }  //  if(cunThisFuncIndex>=m_numberOfAllocatedTables){
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
