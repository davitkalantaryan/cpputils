//
// file:			listandhash.impl.hpp
// path:			include/cpputils/listandhash.impl.hpp
// created on:		2025 May 02
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_HPP
#include <cpputils/listandhash.hpp>
#endif

#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <utility>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {


template <typename DataType>
inline void ListAndHash<DataType>::AddToTheListBegPrivate(Item* CPPUTILS_ARG_NN a_pItem) noexcept
{
    if(m_first){
        m_first->prev = a_pItem;
    }
    else{
        m_last = a_pItem;
    }
    a_pItem->prev = nullptr;
    a_pItem->next = m_first;
    m_first = a_pItem;
}


template <typename DataType>
inline void ListAndHash<DataType>::AddToTheListEndPrivate(Item* CPPUTILS_ARG_NN a_pItem) noexcept
{
    if(m_last){
        m_last->next = a_pItem;
    }
    else{
        m_first = a_pItem;
    }
    a_pItem->prev = m_last;
    a_pItem->next = nullptr;
    m_last = a_pItem;
}


template <typename DataType>
ListAndHash<DataType>::~ListAndHash() noexcept
{
    Item *pItemNext, *pItem = m_first;
    while(pItem){
        pItemNext = pItem->next;
        CInternalHashRemoveDataEx(m_hash,pItem->hashIter);
        pItem->~Item();
        (*(m_hash->deallocator))(pItem);
        pItem = pItemNext;
    }  //  while(pItem){
}


