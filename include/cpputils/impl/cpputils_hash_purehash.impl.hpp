//
// repo:            cpputils
// file:			cpputils_hash_purehash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_purehash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_HPP
#include <cpputils/hash/purehash.hpp>
#endif


namespace cpputils { namespace hash{


namespace ph{


class CPPUTILS_EXPORT Hash_p
{
private:
    ~Hash_p() noexcept;
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    ConstCinternalHash_t    m_hash;

private:
    static int32_t getNextDataIndex(void) noexcept;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    friend class PureHash;
};

}  //  namespace ph{


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
inline int32_t PureHash::reserveUniqueIdForDataInline(void) const noexcept {
    static int32_t dataIndex = ph::Hash_p::getNextDataIndex();
    return dataIndex;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key,dataIndex);
    const CinternalHashItem_t iter = CInternalHashFindEx(m_clhash_data_p->m_hash, (const void*)&extKey, sizeof(TypeKeyExt), a_pHash);
    if (iter) {
        const Item<TypeData>* const pNewItem = (const Item<TypeData>*)iter->data;
        return pNewItem;
    }
    return nullptr;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key, &unHash);
}


template <typename TypeData>
typename PureHash::Iterator<TypeData>
PureHash::findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept
{
    const ph::ItemBase* const itemPrevVoid_p = (const ph::ItemBase*)a_prev;
    const CinternalHashItem_t hsIter = CInternalHashFindNextTheSame(m_clhash_data_p->m_hash, itemPrevVoid_p->hashIter);
    if (hsIter) {
        return (Iterator<TypeData>)hsIter->data;
    }
    return nullptr;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(Item<TypeData>)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) Item<TypeData>(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key,dataIndex);

    pNewItem->hashIter = CInternalHashAddDataWithKnownHash(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey,sizeof(TypeKeyExt), a_hash);
    if (!(pNewItem->hashIter)) {
        pNewItem->~Item<TypeData>();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        throw ::std::bad_alloc();
    }

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(Item<TypeData>)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) Item<TypeData>(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key,dataIndex);

    pNewItem->hashIter = CInternalHashAddDataEvenIfExist(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey,sizeof(TypeKeyExt));
    if (!(pNewItem->hashIter)) {
        pNewItem->~Item<TypeData>();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        throw ::std::bad_alloc();
    }

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(Item<TypeData>)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) Item<TypeData>(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key,dataIndex);

    pNewItem->hashIter = CInternalHashAddDataIfNotExists(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey,sizeof(TypeKeyExt));
    if (!(pNewItem->hashIter)) {
        pNewItem->~Item<TypeData>();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        return nullptr;
    }

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt>
bool PureHash::Remove(const TypeKey& a_key) noexcept
{
    size_t unHash;
    const Iterator<TypeData> iter = findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key,&unHash);
    if(iter){
        RemoveEx<TypeData>(iter);
        return true;
    }
    return false;
}


template <typename TypeData>
inline void PureHash::RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    ph::ItemBase* const pItemBaseToDelete = (ph::ItemBase*)a_iter;
    ph::CKeyBase* const pKeyExt = (ph::CKeyBase*)(pItemBaseToDelete->hashIter->key);
    const CinternalHashItem_t hashIter = pItemBaseToDelete->hashIter;
    pItemBaseToDelete->~ItemBase();
    (*(m_clhash_data_p->m_hash->deallocator))(pItemBaseToDelete);
    CInternalHashRemoveDataEx(m_clhash_data_p->m_hash,hashIter);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename TypeData>
PureHash::Item<TypeData>::Item(TypeData* CPPUTILS_ARG_NN a_data_p)
    :
    data(::std::move(*a_data_p))
{
}


namespace ph{

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


}  //  namespace ph{


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
