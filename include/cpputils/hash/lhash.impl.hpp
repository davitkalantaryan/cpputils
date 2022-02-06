//
// file:			lhash.impl.hpp
// path:			include/cpputils/hash/lhash.hpp
// created on:		2022 Jan 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_LHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
#include "lhash.hpp"
#endif

#include <utility>
#include <string.h>

namespace cpputils { namespace hash {


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator  
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_nullIter;

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator 
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_constNullIter;


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::~LHashApi()
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::begin()
{
    return iterator(const_cast<LHashApi*>(this), m_pFirstItem, m_pFirstItem? m_pFirstItem->m_hash:0);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::end()
{
    return s_nullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::begin()const
{
    return const_iterator(m_pFirstItem);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::end()const
{
    return s_constNullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnown()
{
    ApiDataAdv::ConstructAfterRoundedTableSizeMin1IsKnownB();
    m_pFirstItem = CPPUTILS_NULL;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::RemoveEntryRaw(const const_iterator& a_cI)
{
    ApiDataAdv::RemoveEntryRawB(a_cI.m_pItem,a_cI.m_pItem->m_hash);
    ListItem* pItem = a_cI.m_pItem;
    if(pItem==m_pFirstItem){m_pFirstItem=pItem;}
    if(pItem->nextInTheList){pItem->nextInTheList->prevInTheList = pItem->prevInTheList;}
    if(pItem->prevInTheList){pItem->prevInTheList->nextInTheList = pItem->nextInTheList;}
    delete pItem;    
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::
AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash)
{
    ListItem* pItem = new ListItem(::std::move(a_item),a_hash);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem,a_hash);
    if(m_pFirstItem){m_pFirstItem->prevInTheList=pItem;}
    pItem->prevInTheList = CPPUTILS_NULL;
    pItem->nextInTheList = m_pFirstItem;
    m_pFirstItem = pItem;
    return pItem;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::InitAllToZero()
{
    ApiDataAdv::InitAllToZeroB();
    m_pFirstItem = CPPUTILS_NULL;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ClearRaw() CPPUTILS_NOEXCEPT
{
    ListItem *pItemNext, *pItem = m_pFirstItem;
    while(pItem){
        pItemNext=pItem->nextInTheList;
        ApiDataAdv::m_pTable[pItem->m_hash] = CPPUTILS_NULL;
        delete pItem;
        pItem=pItemNext;
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::
GeFromOther(const LHashApi& a_cM)
{
    ListItem *pItem = a_cM.m_pFirstItem;
    while(pItem){
        AddEntryWithKnownHashRaw(Input(*pItem),pItem->m_hash);
        pItem=pItem->nextInTheList;
    }    
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ReplaceWithOther(LHashApi* a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::ReplaceWithOtherB(a_mM);
    ListItem* pFirstItem = m_pFirstItem;
    m_pFirstItem = a_mM->m_pFirstItem;
    a_mM->m_pFirstItem = pFirstItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base()
    :
      m_pParent(CPPUTILS_NULL),
      m_pItem(CPPUTILS_NULL)
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(const LHashApi* a_pParent, Input* a_pItem,size_t)
    :
      m_pParent(const_cast<LHashApi*>(a_pParent)),
      m_pItem(static_cast<ListItem*>(a_pItem))
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base& 
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator++()
{
    m_pItem = m_pItem->nextInTheList;
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base 
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator++(int)
{
    iterator_base retIter(m_pItem);
    m_pItem = m_pItem->nextInTheList;
    return retIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base& 
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator--()
{
    m_pItem = m_pItem->prevInTheList;
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base 
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator--(int)
{
    iterator_base retIter(m_pItem);
    m_pItem = m_pItem->prevInTheList;
    return retIter;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::next()const
{
    return iterator_base(m_pItem->nextInTheList);
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::previous()const
{
    return iterator_base(m_pItem->prevInTheList);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::RemoveFromContainer()
{
    if(m_pParent && m_pItem){
        m_pParent->RemoveEntryRaw(const_iterator(m_pParent,m_pItem,m_pItem->m_hash));
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator->()const
{
    return iterator_base::m_pItem;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator Input*()const
{
    return iterator_base::m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::const_iterator(const iterator& a_cM)
    :
      iterator_base(a_cM)
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const Input* LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator->()const
{
    return iterator_base::m_pItem;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator const Input*()const
{
    return iterator_base::m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
LHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ListItem::ListItem(InputPrivate&& a_mM, size_t a_hash)
    :
      InputPrivate(a_mM),
      m_hash(a_hash)
{
}


}}  // namespace cpputils { namespace hash {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LHASH_IMPL_HPP
