//
// repo:            cpputils
// file:			cpputils_hash_vecthash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_vecthash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_VECTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_VECTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VECTHASH_HPP
#include <cpputils/hash/vecthash.hpp>
#endif


namespace cpputils { namespace hash{


namespace vh{


struct SVectData {
    bh::ItemBase**  m_items_p;
    size_t          m_count;
    size_t          m_allocated;
};


class CPPUTILS_EXPORT Hash_p : public bh::Hash_p
{
private:
    ~Hash_p() noexcept;

public:
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    int32_t                 m_numberOfAllocatedDataTypes;
    SVectData*              m_vects_p;

private:
    inline void MakeSureHasEnoughLists(int32_t a_dataIndex);
    inline void MakeSureCanAddItemToVector(int32_t a_dataIndex);
    virtual void AddItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept override;
    virtual void RemoveItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept override;
    void AddItemToEndOfList(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    friend class ::cpputils::hash::VectHash;
};

}  //  namespace lh{


template <typename TypeData>
void VectHash::MoveToStart(const Iterator<TypeData>& a_iter) noexcept
{
    Item<TypeData>* const pItemToMove = (Item<TypeData>*)a_iter;
    bh::CKeyBase* const pKeyExt = (bh::CKeyBase*)(pItemToMove->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemToMove);
    m_clhash_data_p->AddItemExtraPart(pKeyExt->dataIndex, pItemToMove);
}


template <typename TypeData>
void VectHash::MoveToEnd(const Iterator<TypeData>& a_iter) noexcept
{
    Item<TypeData>* const pItemToMove = (Item<TypeData>*)a_iter;
    bh::CKeyBase* const pKeyExt = (bh::CKeyBase*)(pItemToMove->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemToMove);
    ((vh::Hash_p*)m_clhash_data_p)->AddItemToEndOfList(pKeyExt->dataIndex, pItemToMove);
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::first()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    if ((dataIndex < (((vh::Hash_p*)m_clhash_data_p)->m_numberOfAllocatedDataTypes)) && (((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_count)>0)) {
        return (Iterator<TypeData>)((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_items_p[0]);
    }
    return CPPUTILS_NULL;
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::last()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    if ((dataIndex < (((vh::Hash_p*)m_clhash_data_p)->m_numberOfAllocatedDataTypes)) && (((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_count) > 0)) {
        return (Iterator<TypeData>)((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_items_p[((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_count)-1]);
    }
    return CPPUTILS_NULL;
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::at(size_t a_index)const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    if ((dataIndex < (((vh::Hash_p*)m_clhash_data_p)->m_numberOfAllocatedDataTypes)) && (((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_count) > a_index)) {
        return (Iterator<TypeData>)((bh::ItemBase*)((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_items_p[a_index]);
    }
    return CPPUTILS_NULL;
}


template <typename TypeData>
size_t VectHash::count()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    if (dataIndex < (((vh::Hash_p*)m_clhash_data_p)->m_numberOfAllocatedDataTypes)) {
        return ((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex].m_count;
    }
    return 0;
}


template <typename TypeData>
const vh::SVectData& VectHash::getVectDataForTypeData(const int32_t a_dataIndex)const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    ((vh::Hash_p*)m_clhash_data_p)->MakeSureHasEnoughLists(dataIndex);
    return ((vh::Hash_p*)m_clhash_data_p)->m_vects_p[dataIndex];
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
Cvh::Item<TypeData>::Item(TypeData* CPPUTILS_ARG_NN a_data_p)
    :
    data(::std::move(*a_data_p))
{
}


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_VECTHASH_IMPL_HPP
