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
#include <type_traits>


namespace cpputils { namespace hash {


template <TypeMalloc mallocFn, TypeFree freeFn>
void* BaseForAlloc<mallocFn,freeFn>::operator new( ::std::size_t a_count )
{
    return mallocFn(a_count);
}

template <TypeMalloc mallocFn, TypeFree freeFn>
void  BaseForAlloc<mallocFn,freeFn>::operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT 
{
    freeFn(a_ptr);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType, TypeMalloc mallocFn, TypeFree freeFn>
SetItem<KeyType,mallocFn,freeFn>::SetItem(const KeyType& a_cM)
    :
      first(a_cM)
{
}


template <typename KeyType, TypeMalloc mallocFn, TypeFree freeFn>
SetItem<KeyType,mallocFn,freeFn>::SetItem( KeyType&& a_mM)
    :
      first(a_mM)
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType, typename DataType, TypeMalloc mallocFn, TypeFree freeFn>
HashItem<KeyType,DataType,mallocFn,freeFn>::HashItem(const ::std::pair<KeyType,DataType>& a_cM)
    :
      SetItem<KeyType,mallocFn,freeFn>(a_cM.first),
      second(a_cM.second)
{
}


template <typename KeyType, typename DataType, TypeMalloc mallocFn, TypeFree freeFn>
HashItem<KeyType,DataType,mallocFn,freeFn>::HashItem( ::std::pair<KeyType,DataType>&& a_mM)
    :
      SetItem<KeyType,mallocFn,freeFn>(::std::move(a_mM.first)),
      second(::std::move(a_mM.second))
{
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace it{


template <typename Input,TypeMalloc mallocFn, TypeFree freeFn>
InputPrivate<Input,mallocFn,freeFn>::InputPrivate(Input&& a_mM)
    :
      Input(::std::move(a_mM))
{
    static_assert( ::std::is_base_of<BaseForAlloc<mallocFn,freeFn>,InputPrivate>(), "InputPrivate shoulb be child of BaseForAlloc" );
    this->prev = CPPUTILS_NULL;
}


}  // namespace it{



}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP