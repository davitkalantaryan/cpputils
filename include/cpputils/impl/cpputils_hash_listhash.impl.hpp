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


typedef void (*TypeCallDestructFnc)(void* a_key);

struct ItemVoid final : public ListHash::Item<void> {
    CinternalHashItem_t     hashIter;
private:
    ItemVoid(const ItemVoid&)=delete;
    ItemVoid(ItemVoid&&) = delete;
    ItemVoid& operator=(const ItemVoid&) = delete;
    ItemVoid& operator=(ItemVoid&&) = delete;
};

struct SDataFunctions{
    TypeCallDestructFnc callDestructFnc;
    ItemVoid*           m_first;
    ItemVoid*           m_last;
    size_t              m_count;
    bool                isReal;
    bool                reserved01[(sizeof(TypeCallDestructFnc)-sizeof(bool))/sizeof(bool)];
};


class CPPUTILS_EXPORT Hash_p
{
private:
    ~Hash_p() noexcept;
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    ConstCinternalHash_t    m_hash;
    size_t                  m_numberOfAllocatedTables;
    int32_t                 m_numberOfDataTypes;
    mutable int32_t         m_counterOfKeyAndHashTypes;
    SDataFunctions*         m_dataFncs;

private:
    int32_t GetNextDataIndex(const TypeCallDestructFnc& a_callDestructFnc);
    int32_t getNextKeyAndHasherIndex(void) const noexcept;
    void AddItemExtraPart(int32_t a_dataIndex, lh::ItemVoid* CPPUTILS_ARG_NN a_item) noexcept;
    void AddItemToEndOfList(int32_t a_dataIndex, lh::ItemVoid* CPPUTILS_ARG_NN a_item) noexcept;
    void RemoveItemExtraPart(int32_t a_dataIndex, lh::ItemVoid* CPPUTILS_ARG_NN a_item) noexcept;

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
inline int ListHash::getReserveUniqueIdForDataInline(void) const noexcept {
    static int dataIndex = m_clhash_data_p->GetNextDataIndex([](void* a_data_p){((TypeData*)a_data_p)->~TypeData();});
    return dataIndex;
}


template <typename TypeKey, typename TypeHasher>
inline int ListHash::getReserveUniqueIdForKeyAndHasherInline(void) const noexcept {
    static int dataIndex = m_clhash_data_p->getNextKeyAndHasherIndex();
    return dataIndex;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename ListHash::Iterator<TypeData>
ListHash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    const int32_t dataIndex = getReserveUniqueIdForDataInline<TypeData>();
    const int32_t keyAndHashIndex = getReserveUniqueIdForKeyAndHasherInline<TypeKey,TypeHasher>();
    const TypeKeyExt extKey(a_key,dataIndex,keyAndHashIndex);
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
    const lh::ItemVoid* const itemPrevVoid_p = (const lh::ItemVoid*)a_prev;
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
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(lh::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    lh::ItemVoid* const pNewItemVoid = (lh::ItemVoid*)pNewItem;

    pNewItem->data_p = (TypeData*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }
    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));

    const int32_t dataIndex = getReserveUniqueIdForDataInline<TypeData>();
    const int32_t keyAndHashIndex = getReserveUniqueIdForKeyAndHasherInline<TypeKey,TypeHasher>();
    const TypeKeyExt extKey(a_key,dataIndex,keyAndHashIndex);

