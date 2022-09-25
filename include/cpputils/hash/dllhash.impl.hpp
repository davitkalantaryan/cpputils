//
// file:			dllhash.impl.hpp
// path:			include/cpputils/hash/dllhash.impl.hpp
// created on:		2022 Sep 25
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_HPP
#include "dllhash.hpp"
#endif

#include <utility>
#include <string.h>

namespace cpputils { namespace hash {


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator  
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_nullIter;

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_constNullIter;


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::~DllHashApi()
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::begin()
{
    return iterator(const_cast<DllHashApi*>(this), m_pFirstItem, m_pFirstItem? m_pFirstItem->m_hash:0);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::end()
{
    return s_nullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::begin()const
{
    return const_iterator(this,m_pFirstItem, m_pFirstItem ? m_pFirstItem->m_hash : 0);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::end()const
{
    return s_constNullIter;
}


template <typename Input, size_t defSize, TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
typename DllHashApi<Input, defSize, mallocFn, callocFn, reallocFn, freeFn>::iterator
DllHashApi<Input, defSize, mallocFn, callocFn, reallocFn, freeFn>::lastIter()
{
    return iterator(const_cast<DllHashApi*>(this), m_pLastItem, m_pLastItem ? m_pLastItem->m_hash : 0);
}


template <typename Input, size_t defSize, TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
typename DllHashApi<Input, defSize, mallocFn, callocFn, reallocFn, freeFn>::const_iterator
DllHashApi<Input, defSize, mallocFn, callocFn, reallocFn, freeFn>::lastIter()const
{
    return const_iterator(this, m_pLastItem, m_pLastItem ? m_pLastItem->m_hash : 0);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnown()
{
    ApiDataAdv::ConstructAfterRoundedTableSizeMin1IsKnownB();
    m_pLastItem = m_pFirstItem = CPPUTILS_NULL;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::RemoveEntryRaw(const const_iterator& a_cI)
{
    ApiDataAdv::RemoveEntryRawB(a_cI.m_pItem,a_cI.m_pItem->m_hash);
    ListItem* pItem = a_cI.m_pItem;
    if(pItem==m_pFirstItem){m_pFirstItem=pItem->nextInTheList;}
    if (pItem == m_pLastItem) { m_pLastItem = pItem->prevInTheList; }
    if(pItem->nextInTheList){pItem->nextInTheList->prevInTheList = pItem->prevInTheList;}
    if(pItem->prevInTheList){pItem->prevInTheList->nextInTheList = pItem->nextInTheList;}
    delete pItem;    
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::
AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash)
{
    ListItem* pItem = new ListItem(::std::move(a_item),a_hash);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem,a_hash);
    if(m_pFirstItem){ m_pLastItem->nextInTheList =pItem;}
    else { m_pFirstItem = pItem; }
    pItem->nextInTheList = CPPUTILS_NULL;
    pItem->prevInTheList = m_pLastItem;
    m_pLastItem = pItem;
    return pItem;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::InitAllToZero()
{
    ApiDataAdv::InitAllToZeroB();
    m_pLastItem = m_pFirstItem = CPPUTILS_NULL;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ClearRaw() CPPUTILS_NOEXCEPT
{
    ListItem *pItemNext, *pItem = m_pFirstItem;
    while(pItem){
        pItemNext=pItem->nextInTheList;
        ApiDataAdv::m_pTable[pItem->m_hash] = CPPUTILS_NULL;
        delete pItem;
        pItem=pItemNext;
    }
    m_pLastItem = m_pFirstItem = nullptr;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::
GeFromOther(const DllHashApi& a_cM)
{
    ListItem *pItem = a_cM.m_pFirstItem;
    while(pItem){
        AddEntryWithKnownHashRaw(Input(*pItem),pItem->m_hash);
        pItem=pItem->nextInTheList;
    }    
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ReplaceWithOther(DllHashApi* a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::ReplaceWithOtherB(a_mM);
    ListItem* pFirstItem = m_pFirstItem;
    ListItem* pLastItem = m_pLastItem;
    m_pFirstItem = a_mM->m_pFirstItem;
    m_pLastItem = a_mM->m_pLastItem;
    a_mM->m_pFirstItem = pFirstItem;
    a_mM->m_pLastItem = pLastItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base()
    :
      m_pParent(CPPUTILS_NULL),
      m_pItem(CPPUTILS_NULL)
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(const DllHashApi* a_pParent, Input* a_pItem,size_t)
    :
      m_pParent(const_cast<DllHashApi*>(a_pParent)),
      m_pItem(static_cast<ListItem*>(a_pItem))
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base&
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator++()
{
    m_pItem = m_pItem->nextInTheList;
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator++(int)
{
    iterator_base retIter(m_pItem);
    m_pItem = m_pItem->nextInTheList;
    return retIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base&
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator--()
{
    m_pItem = m_pItem->prevInTheList;
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator--(int)
{
    iterator_base retIter(m_pParent,m_pItem,0);
    m_pItem = m_pItem->prevInTheList;
    return retIter;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::next()const
{
    return iterator_base(m_pParent,m_pItem->nextInTheList,0);
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::previous()const
{
    return iterator_base(m_pParent,m_pItem->prevInTheList,0);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::RemoveFromContainer()
{
    if(m_pParent && m_pItem){
        m_pParent->RemoveEntryRaw(const_iterator(m_pParent,m_pItem,m_pItem->m_hash));
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator->()const
{
    return iterator_base::m_pItem;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator Input*()const
{
    return iterator_base::m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::const_iterator(const iterator& a_cM)
    :
      iterator_base(a_cM)
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const Input* DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator->()const
{
    return iterator_base::m_pItem;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator const Input*()const
{
    return iterator_base::m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
DllHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ListItem::ListItem(InputPrivate&& a_mM, size_t a_hash)
    :
      InputPrivate(a_mM),
      m_hash(a_hash)
{
}


}}  // namespace cpputils { namespace hash {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_IMPL_HPP
