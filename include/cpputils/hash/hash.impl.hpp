//
// file:			hash.hpp
// path:			include/cpputils/hash.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HPP
#include "hash.hpp"
#endif

#include <utility>
#include <string.h>


namespace cpputils { namespace hash {


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::HashApi(const HashApi& a_cM)
{
    GeFromOther(a_cM);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::HashApi(HashApi&& a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::InitAllToZeroB();
    ApiDataAdv::ReplaceWithOtherB(&a_mM);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::~HashApi()
{
    ClearRaw();
    freeFn(ApiDataAdv::m_pTable);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType* HashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
AddEntryWithKnownHashRaw(HashItemType&& a_item, size_t a_hash)
{
    HashItemPrivateBase* pItem = new HashItemPrivateBase(::std::move(a_item),a_hash);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem);
    return pItem;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void HashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::ClearRaw() CPPUTILS_NOEXCEPT
{
    if(ApiDataAdv::m_pTable){
        const size_t tRet(ApiDataAdv::m_unRoundedTableSizeMin1 + 1);
        HashItemPrivateBase *pItem,*pItemNext;
        for(size_t i(0); i<tRet; ++i){
            pItem = static_cast<HashItemPrivateBase*>(ApiDataAdv::m_pTable[i]);
            while(pItem){
                pItemNext = pItem->next;
                delete pItem;
                pItem = pItemNext;
            }
            
            ApiDataAdv::m_pTable[i] = CPPUTILS_NULL;
        }
        ApiDataAdv::m_unSize = 0;
    } // if(m_pTable){
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void HashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
GeFromOther(const HashApi& a_cM)
{
    HashItemPrivateBase* pItem;
    const size_t tRet(a_cM.m_unRoundedTableSizeMin1 + 1);
    
    if(a_cM.m_unRoundedTableSizeMin1>ApiDataAdv::m_unRoundedTableSizeMin1){
        const size_t cunAllocateSize = tRet*sizeof(HashItemType*);
        HashItemType** pTable = static_cast<HashItemType**>(reallocFn(ApiDataAdv::m_pTable,cunAllocateSize));
        if (!pTable) { throw std::bad_alloc(); }
        ApiDataAdv::m_pTable = pTable;
        :: memset(ApiDataAdv::m_pTable,0,cunAllocateSize);
    }
    
    ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
    
    for(size_t i(0); i<tRet; ++i){
        pItem = a_cM.m_pTable[i];
        while(pItem){
            AddEntryWithKnownHashRaw(*pItem,i); // we call this for a_cM in order to have it inited
            pItem = pItem->next;
        }
    }
}



}}  // namespace cpputils { namespace hash {

#if 0

namespace __private { namespace __implementation {

CPPUTILS_EXPORT size_t hash1_( const void* a_pKey, size_t a_unKeySize );
CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);

}}  // namespace __private { namespace __implementation {


namespace cpputils { namespace hash {

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void* HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void  HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashBase(size_t a_tInitSize)
	:
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItemType**>(callocFn(tRet,sizeof(HashItemType*)));
	if(!m_pTable){throw std::bad_alloc();}
    ApiType::Constructor(this);
}


//HashBase(const HashBase& cM)
template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashBase(const HashBase& a_cM)
	:
      m_pTable(CPPUTILS_NULL),
      m_unRoundedTableSizeMin1(0),
	  m_unSize(0)
{
    GeFromOther(a_cM);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashBase(HashBase&& a_mM) CPPUTILS_NOEXCEPT
    :
      m_pTable(a_mM.m_pTable),
	  m_unRoundedTableSizeMin1(a_mM.m_unRoundedTableSizeMin1),
	  m_unSize(a_mM.m_unSize)
{
	a_mM.m_unSize = 0;
	a_mM.m_pTable = CPPUTILS_NULL;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::~HashBase()
{
    clear();
    freeFn(m_pTable);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>&
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::operator=(const HashBase& a_cM)
{
    clear();
    GeFromOther(a_cM);
    return *this;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>&
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::operator=(HashBase&& a_cM) CPPUTILS_NOEXCEPT
{
    HashItemType**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	size_t		unSize = m_unSize;

	m_pTable=a_cM->m_pTable;
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_unSize = (a_cM->m_unSize);

	a_cM.m_pTable = pTable;
	a_cM.m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_cM.m_unSize = (unSize);

	return *this;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
size_t HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::size()const
{
    return m_unSize;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
inline void 
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::clear() CPPUTILS_NOEXCEPT
{
    if(m_pTable){
        const size_t tRet(m_unRoundedTableSizeMin1 + 1);
        HashItemPrivate *pItem,*pItemNext;
        for(size_t i(0); i<tRet; ++i){
            pItem = static_cast<HashItemPrivate*>(m_pTable[i]);
            while(pItem){
                pItemNext = pItem->next;
                delete pItem;
                pItem = pItemNext;
            }
            
            m_pTable[i] = CPPUTILS_NULL;
        }
        m_unSize = 0;
    } // if(m_pTable){
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::iterator
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::find( const KeyType& a_key, size_t* a_pHash )
{
    return findEntry(a_key,a_pHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::const_iterator
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::find( const KeyType& a_key, size_t* a_pHash )const
{
    return findEntry(a_key,a_pHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
inline void HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
GeFromOther(const HashBase& a_cM)
{
    HashItemPrivate* pItem;
    const size_t tRet(a_cM.m_unRoundedTableSizeMin1 + 1);
    
    if(a_cM.m_unRoundedTableSizeMin1>m_unRoundedTableSizeMin1){
        const size_t cunAllocateSize = tRet*sizeof(HashItemType*);
        HashItemType** pTable = static_cast<HashItemType**>(reallocFn(m_pTable,cunAllocateSize));
        if (!pTable) { freeFn(m_pTable); m_pTable=CPPUTILS_NULL;throw std::bad_alloc(); }
        m_pTable = pTable;
        :: memset(m_pTable,0,cunAllocateSize);
    }
    
    m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
    
    for(size_t i(0); i<tRet; ++i){
        pItem = a_cM.m_pTable[i];
        while(pItem){
            a_cM.AddEntryWithKnownHashRaw(this,*pItem,i); // we call this for a_cM in order to have it inited
            pItem = pItem->next;
        }
    }
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType* HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashRaw(HashBase* a_pContainer, HashItemType&& a_item, size_t a_hash)
{
    HashItemPrivate* pItem = new HashItemPrivate( ::std::move(a_item) );
    //HashItemPrivate* pItem = new HashItemPrivate(  );
	
    //pItem->prev = CPPUTILS_NULL; // this is done in the constructor
	pItem->next = static_cast<HashItemPrivate*>(a_pContainer->m_pTable[a_hash]);
	if(a_pContainer->m_pTable[a_hash]){static_cast<HashItemPrivate*>(a_pContainer->m_pTable[a_hash])->prev=pItem;}
	a_pContainer->m_pTable[a_hash] = pItem;
		
	++(a_pContainer->m_unSize);
	
	return static_cast<HashItemType*>(pItem);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashMv(HashItemType&& a_item, size_t a_hash)
{
    return iterator(AddEntryWithKnownHashRaw(this,::std::move(a_item),a_hash));
	//HashItemPrivate* pItem = new HashItemPrivate(a_item);
	//
	//pItem->next = static_cast<HashItemPrivate*>(m_pTable[a_item.hash]);
	//if(m_pTable[a_hash]){m_pTable[a_hash]->prev=pItem;}
	//m_pTable[a_hash] = pItem;
	//	
	//++m_unSize;
	//
	//return static_cast<HashItemType*>(pItem);
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
    const size_t unHash = fnHash(a_item.first)&m_unRoundedTableSizeMin1;
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsC(const HashItemType& a_item)
{
    Hash fnHash;
    const size_t unHash = fnHash(a_item.first)&m_unRoundedTableSizeMin1;
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistMv(HashItemType&& a_item)
{
    size_t unHash;
    HashItemType* pItem = findEntry(a_item.first,&unHash);
    if(pItem){return iterator({CPPUTILS_NULL});}
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
	
	unHash = (fnHash(a_key))&m_unRoundedTableSizeMin1;
	pItemToRet = static_cast<HashItemPrivate*>(m_pTable[unHash]);

	while (pItemToRet) {
		if(a_key==pItemToRet->first){
            return iterator(pItemToRet);
		}
		pItemToRet = pItemToRet->next;
	}

    return iterator(CPPUTILS_NULL);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
const typename HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::iterator  
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::s_endIter(CPPUTILS_NULL);


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
iterator::iterator()
    :
      m_pItem(CPPUTILS_NULL)
{
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
iterator::iterator(HashItemType* a_pItem)
    :
      m_pItem(a_pItem)
{
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::iterator::operator->()const
{
    return m_pItem;
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::iterator::operator 
HashItemType*()const
{
    return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
const typename HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::const_iterator  
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::s_endConstIter(CPPUTILS_NULL);


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
const_iterator::const_iterator()
    :
      m_pItem(CPPUTILS_NULL)
{
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
const HashItemType*
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::const_iterator::operator->()const
{
    return m_pItem;
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::const_iterator::operator 
const HashItemType*()const
{
    return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void* HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashItemPrivate::
operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void  HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashItemPrivate::
operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
HashItemPrivate::HashItemPrivate(HashItemType&& a_mM)
    :
      HashItemType(::std::move(a_mM))
{
    this->prev = CPPUTILS_NULL;
}



}}  //  namespace cpputils { namespace hash {


#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP
