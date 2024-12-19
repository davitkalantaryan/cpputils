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
#include <cinternal/disable_compiler_warnings.h>
#include <utility>
#include <type_traits>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash {

#ifndef CPPUTILS_HASH_NO_NEW_DELETE

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

#endif  // #ifndef CPPUTILS_HASH_NO_NEW_DELETE


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


template <typename KeyType, TypeMalloc mallocFn, TypeFree freeFn>
SetItem<KeyType,mallocFn,freeFn>&
SetItem<KeyType,mallocFn,freeFn>::operator=(const SetItem&)
{
    return *this;
}


template <typename KeyType, TypeMalloc mallocFn, TypeFree freeFn>
SetItem<KeyType,mallocFn,freeFn>&
SetItem<KeyType,mallocFn,freeFn>::operator=(SetItem&&)
{
    return *this;
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
InputPrivate<Input,mallocFn,freeFn>::InputPrivate(Input&& a_mM, size_t a_hash)
    :
      Input(::std::move(a_mM)),
      m_hash(a_hash)
{
    static_assert( ::std::is_base_of<BaseForAlloc<mallocFn,freeFn>,InputPrivate>(), "InputPrivate shoulb be child of BaseForAlloc" );
    this->prev = CPPUTILS_NULL;
}


}  // namespace it{


template <typename IntType>
size_t FHashInt<IntType>::operator()(const IntType& a_key)const
{
    //return static_cast<size_t>(a_key);
    return (size_t)(a_key);
}



}}  //  namespace cpputils { namespace hash {

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
