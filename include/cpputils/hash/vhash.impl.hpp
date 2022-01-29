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

namespace cpputils { namespace hash {


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator  
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_endIter(CPPUTILS_NULL,CPPUTILS_NULL,0);

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
const typename VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::const_iterator 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::s_endConstIter(CPPUTILS_NULL,CPPUTILS_NULL,0);


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::VHashApi(size_t a_unBacketsCount)
    :
      ApiDataAdv(a_unBacketsCount),
      m_ppVector(CPPUTILS_NULL)
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::VHashApi(const VHashApi& a_cM)
{
    ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
    ApiDataAdv::ConstructAfterRoundedTableSizeMin1IsKnownB();
    GeFromOther(a_cM);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::VHashApi(VHashApi&& a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::InitAllToZero();
    ApiDataAdv::ReplaceWithOther(&a_mM);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::~VHashApi()
{
    ClearRaw();
    freeFn(ApiDataAdv::m_pTable);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>& 
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::operator=(const VHashApi& a_cM)
{
    GeFromOther(a_cM);
    return *this;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>&
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::operator=(VHashApi&& a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::ReplaceWithOther(&a_mM);
    return *this;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
void VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::RemoveEntryRaw(const const_iterator& a_cI)
{
    ApiDataAdv::RemoveEntryRawB(a_cI.m_pItem,a_cI.m_hash);
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
    
    TableItem* pItem = m_ppVector[ApiDataAdv::m_unSize] = new TableItem(::std::move(a_item),this, a_hash, ApiDataAdv::m_unSize);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem,a_hash);
        
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
            --(m_ppVector[i]->m_usageCount);
        }
    }
    
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
      m_pParent(CPPUTILS_NULL),
      m_pItem(CPPUTILS_NULL)
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(const iterator_base& a_cM)
    :
      m_pParent(a_cM.m_pParent),
      m_pItem(a_cM.m_pItem)
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::iterator_base(VHashApi* a_pParent, Input* a_pItem,size_t)
    :
      m_pParent(a_pParent),
      m_pItem(static_cast<TableItem*>(a_pItem))
{
    if(m_pItem){
        ++(m_pItem->m_usageCount);
    }
}


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
Input* VHashApi<Input,defSize,mallocFn,callocFn,reallocFn,freeFn>::iterator_base::pItem()const
{
    return (m_pItem&&(m_pItem->m_usageCount>1))?m_pItem:CPPUTILS_NULL;
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


}}  // namespace cpputils { namespace hash {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
