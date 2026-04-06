//
// repo:            cpputils
// file:			cpputils_hash_vecthash.cpp
// path:			src/core/cpputils_hash_vecthash.cpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/hash/vecthash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <stdlib.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace hash{

namespace vh{

static bh::Hash_p* CreateCollectionHash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

}


VectHash::VectHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    Base(vh::CreateCollectionHash_p(a_numberOfBaskets,a_allocator,a_deallocator))
{
}


void VectHash::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    ((vh::Hash_p*)m_clhash_data_p)->MakeSureHasEnoughLists(a_numberOfLists);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace vh {

Hash_p::~Hash_p() noexcept
{
    bh::ItemBase* pItem;
    size_t unCount, j;

    for (int32_t i(0); i < m_numberOfAllocatedDataTypes; ++i) {
        unCount = m_vects_p[i].m_count;
        for (j = 0; j < unCount; ++j) {
            pItem = m_vects_p[i].m_items_p[j];
            bh::ItemBase* const pItemBaseToDelete = (bh::ItemBase*)pItem;
            CInternalHashRemoveDataEx(m_hash, pItem->hashIter);
            pItemBaseToDelete->~ItemBase();
            (*(m_hash->deallocator))(pItem);
        }
    }  //  for (size_t i(0); i < m_clmp_data_p->m_numberOfTypes; ++i) {

    (*(m_hash->deallocator))(m_vects_p);
}


Hash_p::Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    bh::Hash_p(a_numberOfBaskets,a_allocator,a_deallocator),
    m_numberOfAllocatedDataTypes(0),
    m_vects_p(CPPUTILS_NULL)
{
}


inline void Hash_p::MakeSureHasEnoughLists(int32_t a_dataIndex)
{
    if (a_dataIndex >= m_numberOfAllocatedDataTypes) {
        const int32_t numberOfAllocatedTablesNew = a_dataIndex+1;
        vh::SVectData* const vects_p = m_vects_p;
        m_vects_p = (vh::SVectData*)(*(m_hash->allocator))((size_t)(numberOfAllocatedTablesNew * sizeof(vh::SVectData)));
        if (!m_vects_p) {
            m_vects_p = vects_p;
            throw ::std::bad_alloc();
        }
        memcpy(m_vects_p, vects_p, (size_t)(m_numberOfAllocatedDataTypes * sizeof(vh::SVectData)));
        for (int32_t i(m_numberOfAllocatedDataTypes); i < numberOfAllocatedTablesNew; ++i) {
            m_vects_p[i].m_items_p = CPPUTILS_NULL;
            m_vects_p[i].m_count = 0;
            m_vects_p[i].m_allocated = 0;
        }  //  for(size_t i(m_numberOfAllocatedTables); i<numberOfAllocatedTablesNew; ++i){
        m_numberOfAllocatedDataTypes = numberOfAllocatedTablesNew;
    }  //  if(cunThisFuncIndex>=m_numberOfAllocatedTables){
}


inline void Hash_p::MakeSureCanAddItemToVector(int32_t a_dataIndex)
{
    const size_t unNewCount = m_vects_p[a_dataIndex].m_count + 1;
    if ((m_vects_p[a_dataIndex].m_allocated) < unNewCount) {
        bh::ItemBase** const items_p = m_vects_p[a_dataIndex].m_items_p;
        m_vects_p[a_dataIndex].m_items_p = (bh::ItemBase**)(*(m_hash->allocator))(unNewCount * sizeof(bh::ItemBase*));
        if (!(m_vects_p[a_dataIndex].m_items_p)) {
            m_vects_p[a_dataIndex].m_items_p = items_p;
            throw ::std::bad_alloc();
        }
        memcpy(m_vects_p[a_dataIndex].m_items_p, items_p, (m_vects_p[a_dataIndex].m_allocated) * sizeof(bh::ItemBase*));
        memset(&(m_vects_p[a_dataIndex].m_items_p[m_vects_p[a_dataIndex].m_allocated]), 0, (unNewCount - (m_vects_p[a_dataIndex].m_allocated)) * sizeof(bh::ItemBase*));
        m_vects_p[a_dataIndex].m_allocated = unNewCount;
    }  //  if ((m_vects_p[a_dataIndex].m_allocated) < unNewCount) {
}


void Hash_p::AddItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept
{
    MakeSureHasEnoughLists(a_dataIndex);
    MakeSureCanAddItemToVector(a_dataIndex);

    bh::ItemBase* const pItemBool = (bh::ItemBase*)a_item;
    m_vects_p[a_dataIndex].m_items_p[m_vects_p[a_dataIndex].m_count] = pItemBool;
    ++(m_vects_p[a_dataIndex].m_count);
}


void Hash_p::AddItemToEndOfList(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept
{
    MakeSureHasEnoughLists(a_dataIndex);
    MakeSureCanAddItemToVector(a_dataIndex);

    memmove(&(m_vects_p[a_dataIndex].m_items_p[1]), m_vects_p[a_dataIndex].m_items_p, (m_vects_p[a_dataIndex].m_count) * sizeof(bh::ItemBase*));
    bh::ItemBase* const pItemBool = (bh::ItemBase*)a_item;
    m_vects_p[a_dataIndex].m_items_p[0] = pItemBool;
    ++(m_vects_p[a_dataIndex].m_count);
}


void Hash_p::RemoveItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept
{
    bh::ItemBase* const pItemBool = (bh::ItemBase*)a_item;

    for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
        if ((m_vects_p[a_dataIndex].m_items_p[i]) == pItemBool) {
            memmove(&(m_vects_p[a_dataIndex].m_items_p[i]), &(m_vects_p[a_dataIndex].m_items_p[i + 1]), (m_vects_p[a_dataIndex].m_count - i - 1) * sizeof(bh::ItemBase*));
            --(m_vects_p[a_dataIndex].m_count);
            return;
        }  //  if ((m_vects_p[a_dataIndex].m_items_p[i]) == pItemBool) {
    }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

static bh::Hash_p* CreateCollectionHash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
    if (!a_allocator) {
        a_allocator = &malloc;
    }
    bh::Hash_p* const pClHsData = (bh::Hash_p*)(a_allocator(sizeof(vh::Hash_p)));
    if (!pClHsData) {
        throw ::std::bad_alloc();
    }
    new(pClHsData) vh::Hash_p(a_numberOfBaskets, a_allocator, a_deallocator);
    return pClHsData;
}

}  //  namespace lh{


}}  //  namespace cpputils { namespace hash{
