//
// file:			hashtbl.impl.hpp
// path:			include/cpputils/hashtbl.impl.hpp
// created on:		2017 Jul 21
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP
//#error do not include this header directly
#include "hashtbl.hpp"
#endif

#ifndef cinternal_hash1_raw_mem_inline_needed
#define cinternal_hash1_raw_mem_inline_needed
#endif
#include <cinternal/hash_functions.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <memory.h>
#include <new>

#ifdef CPPUTILS_STD_MOVE_DEFINED
#include <utility>
#define CPPUTILS_STD_MOVE  ::std::move
#else
#define CPPUTILS_STD_MOVE(_val)     (_val)
#endif
#include <cinternal/undisable_compiler_warnings.h>



namespace __private { namespace __implementation {

CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);

}}  // namespace __private { namespace __implementation {

namespace cpputils { namespace hashtbl {


template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
bool BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::RemoveEntry01(const KeyType& a_key)
{
	HashItemTypeAdv* pItem = FindEntry(a_key);
	if(pItem){
		RemoveEntry(pItem);
		return true;
	}
	return false;
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
void BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::RemoveEntry(const HashItemTypeAdv* a_item_p)
{
	HashItemPrivate* pItem = const_cast<HashItemPrivate*>(static_cast<const HashItemPrivate*>(a_item_p));
	
	if(m_pTable[pItem->hash]==pItem){m_pTable[pItem->hash]=pItem->next;}
	if(m_pFirstItem==pItem){m_pFirstItem=pItem->nextInTheList;}
	if(m_pLastItem==pItem){m_pLastItem=pItem->prevInTheList;}
	delete pItem; // destructor will delete from list
	--m_unSize;
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
size_t BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::size()const
{
	return m_unSize;
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
void BaseBase<KeyType,HashItem,HashItemPrivate,Hash,templateDefaultSize>::clear() CPPUTILS_NOEXCEPT
{
	HashItemPrivate *pItemNext, *pItem = static_cast<HashItemPrivate*>(m_pFirstItem);
	
	while(pItem){
        m_pTable[pItem->hash]=CPPUTILS_NULL;
		pItemNext = pItem->nextInTheList;
		delete pItem;
		pItem = pItemNext;
	}
	
	m_unSize = 0;
	m_pLastItem = m_pFirstItem = CPPUTILS_NULL;
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
void BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::pop_back()
{
	RemoveEntry(m_pLastItem);
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
void BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::pop_front() 
{
	RemoveEntry(m_pFirstItem);
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::BaseBase(size_t a_tInitSize)
	:
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_pLastItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItemTypeAdv**>(calloc(tRet,sizeof(HashItemTypeAdv*)));
	if(!m_pTable){throw std::bad_alloc();}
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::BaseBase(const BaseBase& a_cM)
	:
	  m_unRoundedTableSizeMin1(a_cM.m_unRoundedTableSizeMin1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_pLastItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	HashItemPrivate* pItem = static_cast<HashItemPrivate*>(a_cM.m_pFirstItem);
	size_t tRet(m_unRoundedTableSizeMin1 + 1);
	m_pTable = static_cast<HashItemTypeAdv**>(calloc(tRet, sizeof(HashItemTypeAdv*)));
	if (!m_pTable) { throw std::bad_alloc(); }

	for (; pItem; pItem= pItem->nextInTheList) {
		AddEntryWithKnownHashRaw(*pItem);
	}
}

// after this, you can not use a_cM
template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::BaseBase(BaseBase* a_pMM) CPPUTILS_NOEXCEPT
	:
	  m_pTable(a_pMM->m_pTable),
	  m_unRoundedTableSizeMin1(a_pMM->m_unRoundedTableSizeMin1),
	  m_pFirstItem(a_pMM->m_pFirstItem),
	  m_pLastItem(a_pMM->m_pLastItem),
	  m_unSize(a_pMM->m_unSize)
{
	a_pMM->m_pFirstItem = CPPUTILS_NULL;
	a_pMM->m_pLastItem = CPPUTILS_NULL;
	a_pMM->m_unSize = 0;
	a_pMM->m_pTable = CPPUTILS_NULL;
}

#ifdef CPPUTILS_CPP_11_DEFINED
// after this, you can not use a_cM
template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::BaseBase(BaseBase&& a_cM) CPPUTILS_NOEXCEPT
	:
	  BaseBase(&a_cM)
{
}
#endif

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::~BaseBase()
{
	HashItemPrivate *pItemNext, *pItem = static_cast<HashItemPrivate*>(m_pFirstItem);
	
	while(pItem){
		pItemNext = pItem->nextInTheList;
		delete pItem;
		pItem = pItemNext;
	}
	
	:: free(m_pTable);
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
const BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>& 
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::operator=(const BaseBase& a_cM)
{
    {
        HashItemPrivate *pItemNext, *pItem = static_cast<HashItemPrivate*>(m_pFirstItem);
        
        while(pItem){
            pItemNext = pItem->nextInTheList;
            delete pItem;
            pItem = pItemNext;
        }
    }
    
	m_pLastItem=m_pFirstItem=CPPUTILS_NULL;
	m_unSize = (0);

	{
		HashItemPrivate *pItem = static_cast<HashItemPrivate*>(a_cM.m_pFirstItem);
		size_t tRet(m_unRoundedTableSizeMin1 + 1);
		const size_t memorySize = tRet * sizeof(HashItemTypeAdv*);
		HashItemTypeAdv**  pTableTmp = static_cast<HashItemTypeAdv**>(realloc(m_pTable, memorySize));
		if (!pTableTmp) { free(m_pTable);m_pTable=CPPUTILS_NULL;throw std::bad_alloc(); }
		m_pTable = pTableTmp;
		memset(m_pTable, 0, memorySize);
        m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;

		for (; pItem; pItem = pItem->nextInTheList) {
			AddEntryWithKnownHashRaw(*pItem);
		}
	}

	return *this;
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
const BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>& 
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::ReplaceWithOther(BaseBase* a_cM) CPPUTILS_NOEXCEPT
{
	HashItemTypeAdv**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	HashItemTypeAdv*	pFirstItem = m_pFirstItem;
	HashItemTypeAdv*	pLastItem = m_pLastItem;
	size_t		unSize = m_unSize;

	m_pTable=a_cM->m_pTable;
	m_unRoundedTableSizeMin1 = a_cM->m_unRoundedTableSizeMin1;
	m_pFirstItem=a_cM->m_pFirstItem;
	m_pLastItem=a_cM->m_pLastItem;
	m_unSize = (a_cM->m_unSize);

	a_cM->m_pTable = pTable;
	a_cM->m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_cM->m_pFirstItem = pFirstItem;
	a_cM->m_pLastItem = pLastItem;
	a_cM->m_unSize = (unSize);

	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
const BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>& 
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::operator=(BaseBase&& a_cM) CPPUTILS_NOEXCEPT
{
	return this->ReplaceWithOther(&a_cM);
}
#endif

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv* 
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::AddEntryEvenIfExistsRaw(const HashItemType& a_item)
{
	Hash fnHash;
	size_t unHash = (fnHash(a_item.first))&m_unRoundedTableSizeMin1;
	return AddEntryWithKnownHashRaw( HashItemTypeAdv(a_item,unHash) );
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv*
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::AddEntryIfNotExistRaw(const HashItemType& a_item)
{
	size_t unHash;
	if(FindEntry(a_item.first,&unHash)){
		return CPPUTILS_NULL; // we do not overwrite
	}
	
	return AddEntryWithKnownHashRaw( HashItemTypeAdv(a_item,unHash) );
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv*
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::AddEntryWithKnownHashRaw(const HashItemType& a_item, size_t a_hash)
{
    return AddEntryWithKnownHashRaw( HashItemTypeAdv(a_item,a_hash) );
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv*
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::AddEntryWithKnownHashRaw(const HashItemTypeAdv& a_item)
{	
	HashItemPrivate* pItem = new HashItemPrivate(a_item);
	
	pItem->next = static_cast<HashItemPrivate*>(m_pTable[a_item.hash]);
	if(m_pTable[a_item.hash]){pItem->next->prev=pItem;}
	m_pTable[a_item.hash] = pItem;
	
	pItem->nextInTheList = static_cast<HashItemPrivate*>(m_pFirstItem);
	if(m_pFirstItem){
		pItem->nextInTheList->prevInTheList=pItem;
	}
	else{
		m_pLastItem = pItem;
	}
	m_pFirstItem = pItem;
	
	++m_unSize;
	
	return static_cast<HashItemTypeAdv*>(pItem);
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv*
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::FindEntry(const KeyType& a_key,size_t* a_hashPtr)const
{
	Hash fnHash;
	HashItemPrivate* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (fnHash(a_key))&m_unRoundedTableSizeMin1;
	pItemToRet = static_cast<HashItemPrivate*>(m_pTable[unHash]);

	while (pItemToRet) {
		if(a_key==pItemToRet->first){
			return static_cast<HashItemTypeAdv*>(pItemToRet);
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv*
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::FindEntryWithKnownHash(const KeyType& a_key,size_t a_knownHash)const
{
	HashItemPrivate* pItemToRet = static_cast<HashItemPrivate*>(m_pTable[a_knownHash]);

	while (pItemToRet) {
		if(a_key==pItemToRet->first){
			return static_cast<HashItemTypeAdv*>(pItemToRet);
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}

template <typename KeyType,typename HashItemType, typename HashItemPrivate, typename Hash,size_t templateDefaultSize>
typename BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::HashItemTypeAdv*
BaseBase<KeyType,HashItemType,HashItemPrivate,Hash,templateDefaultSize>::firstItem()const
{
	return m_pFirstItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
const typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator  Base<KeyType,DataType,Hash,templateDefaultSize>::s_endIter(CPPUTILS_NULL);
template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
const typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator  Base<KeyType,DataType,Hash,templateDefaultSize>::s_endConstIter(CPPUTILS_NULL);

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::Base(size_t a_tInitSize)
	:
	  BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >(a_tInitSize)
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::Base(const Base& a_cM)
	:
	  BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >(a_cM)
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::Base(Base* a_pMM) CPPUTILS_NOEXCEPT
	:
	  BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >(a_pMM)
{
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::Base(Base&& a_cM) CPPUTILS_NOEXCEPT
	:
	  Base(&a_cM)
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator 
Base<KeyType,DataType,Hash,templateDefaultSize>::AddEntryIfNotExistMv(const KeyType& a_key, DataType&& a_data)
{
    return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
            AddEntryIfNotExistRaw( __p::__i::HashItemBase<KeyType,DataType>(a_key,a_data) );
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator 
Base<KeyType,DataType,Hash,templateDefaultSize>::AddOrReplaceEntryMv(const KeyType& a_key, DataType&& a_data)
{
    __p::__i::HashItemBase<KeyType,DataType>* pItem;
    size_t unHash;
    if((pItem=BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
        FindEntry(a_key,&unHash)))
    {
        pItem->second = a_data;
        return static_cast<HashItemTypeAdv*>(pItem); // we can overwrite
    }

    return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
            AddEntryWithKnownHashRaw( HashItemTypeAdv(__p::__i::HashItemBase<KeyType,DataType>(a_key,a_data),unHash) );
}


template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator 
Base<KeyType,DataType,Hash,templateDefaultSize>::AddEntryWithKnownHashMv(const KeyType& a_key, DataType&& a_data,size_t a_hashVal)
{
    return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
            AddEntryWithKnownHashRaw( HashItemTypeAdv(__p::__i::HashItemBase<KeyType,DataType>(a_key,a_data),a_hashVal) );
}
#endif

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::~Base()
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
const Base<KeyType,DataType,Hash,templateDefaultSize>& Base<KeyType,DataType,Hash,templateDefaultSize>::operator=(const Base& a_cM)
{
	BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::operator=(a_cM);
	return *this;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
const Base<KeyType,DataType,Hash,templateDefaultSize>& Base<KeyType,DataType,Hash,templateDefaultSize>::ReplaceWithOther(Base* a_cM) CPPUTILS_NOEXCEPT
{
	BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::ReplaceWithOther(a_cM);
	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
const Base<KeyType,DataType,Hash,templateDefaultSize>& Base<KeyType,DataType,Hash,templateDefaultSize>::operator=(Base&& a_cM) CPPUTILS_NOEXCEPT
{
	return ReplaceWithOther(&a_cM);
}
#endif

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
bool Base<KeyType,DataType,Hash,templateDefaultSize>::RemoveEntry02(const KeyType& a_key,DataType* a_pData)
{
    HashItemTypeAdv* pItem = BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
            FindEntry(a_key);
    if(pItem){
        *a_pData = CPPUTILS_STD_MOVE(pItem->second);
        BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
                RemoveEntry(pItem);
        return true;
    }
    return false;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::AddEntryEvenIfExists(const KeyType& a_key, const DataType& a_data)
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
			AddEntryEvenIfExistsRaw( __p::__i::HashItemBase<KeyType,DataType>(a_key,a_data) );
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::AddEntryIfNotExist(const KeyType& a_key, const DataType& a_data)
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
			AddEntryIfNotExistRaw( __p::__i::HashItemBase<KeyType,DataType>(a_key,a_data) );
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator 
Base<KeyType,DataType,Hash,templateDefaultSize>::AddOrReplaceEntry(const KeyType& a_key, const DataType& a_data)
{
	__p::__i::HashItemBase<KeyType,DataType>* pItem;
	size_t unHash;
	if((pItem=BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::FindEntry(a_key,&unHash))){
		pItem->second = a_data;
		return static_cast<HashItemTypeAdv*>(pItem); // we can overwrite
	}
	
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
	        AddEntryWithKnownHashRaw( HashItemTypeAdv(__p::__i::HashItemBase<KeyType,DataType>(a_key,a_data),unHash) );
}



template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator 
Base<KeyType,DataType,Hash,templateDefaultSize>::AddEntryWithKnownHash(const KeyType& a_key, const DataType& a_data,size_t a_hashVal)
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::
			AddEntryWithKnownHashRaw( HashItemTypeAdv(__p::__i::HashItemBase<KeyType,DataType>(a_key,a_data),a_hashVal) );
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::FindEntryM(const KeyType& a_key,size_t* a_hashPtr,
																			 typename FuncF<KeyType,DataType>::Find a_fnc, void* a_clbkData)const
{
	__p::__i::HashItemFull<KeyType,DataType>* pItemToRet = 
			static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(
	            BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::FindEntry(a_key,a_hashPtr));

	while (pItemToRet) {
		if((a_key==pItemToRet->first)&&a_fnc(a_clbkData,pItemToRet->first,pItemToRet->second)){
			return static_cast<HashItemTypeAdv*>(pItemToRet);
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
DataType& Base<KeyType,DataType,Hash,templateDefaultSize>::operator[](const KeyType& a_key)
{
	size_t unHash;
	__p::__i::HashItemBase<KeyType,DataType>* pItemToRet = 
			BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::FindEntry(a_key,&unHash);
	
	if(pItemToRet){
		return pItemToRet->second;
	}
	
	pItemToRet = AddEntryWithKnownHash(a_key,DataType(),unHash);
	return pItemToRet->second;
}


template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::begin()
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::firstItem();
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::end()
{
	return s_endIter;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator Base<KeyType,DataType,Hash,templateDefaultSize>::begin()const
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >::firstItem();
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator Base<KeyType,DataType,Hash,templateDefaultSize>::end()const
{
	return s_endConstIter;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::iterator( HashItemTypeAdv* a_pItem)
	:
	  m_pItem(a_pItem)
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator& Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
    typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator& Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
    typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::HashItemTypeAdv* 
Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::operator 
typename Base<KeyType,DataType,Hash,templateDefaultSize>::HashItemTypeAdv*()const
{
	return m_pItem;
}


template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::next()const
{
    return iterator(m_pItem->nextInTheList);
}


template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator Base<KeyType,DataType,Hash,templateDefaultSize>::iterator::previous()const
{
    return iterator(m_pItem->nextInTheList);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::const_iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::const_iterator(const iterator& a_iter)
	:
	  m_pItem(const_cast< HashItemTypeAdv* >(a_iter.operator->()))
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::const_iterator(const HashItemTypeAdv* a_pItem)
	:
	  m_pItem(const_cast< HashItemTypeAdv* >(a_pItem))
{
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator& Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
    typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator& Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
    typename Base<KeyType,DataType,Hash,templateDefaultSize>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
const typename Base<KeyType,DataType,Hash,templateDefaultSize>::HashItemTypeAdv* 
Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::operator 
const typename Base<KeyType,DataType,Hash,templateDefaultSize>::HashItemTypeAdv*()const
{
	return m_pItem;
}


template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::next()const
{
    return iterator(m_pItem->nextInTheList);
}


template <typename KeyType,typename DataType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator Base<KeyType,DataType,Hash,templateDefaultSize>::const_iterator::previous()const
{
    return iterator(m_pItem->prevInTheList);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename Hash,size_t templateDefaultSize>
const typename Base<KeyType,void,Hash,templateDefaultSize>::iterator  Base<KeyType,void,Hash,templateDefaultSize>::s_endIter(CPPUTILS_NULL);
template <typename KeyType,typename Hash,size_t templateDefaultSize>
const typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator  Base<KeyType,void,Hash,templateDefaultSize>::s_endConstIter(CPPUTILS_NULL);

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::Base(size_t a_tInitSize)
	:
	  BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >(a_tInitSize)
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::Base(const Base& a_cM)
	:
	  BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >(a_cM)
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::Base(Base* a_pMM) CPPUTILS_NOEXCEPT
	:
	  BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >(a_pMM)
{
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::Base(Base&& a_cM) CPPUTILS_NOEXCEPT
	:
	  Base(&a_cM)
{
}
#endif

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::~Base()
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
const Base<KeyType,void,Hash,templateDefaultSize>& Base<KeyType,void,Hash,templateDefaultSize>::operator=(const Base& a_cM)
{
	BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::operator=(a_cM);
	return *this;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
const Base<KeyType,void,Hash,templateDefaultSize>& Base<KeyType,void,Hash,templateDefaultSize>::ReplaceWithOther(Base* a_cM) CPPUTILS_NOEXCEPT
{
	BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::ReplaceWithOther(a_cM);
	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename Hash,size_t templateDefaultSize>
const Base<KeyType,void,Hash,templateDefaultSize>& Base<KeyType,void,Hash,templateDefaultSize>::operator=(Base&& a_cM) CPPUTILS_NOEXCEPT
{
	return ReplaceWithOther(&a_cM);
}
#endif

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::AddEntryEvenIfExists(const KeyType& a_key)
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::
			AddEntryEvenIfExistsRaw( __p::__i::HashItemBase<KeyType,void>(a_key) );
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::AddEntryIfNotExist(const KeyType& a_key)
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::
			AddEntryIfNotExistRaw( __p::__i::HashItemBase<KeyType,void>(a_key) );
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator 
Base<KeyType,void,Hash,templateDefaultSize>::AddEntryWithKnownHash(const KeyType& a_key, size_t a_hashVal)
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::
			AddEntryWithKnownHashRaw( HashItemTypeAdv(__p::__i::HashItemBase<KeyType,void>(a_key),a_hashVal) );
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::begin()
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::firstItem();
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::end()
{
	return s_endIter;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator Base<KeyType,void,Hash,templateDefaultSize>::begin()const
{
	return BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash,templateDefaultSize  >::firstItem();
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator Base<KeyType,void,Hash,templateDefaultSize>::end()const
{
	return s_endConstIter;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::iterator::iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::iterator::iterator( HashItemTypeAdv* a_pItem)
	:
	  m_pItem(a_pItem)
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator& Base<KeyType,void,Hash,templateDefaultSize>::iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator& Base<KeyType,void,Hash,templateDefaultSize>::iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::HashItemTypeAdv* 
Base<KeyType,void,Hash,templateDefaultSize>::iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::iterator::operator 
typename Base<KeyType,void,Hash,templateDefaultSize>::HashItemTypeAdv*()const
{
	return m_pItem;
}


template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::iterator::next()const
{
	return iterator(m_pItem->nextInTheList);
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::iterator Base<KeyType,void,Hash,templateDefaultSize>::iterator::previous()const
{
    return iterator(m_pItem->prevInTheList);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::const_iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::const_iterator(const iterator& a_iter)
	:
	  m_pItem(const_cast< HashItemTypeAdv* >(a_iter.operator->()))
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::const_iterator(const HashItemTypeAdv* a_pItem)
	:
	  m_pItem(const_cast< HashItemTypeAdv* >(a_pItem))
{
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator& Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator& Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
const typename Base<KeyType,void,Hash,templateDefaultSize>::HashItemTypeAdv* 
Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::operator 
const typename Base<KeyType,void,Hash,templateDefaultSize>::HashItemTypeAdv*()const
{
	return m_pItem;
}


template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::next()const
{
	return iterator(m_pItem->nextInTheList);
}

template <typename KeyType,typename Hash,size_t templateDefaultSize>
typename Base<KeyType,void,Hash,templateDefaultSize>::const_iterator Base<KeyType,void,Hash,templateDefaultSize>::const_iterator::previous()const
{
    return iterator(m_pItem->prevInTheList);
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
template <typename KeyType>
size_t FHash<KeyType>::operator()(const KeyType& a_key)const
{
	return ::cinternal_hash1_raw_mem_inline(&a_key,sizeof(KeyType));
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType>
bool FuncF<KeyType,DataType>::DefaultFind(void*,const KeyType&, const DataType&)
{
	return true;
}


template <typename CharType>
size_t FHashStr<CharType>::operator()(const ::std::basic_string<CharType>& a_key)const
{
	return ::cinternal_hash1_raw_mem_inline(a_key.c_str(),a_key.length()*sizeof(CharType));
}

template <typename IntType>
size_t FHashInt<IntType>::operator()(const IntType& a_key)const
{
    //return static_cast<size_t>(a_key);
    return (size_t)(a_key);
}


}}  // namespace cpputils { namespace hashtbl {



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
namespace __p { namespace __i {


template <typename KeyType,typename DataType>
HashItemFull<KeyType,DataType>::HashItemFull(const KeyType& a_key, const DataType& a_data)
    :	
	  HashItem<HashItemBase<KeyType,DataType> >(HashItemBase<KeyType,DataType>(a_key,a_data)),
	  prev(CPPUTILS_NULL),
	  next(CPPUTILS_NULL),
	  prevInTheList(CPPUTILS_NULL),
	  nextInTheList(CPPUTILS_NULL)
{
}


template <typename KeyType,typename DataType>
HashItemFull<KeyType,DataType>::HashItemFull(const HashItem<HashItemBase<KeyType,DataType> >& a_item)
    :	
	  HashItem<HashItemBase<KeyType,DataType> >(a_item),
	  prev(CPPUTILS_NULL),
	  next(CPPUTILS_NULL),
	  prevInTheList(CPPUTILS_NULL),
	  nextInTheList(CPPUTILS_NULL)
{
}


template <typename KeyType,typename DataType>
HashItemFull<KeyType,DataType>::~HashItemFull()
{
	if(this->next){
		this->next->prev = this->prev;
	}
	if(this->prev){
		this->prev->next = this->next;
	}
	
	if(this->nextInTheList){
		this->nextInTheList->prevInTheList = this->prevInTheList;
	}
	if(this->prevInTheList){
		this->prevInTheList->nextInTheList = this->nextInTheList;
	}
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType>
HashItemBase<KeyType,DataType>::HashItemBase(const KeyType& a_key, const DataType& a_data)
	:
	  first(a_key),
	  second(a_data)
{
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename DataType>
HashItemBase<KeyType,DataType>::HashItemBase(const KeyType& a_key, DataType&& a_data)
    :
      first(a_key),
      second(a_data)
{
}
#endif  // #ifdef CPPUTILS_CPP_11_DEFINED

template <typename KeyType,typename DataType>
HashItemBase<KeyType,DataType>::~HashItemBase()
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeHashItem>
HashItem<TypeHashItem>::HashItem(const TypeHashItem& a_item, size_t a_hash)
	:
	  TypeHashItem(a_item),
      hash(a_hash)
{
}


template <typename TypeHashItem>
HashItem<TypeHashItem>::~HashItem()
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename KeyType>
HashItemFull<KeyType,void>::HashItemFull(const KeyType& a_key)
    :	
	  HashItem<HashItemBase<KeyType,void> >(a_key),
	  prev(CPPUTILS_NULL),
	  next(CPPUTILS_NULL),
	  prevInTheList(CPPUTILS_NULL),
	  nextInTheList(CPPUTILS_NULL)
{
}


template <typename KeyType>
HashItemFull<KeyType,void>::HashItemFull(const HashItem<HashItemBase<KeyType,void> >& a_item)
    :	
	  HashItem<HashItemBase<KeyType,void> >(a_item),
	  prev(CPPUTILS_NULL),
	  next(CPPUTILS_NULL),
	  prevInTheList(CPPUTILS_NULL),
	  nextInTheList(CPPUTILS_NULL)
{
}


template <typename KeyType>
HashItemFull<KeyType,void>::~HashItemFull()
{
	if(this->next){
		this->next->prev = this->prev;
	}
	if(this->prev){
		this->prev->next = this->next;
	}
	
	if(this->nextInTheList){
		this->nextInTheList->prevInTheList = this->prevInTheList;
	}
	if(this->prevInTheList){
		this->prevInTheList->nextInTheList = this->nextInTheList;
	}
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType>
HashItemBase<KeyType,void>::HashItemBase(const KeyType& a_key)
	:
	  first(a_key)
{
}

template <typename KeyType>
HashItemBase<KeyType,void>::~HashItemBase()
{
}



}}  // namespace __p { namespace __i {



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP
