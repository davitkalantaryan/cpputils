//
// file:			hash.hpp
// path:			include/cpputils/hash/hash.impl.hpp
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
#include <cinternal/disable_compiler_warnings.h>
#include <utility>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash {

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
const typename HashApi<Input,defSize,mallocFn,callocFn,freeFn>::iterator  
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::s_nullIter;

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
const typename HashApi<Input,defSize,mallocFn,callocFn,freeFn>::const_iterator 
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::s_constNullIter;



template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::~HashApi()
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void HashApi<Input,defSize,mallocFn,callocFn,freeFn>::RemoveEntryRaw(const const_iterator& a_cI)
{
    ApiDataAdv::RemoveEntryRawB(a_cI.m_pItem);
    delete a_cI.m_pItem;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
Input* HashApi<Input,defSize,mallocFn,callocFn,freeFn>::
AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash)
{
    HashItem* pItem = new HashItem(::std::move(a_item),this,a_hash);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem);
    return pItem;
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void HashApi<Input,defSize,mallocFn,callocFn,freeFn>::ClearRaw() CPPUTILS_NOEXCEPT
{
    if(ApiDataAdv::m_pTable){
        const size_t tRet(ApiDataAdv::m_unRoundedTableSizeMin1 + 1);
        InputPrivate *pItem,*pItemNext;
        for(size_t i(0); i<tRet; ++i){
            pItem = ApiDataAdv::m_pTable[i];
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


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void HashApi<Input,defSize,mallocFn,callocFn,freeFn>::ReplaceWithOther(HashApi* a_mM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::ReplaceWithOtherB(a_mM);
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void HashApi<Input,defSize,mallocFn,callocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnown()
{
    ApiDataAdv::ConstructAfterRoundedTableSizeMin1IsKnownB();
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void HashApi<Input,defSize,mallocFn,callocFn,freeFn>::
GeFromOther(const HashApi& a_cM)
{
    InputPrivate* pItem;
    const size_t tRet(a_cM.m_unRoundedTableSizeMin1 + 1);
    
    if(a_cM.m_unRoundedTableSizeMin1>ApiDataAdv::m_unRoundedTableSizeMin1){
        const size_t cunAllocateSize = tRet*sizeof(InputPrivate*);
        InputPrivate** pTable = static_cast<InputPrivate**>(reallocFn(ApiDataAdv::m_pTable,cunAllocateSize));
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


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::iterator_base::iterator_base()
    :
      m_pItem(CPPUTILS_NULL)
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::iterator_base::iterator_base(Input* a_pItem)
    :
      m_pItem(static_cast<HashItem*>(a_pItem))
{
}


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void HashApi<Input,defSize,mallocFn,callocFn,freeFn>::iterator_base::RemoveFromContainer()
{
    if(m_pItem && m_pItem->m_ppParent && (*(m_pItem->m_ppParent)) ){
        (*(m_pItem->m_ppParent))->RemoveEntryRaw(const_iterator(m_pItem));
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
Input* HashApi<Input,defSize,mallocFn,callocFn,freeFn>::iterator::operator->()const
{
    return iterator_base::m_pItem;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::iterator::operator Input*()const
{
    return iterator_base::m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::const_iterator::const_iterator(const iterator& a_iter)
    :
      iterator_base(a_iter)
{
}

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
const Input* HashApi<Input,defSize,mallocFn,callocFn,freeFn>::const_iterator::operator->()const
{
    return iterator_base::m_pItem;
}

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::const_iterator::operator const Input*()const
{
    return iterator_base::m_pItem;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
HashApi<Input,defSize,mallocFn,callocFn,freeFn>::HashItem::HashItem(Input&& a_mM, HashApi* a_pParent, size_t a_hash)
    :
      InputPrivate(::std::move(a_mM),a_hash),
      m_ppParent(a_pParent?reinterpret_cast<HashApi**>(a_pParent->m_pThis):nullptr)
{
}



}}  // namespace cpputils { namespace hash {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP
