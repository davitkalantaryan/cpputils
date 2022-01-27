//
// file:			hash.hpp
// path:			include/cpputils/hash.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
#include "vhash.hpp"
#endif

#include <utility>
#include <string.h>


namespace __private { namespace __implementation {

CPPUTILS_EXPORT size_t hash1_( const void* a_pKey, size_t a_unKeySize );
CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);

}}  // namespace __private { namespace __implementation {


namespace cpputils { namespace hash {

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void* VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void  VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::VHashBase(size_t a_tInitSize)
	:
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItemPrivate**>(callocFn(tRet,sizeof(HashItemPrivate*)));
	if(!m_pTable){throw std::bad_alloc();}
    m_vectTable = CPPUTILS_NULL;
}


//HashBase(const HashBase& cM)
template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::VHashBase(const VHashBase& a_cM)
	:
      m_pTable(CPPUTILS_NULL),
      m_unRoundedTableSizeMin1(0),
	  m_unSize(0),
      m_vectTable(CPPUTILS_NULL)
{
    GeFromOther(a_cM);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::VHashBase(VHashBase&& a_mM) CPPUTILS_NOEXCEPT
    :
      m_pTable(a_mM.m_pTable),
	  m_unRoundedTableSizeMin1(a_mM.m_unRoundedTableSizeMin1),
	  m_unSize(a_mM.m_unSize),
      m_vectTable(a_mM.m_vectTable)
{
	a_mM.m_unSize = 0;
	a_mM.m_pTable = CPPUTILS_NULL;
    a_mM.m_vectTable = CPPUTILS_NULL;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::~VHashBase()
{
    clear();
    freeFn(m_vectTable);
    freeFn(m_pTable);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>&
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::operator=(const VHashBase& a_cM)
{
    clear();
    GeFromOther(a_cM);
    return *this;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>&
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::operator=(VHashBase&& a_cM) CPPUTILS_NOEXCEPT
{
    HashItemPrivate**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	size_t		unSize = m_unSize;
    HashItemPrivate** vectTable = m_vectTable;

	m_pTable=a_cM->m_pTable;
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_unSize = (a_cM->m_unSize);
    m_vectTable = a_cM.m_vectTable;

	a_cM.m_pTable = pTable;
	a_cM.m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_cM.m_unSize = (unSize);
    a_cM.m_vectTable = vectTable;

	return *this;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
size_t VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::size()const
{
    return m_unSize;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
inline void 
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::clear() CPPUTILS_NOEXCEPT
{
    for(size_t i(0); i<m_unSize;++i){
        delete m_vectTable[i];
    }
    m_unSize = 0;
    
    if(m_pTable){
        :: memset(m_pTable,0,(m_unRoundedTableSizeMin1+1)*sizeof(HashItemPrivate*));
    }    
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
typename VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::find( const KeyType& a_key, size_t* a_pHash )
{
    return findEntry(a_key,a_pHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
typename VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::find( const KeyType& a_key, size_t* a_pHash )const
{
    return findEntry(a_key,a_pHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
inline void VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
GeFromOther(const VHashBase& a_cM)
{    
    if(a_cM.m_unRoundedTableSizeMin1>m_unRoundedTableSizeMin1){
        const size_t tRet(a_cM.m_unRoundedTableSizeMin1 + 1);
        const size_t cunAllocateSize = tRet*sizeof(HashItemType*);
        HashItemPrivate** pTable = static_cast<HashItemPrivate**>(reallocFn(m_pTable,cunAllocateSize));
        if (!pTable) { throw std::bad_alloc(); }
        m_pTable = pTable;
        :: memset(m_pTable,0,cunAllocateSize);
    }
    
    m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
        
    for(size_t i(0); i<a_cM.m_unSize;++i){
        AddEntryEvenIfExistsC(*a_cM.m_vectTable[i]);
    }    
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType* VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
AddEntryWithKnownHashMv(HashItemType&& a_item, size_t a_hash)
{
    HashItemPrivate* pItem = new HashItemPrivate( ::std::move(a_item) );
    //HashItemPrivate* pItem = new HashItemPrivate(  );
	
    //pItem->prev = CPPUTILS_NULL; // this is done in the constructor
	pItem->next = static_cast<HashItemPrivate*>(m_pTable[a_hash]);
	if(m_pTable[a_hash]){m_pTable[a_hash]->prev=pItem;}
	m_pTable[a_hash] = pItem;
    
    if((m_unSize%CPPUTILS_HASH_VECTOR_RESIZE_SIZEE)==0){
        const size_t cunCount(m_unSize+CPPUTILS_HASH_VECTOR_RESIZE_SIZEE);
        const size_t cunAllocateSize = cunCount*sizeof(HashItemPrivate*);
        HashItemPrivate** pTable = static_cast<HashItemPrivate**>(reallocFn(m_vectTable,cunAllocateSize));
        if (!pTable) { throw std::bad_alloc(); }
        m_vectTable = pTable;
    }
		
	m_vectTable[m_unSize++]=pItem;
	
	return static_cast<HashItemType*>(pItem);
}



template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::AddEntryWithKnownHashC(const HashItemType& a_item, size_t a_hash)
{
    return AddEntryWithKnownHashMv(HashItemType(a_item),a_hash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::AddEntryEvenIfExistsMv(HashItemType&& a_item)
{
    const size_t unHash = fnHash(a_item.first)&m_unRoundedTableSizeMin1;
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::AddEntryEvenIfExistsC(const HashItemType& a_item)
{
    Hash fnHash;
    const size_t unHash = fnHash(a_item.first)&m_unRoundedTableSizeMin1;
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::AddEntryIfNotExistMv(HashItemType&& a_item)
{
    size_t unHash;
    HashItemType* pItem = findEntry(a_item.first,&unHash);
    if(pItem){return iterator({CPPUTILS_NULL});}
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::AddEntryIfNotExistC(const HashItemType& a_item)
{
    size_t unHash;
    HashItemType* pItem = findEntry(a_item.first,&unHash);
    if(pItem){return CPPUTILS_NULL;}
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType* 
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::findEntry( const KeyType& a_key, size_t* a_hashPtr )const
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


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType* VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::at(size_t a_unIndex) const
{
    return m_vectTable[a_unIndex];
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
const typename VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::iterator  
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::s_endIter(CPPUTILS_NULL);


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
iterator::iterator()
    :
      m_pItem(CPPUTILS_NULL)
{
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
iterator::iterator(HashItemType* a_pItem)
    :
      m_pItem(a_pItem)
{
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator->()const
{
    return m_pItem;
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator 
HashItemType*()const
{
    return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
const typename VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator  
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::s_endConstIter(CPPUTILS_NULL);


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
const_iterator::const_iterator()
    :
      m_pItem(CPPUTILS_NULL)
{
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
const HashItemType*
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator->()const
{
    return m_pItem;
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator 
const HashItemType*()const
{
    return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void* VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::HashItemPrivate::
operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void  VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::HashItemPrivate::
operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashBase<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
HashItemPrivate::HashItemPrivate(HashItemType&& a_mM)
    :
      HashItemType(::std::move(a_mM))
{
    this->prev = CPPUTILS_NULL;
}


}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
