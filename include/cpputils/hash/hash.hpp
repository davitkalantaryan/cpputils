//
// file:			hash.hpp
// path:			include/cpputils/hash/hash.hpp
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

template <typename Input,size_t defSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
class HashApi : public ApiData<Input,defSize,mallocFn,callocFn,freeFn>
{
public:
    class const_iterator;
    typedef ApiData<Input,defSize,mallocFn,callocFn,freeFn>  ApiDataAdv;
    typedef it::InputPrivate<Input,mallocFn,freeFn> InputPrivate;
    
public:
	virtual ~HashApi() override;
        
    void    RemoveEntryRaw(const const_iterator& a_cI);
    Input*  AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash);
    
protected:
    void ConstructAfterRoundedTableSizeMin1IsKnown();
    void GeFromOther(const HashApi&);
    void ClearRaw() CPPUTILS_NOEXCEPT;
    
public:
    class iterator_base{
    public:
        iterator_base();
        iterator_base(const HashApi* a_pParent, Input* a_pItem, size_t a_hash);
        void RemoveFromContainer();
    protected:
        HashApi*      m_pParent;
        InputPrivate* m_pItem;
        size_t        m_hash;
        friend HashApi;
    };
    class iterator : public iterator_base{
    public:
        using iterator_base::iterator_base;
        Input* operator->()const;
        operator Input*()const;
    }static const s_nullIter;   
    class const_iterator : public iterator_base{
    public:
        using iterator_base::iterator_base;
        const_iterator(const iterator& iter);
        const Input* operator->()const;
        operator const Input* ()const;
    }static const s_constNullIter;    
};


template <typename Key,typename Data, typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using Hash = HashBase< Key,HashItem<Key,Data,mFn,fFn>,HashT,defSize,mFn,cFn,rFn,fFn,
                HashApi<HashItem<Key,Data,mFn,fFn>,defSize,mFn,cFn,fFn> >;


template <typename Key,typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using Set = HashBase< Key,SetItem<Key,mFn,fFn>,HashT,defSize,mFn,cFn,rFn,fFn,
                HashApi<SetItem<Key,mFn,fFn>,defSize,mFn,cFn,fFn> >;



}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP
#include "hash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HPP
