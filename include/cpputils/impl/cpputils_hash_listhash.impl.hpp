//
// repo:            cpputils
// file:			cpputils_hash_listhash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_listhash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_LISTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_LISTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
#include <cpputils/hash/listhash.hpp>
#endif


namespace cpputils { namespace hash{


namespace lh{


struct SListData {
    Clh::ItemBase*  m_first;
    Clh::ItemBase*  m_last;
    size_t          m_count;
};


class CPPUTILS_EXPORT Hash_p : public bh::Hash_p
{
private:
    ~Hash_p() noexcept;

public:
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    int32_t                 m_numberOfAllocatedDataTypes;
    SListData*              m_lists_p;

private:
    inline void MakeSureHasEnoughLists(int32_t a_dataIndex);
    virtual void AddItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept override;
    virtual void RemoveItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept override;
    void AddItemToEndOfList(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    friend class ::cpputils::hash::ListHash;
};

}  //  namespace lh{


template <typename TypeData>
void ListHash::MoveToStart(const Iterator<TypeData>& a_iter) noexcept
{
    Item<TypeData>* const pItemToMove = (Item<TypeData>*)a_iter;
    bh::CKeyBase* const pKeyExt = (bh::CKeyBase*)(pItemToMove->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemToMove);
    m_clhash_data_p->AddItemExtraPart(pKeyExt->dataIndex, pItemToMove);
}


template <typename TypeData>
void ListHash::MoveToEnd(const Iterator<TypeData>& a_iter) noexcept
{
    Item<TypeData>* const pItemToMove = (Item<TypeData>*)a_iter;
    bh::CKeyBase* const pKeyExt = (bh::CKeyBase*)(pItemToMove->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemToMove);
    ((lh::Hash_p*)m_clhash_data_p)->AddItemToEndOfList(pKeyExt->dataIndex, pItemToMove);
}


template <typename TypeData>
typename ListHash::Iterator<TypeData> ListHash::first()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    return (Iterator<TypeData>)((bh::ItemBase*)((lh::Hash_p*)m_clhash_data_p)->m_lists_p[dataIndex].m_first);
}


template <typename TypeData>
typename ListHash::Iterator<TypeData> ListHash::last()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    return (Iterator<TypeData>)((bh::ItemBase*)((lh::Hash_p*)m_clhash_data_p)->m_lists_p[dataIndex].m_last);
}


template <typename TypeData>
size_t ListHash::count()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    if (dataIndex < (((lh::Hash_p*)m_clhash_data_p)->m_numberOfAllocatedDataTypes)) {
        return ((lh::Hash_p*)m_clhash_data_p)->m_lists_p[dataIndex].m_count;
    }
    return 0;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
Clh::Item<TypeData>::Item(TypeData* CPPUTILS_ARG_NN a_data_p)
    :
    data(::std::move(*a_data_p))
{
}


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
