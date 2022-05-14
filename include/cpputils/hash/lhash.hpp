//
// file:			lhash.hpp
// path:			include/cpputils/hash/lhash.hpp
// created on:		2022 Jan 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_LHASH_HPP


#include <cpputils_internal_header.h>
#include <cpputils/hash/items.hpp>
#include <cpputils/hash/hashbase.hpp>
#include <string>
#include <functional>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


namespace cpputils { namespace hash {


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
class LHashApi : public ApiData<Input,defSize,mallocFn,callocFn,freeFn>
{
public:
    class iterator;
    class const_iterator;
    typedef ApiData<Input,defSize,mallocFn,callocFn,freeFn>  ApiDataAdv;
    typedef it::InputPrivate<Input,mallocFn,freeFn> InputPrivate;
    
public:    
	virtual ~LHashApi() override;
    
    iterator       begin();
	const_iterator begin() const;
    iterator       end();
	const_iterator end() const;
    
    void    RemoveEntryRaw(const const_iterator& a_cI);
    Input*  AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash);
    
protected:
    void ConstructAfterRoundedTableSizeMin1IsKnown();
    void InitAllToZero();
    void GeFromOther(const LHashApi&);
    void ClearRaw() CPPUTILS_NOEXCEPT;
    void ReplaceWithOther(LHashApi*) CPPUTILS_NOEXCEPT;
    
protected:
    struct ListItem;
    
    ListItem* m_pFirstItem;
    
public:
    class iterator_base{
    public:
        iterator_base();
        iterator_base(const LHashApi* a_pParent, Input* a_pItem, size_t a_hash);
        const iterator_base& operator++();
        iterator_base operator++(int);
        const iterator_base& operator--();
        iterator_base operator--(int);
        iterator_base next()const;
        iterator_base previous()const;
        void RemoveFromContainer();
    protected:
        LHashApi*      m_pParent;
        ListItem*      m_pItem;
        friend class LHashApi;
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
        const_iterator(const iterator&);
        const Input* operator->()const;
        operator const Input* ()const;
    }static const s_constNullIter;
    
protected:
    struct ListItem : public InputPrivate{
        ListItem    	*prevInTheList, *nextInTheList;
        const size_t    m_hash;
        ListItem(InputPrivate&& a_mM, size_t a_hash);
    };
};


template <typename Key,typename Data, typename HashT=::std::hash<Key>, typename Equal = ::std::equal_to<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using LHash = HashBase< Key,HashItem<Key,Data,mFn,fFn>,HashT, Equal,defSize,mFn,cFn,rFn,fFn,
                LHashApi<HashItem<Key,Data,mFn,fFn>,defSize,mFn,cFn,rFn,fFn> >;


template <typename Key,typename HashT=::std::hash<Key>, typename Equal = ::std::equal_to<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using LSet = HashBase< Key,SetItem<Key,mFn,fFn>,HashT, Equal,defSize,mFn,cFn,rFn,fFn,
                LHashApi<SetItem<Key,mFn,fFn>,defSize,mFn,cFn,rFn,fFn> >;


}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LHASH_IMPL_HPP
#include "lhash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
