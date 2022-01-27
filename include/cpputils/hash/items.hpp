//
// file:			items.hpp
// path:			include/cpputils/hash/items.hpp
// created on:		2021 Mar 26
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP

#include <cpputils_internal_header.h>
#include <utility>


namespace cpputils { namespace hash {


#define CPPUTILS_HASH_DEFAULT_TABLE_SIZE	256
#define CPPUTILS_HASH_VECTOR_RESIZE_SIZEE	512

typedef void* (*TypeMalloc)  ( size_t );
typedef void* (*TypeCalloc)  ( size_t,size_t );
typedef void* (*TypeRealloc)  ( void*,size_t );
typedef void  (*TypeFree)  ( void* );

template <typename KeyType,typename DataType>
struct HashItem {
	//template <typename KeyType1, typename DataType1,typename Hash,size_t templateDefaultSize>
	//friend class ::cpputils::hashtbl::Base;
public:
    HashItem(const ::std::pair<KeyType,DataType>&);
    HashItem( ::std::pair<KeyType,DataType>&&);
public:
	const KeyType first; DataType second;
};


template <typename KeyType>
struct SetItem {
public:
    SetItem(const KeyType&);
    SetItem( KeyType&&);
public:
	const KeyType first;
};


}}  // namespace cpputils { namespace hash { 


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
#include "items.impl.hpp"
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP
