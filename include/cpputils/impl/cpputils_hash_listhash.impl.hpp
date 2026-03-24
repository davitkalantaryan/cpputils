//
// repo:            cpputils
// file:			cpputils_collectionhash.impl.hpp
// path:			include/cpputils/cpputils_collectionhash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
#include <cpputils/hash/listhash.hpp>
#endif


namespace cpputils { namespace hash{


namespace lh{


typedef ListHash::Item<bool> ItemBool;

struct SListData {
    ItemBool*   m_first;
    ItemBool*   m_last;
    size_t      m_count;
};


class CPPUTILS_EXPORT Hash_p
{
private:
    ~Hash_p() noexcept;
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    ConstCinternalHash_t    m_hash;
    int32_t                 m_numberOfAllocatedDataTypes;
    SListData*              m_lists_p;

private:
    static int32_t getNextDataIndex(void) noexcept;
    void AddItemExtraPart(int32_t a_dataIndex, ItemBase* CPPUTILS_ARG_NN a_item) noexcept;
    void AddItemToEndOfList(int32_t a_dataIndex, ItemBase* CPPUTILS_ARG_NN a_item) noexcept;
    void RemoveItemExtraPart(int32_t a_dataIndex, ItemBase* CPPUTILS_ARG_NN a_item) noexcept;
    void MakeSureHasEnoughLists(int32_t a_dataIndex) noexcept;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    friend class ::cpputils::hash::ListHash;
};

}  //  namespace lh{


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
inline int32_t ListHash::reserveUniqueIdForDataInline(void) const noexcept {
    static int32_t dataIndex = lh::Hash_p::getNextDataIndex();
    m_clhash_data_p->MakeSureHasEnoughLists(dataIndex);
    return dataIndex;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
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
typename ListHash::Iterator<TypeData>
ListHash::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key, &unHash);
}


template <typename TypeData>
typename ListHash::Iterator<TypeData>
ListHash::findNextTheSame( const ListHash::Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept
{
    const lh::ItemBool* const itemPrevVoid_p = (const lh::ItemBool*)((lh::ItemBase*)a_prev);
    const CinternalHashItem_t hsIter = CInternalHashFindNextTheSame(m_clhash_data_p->m_hash,itemPrevVoid_p->hashIter);
    if(hsIter){
        return (ListHash::Iterator<TypeData>)hsIter->data;
    }
    return nullptr;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
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

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
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

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
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

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItem);

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt>
bool ListHash::Remove(const TypeKey& a_key) noexcept
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
inline void ListHash::RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    lh::ItemBase* const pItemBaseToDelete = (lh::ItemBase*)a_iter;
    lh::CKeyBase* const pKeyExt = (lh::CKeyBase*)(pItemBaseToDelete->hashIter->key);
    const CinternalHashItem_t hashIter = pItemBaseToDelete->hashIter;
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemBaseToDelete);
    pItemBaseToDelete->~ItemBase();
    (*(m_clhash_data_p->m_hash->deallocator))(pItemBaseToDelete);
    CInternalHashRemoveDataEx(m_clhash_data_p->m_hash,hashIter);
}


template <typename TypeData>
void ListHash::MoveToStart(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    Item<TypeData>* const pItemToMove = (Item<TypeData>*)a_iter;
    lh::CKeyBase* const pKeyExt = (lh::CKeyBase*)(pItemToMove->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemToMove);
    m_clhash_data_p->AddItemExtraPart(pKeyExt->dataIndex, pItemToMove);
}


template <typename TypeData>
void ListHash::MoveToEnd(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    Item<TypeData>* const pItemToMove = (Item<TypeData>*)a_iter;
    lh::CKeyBase* const pKeyExt = (lh::CKeyBase*)(pItemToMove->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex, pItemToMove);
    m_clhash_data_p->AddItemToEndOfList(pKeyExt->dataIndex, pItemToMove);
}


template <typename TypeData>
typename ListHash::Iterator<TypeData> ListHash::first()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    return (Iterator<TypeData>)((lh::ItemBase*)m_clhash_data_p->m_lists_p[dataIndex].m_first);
}


template <typename TypeData>
typename ListHash::Iterator<TypeData> ListHash::last()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    return (Iterator<TypeData>)((lh::ItemBase*)m_clhash_data_p->m_lists_p[dataIndex].m_last);
}


template <typename TypeData>
size_t ListHash::count()const noexcept
{
    const int32_t dataIndex = reserveUniqueIdForDataInline<TypeData>();
    return m_clhash_data_p->m_lists_p[dataIndex].m_count;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename TypeData>
ListHash::Item<TypeData>::Item(TypeData* CPPUTILS_ARG_NN a_data_p)
    :
    prev(CPPUTILS_NULL),
    next(CPPUTILS_NULL),
    data(::std::move(*a_data_p))
{
}


namespace lh{

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


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_IMPL_HPP
