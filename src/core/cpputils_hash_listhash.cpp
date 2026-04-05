//
// repo:            cpputils
// file:			cpputils_hash_listhash.cpp
// path:			src/core/cpputils_hash_listhash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/listhash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace hash{

namespace lh{

static bh::Hash_p* CreateCollectionHash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

}


ListHash::ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    Base(lh::CreateCollectionHash_p(a_numberOfBaskets,a_allocator,a_deallocator))
{
}


void ListHash::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    ((lh::Hash_p*)m_clhash_data_p)->MakeSureHasEnoughLists(a_numberOfLists);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace lh {

Hash_p::~Hash_p() noexcept
{
    ItemBool* pItemNext, * pItem;

    for (int32_t i(0); i < m_numberOfAllocatedDataTypes; ++i) {
        pItem = m_lists_p[i].m_first;
        while (pItem) {
            pItemNext = pItem->next;
            bh::ItemBase* const pItemBaseToDelete = (bh::ItemBase*)pItem;
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
    bh::Hash_p(a_numberOfBaskets,a_allocator,a_deallocator),
    m_numberOfAllocatedDataTypes(0),
    m_lists_p(CPPUTILS_NULL)
{
}


void Hash_p::AddItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept
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


void Hash_p::AddItemToEndOfList(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept
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


void Hash_p::RemoveItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept
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

static bh::Hash_p* CreateCollectionHash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
    if (!a_allocator) {
        a_allocator = &malloc;
    }
    bh::Hash_p* const pClHsData = (bh::Hash_p*)(a_allocator(sizeof(lh::Hash_p)));
    if (!pClHsData) {
        throw ::std::bad_alloc();
    }
    new(pClHsData) lh::Hash_p(a_numberOfBaskets, a_allocator, a_deallocator);
    return pClHsData;
}

}  //  namespace lh{


}}  //  namespace cpputils { namespace hash{
