//
// file:			items.hpp
// path:			include/cpputils/hash/items.hpp
// created on:		2021 Mar 26
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP

#include <cpputils/export_symbols.h>
#include <utility>


namespace cpputils { namespace hash {


#define CPPUTILS_HASH_DEFAULT_TABLE_SIZE	256
#define CPPUTILS_HASH_VECTOR_RESIZE_SIZE	512

typedef void* (*TypeMalloc)  ( size_t );
typedef void* (*TypeCalloc)  ( size_t,size_t );
typedef void* (*TypeRealloc)  ( void*,size_t );
typedef void  (*TypeFree)  ( void* );

template <TypeMalloc mallocFn, TypeFree freeFn>
struct BaseForAlloc {
#ifndef CPPUTILS_HASH_NO_NEW_DELETE
    static void* operator new( ::std::size_t a_count );
    static void operator delete  ( void* a_ptr ) CINTERNAL_NOEXCEPT ;
#endif
};


template <typename KeyType, TypeMalloc mallocFn, TypeFree freeFn>
struct SetItem : public BaseForAlloc<mallocFn,freeFn> {
    SetItem(const KeyType&);
    SetItem( KeyType&&);
    SetItem(const SetItem&)=default;
    SetItem(SetItem&&)=default;
    SetItem& operator=(const SetItem&);
    SetItem& operator=( SetItem&&);
public:
	const KeyType first;
};


template <typename KeyType,typename DataType, TypeMalloc mallocFn, TypeFree freeFn>
struct HashItem : public SetItem<KeyType,mallocFn,freeFn> {
    HashItem(const ::std::pair<KeyType,DataType>&);
    HashItem( ::std::pair<KeyType,DataType>&&);
    HashItem(const HashItem&)=default;
    HashItem(HashItem&&)=default;
    HashItem& operator=(const HashItem&)=default;
    HashItem& operator=( HashItem&&)=default;
public:
	DataType second;
};


namespace it{

template <typename Input,TypeMalloc mallocFn, TypeFree freeFn>
struct InputPrivate : public Input{
    //static_assert( ::std::is_base_of<BaseForAlloc<mallocFn,freeFn>,InputPrivate>(), "InputPrivate shoulb be child of BaseForAlloc" );
    InputPrivate(Input&&, size_t a_hash);
    InputPrivate *prev, *next;
    const size_t    m_hash;
    InputPrivate(const InputPrivate&) = delete;
    InputPrivate(InputPrivate&&) = delete;
    InputPrivate& operator=(const InputPrivate&) = delete;
    InputPrivate& operator=(InputPrivate&&) = delete;
};


}  // namespace iter{

template <typename IntType>
class FHashInt
{
public:
	size_t	operator()(const IntType& key)const;
};



}}  // namespace cpputils { namespace hash { 


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_IMPL_HPP
#include "items.impl.hpp"
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_ITEMS_HPP
