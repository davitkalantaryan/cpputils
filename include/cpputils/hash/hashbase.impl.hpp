//
// file:			hash.hpp
// path:			include/cpputils/hash.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP
#include "hashbase.hpp"
#endif

#include <utility>
#include <string.h>


namespace __private { namespace __implementation {

CPPUTILS_EXPORT size_t hash1_( const void* a_pKey, size_t a_unKeySize );
CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);

}}  // namespace __private { namespace __implementation {


namespace cpputils { namespace hash {


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
ApiData<HashItemType,mallocFn,callocFn,freeFn>::ApiData(size_t a_tInitSize)
	:
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1)
{
	ConstructAfterRoundedTableSizeMin1IsKnown();
}


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
ApiData<HashItemType,mallocFn,callocFn,freeFn>::~ApiData()
{
}


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<HashItemType,mallocFn,callocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnown()
{
    m_unSize = 0;
    const size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItemType**>(callocFn(tRet,sizeof(HashItemType*)));
	if(!m_pTable){throw std::bad_alloc();}
}


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<HashItemType,mallocFn,callocFn,freeFn>::InitAllToZeroB()
{
    m_pTable = nullptr;
	m_unRoundedTableSizeMin1 = size_t(-1);
	m_unSize = 0;
}


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<HashItemType,mallocFn,callocFn,freeFn>::ReplaceWithOtherB(ApiData* a_pmM) CPPUTILS_NOEXCEPT
{
    HashItemType**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	size_t		unSize = m_unSize;

	m_pTable=a_pmM->m_pTable;
	m_unRoundedTableSizeMin1 = a_pmM->m_unRoundedTableSizeMin1;
	m_unSize = a_pmM->m_unSize;

	a_pmM->m_pTable = pTable;
	a_pmM->m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_pmM->m_unSize = unSize;
}


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<HashItemType,mallocFn,callocFn,freeFn>::AddEntryWithAlreadyCreatedItemB(HashItemType* a_pItem)
{
    HashItemPrivateBase*const pItem = static_cast<HashItemPrivateBase*>(a_pItem);
	pItem->next = static_cast<HashItemPrivateBase*>(m_pTable[pItem->hash]);
	if(m_pTable[pItem->hash]){static_cast<HashItemPrivateBase*>(m_pTable[pItem->hash])->prev=pItem;}
	m_pTable[pItem->hash] = a_pItem;	
	++m_unSize;
}


template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void* ApiData<HashItemType,mallocFn,callocFn,freeFn>::operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void  ApiData<HashItemType,mallocFn,callocFn,freeFn>::operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}

//

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::~HashBase()
{
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::RemoveEntryByKey(const KeyType& a_key)
{
    HashItemType* pItem = findEntry(a_key);
    if(pItem){
        ApiType::RemoveEntryRaw(pItem);
    }
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
size_t HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::size()const
{
    return ApiType::m_unSize;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
inline void 
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::clear() CPPUTILS_NOEXCEPT
{
    ApiType::ClearRaw();
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashMv(HashItemType&& a_item, size_t a_hash)
{
    return ApiType::AddEntryWithKnownHashRaw(::std::move(a_item),a_hash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryWithKnownHashC(const HashItemType& a_item, size_t a_hash)
{
    return AddEntryWithKnownHashMv(HashItemType(a_item),a_hash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsMv(HashItemType&& a_item)
{
    const size_t unHash = fnHash(a_item.first)&(ApiType::m_unRoundedTableSizeMin1);
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsC(const HashItemType& a_item)
{
    Hash fnHash;
    const size_t unHash = fnHash(a_item.first)&(ApiType::m_unRoundedTableSizeMin1);
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistMv(HashItemType&& a_item)
{
    size_t unHash;
    HashItemType* pItem = findEntry(a_item.first,&unHash);
    if(pItem){return CPPUTILS_NULL;}
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistC(const HashItemType& a_item)
{
    size_t unHash;
    HashItemType* pItem = findEntry(a_item.first,&unHash);
    if(pItem){return CPPUTILS_NULL;}
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType* 
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::findEntry( const KeyType& a_key, size_t* a_hashPtr )const
{
    Hash fnHash;
	HashItemPrivate* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (fnHash(a_key))&(ApiType::m_unRoundedTableSizeMin1);
	pItemToRet = static_cast<HashItemPrivate*>(ApiType::m_pTable[unHash]);

	while (pItemToRet) {
		if(a_key==pItemToRet->first){
            return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

    return CPPUTILS_NULL;
}



}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
