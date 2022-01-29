//
// file:			vhash.hpp
// path:			include/cpputils/hash/vhash.impl.hpp
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

namespace cpputils { namespace hash {


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator  
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_nullIter;

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_constNullIter;


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::~VHashApi()
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::operator[](size_t a_index)
{
    return iterator(m_ppVector[a_index]);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::operator[](size_t a_index)const
{
    return const_iterator(m_ppVector[a_index]);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::at(size_t a_index)
{
    if(a_index<ApiDataAdv::m_unSize){
        return iterator(m_ppVector[a_index]);
    }
    return s_nullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::at(size_t a_index)const
{
    if(a_index<ApiDataAdv::m_unSize){
        return const_iterator(m_ppVector[a_index]);
    }
    return s_constNullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::begin()
{
    return iterator(m_ppVector[0]);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::end()
{
    return s_nullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::begin()const
{
    return const_iterator(m_ppVector[0]);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::end()const
{
    return s_constNullIter;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnown()
{
    ApiDataAdv::ConstructAfterRoundedTableSizeMin1IsKnownB();
    m_ppVector = CPPUTILS_NULL;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::RemoveEntryRaw(const const_iterator& a_cI)
{
    ApiDataAdv::RemoveEntryRawB(a_cI.m_pItem,a_cI.m_hash);
    
    if(a_cI.m_pItem->m_index<ApiDataAdv::m_unSize){
        :: memmove(&m_ppVector[a_cI.m_pItem->m_index],&m_ppVector[a_cI.m_pItem->m_index+1],
                   sizeof(TableItem*)*(ApiDataAdv::m_unSize-a_cI.m_pItem->m_index));
        for(size_t i(0); i<ApiDataAdv::m_unSize;++i){
            m_ppVector[i]->m_index = i;
        }
    }
    
    if(a_cI.m_pItem->m_usageCount==1){
        delete a_cI.m_pItem;
    }
    else{
        a_cI.m_pItem->m_pParent = CPPUTILS_NULL;
        --(a_cI.m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::
AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash)
{
    if((ApiDataAdv::m_unSize%CPPUTILS_HASH_VECTOR_RESIZE_SIZE)==0){
        const size_t newTblSize(ApiDataAdv::m_unSize+CPPUTILS_HASH_VECTOR_RESIZE_SIZE);
        TableItem** ppVector = static_cast<TableItem**>(reallocFn(m_ppVector,newTblSize*sizeof(TableItem*)));
        if(!ppVector){throw std::bad_alloc();}
        m_ppVector = ppVector;
    }
    
    TableItem* pItem = m_ppVector[ApiDataAdv::m_unSize] = new TableItem(::std::move(a_item),this,a_hash,ApiDataAdv::m_unSize);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem,a_hash);
    pItem->m_usageCount = 1;
        
    return pItem;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::InitAllToZero()
{
    ApiDataAdv::InitAllToZeroB();
    m_ppVector = CPPUTILS_NULL;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ClearRaw() CPPUTILS_NOEXCEPT
{
    for(size_t i(0); i<ApiDataAdv::m_unSize;++i){
        ApiDataAdv::m_pTable[m_ppVector[i]->m_hash] = CPPUTILS_NULL;
        if(m_ppVector[i]->m_usageCount==1){
            delete m_ppVector[i];
        }
        else{
            m_ppVector[i]->m_pParent = CPPUTILS_NULL;
            --(m_ppVector[i]->m_usageCount);
        }
    }
    //:: memset(ApiDataAdv::m_pTable,0,sizeof(InputPrivate*)*(ApiDataAdv::m_unRoundedTableSizeMin1+1));
    
    ApiDataAdv::m_unSize = 0;
    freeFn(m_ppVector);
    m_ppVector = CPPUTILS_NULL;    
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::
GeFromOther(const VHashApi& a_cM)
{
    for(size_t i(0); i<a_cM.m_unSize;++i){
        AddEntryWithKnownHashRaw(*(a_cM.m_ppVector[i]),a_cM.m_ppVector[i]->m_hash);
    }
    
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::ReplaceWithOther(VHashApi* a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::ReplaceWithOtherB(a_mM);
    TableItem** ppVector = m_ppVector;
    m_ppVector = a_mM->m_ppVector;
    a_mM->m_ppVector = ppVector;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::~iterator_base()
{
    if(m_pItem){
        if((--(m_pItem->m_usageCount))<1){
            delete m_pItem;
        }
    }  // if(m_pItem){
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base()
    :
      m_pItem(CPPUTILS_NULL)
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(const iterator_base& a_cM)
    :
      m_pItem(a_cM.m_pItem)
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(const VHashApi*, Input* a_pItem,size_t)
    :
      m_pItem(static_cast<TableItem*>(a_pItem))
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(Input* a_pItem)
    :
      m_pItem(static_cast<TableItem*>(a_pItem))
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::pItem()const
{
    return (m_pItem&&m_pItem->m_pParent)?m_pItem:CPPUTILS_NULL;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base& 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator++()
{
    if(pItem() && ((m_pItem->m_index+1)<m_pItem->m_pParent->m_unSize)){
        m_pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index+1];
    }
    else{
        m_pItem = CPPUTILS_NULL;
    }
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator++(int)
{
    iterator_base retIter(m_pItem);
    if(pItem() && ((m_pItem->m_index+1)<m_pItem->m_pParent->m_unSize)){
        m_pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index+1];
    }
    else{
        m_pItem = CPPUTILS_NULL;
    }
    return retIter;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base& 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator--()
{
    if(pItem() && (m_pItem->m_index>0)){
        m_pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index-1];
    }
    else{
        m_pItem = CPPUTILS_NULL;
    }
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator--(int)
{
    iterator_base retIter(m_pItem);
    if(pItem() && (m_pItem->m_index>0)){
        m_pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index-1];
    }
    else{
        m_pItem = CPPUTILS_NULL;
    }
    return retIter;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator+(size_t a_offset)const
{
    if(pItem() && ((m_pItem->m_index+a_offset)<m_pItem->m_pParent->m_unSize)){
        TableItem* pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index+a_offset];
        return iterator_base(pItem);
    }
    
    return static_cast<const iterator_base&>(VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_nullIter);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator-(size_t a_offset)const
{
    if(pItem() && (m_pItem->m_index>=a_offset)){
        TableItem* pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index-a_offset];
        return iterator_base(pItem);
    }
    
    return static_cast<const iterator_base&>(VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_nullIter);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator+=(size_t a_offset)
{
    if(pItem() && ((m_pItem->m_index+a_offset)<m_pItem->m_pParent->m_unSize)){
        m_pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index+a_offset];
    }
    else{
        m_pItem = CPPUTILS_NULL;
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::operator-=(size_t a_offset)
{
    if(pItem() && (m_pItem->m_index>=a_offset)){
        m_pItem = m_pItem->m_pParent->m_ppVector[m_pItem->m_index+a_offset];
    }
    else{
        m_pItem = CPPUTILS_NULL;
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::RemoveFromContainer()
{
    if(pItem()){
        m_pItem->m_pParent->erase(*this);
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator->()const
{
    return iterator_base::pItem();
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator::operator Input*()const
{
    return iterator_base::pItem();
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::const_iterator(const iterator& a_iter)
    :
      iterator_base(a_iter)
{
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const Input* VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator->()const
{
    return iterator_base::pItem();
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator::operator const Input*()const
{
    return iterator_base::pItem();
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::TableItem::TableItem(InputPrivate&& a_mM, VHashApi* a_pParent, size_t a_hash, size_t a_index)
    :
      InputPrivate(a_mM),
      m_pParent(a_pParent),
      m_hash(a_hash),
      m_index(a_index)
{
}


}}  // namespace cpputils { namespace hash {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
