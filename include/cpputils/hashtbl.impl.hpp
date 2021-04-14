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

#include <stdlib.h>
#include <memory.h>
#include <new>



namespace __private { namespace __implementation {

CPPUTILS_EXPORT size_t hash1_( const void* a_pKey, size_t a_unKeySize );
CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);

}}  // namespace __private { namespace __implementation {

namespace cpputils { namespace hashtbl {


template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
bool BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::RemoveEntry(const KeyType& a_key)
{
	HashItem* pItem = FindEntryRaw(a_key);
	if(pItem){
		RemoveEntry(pItem);
		return true;
	}
	return false;
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
void BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::RemoveEntry(const HashItem* a_item_p)
{
	HashItemPrivate* pItem = const_cast<HashItemPrivate*>(static_cast<const HashItemPrivate*>(a_item_p));
	
	if(m_pTable[pItem->hashValue]==pItem){m_pTable[pItem->hashValue]=pItem->next;}
	if(m_pFirstItem==pItem){m_pFirstItem=pItem->nextInTheList;}
	delete pItem; // destructor will delete from list
	--m_unSize;
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
size_t BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::size()const
{
	return m_unSize;
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::BaseBase(size_t a_tInitSize)
	:
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItem**>(calloc(tRet,sizeof(HashItem*)));
	if(!m_pTable){throw std::bad_alloc();}
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::BaseBase(const BaseBase& a_cM)
	:
	  m_unRoundedTableSizeMin1(a_cM.m_unRoundedTableSizeMin1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	HashItemPrivate* pItem = static_cast<HashItemPrivate*>(a_cM.m_pFirstItem);
	size_t tRet(m_unRoundedTableSizeMin1 + 1);
	m_pTable = static_cast<HashItem**>(calloc(tRet, sizeof(HashItem*)));
	if (!m_pTable) { throw std::bad_alloc(); }

	for (; pItem; pItem= pItem->nextInTheList) {
		AddEntryWithKnownHashRaw(*pItem, pItem->hashValue);
	}
}

// after this, you can not use a_cM
template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::BaseBase(BaseBase* a_pMM) noexcept
	:
	  m_pTable(a_pMM->m_pTable),
	  m_unRoundedTableSizeMin1(a_pMM->m_unRoundedTableSizeMin1),
	  m_pFirstItem(a_pMM->m_pFirstItem),
	  m_unSize(a_pMM->m_unSize)
{
	a_pMM->m_pFirstItem = CPPUTILS_NULL;
	a_pMM->m_unSize = 0;
	a_pMM->m_pTable = CPPUTILS_NULL;
}

#ifdef CPPUTILS_CPP_11_DEFINED
// after this, you can not use a_cM
template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::BaseBase(BaseBase&& a_cM) noexcept
	:
	  BaseBase(&a_cM)
{
}
#endif

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::~BaseBase()
{
	HashItemPrivate *pItemNext, *pItem = static_cast<HashItemPrivate*>(m_pFirstItem);
	
	while(pItem){
		pItemNext = pItem->nextInTheList;
		delete pItem;
		pItem = pItemNext;
	}
	
	free(m_pTable);
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
const BaseBase<KeyType,HashItem,HashItemPrivate,Hash>& BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::operator=(const BaseBase& a_cM)
{
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_pFirstItem=CPPUTILS_NULL;
	m_unSize = (0);

	{
		HashItemPrivate *pItem = static_cast<HashItemPrivate*>(a_cM.m_pFirstItem);
		size_t tRet(m_unRoundedTableSizeMin1 + 1);
		const size_t memorySize = tRet * sizeof(HashItem*);
		HashItem**  pTableTmp = static_cast<HashItem**>(realloc(m_pTable, memorySize));
		if (!pTableTmp) { throw std::bad_alloc(); }
		m_pTable = pTableTmp;
		memset(m_pTable, 0, memorySize);

		for (; pItem; pItem = pItem->nextInTheList) {
			AddEntryWithKnownHashRaw(*pItem, pItem->hashValue);
		}
	}

	return *this;
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
const BaseBase<KeyType,HashItem,HashItemPrivate,Hash>& BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::ReplaceWithOther(BaseBase* a_cM) noexcept
{
	HashItem**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	HashItem*	pFirstItem = m_pFirstItem;
	size_t		unSize = m_unSize;

	m_pTable=a_cM->m_pTable;
	m_unRoundedTableSizeMin1 = a_cM->m_unRoundedTableSizeMin1;
	m_pFirstItem=a_cM->m_pFirstItem;
	m_unSize = (a_cM->m_unSize);

	a_cM->m_pTable = pTable;
	a_cM->m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_cM->m_pFirstItem = pFirstItem;
	a_cM->m_unSize = (unSize);

	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
const BaseBase<KeyType,HashItem,HashItemPrivate,Hash>& BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::operator=(BaseBase&& a_cM) noexcept
{
	return this->ReplaceWithOther(&a_cM);
}
#endif

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
HashItem* BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::AddEntryEvenIfExistsRaw(const HashItem& a_item)
{
	Hash fnHash;
	size_t unHash = (fnHash(a_item.first))&m_unRoundedTableSizeMin1;
	return AddEntryWithKnownHashRaw(a_item,unHash);
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
HashItem* BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::AddEntryIfNotExistRaw(const HashItem& a_item)
{
	size_t unHash;
	if(FindEntry(a_item.first,&unHash)){
		return CPPUTILS_NULL; // we do not overwrite
	}
	
	return AddEntryWithKnownHashRaw(a_item,unHash);
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
HashItem* BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::AddOrReplaceEntryRaw(const HashItem& a_item)
{
	HashItem* pItem;
	size_t unHash;
	if((pItem=FindEntry(a_item.first,&unHash))){
		*pItem = a_item;
		return pItem; // we can overwrite
	}
	
	return AddEntryWithKnownHashRaw(a_item,unHash);
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
HashItem* BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::AddEntryWithKnownHashRaw(const HashItem& a_item, size_t a_hashVal)
{	
	HashItemPrivate* pItem = new HashItemPrivate(a_item);

	pItem->hashValue = a_hashVal;
	
	pItem->next = static_cast<HashItemPrivate*>(m_pTable[a_hashVal]);
	if(m_pTable[a_hashVal]){pItem->next->prev=pItem;}
	m_pTable[a_hashVal] = pItem;
	
	pItem->nextInTheList = static_cast<HashItemPrivate*>(m_pFirstItem);
	if(m_pFirstItem){pItem->nextInTheList->prevInTheList=pItem;}
	m_pFirstItem = pItem;
	
	++m_unSize;
	
	return static_cast<HashItem*>(pItem);
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
HashItem* BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::FindEntry(const KeyType& a_key,size_t* a_hashPtr)const
{
	Hash fnHash;
	HashItemPrivate* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (fnHash(a_key))&m_unRoundedTableSizeMin1;
	pItemToRet = static_cast<HashItemPrivate*>(m_pTable[unHash]);

	while (pItemToRet) {
		if(a_key==pItemToRet->first){
			return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}

template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
HashItem* BaseBase<KeyType,HashItem,HashItemPrivate,Hash>::firstItem()const
{
	return m_pFirstItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash>
const typename Base<KeyType,DataType,Hash>::iterator  Base<KeyType,DataType,Hash>::s_endIter(CPPUTILS_NULL);
template <typename KeyType,typename DataType,typename Hash>
const typename Base<KeyType,DataType,Hash>::const_iterator  Base<KeyType,DataType,Hash>::s_endConstIter(CPPUTILS_NULL);

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::Base(size_t a_tInitSize)
	:
	  BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >(a_tInitSize)
{
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::Base(const Base& a_cM)
	:
	  BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >(a_cM)
{
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::Base(Base* a_pMM) noexcept
	:
	  BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >(a_pMM)
{
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::Base(Base&& a_cM) noexcept
	:
	  Base(&a_cM)
{
}
#endif

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::~Base()
{
}

template <typename KeyType,typename DataType,typename Hash>
const Base<KeyType,DataType,Hash>& Base<KeyType,DataType,Hash>::operator=(const Base& a_cM)
{
	BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::operator=(a_cM);
	return *this;
}

template <typename KeyType,typename DataType,typename Hash>
const Base<KeyType,DataType,Hash>& Base<KeyType,DataType,Hash>::ReplaceWithOther(Base* a_cM) noexcept
{
	BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::ReplaceWithOther(a_cM);
	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename DataType,typename Hash>
const Base<KeyType,DataType,Hash>& Base<KeyType,DataType,Hash>::operator=(Base&& a_cM) noexcept
{
	return ReplaceWithOther(&a_cM);
}
#endif

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::AddEntryEvenIfExists(const KeyType& a_key, const DataType& a_data)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::
			AddEntryEvenIfExistsRaw( __p::__i::HashItem<KeyType,DataType>(a_key,a_data) );
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::AddEntryIfNotExist(const KeyType& a_key, const DataType& a_data)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::
			AddEntryIfNotExistRaw( __p::__i::HashItem<KeyType,DataType>(a_key,a_data) );
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::AddOrReplaceEntry(const KeyType& a_key, const DataType& a_data)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::
			AddOrReplaceEntryRaw( __p::__i::HashItem<KeyType,DataType>(a_key,a_data) );
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::AddEntryWithKnownHash(const KeyType& a_key, const DataType& a_data,size_t a_hashVal)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::
			AddEntryWithKnownHashRaw( __p::__i::HashItem<KeyType,DataType>(a_key,a_data),a_hashVal );
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::FindEntryM(const KeyType& a_key,size_t* a_hashPtr,
																			 typename FuncF<KeyType,DataType>::Find a_fnc, void* a_clbkData)const
{
	__p::__i::HashItemFull<KeyType,DataType>* pItemToRet = 
			BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::FindEntry(a_key,a_hashPtr);

	while (pItemToRet) {
		if((a_key==pItemToRet->first)&&a_fnc(a_clbkData,pItemToRet->first,pItemToRet->second)){
			return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}

template <typename KeyType,typename DataType,typename Hash>
DataType& Base<KeyType,DataType,Hash>::operator[](const KeyType& a_key)
{
	size_t unHash;
	__p::__i::HashItem<KeyType,DataType>* pItemToRet = 
			BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::FindEntry(a_key,&unHash);
	
	if(pItemToRet){
		return pItemToRet->second;
	}
	
	pItemToRet = AddEntryWithKnownHash(a_key,DataType(),unHash);
	return pItemToRet->second;
}


template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::begin()
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::firstItem();
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::end()
{
	return s_endIter;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::const_iterator Base<KeyType,DataType,Hash>::begin()const
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >::firstItem();
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::const_iterator Base<KeyType,DataType,Hash>::end()const
{
	return s_endConstIter;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::iterator::iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::iterator::iterator( __p::__i::HashItem<KeyType,DataType>* a_pItem)
	:
	  m_pItem(a_pItem)
{
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator& Base<KeyType,DataType,Hash>::iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator& Base<KeyType,DataType,Hash>::iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::iterator Base<KeyType,DataType,Hash>::iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash>
typename __p::__i::HashItem<KeyType,DataType>* Base<KeyType,DataType,Hash>::iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::iterator::operator typename __p::__i::HashItem<KeyType,DataType>*()const
{
	return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::const_iterator::const_iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::const_iterator::const_iterator(const iterator& a_iter)
	:
	  m_pItem(const_cast< __p::__i::HashItem<KeyType,DataType>* >(a_iter.operator->()))
{
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::const_iterator::const_iterator(const __p::__i::HashItem<KeyType,DataType>* a_pItem)
	:
	  m_pItem(const_cast< __p::__i::HashItem<KeyType,DataType>* >(a_pItem))
{
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::const_iterator& Base<KeyType,DataType,Hash>::const_iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::const_iterator Base<KeyType,DataType,Hash>::const_iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::const_iterator& Base<KeyType,DataType,Hash>::const_iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename DataType,typename Hash>
typename Base<KeyType,DataType,Hash>::const_iterator Base<KeyType,DataType,Hash>::const_iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,DataType>* pItem = static_cast<__p::__i::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType,typename Hash>
const typename __p::__i::HashItem<KeyType,DataType>* Base<KeyType,DataType,Hash>::const_iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename DataType,typename Hash>
Base<KeyType,DataType,Hash>::const_iterator::operator const typename __p::__i::HashItem<KeyType,DataType>*()const
{
	return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename Hash>
const typename Base<KeyType,void,Hash>::iterator  Base<KeyType,void,Hash>::s_endIter(CPPUTILS_NULL);
template <typename KeyType,typename Hash>
const typename Base<KeyType,void,Hash>::const_iterator  Base<KeyType,void,Hash>::s_endConstIter(CPPUTILS_NULL);

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::Base(size_t a_tInitSize)
	:
	  BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >(a_tInitSize)
{
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::Base(const Base& a_cM)
	:
	  BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >(a_cM)
{
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::Base(Base* a_pMM) noexcept
	:
	  BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >(a_pMM)
{
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::Base(Base&& a_cM) noexcept
	:
	  Base(&a_cM)
{
}
#endif

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::~Base()
{
}

template <typename KeyType,typename Hash>
const Base<KeyType,void,Hash>& Base<KeyType,void,Hash>::operator=(const Base& a_cM)
{
	BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::operator=(a_cM);
	return *this;
}

template <typename KeyType,typename Hash>
const Base<KeyType,void,Hash>& Base<KeyType,void,Hash>::ReplaceWithOther(Base* a_cM) noexcept
{
	BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::ReplaceWithOther(a_cM);
	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType,typename Hash>
const Base<KeyType,void,Hash>& Base<KeyType,void,Hash>::operator=(Base&& a_cM) noexcept
{
	return ReplaceWithOther(&a_cM);
}
#endif

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::AddEntryEvenIfExists(const KeyType& a_key)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::
			AddEntryEvenIfExistsRaw( __p::__i::HashItem<KeyType,void>(a_key) );
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::AddEntryIfNotExist(const KeyType& a_key)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::
			AddEntryIfNotExistRaw( __p::__i::HashItem<KeyType,void>(a_key) );
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::AddEntryWithKnownHash(const KeyType& a_key, size_t a_hashVal)
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::
			AddEntryWithKnownHashRaw( __p::__i::HashItem<KeyType,void>(a_key),a_hashVal );
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::begin()
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::firstItem();
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::end()
{
	return s_endIter;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::const_iterator Base<KeyType,void,Hash>::begin()const
{
	return BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >::firstItem();
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::const_iterator Base<KeyType,void,Hash>::end()const
{
	return s_endConstIter;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::iterator::iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::iterator::iterator( __p::__i::HashItem<KeyType,void>* a_pItem)
	:
	  m_pItem(a_pItem)
{
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator& Base<KeyType,void,Hash>::iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator& Base<KeyType,void,Hash>::iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::iterator Base<KeyType,void,Hash>::iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash>
typename __p::__i::HashItem<KeyType,void>* Base<KeyType,void,Hash>::iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::iterator::operator typename __p::__i::HashItem<KeyType,void>*()const
{
	return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::const_iterator::const_iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::const_iterator::const_iterator(const iterator& a_iter)
	:
	  m_pItem(const_cast< __p::__i::HashItem<KeyType,void>* >(a_iter.operator->()))
{
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::const_iterator::const_iterator(const __p::__i::HashItem<KeyType,void>* a_pItem)
	:
	  m_pItem(const_cast< __p::__i::HashItem<KeyType,void>* >(a_pItem))
{
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::const_iterator& Base<KeyType,void,Hash>::const_iterator::operator++()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::const_iterator Base<KeyType,void,Hash>::const_iterator::operator++(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::const_iterator& Base<KeyType,void,Hash>::const_iterator::operator--()
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename Hash>
typename Base<KeyType,void,Hash>::const_iterator Base<KeyType,void,Hash>::const_iterator::operator--(int)
{
	__p::__i::HashItemFull<KeyType,void>* pItem = static_cast<__p::__i::HashItemFull<KeyType,void>*>(m_pItem);
	typename Base<KeyType,void>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename Hash>
const typename __p::__i::HashItem<KeyType,void>* Base<KeyType,void,Hash>::const_iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename Hash>
Base<KeyType,void,Hash>::const_iterator::operator const typename __p::__i::HashItem<KeyType,void>*()const
{
	return m_pItem;
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
template <typename KeyType>
size_t FHash<KeyType>::operator()(const KeyType& a_key)const
{
	return __private::__implementation::hash1_(&a_key,sizeof(KeyType));
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
	return __private::__implementation::hash1_(a_key.c_str(),a_key.length()*sizeof(CharType));
}

template <typename IntType>
size_t FHashInt<IntType>::operator()(const IntType& a_key)const
{
	return static_cast<size_t>(a_key);
}


}}  // namespace cpputils { namespace hashtbl {



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
namespace __p { namespace __i {


template <typename KeyType,typename DataType>
HashItemFull<KeyType,DataType>::HashItemFull(const KeyType& a_key, const DataType& a_data)
    :	
	  HashItem<KeyType,DataType>(a_key,a_data),
	  prev(CPPUTILS_NULL),
	  next(CPPUTILS_NULL),
	  prevInTheList(CPPUTILS_NULL),
	  nextInTheList(CPPUTILS_NULL)
{
}


template <typename KeyType,typename DataType>
HashItemFull<KeyType,DataType>::HashItemFull(const HashItem<KeyType,DataType>& a_item)
    :	
	  HashItem<KeyType,DataType>(a_item.first,a_item.second),
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
HashItem<KeyType,DataType>::HashItem(const KeyType& a_key, const DataType& a_data)
	:
	  first(a_key),
	  second(a_data)
{
}

template <typename KeyType,typename DataType>
HashItem<KeyType,DataType>::~HashItem()
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename KeyType>
HashItemFull<KeyType,void>::HashItemFull(const KeyType& a_key)
    :	
	  HashItem<KeyType,void>(a_key),
	  prev(CPPUTILS_NULL),
	  next(CPPUTILS_NULL),
	  prevInTheList(CPPUTILS_NULL),
	  nextInTheList(CPPUTILS_NULL)
{
}


template <typename KeyType>
HashItemFull<KeyType,void>::HashItemFull(const HashItem<KeyType,void>& a_item)
    :	
	  HashItem<KeyType,void>(a_item.first),
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
HashItem<KeyType,void>::HashItem(const KeyType& a_key)
	:
	  first(a_key)
{
}

template <typename KeyType>
HashItem<KeyType,void>::~HashItem()
{
}


}}  // namespace __p { namespace __i {



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP
