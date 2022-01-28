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


namespace it{

template <typename HashItemType,TypeMalloc mallocFn, TypeFree freeFn>
struct HashItemPrivate : public HashItemType{
    //using HashItemType::HashItemType;
    HashItemPrivate(HashItemType&&, size_t a_hash);
    static void* operator new( ::std::size_t a_count );
    static void operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT ;
    HashItemPrivate *prev, *next;
    const size_t hash;
};

template <typename HashItemType>
class iterator{
public:
    virtual ~iterator();
    iterator();
    iterator(HashItemType* a_pItem);
    virtual HashItemType* operator->()const;
    virtual operator HashItemType*()const;
public:
    static const iterator s_endIter;
protected:
    HashItemType* m_pItem;
};

template <typename HashItemType>
class const_iterator{
public:
    virtual ~const_iterator();
    const_iterator();
    const_iterator(const HashItemType* a_pItem);
    const_iterator(const iterator<HashItemType>& iter);
    virtual const HashItemType* operator->()const;
    virtual operator const HashItemType* ()const;
public:
    static const const_iterator s_endConstIter;
protected:
    HashItemType* m_pItem;
};

}  // namespace iter{



}}  // namespace cpputils { namespace hash { 


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
#include "items.impl.hpp"
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP
