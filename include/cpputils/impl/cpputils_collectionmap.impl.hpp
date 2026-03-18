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

namespace cpputils { namespace collectionmap{


namespace __private{

CPPUTILS_EXPORT int GetNextIndex(void) noexcept;
typedef void (*TypeWithAnyKeyDeleteKey)(void* a_key);
struct ItemVoid final : public Base::Item<void> {
    CinternalHashItem_t     hashIter2;
    TypeWithAnyKeyDeleteKey dataDeleter;
};


struct SnglListItem {
    ItemVoid*   m_first;
    ItemVoid*   m_last;
    size_t      m_count;
};


struct SWithAnyKeyKeyExt;

typedef size_t (*TypeWithAnyKeyHasher)(const void* key);
typedef bool (*TypeWithAnyKeyIsMemoriesIdentical)(const void* key1,const void* key2);
typedef void (*TypeWithAnyKeyDublicateKey)(void* a_createdMemory, const void* a_key);

struct SWithAnyKeyKeyExt {
    const TypeWithAnyKeyHasher              fncHasher;
    const TypeWithAnyKeyIsMemoriesIdentical fncIsEq;
    const size_t                            typeIndex;

private:
    void*                                   keyRaw_p;
    const TypeWithAnyKeyDublicateKey        fncDublicateKey;
    const TypeWithAnyKeyDeleteKey           fncDeleteKey;

private:
    SWithAnyKeyKeyExt(const SWithAnyKeyKeyExt&) = default;
    SWithAnyKeyKeyExt(SWithAnyKeyKeyExt&&) = default;
    SWithAnyKeyKeyExt(
        const void* a_keyRaw_p, TypeWithAnyKeyHasher a_fncHasher, 
        TypeWithAnyKeyIsMemoriesIdentical a_fncIsEq, TypeWithAnyKeyDublicateKey a_fncDublicateKey, 
        TypeWithAnyKeyDeleteKey a_fncDeleteKey, int a_typeIndex) noexcept;
    SWithAnyKeyKeyExt& operator=(const SWithAnyKeyKeyExt&) = delete;
    SWithAnyKeyKeyExt& operator=(SWithAnyKeyKeyExt&&) = delete;
    template <typename TypeData, typename KeyType, typename TypeHasher>
    static SWithAnyKeyKeyExt CreateRaw(const void* a_keyRaw_p) noexcept;

public:
    ~SWithAnyKeyKeyExt() noexcept;
    static SWithAnyKeyKeyExt* MakeCopy(TypeCinternalAllocator a_allocator, const SWithAnyKeyKeyExt& a_cM);
    template <typename TypeData, typename KeyType, typename TypeHasher>
    static SWithAnyKeyKeyExt Create(const KeyType& a_keyRaw);
    template <typename KeyType>
    const KeyType* getKeyRawPtr()const;

};


template <typename DataType>
class WithAnyKeyFncs1
{
public:
    static bool WithAnyKeyIsMemoriesIdentical(const void* a_key1, const void* a_key2);
    static void WithAnyKeyStoreKey(void* a_createdMemory, const void* a_key);
    static void WithAnyKeyUnstoreKey(void* a_key);
};


template <typename KeyType, typename TypeHasher>
class WithAnyKeyFncs2
{
public:
    static size_t WithAnyKeyHasher(const void* a_key);
};


}  //  namespace __private{


class CPPUTILS_EXPORT CollectionMap_p
{
public:
    ~CollectionMap_p() noexcept;
    CollectionMap_p();

public:
    ConstCinternalHash_t        m_hash;
    size_t                      m_bufferSize;
    int                         m_numberOfTypes;
    int                         m_reserved01;
    __private::SnglListItem*    m_lists;

public:
    const Base::Item<void>* getFirstByTypeIndex(int a_typeIndex)const;
    const Base::Item<void>* getLastByTypeIndex(int a_typeIndex)const;
    void AddBegWithKnownHash(int a_typeIndex, void* CPPUTILS_ARG_NN a_data_p, void* CPPUTILS_ARG_NN a_key, size_t a_keySize, size_t a_hash, const __private::TypeWithAnyKeyDeleteKey& a_dataDeleter);
    void AddEndWithKnownHash(int a_typeIndex, void* CPPUTILS_ARG_NN a_data_p, void* CPPUTILS_ARG_NN a_key, size_t a_keySize, size_t a_hash, const __private::TypeWithAnyKeyDeleteKey& a_dataDeleter);

private:
    CollectionMap_p(const CollectionMap_p&) = delete;
    CollectionMap_p(CollectionMap_p&&) = delete;
    CollectionMap_p& operator=(const CollectionMap_p&) = delete;
    CollectionMap_p& operator=(CollectionMap_p&&) = delete;
    inline void MakeSureListHasEnoughElements(int a_typeIndex);
    void AddToTheListBegPrivate(Base::Item<void>* CPPUTILS_ARG_NN a_item_p, int a_typeIndex);
    void AddToTheListEndPrivate(Base::Item<void>* CPPUTILS_ARG_NN a_item_p, int a_typeIndex);
};


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData>
inline int Base::getReserveUniqueIdInline(void) noexcept {
    static int dataIndex = __private::GetNextIndex();
    return dataIndex;
}


template <typename TypeData>
typename Base::Iterator<TypeData> Base::first()const noexcept
{
    const Base::Item<void>* pFirst = m_clmp_data_p->getFirstByTypeIndex(getReserveUniqueIdInline<TypeData>());
    return (Base::Iterator<TypeData>)pFirst;
}


template <typename TypeData>
typename Base::Iterator<TypeData> Base::last()const noexcept
{
    const Base::Item<void>* pFirst = m_clmp_data_p->getLastByTypeIndex(getReserveUniqueIdInline<TypeData>());
    return (Base::Iterator<TypeData>)pFirst;
}


template <typename TypeData>
typename Base::Iterator<TypeData>
Base::findNextTheSame(const Iterator<TypeData>& a_prev)const noexcept
{
    const Item<TypeData>* const pNewItem = (const Item<TypeData>*)a_prev;
    __private::ItemVoid* const pNewItemVoid = (__private::ItemVoid*)pNewItem;
    const CinternalHashItem_t iter = CInternalHashFindNextTheSame(m_clmp_data_p->m_hash, pNewItemVoid->hashIter2);
    if (iter) {
        const Item<TypeData>* const pNewItemInner = (const Item<TypeData>*)iter->data;
        return pNewItemInner;
    }

    return nullptr;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData, typename TypeInt>
typename Base::Iterator<TypeData> 
WithIntKey::findEx(const TypeInt& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    const uint64_t typeIndex = (uint64_t)getReserveUniqueIdInline<TypeData>();
    const uint64_t wholeKey = (typeIndex << 32) | ((uint64_t)((uint32_t)a_key));
    const CinternalHashItem_t iter = CInternalHashFindEx(m_clmp_data_p->m_hash, CInternalSmallIntHPairFn(wholeKey), a_pHash);
    if (iter) {
        const Item<TypeData>* const pNewItem = (const Item<TypeData>*)iter->data;
        return pNewItem;
    }
    return nullptr;
}


template <typename TypeData, typename TypeInt>
typename Base::Iterator<TypeData>
WithIntKey::find(const TypeInt& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData, TypeInt>(a_key, &unHash);
}


template <typename TypeData, typename TypeInt>
typename Base::Iterator<TypeData>
WithIntKey::AddBegWithKnownHash(const TypeData& a_data, const TypeInt& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddBegWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeInt>
typename Base::Iterator<TypeData>
WithIntKey::AddBegWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeInt& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }

    pNewItem->data_p = (TypeData*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }

    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));
    const uint64_t typeIndex = (uint64_t)getReserveUniqueIdInline<TypeData>();
    const uint64_t wholeKey = (typeIndex << 32) | ((uint64_t)((uint32_t)a_key));