    pNewItemVoid->hashIter = CInternalHashAddDataWithKnownHash(m_clhash_data_p->m_hash,pNewItemVoid, (const void*)&extKey,sizeof(TypeKeyExt), a_hash);
    if (!(pNewItemVoid->hashIter)) {
        throw ::std::bad_alloc();
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItemVoid);

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
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(lh::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    lh::ItemVoid* const pNewItemVoid = (lh::ItemVoid*)pNewItem;

    pNewItem->data_p = (TypeData*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }
    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));

    const int32_t dataIndex = getReserveUniqueIdForDataInline<TypeData>();
    const int32_t keyAndHashIndex = getReserveUniqueIdForKeyAndHasherInline<TypeKey,TypeHasher>();
    const TypeKeyExt extKey(a_key,dataIndex,keyAndHashIndex);

    pNewItemVoid->hashIter = CInternalHashAddDataEvenIfExist(m_clhash_data_p->m_hash,pNewItemVoid, (const void*)&extKey,sizeof(TypeKeyExt));
    if (!(pNewItemVoid->hashIter)) {
        throw ::std::bad_alloc();
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex,pNewItemVoid);

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
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(lh::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    lh::ItemVoid* const pNewItemVoid = (lh::ItemVoid*)pNewItem;

    pNewItem->data_p = (TypeData*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }
    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));

    const int32_t dataIndex = getReserveUniqueIdForDataInline<TypeData>();
    const int32_t keyAndHashIndex = getReserveUniqueIdForKeyAndHasherInline<TypeKey,TypeHasher>();
    const TypeKeyExt extKey(a_key,dataIndex,keyAndHashIndex);

    pNewItemVoid->hashIter = CInternalHashAddDataIfNotExists(m_clhash_data_p->m_hash,pNewItemVoid, (const void*)&extKey,sizeof(TypeKeyExt));
    if (!(pNewItemVoid->hashIter)) {
        pNewItem->data_p->~TypeData();
        (*(m_clhash_data_p->m_hash->deallocator))(pNewItem);
        return nullptr;
    }

    m_clhash_data_p->AddItemExtraPart(dataIndex, pNewItemVoid);

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
    lh::ItemVoid* const pItemVoid = (lh::ItemVoid*)a_iter;
    lh::CKeyBase* const pKeyExt = (lh::CKeyBase*)(pItemVoid->hashIter->key);
    const lh::SDataFunctions& dtFncs = (m_clhash_data_p->m_dataFncs)[pKeyExt->dataIndex];
    const CinternalHashItem_t hashIter = pItemVoid->hashIter;
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex,pItemVoid);
    (*(dtFncs.callDestructFnc))(pItemVoid->data_p);
    (*(m_clhash_data_p->m_hash->deallocator))(pItemVoid->data_p);
    (*(m_clhash_data_p->m_hash->deallocator))(pItemVoid);
    CInternalHashRemoveDataEx(m_clhash_data_p->m_hash,hashIter);
}


template <typename TypeData>
void ListHash::MoveToStart(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    lh::ItemVoid* const pItemVoid = (lh::ItemVoid*)a_iter;
    lh::CKeyBase* const pKeyExt = (lh::CKeyBase*)(pItemVoid->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex,pItemVoid);
    m_clhash_data_p->AddItemExtraPart(pKeyExt->dataIndex,pItemVoid);
}


template <typename TypeData>
void ListHash::MoveToEnd(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    lh::ItemVoid* const pItemVoid = (lh::ItemVoid*)a_iter;
    lh::CKeyBase* const pKeyExt = (lh::CKeyBase*)(pItemVoid->hashIter->key);
    m_clhash_data_p->RemoveItemExtraPart(pKeyExt->dataIndex,pItemVoid);
    m_clhash_data_p->AddItemToEndOfList(pKeyExt->dataIndex,pItemVoid);
}


template <typename TypeData>
typename ListHash::Iterator<TypeData> ListHash::first()const noexcept
{
    const int32_t dataIndex = getReserveUniqueIdForDataInline<TypeData>();
    return (Iterator<TypeData>)m_clhash_data_p->m_dataFncs[dataIndex].m_first;
}


template <typename TypeData>
typename ListHash::Iterator<TypeData> ListHash::last()const noexcept
{
    const int32_t dataIndex = getReserveUniqueIdForDataInline<TypeData>();
    return (Iterator<TypeData>)m_clhash_data_p->m_dataFncs[dataIndex].m_last;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace lh{

template <typename TypeKey, typename TypeHasher >
SKeyAny<TypeKey,TypeHasher>::SKeyAny(const TypeKey& a_rawKey, int32_t a_dataIndex, int32_t a_keyAndHashIndex)
    :
    CKeyBase(a_dataIndex,a_keyAndHashIndex),
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
    if(((this->keyAndHashIndex)==(a_key2.keyAndHashIndex))&&((this->dataIndex)==(a_key2.dataIndex))){
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
SKeyInt<TypeIntKey>::SKeyInt(const TypeIntKey& a_rawKey, int32_t a_dataIndex, int32_t a_keyAndHashIndex)
    :
    CKeyBase(a_dataIndex,a_keyAndHashIndex),
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
    if(((this->keyAndHashIndex)==(a_key2.keyAndHashIndex))&&((this->dataIndex)==(a_key2.dataIndex))){
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
