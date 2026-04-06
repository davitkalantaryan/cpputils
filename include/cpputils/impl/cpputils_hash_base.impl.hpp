//
// repo:            cpputils
// file:			cpputils_hash_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_HPP
#include <cpputils/hash/base.hpp>
#endif


namespace cpputils { namespace hash{


namespace bh{


class CPPUTILS_EXPORT Hash_p
{
public:
    virtual ~Hash_p() noexcept;
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

    static int32_t getNextDataIndex(void) noexcept;
    virtual void AddItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept;
    virtual void RemoveItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept;

public:
    ConstCinternalHash_t    m_hash;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    //friend class ::cpputils::hash::Base;
};

}  //  namespace bh{


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeIterCont>
Base<TypeIterCont>::~Base() noexcept
{
    const TypeCinternalDeallocator aDeallocator = m_clhash_data_p->m_hash->deallocator;
    m_clhash_data_p->~Hash_p();
    (*aDeallocator)(m_clhash_data_p);
}


template <typename TypeIterCont>
Base<TypeIterCont>::Base(bh::Hash_p* CPPUTILS_ARG_NN a_clhash_data_p)
    :
    m_clhash_data_p(a_clhash_data_p)
{
}


template <typename TypeIterCont>
ConstCinternalHash_t Base<TypeIterCont>::getHash()const
{
    return m_clhash_data_p->m_hash;
}


template <typename TypeIterCont>
template <typename TypeData>
inline int32_t Base<TypeIterCont>::reserveUniqueIdForDataInline(void) const noexcept {
    static int32_t dataIndex = bh::Hash_p::getNextDataIndex();
    return dataIndex;
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key,dataIndex);
    const CinternalHashItem_t iter = CInternalHashFindEx(m_clhash_data_p->m_hash, (const void*)&extKey, sizeof(TypeKeyExt), a_pHash);
    if (iter) {
        const bh::ItemBase* const pNewItem = (const bh::ItemBase*)iter->data;
        return (const Base<TypeIterCont>::Item<TypeData>*)pNewItem;
    }
    return nullptr;
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, &unHash);
}


template <typename TypeIterCont>
template <typename TypeData>
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::findNextTheSame(const Base<TypeIterCont>::Item<TypeData>* a_prev ) const noexcept
{
    const bh::ItemBase* const itemPrevVoid_p = (const bh::ItemBase*)a_prev;
    const CinternalHashItem_t hsIter = CInternalHashFindNextTheSame(m_clhash_data_p->m_hash, itemPrevVoid_p->hashIter);
    if (hsIter) {
        const bh::ItemBase* const pNewItem = (const bh::ItemBase*)hsIter->data;
        return (const Base<TypeIterCont>::Item<TypeData>*)pNewItem;
    }
    return nullptr;
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(Item<TypeData>)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) Item<TypeData>(a_data_p);
    
    
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key, dataIndex);

    pNewItem->hashIter = CInternalHashAddDataWithKnownHash(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey, sizeof(TypeKeyExt), a_hash);
    if (!(pNewItem->hashIter)) {
        pNewItem->~Item<TypeData>();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        throw ::std::bad_alloc();
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return (const Base<TypeIterCont>::Item<TypeData>*)pNewItem;
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash<TypeData,TypeKey, TypeHasher,TypeKeyExt>(&aData, a_key, a_hash);
}



template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(Item<TypeData>)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) Item<TypeData>(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key, dataIndex);

    pNewItem->hashIter = CInternalHashAddDataEvenIfExist(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey, sizeof(TypeKeyExt));
    if (!(pNewItem->hashIter)) {
        pNewItem->~Item<TypeData>();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        throw ::std::bad_alloc();
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return (const Base<TypeIterCont>::Item<TypeData>*)pNewItem;
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key);
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(Item<TypeData>)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) Item<TypeData>(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key, dataIndex);

    pNewItem->hashIter = CInternalHashAddDataIfNotExists(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey, sizeof(TypeKeyExt));
    if (!(pNewItem->hashIter)) {
        pNewItem->~Item<TypeData>();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        return nullptr;
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return (const Base<TypeIterCont>::Item<TypeData>*)pNewItem;
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const typename Base<TypeIterCont>::template Item<TypeData>*
Base<TypeIterCont>::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key);
}


