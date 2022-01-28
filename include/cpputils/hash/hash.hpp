//
// file:			hash.hpp
// path:			include/cpputils/hash.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_HPP


#include <cpputils_internal_header.h>
#include <cpputils/hash/items.hpp>
#include <cpputils/hash/hashbase.hpp>
#include <cpputils/functional.hpp>
#include <string>
#include <functional>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


namespace cpputils { namespace hash {

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
class HashApi : public ApiData<HashItemType,mallocFn,callocFn,freeFn>
{
public:
    typedef ApiData<HashItemType,mallocFn,callocFn,freeFn>  ApiDataAdv;
    typedef it::HashItemPrivate<HashItemType,mallocFn,freeFn> HashItemPrivateBase;
    typedef it::iterator<HashItemType> iterator;
    typedef it::const_iterator<HashItemType> const_iterator;
    
public:
    using ApiData<HashItemType,mallocFn,callocFn,freeFn>::ApiData;
    HashItemType*   AddEntryWithKnownHashRaw(HashItemType&& a_item, size_t a_hash);
    
	HashApi(const HashApi& cM);
	HashApi(HashApi&& cM) CPPUTILS_NOEXCEPT;
	virtual ~HashApi() override;
    
    HashApi& operator=(const HashApi& cM);
	HashApi& operator=(HashApi&& cM) CPPUTILS_NOEXCEPT;
    
protected:
    void GeFromOther(const HashApi&);
    void ClearRaw() CPPUTILS_NOEXCEPT;
};



template <typename Key,typename Data, typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using Hash = HashBase<Key,HashItem<Key,Data>,HashT,defSize,mFn,cFn,rFn,fFn,
                HashApi<Key,HashItem<Key,Data>,HashT,defSize,mFn,cFn,rFn,fFn> >;


template <typename Key,typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using Set = HashBase<Key,SetItem<Key>,HashT,defSize,mFn,cFn,rFn,fFn,HashApi<Key,SetItem<Key>,HashT,defSize,mFn,cFn,rFn,fFn> >;



}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP
#include "hash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HPP
