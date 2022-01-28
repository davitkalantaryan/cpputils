//
// file:			hashbase.hpp
// path:			include/cpputils/hash/hashbase.hpp
// created on:		2022 Jan 28
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP


#include <cpputils_internal_header.h>
#include <cpputils/hash/items.hpp>
#include <cpputils/functional.hpp>
#include <string>
#include <functional>
#include <type_traits>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


namespace cpputils { namespace hash {

template <typename HashItemType,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
class ApiData
{
public:
    typedef it::HashItemPrivate<HashItemType,mallocFn,freeFn> HashItemPrivateBase;
    
protected:
    ApiData(bool,size_t a_unBacketsCount=0);
    
public:
    ApiData(size_t a_unBacketsCount=0);
    virtual ~ApiData();
    
    static void* operator new( ::std::size_t a_count );
    static void operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT ;
    
protected:
    void ConstructAfterRoundedTableSizeMin1IsKnown();
    void InitAllToZeroB();
    void ReplaceWithOtherB(ApiData*) CPPUTILS_NOEXCEPT;
    void AddEntryWithAlreadyCreatedItemB(HashItemType* a_pItem);
    
protected:
    HashItemType**  m_pTable;
	size_t          m_unRoundedTableSizeMin1;
	size_t			m_unSize;
};

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
class HashBase : public ApiType
{
    static_assert( ::std::is_base_of<ApiData<HashItemType,mallocFn,callocFn,freeFn>,ApiType>(), "ApiType shoulb be child of ApiData" );
public:
    typedef it::HashItemPrivate<HashItemType,mallocFn,freeFn> HashItemPrivate;
    
public:
    using ApiType::ApiType;
	virtual ~HashBase() override;
    
    using ApiType::operator=;
        
    size_t          size()const;
	void            clear() CPPUTILS_NOEXCEPT;
    
    HashItemType*   AddEntryWithKnownHashMv(HashItemType&& a_item, size_t a_hash);
    HashItemType*   AddEntryWithKnownHashC(const HashItemType& a_item, size_t a_hash);
    HashItemType*   AddEntryEvenIfExistsMv(HashItemType&& a_item);
    HashItemType*   AddEntryEvenIfExistsC(const HashItemType& a_item);
    HashItemType*   AddEntryIfNotExistMv(HashItemType&& a_item);
    HashItemType*   AddEntryIfNotExistC(const HashItemType& a_item);
    HashItemType*   findEntry( const KeyType& key, size_t* a_pHash )const;
    void RemoveEntryByKey(const KeyType& a_key);    
    
protected:
    inline void GeFromOther(const HashBase& a_cM);
        
    //friend ApiType;
};




}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
#include "hashbase.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP
