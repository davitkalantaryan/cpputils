//
// repo:            cpputils
// file:			cpputils_collectionhash.impl.hpp
// path:			include/cpputils/cpputils_collectionhash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONMAP_HPP
#include <cpputils/collectionhash.hpp>
#endif

#include <cinternal/disable_compiler_warnings.h>
//#include <new>
//#include <utility>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace collectionhash{


namespace __private{


typedef void (*TypeCallDestructFnc)(void* a_key);

struct ItemVoid final : public Hash::Item<void> {
    CinternalHashItem_t     hashIter;
};

struct SDataFunctions{
    TypeCallDestructFnc callDestructFnc;
    bool                isReal;
    bool                reserved01[(sizeof(TypeCallDestructFnc)-sizeof(bool))/sizeof(bool)];
};

}  //  namespace __private{


class CPPUTILS_EXPORT Hash_p
{
private:
    ~Hash_p() noexcept;
    Hash_p(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);

protected:
    ConstCinternalHash_t                m_hash;
    size_t                              m_numberOfAllocatedTables;
    int32_t                             m_numberOfDataTypes;
    mutable int32_t                     m_counterOfKeyAndHashTypes;
    __private::SDataFunctions*          m_dataFncs;
    //__private::SKeyAndHasherFunctions*  m_keyAndHasherFncs;

private:
    int32_t GetNextDataIndex(const __private::TypeCallDestructFnc& a_callDestructFnc);
    int32_t getNextKeyAndHasherIndex(void) const noexcept;

private:
    Hash_p(const Hash_p&) = delete;
    Hash_p(Hash_p&&) = delete;
    Hash_p& operator=(const Hash_p&) = delete;
    Hash_p& operator=(Hash_p&&) = delete;
    friend class Hash;
    //friend struct __private::SKeyExt;
};


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
inline int Hash::getReserveUniqueIdForDataInline(void) const noexcept {
    static int dataIndex = m_clhash_data_p->GetNextDataIndex([](void* a_data_p){((TypeData*)a_data_p)->~TypeData();});
    return dataIndex;
}


template <typename TypeKey, typename TypeHasher>
inline int Hash::getReserveUniqueIdForKeyAndHasherInline(void) const noexcept {
    static int dataIndex = m_clhash_data_p->getNextKeyAndHasherIndex();
    return dataIndex;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
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
typename Hash::Iterator<TypeData>
Hash::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key, &unHash);
}


template <typename TypeData>
typename Hash::Iterator<TypeData>
Hash::findNextTheSame( const Hash::Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept
{
    const __private::ItemVoid* const itemPrevVoid_p = (const __private::ItemVoid*)a_prev;
    const CinternalHashItem_t hsIter = CInternalHashFindNextTheSame(m_clhash_data_p->m_hash,itemPrevVoid_p->hashIter);
    if(hsIter){
        return (Hash::Iterator<TypeData>)hsIter->data;
    }
    return nullptr;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    __private::ItemVoid* const pNewItemVoid = (__private::ItemVoid*)pNewItem;

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

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    __private::ItemVoid* const pNewItemVoid = (__private::ItemVoid*)pNewItem;

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

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename Hash::Iterator<TypeData>
Hash::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clhash_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }
    __private::ItemVoid* const pNewItemVoid = (__private::ItemVoid*)pNewItem;

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

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt>
bool Hash::Remove(const TypeKey& a_key) noexcept
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
inline void Hash::RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    __private::ItemVoid* const pItemVoid = (__private::ItemVoid*)a_iter;
    CKeyBase* const pKeyExt = (CKeyBase*)(pItemVoid->hashIter->key);
    const __private::SDataFunctions& dtFncs = (m_clhash_data_p->m_dataFncs)[pKeyExt->dataIndex];
    const CinternalHashItem_t hashIter = pItemVoid->hashIter;
    (*(dtFncs.callDestructFnc))(pItemVoid->data_p);
    (*(m_clhash_data_p->m_hash->deallocator))(pItemVoid);
    CInternalHashRemoveDataEx(m_clhash_data_p->m_hash,hashIter);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

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


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONHASH_IMPL_HPP
