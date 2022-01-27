//
// file:			hashtbl.def.hpp
// path:			include/cpputils/hashtbl.impl.hpp
// created on:		2021 Mar 26
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once

#include <cpputils_internal_header.h>
#include <utility>


#define CPPUTILS_DEFAULT_TABLE_SIZE	256

namespace cpputils { namespace hash {

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