template <typename TypeIterCont>
template <typename TypeData>
inline void Base<TypeIterCont>::RemoveEx(const Item<TypeData>* a_iter) noexcept
{
    bh::ItemBase* const pItemBaseToDelete = (bh::ItemBase*)a_iter;
    const CinternalHashItem_t hashIter = pItemBaseToDelete->hashIter;
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    m_clhash_data_p->RemoveItemExtraPart(dataIndex, pItemBaseToDelete);
    pItemBaseToDelete->~ItemBase();
    (*(m_clhash_data_p->m_hash->deallocator))(pItemBaseToDelete);
    CInternalHashRemoveDataEx(m_clhash_data_p->m_hash,hashIter);
}


template <typename TypeIterCont>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline bool Base<TypeIterCont>::Remove(const TypeKey& a_key) noexcept
{
    size_t unHash;
    const Item<TypeData>* const pItemToDelete = findEx<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key,&unHash);
    if (pItemToDelete) {
        RemoveEx<TypeData>(pItemToDelete);
        return true;
    }
    return false;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


namespace bh {


template <typename TypeKey, typename TypeHasher >
SKeyAny<TypeKey,TypeHasher>::SKeyAny(const TypeKey& a_rawKey, int32_t a_dataIndex)
    :
    CKeyBase(a_dataIndex),
    rawKey(a_rawKey)
{
}


template <typename TypeKey, typename TypeHasher >
uint64_t SKeyAny<TypeKey,TypeHasher>::hash()const
{
    TypeHasher aHasher;
    const uint64_t unHash = (uint64_t)aHasher(this->rawKey);
    return unHash;
}


template <typename TypeKey, typename TypeHasher >
bool SKeyAny<TypeKey,TypeHasher>::areTheKeysSame(const CKeyBase& a_key2) const
{
    if((this->dataIndex)==(a_key2.dataIndex)){
        const SKeyAny<TypeKey,TypeHasher>& key2Ext = (const SKeyAny<TypeKey,TypeHasher>&)a_key2;
        return (this->rawKey)==(key2Ext.rawKey);
    }
    return false;
}


template <typename TypeKey, typename TypeHasher >
CKeyBase* SKeyAny<TypeKey,TypeHasher>::clone(TypeCinternalAllocator a_allocator)const
{
    SKeyAny<TypeKey,TypeHasher>* const pNew = (SKeyAny<TypeKey,TypeHasher>*)(*a_allocator)(sizeof(SKeyAny<TypeKey,TypeHasher>));
    new(pNew) SKeyAny<TypeKey,TypeHasher>(*this);
    return pNew;
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeIntKey>
SKeyInt<TypeIntKey>::SKeyInt(const TypeIntKey& a_rawKey, int32_t a_dataIndex)
    :
    CKeyBase(a_dataIndex),
    rawKey(a_rawKey)
{
}


template <typename TypeIntKey >
uint64_t SKeyInt<TypeIntKey>::hash()const
{
    const size_t unHash = (uint64_t)(this->rawKey);
    return unHash;
}


template <typename TypeIntKey >
bool SKeyInt<TypeIntKey>::areTheKeysSame(const CKeyBase& a_key2) const
{
    if((this->dataIndex)==(a_key2.dataIndex)){
        const SKeyInt<TypeIntKey>& key2Ext = (const SKeyInt<TypeIntKey>&)a_key2;
        return (this->rawKey)==(key2Ext.rawKey);
    }
    return false;
}


template <typename TypeIntKey >
CKeyBase* SKeyInt<TypeIntKey>::clone(TypeCinternalAllocator a_allocator)const
{
    SKeyInt<TypeIntKey>* const pNew = (SKeyInt<TypeIntKey>*)(*a_allocator)(sizeof(SKeyInt<TypeIntKey>));
    new(pNew) SKeyInt<TypeIntKey>(*this);
    return pNew;
}


}  //  namespace bh{


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