template <typename DataType>
ListAndHash<DataType>::ListAndHash(size_t a_numberOfBaskets,
                                   TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
                                   TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
                                   TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
      m_first(nullptr),
      m_last(nullptr),
      m_hash(nullptr)
{
    m_hash = CInternalHashCreateAnyEx(a_numberOfBaskets,a_hasher, a_isEq, a_keyStore, a_keyUnstore, a_allocator, a_deallocator);
    if(!m_hash){
        throw ::std::bad_alloc();
    }
}


template <typename DataType>
ListAndHash<DataType>::ListAndHash(const Type&  a_type, size_t a_numberOfBaskets,
                                   TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
      m_first(nullptr),
      m_last(nullptr),
      m_hash(nullptr)
{
    switch(a_type){
    case Type::SmlInt:
        m_hash = CInternalHashCreateSmlIntEx(a_numberOfBaskets,a_allocator, a_deallocator);
        break;
    default:
        m_hash = CInternalHashCreateRawMemEx(a_numberOfBaskets,a_allocator, a_deallocator);
        break;
    }  //  switch(a_type){
    if(!m_hash){
        throw ::std::bad_alloc();
    }
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator ListAndHash<DataType>::first()const
{
    return m_first;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator ListAndHash<DataType>::last()const
{
    return m_last;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddBegWithKnownHash(const DataType& a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
    DataType aData(a_data);
    return AddBegWithKnownHash(&aData,a_key,a_keySize,a_hash);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddBegWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize, size_t a_hash)
{
    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
    if(!pNewItem){
        throw ::std::bad_alloc();
    }
    
    new(pNewItem) Item(a_data_p);
    pNewItem->hashIter = CInternalHashAddDataWithKnownHash(m_hash,pNewItem,a_key,a_keySize,a_hash);
    if(!(pNewItem->hashIter)){
        throw ::std::bad_alloc();
    }
    
    AddToTheListBegPrivate(pNewItem);
    return pNewItem;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddEndWithKnownHash(const DataType& a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
    DataType aData(a_data);
    return AddEndWithKnownHash(&aData,a_key,a_keySize,a_hash);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddEndWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize, size_t a_hash)
{
    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
    if(!pNewItem){
        throw ::std::bad_alloc();
    }
    
    new(pNewItem) Item(a_data_p);
    pNewItem->hashIter = CInternalHashAddDataWithKnownHash(m_hash,pNewItem,a_key,a_keySize,a_hash);
    if(!(pNewItem->hashIter)){
        throw ::std::bad_alloc();
    }
    
    AddToTheListEndPrivate(pNewItem);
    return pNewItem;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddBegEvenIfExist(const DataType& a_data, const void* a_key, size_t a_keySize)
{
    DataType aData(a_data);
    return AddBegEvenIfExist(&aData,a_key,a_keySize);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddBegEvenIfExist(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize)
{
    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
    if(!pNewItem){
        throw ::std::bad_alloc();
    }
    
    new(pNewItem) Item(a_data_p);
    pNewItem->hashIter = CInternalHashAddDataEvenIfExist(m_hash,pNewItem,a_key,a_keySize);
    if(!(pNewItem->hashIter)){
        throw ::std::bad_alloc();
    }
    
    AddToTheListBegPrivate(pNewItem);
    return pNewItem;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddEndEvenIfExist(const DataType& a_data, const void* a_key, size_t a_keySize)
{
    DataType aData(a_data);
    return AddEndEvenIfExist(&aData,a_key,a_keySize);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddEndEvenIfExist(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize)
{
    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
    if(!pNewItem){
        throw ::std::bad_alloc();
    }
    
    new(pNewItem) Item(a_data_p);
    pNewItem->hashIter = CInternalHashAddDataEvenIfExist(m_hash,pNewItem,a_key,a_keySize);
    if(!(pNewItem->hashIter)){
        throw ::std::bad_alloc();
    }
    
    AddToTheListEndPrivate(pNewItem);
    return pNewItem;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddBegIfNotExists(const DataType& a_data, const void* a_key, size_t a_keySize)
{
    DataType aData(a_data);
    return AddBegIfNotExists(&aData,a_key,a_keySize);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddBegIfNotExists(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize)
{
    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
    if(!pNewItem){
        throw ::std::bad_alloc();
    }
    
    new(pNewItem) Item(a_data_p);
    pNewItem->hashIter = CInternalHashAddDataIfNotExists(m_hash,pNewItem,a_key,a_keySize);
    if(!(pNewItem->hashIter)){
        pNewItem->~Item();
        (*(m_hash->deallocator))(pNewItem);
        return nullptr;
    }
    
    AddToTheListBegPrivate(pNewItem);
    return pNewItem;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddEndIfNotExists(const DataType& a_data, const void* a_key, size_t a_keySize)
{
    DataType aData(a_data);
    return AddEndIfNotExists(&aData,a_key,a_keySize);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::AddEndIfNotExists(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize)
{
    Item* const pNewItem = (Item*)((*(m_hash->allocator))(sizeof(Item)));
    if(!pNewItem){
        throw ::std::bad_alloc();
    }
    
    new(pNewItem) Item(a_data_p);
    pNewItem->hashIter = CInternalHashAddDataIfNotExists(m_hash,pNewItem,a_key,a_keySize);
    if(!(pNewItem->hashIter)){
        pNewItem->~Item();
        (*(m_hash->deallocator))(pNewItem);
        return nullptr;
    }
    
    AddToTheListEndPrivate(pNewItem);
    return pNewItem;
}


template <typename DataType>
inline void ListAndHash<DataType>::RemoveEx(Iterator CPPUTILS_ARG_NN a_iter) noexcept
{
    if(a_iter->next){
        a_iter->next->prev = a_iter->prev;
    }
    else{
        m_last = a_iter->prev;
    }
    
    if(a_iter->prev){
        a_iter->prev->next = a_iter->next;
    }
    else{
        m_first = a_iter->next;
    }
    
    CInternalHashRemoveDataEx(m_hash,a_iter->hashIter);
    a_iter->~Item();
    (*(m_hash->deallocator))(const_cast<Item*>(a_iter));
}


template <typename DataType>
bool ListAndHash<DataType>::Remove(const void* a_key, size_t a_keySize) noexcept
{
    size_t unHash;
    const Iterator iter = findEx(a_key,a_keySize,&unHash);
    if(iter){
        RemoveEx(iter);
        return true;
    }
    return false;
}


template <typename DataType>
inline typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::findEx( const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) const noexcept
{
    const CinternalHashItem_t hsIter = CInternalHashFindEx(m_hash,a_key,a_keySize,a_pHash);
    if(hsIter){
        return (Item*)hsIter->data;
    }
    return nullptr;
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::find( const void* a_key, size_t a_keySize) const noexcept
{
    size_t unHash;
    return findEx(a_key,a_keySize,&unHash);
}


template <typename DataType>
typename ListAndHash<DataType>::Iterator 
ListAndHash<DataType>::findNextTheSame( Iterator CPPUTILS_ARG_NN a_prev ) const noexcept
{
    const CinternalHashItem_t hsIter = CInternalHashFindNextTheSame(m_hash,a_prev->hashIter);
    if(hsIter){
        return (Item*)hsIter->data;
    }
    return nullptr;
}


template <typename DataType>
ConstCinternalHash_t ListAndHash<DataType>::getHash()const
{
    return m_hash;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename DataType>
ListAndHash<DataType>::Item::Item(DataType* CPPUTILS_ARG_NN a_data_p) noexcept
    :
      data(::std::move(*a_data_p))
{
}



}  //  namespace cpputils {


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_IMPL_HPP
