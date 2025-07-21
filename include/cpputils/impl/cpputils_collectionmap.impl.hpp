//
// repo:            cpputils
// file:			cpputils_collectionmap.impl.hpp
// path:			include/cpputils/cpputils_collectionmap.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONMAP_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONMAP_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONMAP_HPP
#include <cpputils/collectionmap.hpp>
#endif

#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <utility>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils {


namespace collectionmap{ namespace __private{

CPPUTILS_EXPORT int GetNextIndex(void) noexcept;
struct ItemVoid final : public CollectionMap::Item<void> {
    CinternalHashItem_t hashIter;
    void* reserved01;
};


struct SnglListItem {
    ItemVoid*   m_first;
    ItemVoid*   m_last;
    size_t      m_count;
};


}}  //  namespace collectionmap{ namespace __private{


class CPPUTILS_DLL_PRIVATE CollectionMap_p
{
public:
    CollectionMap_p();

public:
    ConstCinternalHash_t                        m_hash;
    size_t                                      m_bufferSize;
    int                                         m_numberOfTypes;
    int                                         m_reserved01;
    collectionmap::__private::SnglListItem*     m_lists;

private:
    CollectionMap_p(const CollectionMap_p&) = delete;
    CollectionMap_p(CollectionMap_p&&) = delete;
    CollectionMap_p& operator=(const CollectionMap_p&) = delete;
    CollectionMap_p& operator=(CollectionMap_p&&) = delete;
};


template <typename DataType>
inline int CollectionMap::getUniqueIdInline(void) noexcept {
    static int dataIndex = collectionmap::__private::GetNextIndex();
    return dataIndex;
}


template <typename DataType>
typename CollectionMap::Iterator<DataType> CollectionMap::first()const noexcept
{
    const CollectionMap::Item<void>* pFirst = getFirstByTypeIndex(getUniqueIdInline<DataType>());
    return (CollectionMap::Iterator<DataType>)pFirst;
}


template <typename DataType>
typename CollectionMap::Iterator<DataType> CollectionMap::last()const noexcept
{
    const CollectionMap::Item<void>* pFirst = getLastByTypeIndex(getUniqueIdInline<DataType>());
    return (CollectionMap::Iterator<DataType>)pFirst;
}


template <typename DataType,typename TypeInt>
typename CollectionMap::Iterator<DataType>
CollectionMap::AddBegWithKnownHash(const DataType& a_data, const TypeInt& a_key, size_t a_hash)
{
    DataType aData(a_data);
    return AddBegWithKnownHash(&aData, a_key, a_hash);
}


template <typename DataType, typename TypeInt>
typename CollectionMap::Iterator<DataType>
CollectionMap::AddBegWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const TypeInt& a_key, size_t a_hash)
{
    Item<DataType>* const pNewItem = (Item<DataType>*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(collectionmap::__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    collectionmap::__private::ItemVoid* const pNewItemVoid = (collectionmap::__private::ItemVoid*)pNewItem;
    pNewItem->prev = pNewItem->next = CPPUTILS_NULL;
    pNewItemVoid->hashIter = CPPUTILS_NULL;

    pNewItem->data_p = (DataType*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(DataType)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }
    const uint64_t typeIndex = (uint64_t)getUniqueIdInline<DataType>();
    const uint64_t wholeKey = (typeIndex << 32) | ((uint64_t)((uint32_t)a_key));
    new(pNewItem->data_p) DataType( ::std::move(*a_data_p) );
    pNewItemVoid->hashIter = CInternalHashAddDataWithKnownHash(m_clmp_data_p->m_hash, pNewItem, (void*)((size_t)wholeKey), sizeof(wholeKey), a_hash);
    if (!(pNewItemVoid->hashIter)) {
        throw ::std::bad_alloc();
    }

    AddToTheListBegPrivate(pNewItemVoid,(int)typeIndex);
    return pNewItem;
}


}  //  namespace cpputils 


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONMAP_IMPL_HPP
