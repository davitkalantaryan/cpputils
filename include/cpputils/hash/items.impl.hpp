//
// file:			items.hpp
// path:			include/cpputils/hash/items.impl.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP
#include "items.hpp"
#endif

#include <utility>


namespace cpputils { namespace hash {


template <typename KeyType,typename DataType>
HashItem<KeyType,DataType>::HashItem(const ::std::pair<KeyType,DataType>& a_cM)
    :
      first(a_cM.first),
      second(a_cM.second)
{
}


template <typename KeyType,typename DataType>
HashItem<KeyType,DataType>::HashItem( ::std::pair<KeyType,DataType>&& a_mM)
    :
      first(::std::move(a_mM.first)),
      second(::std::move(a_mM.second))
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType>
SetItem<KeyType>::SetItem(const KeyType& a_cM)
    :
      first(a_cM)
{
}


template <typename KeyType>
SetItem<KeyType>::SetItem( KeyType&& a_mM)
    :
      first(a_mM)
{
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace it{

template <typename HashItemType,TypeMalloc mallocFn, TypeFree freeFn>
void* HashItemPrivate<HashItemType,mallocFn,freeFn>::operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <typename HashItemType,TypeMalloc mallocFn, TypeFree freeFn>
void  HashItemPrivate<HashItemType,mallocFn,freeFn>::operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}

template <typename HashItemType,TypeMalloc mallocFn, TypeFree freeFn>
HashItemPrivate<HashItemType,mallocFn,freeFn>::HashItemPrivate(HashItemType&& a_mM, size_t a_hash)
    :
      HashItemType(::std::move(a_mM)),
      hash(a_hash)
{
    this->prev = CPPUTILS_NULL;
}


//

template <typename HashItemType>
const iterator<HashItemType> s_endIter(CPPUTILS_NULL);


template <typename HashItemType>
iterator<HashItemType>::~iterator()
{
}

template <typename HashItemType>
iterator<HashItemType>::iterator()
    :
      m_pItem(CPPUTILS_NULL)
{
}

template <typename HashItemType>
iterator<HashItemType>::iterator(HashItemType* a_pItem)
    :
      m_pItem(a_pItem)
{
}

template <typename HashItemType>
HashItemType* iterator<HashItemType>::operator->()const
{
    return m_pItem;
}

template <typename HashItemType>
iterator<HashItemType>::operator HashItemType*()const
{
    return m_pItem;
}


//


template <typename HashItemType>
const const_iterator<HashItemType> s_endConstIter(CPPUTILS_NULL);

template <typename HashItemType>
const_iterator<HashItemType>::~const_iterator()
{
}

template <typename HashItemType>
const_iterator<HashItemType>::const_iterator()
    :
      m_pItem(CPPUTILS_NULL)
{
}

template <typename HashItemType>
const_iterator<HashItemType>::const_iterator(const HashItemType* a_pItem)
    :
      m_pItem(const_cast<HashItemType*>(a_pItem))
{
}

template <typename HashItemType>
const_iterator<HashItemType>::const_iterator(const iterator<HashItemType>& a_iter)
    :
      m_pItem(a_iter.m_pItem)
{
}

template <typename HashItemType>
const HashItemType* const_iterator<HashItemType>::operator->()const
{
    return m_pItem;
}

template <typename HashItemType>
const_iterator<HashItemType>::operator const HashItemType*()const
{
    return m_pItem;
}


}  // namespace it{



}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
