//
// file:			hashtbl.impl.hpp
// path:			include/common/hashtbl.impl.hpp
// created on:		2017 Jul 21
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef COMMON_HASHTBL_IMPL_HPP
#define COMMON_HASHTBL_IMPL_HPP


#ifndef COMMON_HASHTBL_HPP
//#error do not include this header directly
#include "hashtbl.hpp"
#endif

#include <stdlib.h>
#include <memory.h>
#include <new>



namespace __private { namespace __implementation {


template <typename KeyType,typename DataType>
struct HashItemFull : public ::common::hashtbl::Base<KeyType,DataType>::HashItem {
public:
	HashItemFull(const KeyType& key, const DataType& data);
	~HashItemFull();
public:
	HashItemFull	*prev, *next;
	HashItemFull	*prevInTheList, *nextInTheList;
	size_t			hashValue;
};

template <typename KeyType>
struct HashItemFull<KeyType,void> : public ::common::hashtbl::Base<KeyType,void>::HashItem {
public:
	HashItemFull(const KeyType& key);
	~HashItemFull();
public:
	HashItemFull	*prev, *next;
	HashItemFull	*prevInTheList, *nextInTheList;
	size_t			hashValue;
};

CPPUTILS_EXPORT size_t hash1_( const void* a_pKey, size_t a_unKeySize );
CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);


}}  // namespace __private { namespace __implementation {

namespace common { namespace hashtbl {

template <typename KeyType,typename DataType>
const typename Base<KeyType,DataType>::iterator  Base<KeyType,DataType>::s_endIter(CPPUTILS_NULL);
template <typename KeyType,typename DataType>
const typename Base<KeyType,DataType>::const_iterator  Base<KeyType,DataType>::s_endConstIter(CPPUTILS_NULL);


template <typename KeyType,typename DataType>
Base<KeyType,DataType>::Base(size_t a_tInitSize, typename FuncsT<KeyType,DataType>::Hash a_funcHash)
	:
	  m_funcHash(a_funcHash? a_funcHash: (typename FuncsT<KeyType,DataType>::Hash(&Funcs<KeyType, DataType>::DefaultHash))),
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItem**>(calloc(tRet,sizeof(HashItem*)));
	if(!m_pTable){throw std::bad_alloc();}
}

template <typename KeyType, typename DataType>
Base<KeyType, DataType>::Base(typename FuncsT<KeyType, DataType>::Hash a_funcHash)
	:
	  m_funcHash(a_funcHash ? a_funcHash : (&Funcs<KeyType, DataType>::DefaultHash)),
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(DEFAULT_TABLE_SIZE) - 1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1 + 1);
	m_pTable = static_cast<HashItem**>(calloc(tRet, sizeof(HashItem*)));
	if (!m_pTable) { throw std::bad_alloc(); }
}


template <typename KeyType, typename DataType>
Base<KeyType, DataType>::Base(const Base& a_cM)
	:
	  m_funcHash(a_cM.m_funcHash),
	  m_unRoundedTableSizeMin1(a_cM.m_unRoundedTableSizeMin1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	__private::__implementation::HashItemFull<KeyType, DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType, DataType>*>(a_cM.m_pFirstItem);
	size_t tRet(m_unRoundedTableSizeMin1 + 1);
	m_pTable = static_cast<HashItem**>(calloc(tRet, sizeof(HashItem*)));
	if (!m_pTable) { throw std::bad_alloc(); }

	for (; pItem; pItem= pItem->nextInTheList) {
		AddEntryWithKnownHash(pItem->first, pItem->second, pItem->hashValue);
	}
}


// after this, you can not use a_cM
template <typename KeyType, typename DataType>
Base<KeyType, DataType>::Base(Base& a_cM,int) noexcept
	:
	  m_funcHash(a_cM.m_funcHash),
	  m_pTable(a_cM.m_pTable),
	  m_unRoundedTableSizeMin1(a_cM.m_unRoundedTableSizeMin1),
	  m_pFirstItem(a_cM.m_pFirstItem),
	  m_unSize(a_cM.m_unSize)
{
	a_cM.m_pFirstItem = CPPUTILS_NULL;
	a_cM.m_unSize = 0;
	a_cM.m_pTable = CPPUTILS_NULL;
}


