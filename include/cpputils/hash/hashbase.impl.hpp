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


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::ApiData(size_t a_tInitSize)
	:
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1)
{
	ConstructAfterRoundedTableSizeMin1IsKnownB();
}


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::~ApiData()
{
}


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnownB()
{
    m_unSize = 0;
    const size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<InputPrivate**>(callocFn(tRet,sizeof(InputPrivate*)));
	if(!m_pTable){throw std::bad_alloc();}
}


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::InitAllToZeroB()
{
    m_pTable = CPPUTILS_NULL;
	m_unRoundedTableSizeMin1 = size_t(-1);
	m_unSize = 0;
}


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::ReplaceWithOtherB(ApiData* a_pmM) CPPUTILS_NOEXCEPT
{
    InputPrivate**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	size_t		unSize = m_unSize;

	m_pTable=a_pmM->m_pTable;
	m_unRoundedTableSizeMin1 = a_pmM->m_unRoundedTableSizeMin1;
	m_unSize = a_pmM->m_unSize;

	a_pmM->m_pTable = pTable;
	a_pmM->m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_pmM->m_unSize = unSize;
}


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::AddEntryWithAlreadyCreatedItemB(InputPrivate* a_pItem, size_t a_hash)
{
	a_pItem->next = m_pTable[a_hash];
	if(m_pTable[a_hash]){m_pTable[a_hash]->prev=a_pItem;}
	m_pTable[a_hash] = a_pItem;	
	++m_unSize;
}


template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<Input,templateDefaultSize,mallocFn,callocFn,freeFn>::RemoveEntryRawB(InputPrivate* a_pItem, size_t a_hash)
{
    if(m_pTable[a_hash]==a_pItem){m_pTable[a_hash]=a_pItem->next;}
    if(a_pItem->next){a_pItem->next->prev=a_pItem->prev;}
    if(a_pItem->prev){a_pItem->prev->next=a_pItem->next;}
	//delete a_pItem; // delete should be done by caller
	--m_unSize;
}


//

template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::~HashBase()
{
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::RemoveEntryByKey(const Key& a_key)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_key,&unHash);
    if(pItem){
        ApiType::RemoveEntryRaw(COutput(this,pItem,unHash));
    }
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
size_t HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::size()const
{
    return ApiType::m_unSize;
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
inline void 
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::clear() CPPUTILS_NOEXCEPT
{
    ApiType::ClearRaw();
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashMv(Input&& a_item, size_t a_hash)
{
    Input* pInTheTable = ApiType::AddEntryWithKnownHashRaw(::std::move(a_item),a_hash);
    return Output(this,pInTheTable,a_hash);
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashC(const Input& a_item, size_t a_hash)
{
    return AddEntryWithKnownHashMv(Input(a_item),a_hash);
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsMv(Input&& a_item)
{
    const size_t unHash = fnHash(a_item.first)&(ApiType::m_unRoundedTableSizeMin1);
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsC(const Input& a_item)
{
    Hash fnHash;
    const size_t unHash = fnHash(a_item.first)&(ApiType::m_unRoundedTableSizeMin1);
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistMv(Input&& a_item)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_item.first,&unHash);
    if(pItem){return Output(this,CPPUTILS_NULL,0);}
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistC(const Input& a_item)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_item.first,&unHash);
    if(pItem){return Output(this,CPPUTILS_NULL,0);}
    return AddEntryWithKnownHashC(a_item,unHash);
}

template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
Input*
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
findEntryRaw( const Key& a_key, size_t* a_hashPtr )const
{
    Hash fnHash;
	InputPrivate* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (fnHash(a_key))&(ApiType::m_unRoundedTableSizeMin1);
	pItemToRet = ApiType::m_pTable[unHash];

	while (pItemToRet) {
		if(a_key==pItemToRet->first){
            return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

    return CPPUTILS_NULL;
}


template <typename Key,typename Input, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output 
HashBase<Key,Input,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
findEntry( const Key& a_key, size_t* a_hashPtr )const
{
    if(a_hashPtr){
        Input* pItem = findEntryRaw(a_key,a_hashPtr);
        return Output(this,pItem,*a_hashPtr);
    }
    
    size_t unHash;
    Input* pItem = findEntryRaw(a_key,&unHash);
    return Output(this,pItem,unHash);
}



}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