    m_clmp_data_p->AddBegWithKnownHash((int)typeIndex, (void*)pNewItem, (void*)((size_t)wholeKey), sizeof(wholeKey), a_hash, &__private::WithAnyKeyFncs1<TypeData>::WithAnyKeyUnstoreKey);

    return pNewItem;
}


template <typename TypeData, typename TypeInt>
typename Base::Iterator<TypeData>
WithIntKey::AddEndWithKnownHash(const TypeData& a_data, const TypeInt& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddBegWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeInt>
typename Base::Iterator<TypeData>
WithIntKey::AddEndWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeInt& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }

    pNewItem->data_p = (TypeData*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }

    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));
    const uint64_t typeIndex = (uint64_t)getReserveUniqueIdInline<TypeData>();
    const uint64_t wholeKey = (typeIndex << 32) | ((uint64_t)((uint32_t)a_key));

    m_clmp_data_p->AddBegWithKnownHash((int)typeIndex, (void*)pNewItem, (void*)((size_t)wholeKey), sizeof(wholeKey), a_hash, &__private::WithAnyKeyFncs1<TypeData>::WithAnyKeyUnstoreKey);

    return pNewItem;
}


//template <typename TypeData, typename TypeInt>
//typename Base::Iterator<TypeData>
//WithIntKey::AddBegEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeInt& a_key)
//{
//    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
//    if (!pNewItem) {
//        throw ::std::bad_alloc();
//    }
//
//    new(pNewItem) Item(a_data_p);
//    pNewItem->hashIter = CInternalHashAddDataEvenIfExist(m_hash, pNewItem, a_key, a_keySize);
//    if (!(pNewItem->hashIter)) {
//        throw ::std::bad_alloc();
//    }
//
//    AddToTheListBegPrivate(pNewItem);
//    return pNewItem;
//}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeData, typename TypeKey, typename TypeHasher >
typename Base::Iterator<TypeData>
WithAnyKey::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    const __private::SWithAnyKeyKeyExt keyExt = __private::SWithAnyKeyKeyExt::Create<TypeData, TypeKey, TypeHasher>(a_key);
    const CinternalHashItem_t iter = CInternalHashFindEx(m_clmp_data_p->m_hash, &keyExt,0, a_pHash);
    if (iter) {
        const Item<TypeData>* const pNewItem = (const Item<TypeData>*)iter->data;
        return pNewItem;
    }
    return nullptr;
}


