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


//VHashApi(const VHashApi& cM)
template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::VHashApi(size_t a_unBacketsCount)
    :
      ApiDataAdv(a_unBacketsCount),
      m_ppVector(CPPUTILS_NULL)
{
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::VHashApi(const VHashApi& a_cM)
    :
      m_ppVector(CPPUTILS_NULL)
{
    ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
    ApiDataAdv::ConstructAfterRoundedTableSizeMin1IsKnown();
    GeFromOther(a_cM);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::VHashApi(VHashApi&& a_mM) CPPUTILS_NOEXCEPT
{
    InitAllToZero();
    ApiDataAdv::ReplaceWithOtherB(&a_mM);
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::~VHashApi()
{
    ClearRaw();
    // todo: think on m_ppVector
    freeFn(ApiDataAdv::m_pTable);
}

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::InitAllToZero()
{
    ApiDataAdv::InitAllToZeroB();
    freeFn(m_ppVector);
    m_ppVector = CPPUTILS_NULL;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::GeFromOther(const VHashApi& a_cM)
{
    for(size_t i(0); i<a_cM.m_unSize;++i){
        AddEntryWithKnownHashRaw(a_cM.m_ppVector[i],a_cM.m_ppVector[i]->hash);
    }    
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::ClearRaw() CPPUTILS_NOEXCEPT
{
    for(size_t i(0); i<ApiDataAdv::m_unSize;++i){
        delete m_ppVector[i];
    }
    const size_t tRet(ApiDataAdv::m_unRoundedTableSizeMin1+1);
    :: memset(ApiDataAdv::m_pTable,0,tRet*sizeof(HashItemType));
    ApiDataAdv::m_unSize = 0;
    freeFn(m_ppVector);
    m_ppVector = CPPUTILS_NULL;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
void VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::ReplaceWithOther(VHashApi* a_pmM) CPPUTILS_NOEXCEPT
{
    ApiDataAdv::ReplaceWithOtherB(a_pmM);
    HashItemPrivate**	ppVector = m_ppVector;
    m_ppVector = a_pmM->m_ppVector;
    a_pmM->m_ppVector = m_ppVector;
}


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
HashItemType* VHashApi<KeyType,HashItemType,Hash,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn>::
AddEntryWithKnownHashRaw(HashItemType&& a_item, size_t a_hash)
{
    HashItemPrivate* pItem = new HashItemPrivate(::std::move(a_item),a_hash,ApiDataAdv::m_unSize,this);
    ApiDataAdv::AddEntryWithAlreadyCreatedItemB(pItem);
    return pItem;
}


}}  // namespace cpputils { namespace hash {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