#ifdef CPPUTILS_CPP_11_DEFINED
// after this, you can not use a_cM
template <typename KeyType, typename DataType>
Base<KeyType, DataType>::Base(Base&& a_cM) noexcept
	:
	  Base(a_cM,1)
{
}
#endif

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::~Base()
{
	__private::__implementation::HashItemFull<KeyType,DataType> *pItem=static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pFirstItem), *pItemNext;
	
	while(pItem){
		pItemNext = pItem->nextInTheList;
		delete pItem;
		pItem = pItemNext;
	}
	
	free(m_pTable);
}

template <typename KeyType, typename DataType>
Base<KeyType, DataType>& Base<KeyType, DataType>::operator=(const Base& a_cM)
{
	m_funcHash = a_cM.m_funcHash;
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_pFirstItem=CPPUTILS_NULL;
	m_unSize = (0);

	{
		__private::__implementation::HashItemFull<KeyType, DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType, DataType>*>(a_cM.m_pFirstItem);
		size_t tRet(m_unRoundedTableSizeMin1 + 1);
		const size_t memorySize = tRet * sizeof(HashItem*);
		HashItem**  pTableTmp = static_cast<HashItem**>(realloc(m_pTable, memorySize));
		if (!pTableTmp) { throw std::bad_alloc(); }
		m_pTable = pTableTmp;
		memset(m_pTable, 0, memorySize);

		for (; pItem; pItem = pItem->nextInTheList) {
			AddEntryWithKnownHash(pItem->first, pItem->second, pItem->hashValue);
		}
	}

	return *this;
}

template <typename KeyType, typename DataType>
Base<KeyType, DataType>& Base<KeyType, DataType>::ReplaceWithOther(Base& a_cM) noexcept
{
	typename FuncsT<KeyType, DataType>::Hash funcHash = m_funcHash;
	HashItem**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	HashItem*	pFirstItem = m_pFirstItem;
	size_t		unSize = m_unSize;

	m_funcHash = a_cM.m_funcHash;
	m_pTable=a_cM.m_pTable;
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_pFirstItem=a_cM.m_pFirstItem;
	m_unSize = (a_cM.m_unSize);

	a_cM.m_funcHash = funcHash;
	a_cM.m_pTable = pTable;
	a_cM.m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_cM.m_pFirstItem = pFirstItem;
	a_cM.m_unSize = (unSize);

	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType, typename DataType>
Base<KeyType, DataType>& Base<KeyType, DataType>::operator=(Base&& a_cM) noexcept
{
	return this->ReplaceWithOther(a_cM);
}
#endif

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::AddEntry(const KeyType& a_key, const DataType& a_data)
{
	size_t unHash;
	if(FindEntry(a_key,&unHash)){
		return CPPUTILS_NULL; // we do not overwrite
	}
	
	return AddEntryWithKnownHash(a_key,a_data,unHash);
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::AddOrReplaceEntry(const KeyType& a_key, const DataType& a_data)
{
	HashItem* pItem;
	size_t unHash;
	if((pItem=FindEntry(a_key,&unHash))){
		pItem->second = a_data;
		return pItem; // we can overwrite
	}
	
	return AddEntryWithKnownHash(a_key,a_data,unHash);
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::AddEntryEvenIfExists(const KeyType& a_key, const DataType& a_data)
{
	size_t unHash = (m_funcHash(a_key))&m_unRoundedTableSizeMin1;
	return AddEntryWithKnownHash(a_key,a_data,unHash);
}

// calling this function means that already Find shown, that no entry exist and we can add one
template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::AddEntryWithKnownHash(const KeyType& a_key,const DataType& a_data, size_t a_hashVal)
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = new __private::__implementation::HashItemFull<KeyType,DataType>(a_key,a_data);

	pItem->hashValue = a_hashVal;
	
	pItem->next = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pTable[a_hashVal]);
	if(m_pTable[a_hashVal]){pItem->next->prev=pItem;}
	m_pTable[a_hashVal] = pItem;
	
	pItem->nextInTheList = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pFirstItem);
	if(m_pFirstItem){pItem->nextInTheList->prevInTheList=pItem;}
	m_pFirstItem = pItem;
	
	++m_unSize;
	
	return pItem;
}


template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::FindEntry(const KeyType& a_key,size_t* a_hashPtr,
																			typename FuncsT<KeyType,DataType>::Find a_fnc, void* a_clbkData)const
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (m_funcHash(a_key))&m_unRoundedTableSizeMin1;
	pItemToRet = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pTable[unHash]);

	while (pItemToRet) {
		if((a_key==pItemToRet->first)&&a_fnc(a_clbkData,pItemToRet->first,pItemToRet->second)){
			return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}



template <typename KeyType,typename DataType>
bool Base<KeyType,DataType>::RemoveEntry(const KeyType& a_key)
{
	HashItem *pItem=FindEntry(a_key);
	if(pItem){
		RemoveEntry(pItem);
		return true;
	}
	return false;
}


template <typename KeyType,typename DataType>
void Base<KeyType,DataType>::RemoveEntry(const Base<KeyType,DataType>::const_iterator a_entry)
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(a_entry.m_pItem);
	
	if(m_pTable[pItem->hashValue]==pItem){m_pTable[pItem->hashValue]=pItem->next;}
	if(m_pFirstItem==pItem){m_pFirstItem=pItem->nextInTheList;}
	delete pItem; // destructor will delete from list
	--m_unSize;
}


template <typename KeyType,typename DataType>
DataType& Base<KeyType,DataType>::operator[]( const KeyType& a_key )
{
	size_t corespondingHash;
	iterator iter = FindEntry(a_key,&corespondingHash);
	if(iter){return iter->second;}
	iter = AddEntryWithKnownHash(a_key,DataType(),corespondingHash);
	return iter->second;
}