template <typename TypeData, typename TypeKey, typename TypeHasher >
typename Base::Iterator<TypeData>
WithAnyKey::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData, TypeKey, TypeHasher>(a_key, &unHash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher >
typename Base::Iterator<TypeData>
WithAnyKey::AddBegWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddBegWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher >
typename Base::Iterator<TypeData>
WithAnyKey::AddBegWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }

    pNewItem->data_p = (TypeData*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }

    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));
    const __private::SWithAnyKeyKeyExt keyExt = __private::SWithAnyKeyKeyExt::Create<TypeData, TypeKey, TypeHasher>(a_key);

    m_clmp_data_p->AddBegWithKnownHash((int)(keyExt.typeIndex), (void*)pNewItem, (void*)&keyExt, 0, a_hash,&__private::WithAnyKeyFncs1<TypeData>::WithAnyKeyUnstoreKey);

    return pNewItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher >
typename Base::Iterator<TypeData>
WithAnyKey::AddEndWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddEndWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher >
typename Base::Iterator<TypeData>
WithAnyKey::AddEndWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    Item<TypeData>* const pNewItem = (Item<TypeData>*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(__private::ItemVoid)));
    if (!pNewItem) {
        throw ::std::bad_alloc();
    }

    pNewItem->data_p = (TypeData*)((*(m_clmp_data_p->m_hash->allocator))(sizeof(TypeData)));
    if (!(pNewItem->data_p)) {
        throw ::std::bad_alloc();
    }

    new(pNewItem->data_p) TypeData(::std::move(*a_data_p));
    const __private::SWithAnyKeyKeyExt keyExt = __private::SWithAnyKeyKeyExt::Create<TypeData, TypeKey, TypeHasher>(a_key);

    m_clmp_data_p->AddEndWithKnownHash((int)(keyExt.typeIndex), (void*)pNewItem, (void*)&keyExt, 0, a_hash, &__private::WithAnyKeyFncs1<TypeData>::WithAnyKeyUnstoreKey);

    return pNewItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace __private{


template <typename TypeKey, typename TypeHasher>
size_t WithAnyKeyFncs2<TypeKey, TypeHasher>::WithAnyKeyHasher(const void* a_key)
{
    const TypeKey* const pKeyRaw = (const TypeKey*)a_key;
    const TypeHasher aHasher;
    const size_t cunHash = aHasher(*pKeyRaw);
    return cunHash;
}


template <typename TypeData>
bool WithAnyKeyFncs1<TypeData>::WithAnyKeyIsMemoriesIdentical(const void* a_key1, const void* a_key2)
{
    const TypeData* const pKey1 = (const TypeData*)a_key1;
    const TypeData* const pKey2 = (const TypeData*)a_key2;
    return (*pKey1) == (*pKey2);
}


template <typename TypeData>
void WithAnyKeyFncs1<TypeData>::WithAnyKeyStoreKey(void* a_createdMemory, const void* a_key)
{
    if (a_key) {
        const TypeData* const pKeyRaw = (const TypeData*)a_key;
        TypeData* const pKeyRawRet = (TypeData*)a_createdMemory;
        new(pKeyRawRet) TypeData(*pKeyRaw);
    }
}


template <typename TypeData>
void WithAnyKeyFncs1<TypeData>::WithAnyKeyUnstoreKey(void* a_key)
{
    TypeData* const pKey = (TypeData*)a_key;
    pKey->~TypeData();
}


template <typename TypeData, typename KeyType, typename TypeHasher>
SWithAnyKeyKeyExt SWithAnyKeyKeyExt::CreateRaw(const void* a_keyRaw_p) noexcept
{
    return SWithAnyKeyKeyExt(
        a_keyRaw_p,
        &WithAnyKeyFncs2<KeyType, TypeHasher>::WithAnyKeyHasher, 
        &WithAnyKeyFncs1<KeyType>::WithAnyKeyIsMemoriesIdentical, 
        &WithAnyKeyFncs1<KeyType>::WithAnyKeyStoreKey, 
        &WithAnyKeyFncs1<KeyType>::WithAnyKeyUnstoreKey, 
        Base::getReserveUniqueIdInline<TypeData>());
}


template <typename TypeData, typename KeyType, typename TypeHasher>
SWithAnyKeyKeyExt SWithAnyKeyKeyExt::Create(const KeyType& a_keyRaw)
{
    return SWithAnyKeyKeyExt::CreateRaw<TypeData, KeyType, TypeHasher>((void*)(new KeyType(a_keyRaw)));
}


template <typename KeyType>
const KeyType* SWithAnyKeyKeyExt::getKeyRawPtr()const
{
    return (const KeyType*)(this->keyRaw_p);
}


}  //  namespace __private{




}}  //  namespace cpputils { namespace collectionmap{ 


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONMAP_IMPL_HPP
