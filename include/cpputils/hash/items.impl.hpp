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



}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
