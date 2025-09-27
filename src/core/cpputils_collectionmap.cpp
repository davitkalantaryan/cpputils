//
// repo:            cpputils
// file:			cpputils_named_types.cpp
// path:			src/core/cpputils_named_types.cpp
// created on:		2024 Dec 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cpputils/collectionmap.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <stddef.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils {


CollectionMap::~CollectionMap() noexcept
{
    collectionmap::__private::ItemVoid *pItemNext, *pItem;

    for (int i(0); i < m_clmp_data_p->m_numberOfTypes; ++i) {
        pItem = m_clmp_data_p->m_lists[i].m_first;
        while (pItem) {
            pItemNext = static_cast<collectionmap::__private::ItemVoid*>(pItem->next);
            CInternalHashRemoveDataEx(m_clmp_data_p->m_hash, pItem->hashIter);
            pItem->~ItemVoid();
            (*(m_clmp_data_p->m_hash->deallocator))(pItem);
            pItem = pItemNext;
        }  //  while(pItem){
    }  //  for (size_t i(0); i < m_clmp_data_p->m_numberOfTypes; ++i) {

    m_clmp_data_p->m_hash->deallocator(m_clmp_data_p->m_lists);

    CInternalHashDestroy(m_clmp_data_p->m_hash);
}


CollectionMap::CollectionMap(size_t a_numberOfBaskets,TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_clmp_data_p(new CollectionMap_p())
{
    m_clmp_data_p->m_hash = CInternalHashCreateSmlIntEx(a_numberOfBaskets, a_allocator, a_deallocator);
    if (!(m_clmp_data_p->m_hash)) {
        throw ::std::bad_alloc();
    }
}


const CollectionMap::Item<void>* CollectionMap::getFirstByTypeIndex(int a_typeIndex)const
{
    if (a_typeIndex < (m_clmp_data_p->m_numberOfTypes)) {
        return m_clmp_data_p->m_lists[a_typeIndex].m_first;
    }  //  if (a_typeIndex < (m_clmp_data_p->m_numberOfTypes)) {
    return CPPUTILS_NULL;
}


const CollectionMap::Item<void>* CollectionMap::getLastByTypeIndex(int a_typeIndex)const
{
    if (a_typeIndex < (m_clmp_data_p->m_numberOfTypes)) {
        return m_clmp_data_p->m_lists[a_typeIndex].m_last;
    }  //  if (a_typeIndex < (m_clmp_data_p->m_numberOfTypes)) {
    return CPPUTILS_NULL;
}


void CollectionMap::AddToTheListBegPrivate(Item<void>* CPPUTILS_ARG_NN a_item_p, int a_typeIndex)
{
    const int requieredNumberOfTypes = a_typeIndex + 1;
    if (requieredNumberOfTypes > (m_clmp_data_p->m_numberOfTypes)) {
        const size_t requieredBufferSize = static_cast<size_t>(requieredNumberOfTypes) * sizeof(collectionmap::__private::SnglListItem);
        char* const pTmpList = (char*)m_clmp_data_p->m_hash->allocator(requieredBufferSize);
        if (!pTmpList) {
            throw ::std::bad_alloc();
        }
        memcpy(pTmpList, m_clmp_data_p->m_lists, m_clmp_data_p->m_bufferSize);
        memset(pTmpList + m_clmp_data_p->m_bufferSize, 0, (requieredBufferSize - m_clmp_data_p->m_bufferSize));
        m_clmp_data_p->m_hash->deallocator(m_clmp_data_p->m_lists);
        m_clmp_data_p->m_lists = (collectionmap::__private::SnglListItem*)pTmpList;
        m_clmp_data_p->m_bufferSize = requieredBufferSize;
        m_clmp_data_p->m_numberOfTypes = requieredNumberOfTypes;
    }  //  if (a_typeIndex >= (m_clmp_data_p->m_numberOfTypes)) {

    a_item_p->prev = CPPUTILS_NULL;
    a_item_p->next = m_clmp_data_p->m_lists[a_typeIndex].m_first;
    if (m_clmp_data_p->m_lists[a_typeIndex].m_first) {
        m_clmp_data_p->m_lists[a_typeIndex].m_first->prev = a_item_p;
    }
    else {
        m_clmp_data_p->m_lists[a_typeIndex].m_last = (collectionmap::__private::ItemVoid*)a_item_p;
    }
    m_clmp_data_p->m_lists[a_typeIndex].m_first = (collectionmap::__private::ItemVoid*)a_item_p;
    ++(m_clmp_data_p->m_lists[a_typeIndex].m_count);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

CollectionMap_p::CollectionMap_p()
    :
    m_hash(CPPUTILS_NULL),
    m_bufferSize(0),
    m_numberOfTypes(0),
    m_lists(CPPUTILS_NULL)
{
    (void)m_reserved01;
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace collectionmap{ namespace __private{

CPPUTILS_EXPORT int GetNextIndex(void) noexcept
{
    static int snCounter = 0;
    return (snCounter++);
}

}}  //  namespace collectionmap{ namespace __private{ 


}  //  namespace cpputils {
