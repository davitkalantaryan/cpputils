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
protected:
    virtual ~Hash_p() noexcept;

public:
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    ConstCinternalHash_t    m_hash;

private:
    static int32_t getNextDataIndex(void) noexcept;

public:
    virtual void AddItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept;
    virtual void RemoveItemExtraPart(int32_t a_dataIndex, bh::ItemBase* CPPUTILS_ARG_NN a_item) noexcept;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    friend class ::cpputils::hash::Base;
};

}  //  namespace bh{


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
inline int32_t Base::reserveUniqueIdForDataInline(void) const noexcept {
    static int32_t dataIndex = bh::Hash_p::getNextDataIndex();
    return dataIndex;
}


template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const TypeIter*
Base::findExRaw(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key,dataIndex);
    const CinternalHashItem_t iter = CInternalHashFindEx(m_clhash_data_p->m_hash, (const void*)&extKey, sizeof(TypeKeyExt), a_pHash);
    if (iter) {
        const TypeIter* const pNewItem = (const TypeIter*)iter->data;
        return pNewItem;
    }
    return nullptr;
}


template <typename TypeIter>
inline const TypeIter*
Base::findNextTheSameRaw( const TypeIter* CPPUTILS_ARG_NN a_prev ) const noexcept
{
    const bh::ItemBase* const itemPrevVoid_p = (const bh::ItemBase*)a_prev;
    const CinternalHashItem_t hsIter = CInternalHashFindNextTheSame(m_clhash_data_p->m_hash, itemPrevVoid_p->hashIter);
    if (hsIter) {
        const TypeIter* const pNewItem = (const TypeIter*)hsIter->data;
        return pNewItem;
    }
    return nullptr;
}


template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const TypeIter*
Base::AddWithKnownHashRaw(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    TypeIter* const pNewItem = (TypeIter*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(TypeIter)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) TypeIter(a_data_p);
    
    
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key, dataIndex);

    pNewItem->hashIter = CInternalHashAddDataWithKnownHash(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey, sizeof(TypeKeyExt), a_hash);
    if (!(pNewItem->hashIter)) {
        pNewItem->~TypeIter();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        throw ::std::bad_alloc();
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return pNewItem;
}



template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const TypeIter*
Base::AddEvenIfExistRaw(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    TypeIter* const pNewItem = (TypeIter*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(TypeIter)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) TypeIter(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key, dataIndex);

    pNewItem->hashIter = CInternalHashAddDataEvenIfExist(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey, sizeof(TypeKeyExt));
    if (!(pNewItem->hashIter)) {
        pNewItem->~TypeIter();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        throw ::std::bad_alloc();
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return pNewItem;
}


template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline const TypeIter*
Base::AddIfNotExistRaw(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    TypeIter* const pNewItem = (TypeIter*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(TypeIter)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    new(pNewItem) TypeIter(a_data_p);

    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    const TypeKeyExt extKey(a_key, dataIndex);

    pNewItem->hashIter = CInternalHashAddDataIfNotExists(m_clhash_data_p->m_hash, pNewItem, (const void*)&extKey, sizeof(TypeKeyExt));
    if (!(pNewItem->hashIter)) {
        pNewItem->~TypeIter();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        return nullptr;
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return pNewItem;
}


template <typename TypeData>
inline void Base::RemoveEx(const bh::Item<TypeData>* CPPUTILS_ARG_NN a_iter) noexcept
{
    bh::ItemBase* const pItemBaseToDelete = (bh::ItemBase*)a_iter;
    const CinternalHashItem_t hashIter = pItemBaseToDelete->hashIter;
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    m_clhash_data_p->RemoveItemExtraPart(dataIndex, pItemBaseToDelete);
    pItemBaseToDelete->~ItemBase();
    (*(m_clhash_data_p->m_hash->deallocator))(pItemBaseToDelete);
    CInternalHashRemoveDataEx(m_clhash_data_p->m_hash,hashIter);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


namespace bh {


template <typename TypeData>
Item<TypeData>::Item(TypeData* CPPUTILS_ARG_NN a_data_p)
    :
    data(::std::move(*a_data_p))
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

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
