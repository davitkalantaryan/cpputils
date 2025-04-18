//
// file:			hashbase.hpp
// path:			include/cpputils/hash/hashbase.impl.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP
#include "hashbase.hpp"
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <utility>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace __private { namespace __implementation {

CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize);

}}  // namespace __private { namespace __implementation {


namespace cpputils { namespace hash {


template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::ApiData()
{
    m_pThis = static_cast<ApiData**>(mallocFn(sizeof(ApiData*)));
    if(!m_pThis){throw std::bad_alloc();}
    *m_pThis = this;
}



template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::~ApiData()
{
    freeFn(m_pThis);
}


template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::ConstructAfterRoundedTableSizeMin1IsKnownB()
{
    m_unSize = 0;
    const size_t tRet(m_unRoundedTableSizeMin1+1);
    m_pTable = static_cast<InputPrivate**>(callocFn(tRet,sizeof(InputPrivate*)));
	if(!m_pTable){throw std::bad_alloc();}
}


template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::InitAllToZeroB()
{
    m_pTable = CPPUTILS_NULL;
	m_unRoundedTableSizeMin1 = size_t(-1);
	m_unSize = 0;
}


template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::ReplaceWithOtherB(ApiData* a_pmM) CPPUTILS_NOEXCEPT
{
    ApiData** pThis = m_pThis;
    InputPrivate**	pTable = m_pTable;
	size_t		unRoundedTableSizeMin1 = m_unRoundedTableSizeMin1;
	size_t		unSize = m_unSize;

    m_pThis = a_pmM->m_pThis;
    *m_pThis = this;
	m_pTable=a_pmM->m_pTable;
	m_unRoundedTableSizeMin1 = a_pmM->m_unRoundedTableSizeMin1;
	m_unSize = a_pmM->m_unSize;

    a_pmM->m_pThis = pThis;
    *(a_pmM->m_pThis) = a_pmM;
	a_pmM->m_pTable = pTable;
	a_pmM->m_unRoundedTableSizeMin1 = unRoundedTableSizeMin1;
	a_pmM->m_unSize = unSize;
}


template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::AddEntryWithAlreadyCreatedItemB(InputPrivate* a_pItem)
{
    a_pItem->next = m_pTable[a_pItem->m_hash];
    if(m_pTable[a_pItem->m_hash]){m_pTable[a_pItem->m_hash]->prev=a_pItem;}
    m_pTable[a_pItem->m_hash] = a_pItem;
	++m_unSize;
}


template <typename InputT,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
void ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>::RemoveEntryRawB(InputPrivate* a_pItem)
{
    if(m_pTable[a_pItem->m_hash]==a_pItem){m_pTable[a_pItem->m_hash]=a_pItem->next;}
    if(a_pItem->next){a_pItem->next->prev=a_pItem->prev;}
    if(a_pItem->prev){a_pItem->prev->next=a_pItem->next;}
	//delete a_pItem; // delete should be done by caller
	--m_unSize;
}


//

template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::~HashBase()
{
    ApiType::ClearRaw();
    freeFn(ApiDataAdv::m_pTable);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashBase(size_t a_tInitSize)
{
    ApiDataAdv::m_unRoundedTableSizeMin1 = __private::__implementation::FindTableSizeFromIitialArg(a_tInitSize)-1;
	ApiType::ConstructAfterRoundedTableSizeMin1IsKnown();
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashBase(const HashBase& a_cM)
{
    ApiDataAdv::m_unSize = 0;
    ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
    ApiType::ConstructAfterRoundedTableSizeMin1IsKnown();
    ApiType::GeFromOther(a_cM);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::HashBase(HashBase&& a_mM) CPPUTILS_NOEXCEPT
{
    ApiType::InitAllToZero();
    ApiType::ReplaceWithOther(&a_mM);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>&
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
operator=(const HashBase& a_cM)
{
    ApiType::ClearRaw();
    ApiDataAdv::m_unSize = 0;
    ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
    const size_t tRet(ApiDataAdv::m_unRoundedTableSizeMin1+1);
    const size_t cunMemSize(tRet*sizeof(InputPrivate*));
    InputPrivate** pTable = static_cast<InputPrivate**>(reallocFn(ApiDataAdv::m_pTable,cunMemSize));
    if(!pTable){throw std::bad_alloc();}
    ApiDataAdv::m_pTable = pTable;
    :: memset(ApiDataAdv::m_pTable,0,cunMemSize);
    ApiType::GeFromOther(a_cM);
    return *this;
}


// bool    TekeFromOtherAndReturnIfChanged(HashBase&& cM)const
template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
bool
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
TekeFromOtherAndReturnIfChanged(const HashBase& a_cM)
{
    if((ApiDataAdv::m_unSize!=a_cM.m_unSize)||(ApiDataAdv::m_unRoundedTableSizeMin1!=a_cM.m_unRoundedTableSizeMin1)){
        ApiType::ClearRaw();
        ApiDataAdv::m_unSize = 0;
        ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
        const size_t tRet(ApiDataAdv::m_unRoundedTableSizeMin1+1);
        const size_t cunMemSize(tRet*sizeof(InputPrivate*));
        InputPrivate** pTable = static_cast<InputPrivate**>(reallocFn(ApiDataAdv::m_pTable,cunMemSize));
        if(!pTable){throw std::bad_alloc();}
        ApiDataAdv::m_pTable = pTable;
        :: memset(ApiDataAdv::m_pTable,0,cunMemSize);
        ApiType::GeFromOther(a_cM);
        return true;
    }

    bool bRet = false;
    COutput thatIter = a_cM.begin();
    Output thisIter = ApiType::begin();

    for(;thatIter!=ApiType::s_constNullIter;++thatIter,++thisIter){
        if(thisIter->first != thatIter->first){
            ApiType::ClearRaw();
            ApiDataAdv::m_unSize = 0;
            ApiDataAdv::m_unRoundedTableSizeMin1 = a_cM.m_unRoundedTableSizeMin1;
            const size_t tRet(ApiDataAdv::m_unRoundedTableSizeMin1+1);
            const size_t cunMemSize(tRet*sizeof(InputPrivate*));
            InputPrivate** pTable = static_cast<InputPrivate**>(reallocFn(ApiDataAdv::m_pTable,cunMemSize));
            if(!pTable){throw std::bad_alloc();}
            ApiDataAdv::m_pTable = pTable;
            :: memset(ApiDataAdv::m_pTable,0,cunMemSize);
            ApiType::GeFromOther(a_cM);
            return true;
        }

        if(thisIter->second != thatIter->second){
            thisIter->second = thatIter->second;
            bRet = true;
        }
    }

    return bRet;
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>&
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::operator=(HashBase&& a_mM) CPPUTILS_NOEXCEPT
{
    ApiType::ReplaceWithOther(&a_mM);
    return *this;
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
bool HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::erase(const Key& a_key)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_key,&unHash);
    if(pItem){
        ApiType::RemoveEntryRaw(COutput(pItem));
        return true;
    }
    return false;
}


// bool     erase(const COutput& a_iter)
template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
void HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::erase(const COutput& a_iter)
{
    ApiType::RemoveEntryRaw(a_iter);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
size_t HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::size()const
{
    return ApiDataAdv::m_unSize;
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
inline void 
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::clear() CPPUTILS_NOEXCEPT
{
    ApiType::ClearRaw();
    ApiDataAdv::m_unSize = 0;
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashMv(Input&& a_item, size_t a_hash)
{
    Input* pInTheTable = ApiType::AddEntryWithKnownHashRaw(::std::move(a_item),a_hash);
    return Output(pInTheTable);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
AddEntryWithKnownHashC(const Input& a_item, size_t a_hash)
{
    return AddEntryWithKnownHashMv(Input(a_item),a_hash);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsMv(Input&& a_item)
{
    Hash fnHash;
    const size_t unHash = fnHash(a_item.first)&(ApiType::m_unRoundedTableSizeMin1);
    return AddEntryWithKnownHashMv(::std::move(a_item),unHash);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryEvenIfExistsC(const Input& a_item)
{
    Hash fnHash;
    const size_t unHash = fnHash(a_item.first)&(ApiType::m_unRoundedTableSizeMin1);
    return AddEntryWithKnownHashC(a_item,unHash);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistMv(Input&& a_item)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_item.first,&unHash);
    if(pItem){return Output(CPPUTILS_NULL);}
    return AddEntryWithKnownHashMv(::std::move(a_item),unHash);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddEntryIfNotExistC(const Input& a_item)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_item.first,&unHash);
    if(pItem){return Output(CPPUTILS_NULL);}
    return AddEntryWithKnownHashC(a_item,unHash);
}



template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddOrReplaceEntryMv(Input&& a_item)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_item.first,&unHash);
    if(pItem){
        *pItem= ::std::move(a_item);
        return Output(pItem);
    }
    return AddEntryWithKnownHashMv(a_item,unHash);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::AddOrReplaceEntryC(const Input& a_item)
{
    size_t unHash;
    Input* pItem = findEntryRaw(a_item.first,&unHash);
    if(pItem){
        *pItem= a_item;
        return Output(pItem);
    }
    return AddEntryWithKnownHashC(a_item,unHash);
}



template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
InputT*
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
findEntryRaw( const Key& a_key, size_t* a_hashPtr )const
{
    const Equal fnEqual;
    const Hash fnHash;
	InputPrivate* pItemToRet;
	size_t unHashForNull;
	size_t& unHash = a_hashPtr?*a_hashPtr:unHashForNull;
	
	unHash = (fnHash(a_key))&(ApiType::m_unRoundedTableSizeMin1);
	pItemToRet = ApiType::m_pTable[unHash];

	while (pItemToRet) {
        if(fnEqual(a_key,pItemToRet->first)){
            return pItemToRet;
		}
		pItemToRet = pItemToRet->next;
	}

    return CPPUTILS_NULL;
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
find( const Key& a_key, size_t* a_hashPtr )const
{
    if(a_hashPtr){
        Input* pItem = findEntryRaw(a_key,a_hashPtr);
        return Output(pItem);
    }
    
    size_t unHash;
    Input* pItem = findEntryRaw(a_key,&unHash);
    return Output(pItem);
}


template <typename Key,typename InputT, typename Hash, typename Equal, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
typename HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::Output
HashBase<Key,InputT,Hash,Equal,templateDefaultSize,mallocFn,callocFn,reallocFn,freeFn,ApiType>::
end(  )const
{
    return ApiType::s_nullIter;
}


}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