template <typename KeyType,typename DataType>
size_t Base<KeyType,DataType>::size()const
{
	return m_unSize;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::begin()
{
	return m_pFirstItem;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::end()
{
	return s_endIter;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::const_iterator Base<KeyType,DataType>::begin()const
{
	return m_pFirstItem;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::const_iterator Base<KeyType,DataType>::end()const
{
	return s_endConstIter;
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::HashItem::HashItem(const KeyType& a_key, const DataType& a_data)
	:
	  first(a_key),
	  second(a_data)
{
}

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::HashItem::~HashItem()
{
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::iterator::iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::iterator::iterator(HashItem* a_pItem)
	:
	  m_pItem(a_pItem)
{
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator& Base<KeyType,DataType>::iterator::operator++()
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::iterator::operator++(int)
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator& Base<KeyType,DataType>::iterator::operator--()
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::iterator Base<KeyType,DataType>::iterator::operator--(int)
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::HashItem* Base<KeyType,DataType>::iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::iterator::operator typename Base<KeyType,DataType>::HashItem*()const
{
	return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::const_iterator::const_iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::const_iterator::const_iterator(const iterator& a_iter)
	:
	  m_pItem(const_cast<HashItem*>(a_iter.operator->()))
{
}

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::const_iterator::const_iterator(const HashItem* a_pItem)
	:
	  m_pItem(const_cast<HashItem*>(a_pItem))
{
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::const_iterator& Base<KeyType,DataType>::const_iterator::operator++()
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::const_iterator Base<KeyType,DataType>::const_iterator::operator++(int)
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->nextInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::const_iterator& Base<KeyType,DataType>::const_iterator::operator--()
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType,typename DataType>
typename Base<KeyType,DataType>::const_iterator Base<KeyType,DataType>::const_iterator::operator--(int)
{
	__private::__implementation::HashItemFull<KeyType,DataType>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,DataType>*>(m_pItem);
	typename Base<KeyType,DataType>::iterator iterToRet(m_pItem);
	m_pItem = pItem->prevInTheList;
	return iterToRet;
}

template <typename KeyType,typename DataType>
const typename Base<KeyType,DataType>::HashItem* Base<KeyType,DataType>::const_iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType,typename DataType>
Base<KeyType,DataType>::const_iterator::operator const typename Base<KeyType,DataType>::HashItem*()const
{
	return m_pItem;
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType>
const typename Base<KeyType,void>::iterator  Base<KeyType,void>::s_endIter(CPPUTILS_NULL);


template <typename KeyType>
Base<KeyType,void>::Base(size_t a_tInitSize, typename FuncsT<KeyType>::Hash a_funcHash)
	:
	  m_funcHash(a_funcHash? a_funcHash: (typename FuncsT<KeyType>::Hash(&Funcs<KeyType>::DefaultHash)) ),
	  m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<HashItem**>(calloc(tRet,sizeof(HashItem*)));
	if(!m_pTable){throw std::bad_alloc();}
}


template <typename KeyType>
Base<KeyType, void>::Base(typename FuncsT<KeyType>::Hash a_funcHash)
	:
	m_funcHash(a_funcHash ? a_funcHash : (&Funcs<KeyType>::DefaultHash)),
	m_unRoundedTableSizeMin1(__private::__implementation::FindTableSizeFromIitialArg(DEFAULT_TABLE_SIZE) - 1),
	m_pFirstItem(CPPUTILS_NULL),
	m_unSize(0)
{
	size_t tRet(m_unRoundedTableSizeMin1 + 1);
	m_pTable = static_cast<HashItem**>(calloc(tRet, sizeof(HashItem*)));
	if (!m_pTable) { throw std::bad_alloc(); }
}


template <typename KeyType>
Base<KeyType, void>::Base(const Base& a_cM)
	:
	  m_funcHash(a_cM.m_funcHash),
	  m_unRoundedTableSizeMin1(a_cM.m_unRoundedTableSizeMin1),
	  m_pFirstItem(CPPUTILS_NULL),
	  m_unSize(0)
{
	__private::__implementation::HashItemFull<KeyType, void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType, void>*>(a_cM.m_pFirstItem);
	size_t tRet(m_unRoundedTableSizeMin1 + 1);
	m_pTable = static_cast<HashItem**>(calloc(tRet, sizeof(HashItem*)));
	if (!m_pTable) { throw std::bad_alloc(); }

	for (; pItem; pItem= pItem->nextInTheList) {
		AddEntryWithKnownHash(pItem->first, pItem->hashValue);
	}

}


// after this, you can not use a_cM
template <typename KeyType>
Base<KeyType, void>::Base(Base& a_cM,int) noexcept
	:
	  m_funcHash(a_cM.m_funcHash),
	  m_pTable(a_cM.m_pTable),
	  m_unRoundedTableSizeMin1(a_cM.m_unRoundedTableSizeMin1),
	  m_pFirstItem(a_cM.m_pFirstItem),
	  m_unSize(a_cM.m_unSize)
{
	a_cM.m_pFirstItem = CPPUTILS_NULL;
	a_cM.m_unSize = 0;
	a_cM.m_pTable = CPPUTILS_NULL;
}


#ifdef CPPUTILS_CPP_11_DEFINED
// after this, you can not use a_cM
template <typename KeyType>
Base<KeyType, void>::Base(Base&& a_cM) noexcept
	:
	  Base(a_cM,1)
{
}
#endif


template <typename KeyType>
Base<KeyType,void>::~Base()
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pFirstItem), * pItemNext;

	while (pItem) {
		pItemNext = pItem->nextInTheList;
		delete pItem;
		pItem = pItemNext;
	}

	free(m_pTable);

}

template <typename KeyType>
Base<KeyType, void>& Base<KeyType,void>::operator=(const Base& a_cM)
{
	m_funcHash = a_cM.m_funcHash;
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_pFirstItem = CPPUTILS_NULL;
	m_unSize = (0);

	{
		__private::__implementation::HashItemFull<KeyType, void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType, void>*>(a_cM.m_pFirstItem);
		size_t tRet(m_unRoundedTableSizeMin1 + 1);
		const size_t memorySize = tRet * sizeof(HashItem*);
		HashItem** pTableTmp = static_cast<HashItem**>(realloc(m_pTable, memorySize));
		if (!pTableTmp) { throw std::bad_alloc(); }
		m_pTable = pTableTmp;
		memset(m_pTable, 0, memorySize);

		for (; pItem; pItem = pItem->nextInTheList) {
			AddEntryWithKnownHash(pItem->first, pItem->hashValue);
		}
	}

	return *this;
}

template <typename KeyType>
Base<KeyType, void>& Base<KeyType, void>::ReplaceWithOther(Base& a_cM) noexcept
{
	typename FuncsT<KeyType>::Hash funcHash = m_funcHash;
	HashItem** pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	HashItem* pFirstItem = m_pFirstItem;
	size_t		unSize = m_unSize;

	m_funcHash = a_cM.m_funcHash;
	m_pTable = a_cM.m_pTable;
	m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
	m_pFirstItem = a_cM.m_pFirstItem;
	m_unSize = (a_cM.m_unSize);

	a_cM.m_funcHash = funcHash;
	a_cM.m_pTable = pTable;
	a_cM.m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_cM.m_pFirstItem = pFirstItem;
	a_cM.m_unSize = (unSize);

	return *this;
}

#ifdef CPPUTILS_CPP_11_DEFINED
template <typename KeyType>
Base<KeyType, void>& Base<KeyType, void>::operator=(Base&& a_cM) noexcept
{
	return this->ReplaceWithOther(a_cM);
}
#endif

template <typename KeyType>
typename Base<KeyType,void>::iterator Base<KeyType,void>::AddEntry(const KeyType& a_key)
{
	size_t unHash;
	if(FindEntry(a_key,&unHash)){
		return CPPUTILS_NULL; // we do not overwrite
	}
	
	return AddEntryWithKnownHash(a_key,unHash);
}

template <typename KeyType>
typename Base<KeyType, void>::iterator Base<KeyType, void>::AddEntryEvenIfExists(const KeyType& a_key)
{
	size_t unHash = (m_funcHash(a_key)) & m_unRoundedTableSizeMin1;
	return AddEntryWithKnownHash(a_key, unHash);
}


// calling this function means that already Find shown, that no entry exist and we can add one
template <typename KeyType>
typename Base<KeyType,void>::iterator Base<KeyType,void>::AddEntryWithKnownHash(const KeyType& a_key,size_t a_hashVal)
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = new __private::__implementation::HashItemFull<KeyType,void>(a_key);

	pItem->hashValue = a_hashVal;
	
	pItem->next = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pTable[a_hashVal]);
	if(m_pTable[a_hashVal]){pItem->next->prev=pItem;}
	m_pTable[a_hashVal] = pItem;
	
	pItem->nextInTheList = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pFirstItem);
	if(m_pFirstItem){pItem->nextInTheList->prevInTheList=pItem;}
	m_pFirstItem = pItem;
	++m_unSize;
	
	return pItem;
}


template <typename KeyType>
typename Base<KeyType,void>::iterator Base<KeyType,void>::FindEntry(const KeyType& a_key,size_t* a_hashPtr,
																	void* a_clbkData,typename FuncsT<KeyType>::FindVoid a_fnc)
{
	__private::__implementation::HashItemFull<KeyType,void>* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (m_funcHash(a_key))&m_unRoundedTableSizeMin1;
	pItemToRet = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pTable[unHash]);

	while (pItemToRet) {
		if((a_key==pItemToRet->first)&&a_fnc(a_clbkData,pItemToRet->first)){
			return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

	return CPPUTILS_NULL;
}


template <typename KeyType>
bool Base<KeyType,void>::RemoveEntry(const KeyType& a_key)
{
	HashItem *pItem=FindEntry(a_key);
	if(pItem){
		RemoveEntry(pItem);
		return true;
	}
	return false;
}


template <typename KeyType>
void Base<KeyType,void>::RemoveEntry(Base<KeyType,void>::iterator a_entry)
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(a_entry.m_pItem);
	
	if(m_pTable[pItem->hashValue]==pItem){m_pTable[pItem->hashValue]=pItem->next;}
	if(m_pFirstItem==pItem){m_pFirstItem=pItem->nextInTheList;}
	delete pItem; // destructor will delete from list
	++m_unSize;
}

template <typename KeyType>
size_t Base<KeyType,void>::size()const
{
	return m_unSize;
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType>
Base<KeyType,void>::HashItem::HashItem(const KeyType& a_key)
	:
	  first(a_key)
{
}

template <typename KeyType>
Base<KeyType,void>::HashItem::~HashItem()
{
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType>
Base<KeyType,void>::iterator::iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType>
Base<KeyType,void>::iterator::iterator(HashItem* a_pItem)
	:
	  m_pItem(a_pItem)
{
}

template <typename KeyType>
typename Base<KeyType,void>::iterator& Base<KeyType,void>::iterator::operator++()
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType>
typename Base<KeyType,void>::iterator Base<KeyType,void>::iterator::operator++(int)
{
	typename Base<KeyType,void>::iterator iterToRet(this->m_pItem);
	this->operator++();
	return iterToRet;
}

template <typename KeyType>
typename Base<KeyType,void>::iterator& Base<KeyType,void>::iterator::operator--()
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType>
typename Base<KeyType,void>::iterator Base<KeyType,void>::iterator::operator--(int)
{
	typename Base<KeyType,void>::iterator iterToRet(this->m_pItem);
	this->operator--();
	return iterToRet;
}

template <typename KeyType>
typename Base<KeyType,void>::HashItem* Base<KeyType,void>::iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType>
Base<KeyType,void>::iterator::operator typename Base<KeyType,void>::HashItem*()const
{
	return m_pItem;
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType>
Base<KeyType,void>::const_iterator::const_iterator()
	:
	  m_pItem(CPPUTILS_NULL)
{
}

template <typename KeyType>
Base<KeyType,void>::const_iterator::const_iterator(const HashItem* a_pItem)
	:
	  m_pItem(const_cast< typename Base<KeyType,void>::HashItem* >(a_pItem))
{
}

template <typename KeyType>
Base<KeyType,void>::const_iterator::const_iterator(const iterator& a_iter)
    :
      m_pItem(a_iter.operator->())
{
}

template <typename KeyType>
typename Base<KeyType,void>::const_iterator& Base<KeyType,void>::const_iterator::operator++()
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->nextInTheList;
	return *this;
}

template <typename KeyType>
typename Base<KeyType,void>::const_iterator Base<KeyType,void>::const_iterator::operator++(int)
{
	typename Base<KeyType,void>::const_iterator iterToRet(this->m_pItem);
	this->operator++();
	return iterToRet;
}

template <typename KeyType>
typename Base<KeyType,void>::const_iterator& Base<KeyType,void>::const_iterator::operator--()
{
	__private::__implementation::HashItemFull<KeyType,void>* pItem = static_cast<__private::__implementation::HashItemFull<KeyType,void>*>(m_pItem);
	m_pItem = pItem->prevInTheList;
	return *this;
}

template <typename KeyType>
typename Base<KeyType,void>::const_iterator Base<KeyType,void>::const_iterator::operator--(int)
{
	typename Base<KeyType,void>::const_iterator iterToRet(this->m_pItem);
	this->operator--();
	return iterToRet;
}


template <typename KeyType>
const typename Base<KeyType,void>::HashItem* Base<KeyType,void>::const_iterator::operator->()const
{
	return m_pItem;
}

template <typename KeyType>
Base<KeyType,void>::const_iterator::operator const typename Base<KeyType,void>::HashItem*()const
{
	return m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType>
size_t Funcs<KeyType,DataType>::DefaultHash(const KeyType& a_key)
{
	return __private::__implementation::hash1_(&a_key,sizeof(KeyType));
}

template <typename KeyType,typename DataType>
bool Funcs<KeyType,DataType>::DefaultFind(void*,const KeyType&, const DataType&)
{
	return true;
}

template <typename KeyType, typename DataType>
bool Funcs<KeyType, DataType>::DefaultFindVoid(void*, const KeyType&)
{
	return true;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename DataType>
size_t Funcs<VoidPtrKey,DataType>::DefaultHash(const VoidPtrKey& a_key)
{
	return __private::__implementation::hash1_(a_key.key,a_key.keyLen);
}

template <typename DataType>
bool Funcs<VoidPtrKey,DataType>::DefaultFind(void*,const VoidPtrKey&, const DataType&)
{
	return true;
}

template <typename DataType>
bool Funcs<VoidPtrKey, DataType>::DefaultFindVoid(void*, const VoidPtrKey&)
{
	return true;
}


}}  // namespace common { namespace hashtbl {


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
namespace __private { namespace __implementation {


template <typename KeyType,typename DataType>
HashItemFull<KeyType,DataType>::HashItemFull(const KeyType& a_key, const DataType& a_data)
    :	
	  ::common::hashtbl::Base<KeyType,DataType>::HashItem(a_key,a_data),
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


template <typename KeyType>
HashItemFull<KeyType,void>::HashItemFull(const KeyType& a_key)
    :	
	  ::common::hashtbl::Base<KeyType,void>::HashItem(a_key),
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



}}  // namespace __private { namespace __implementation {


#endif  // #ifndef COMMON_HASHTBL_IMPL_HPP
