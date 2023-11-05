//
// file:			dllhash.hpp  (Double linked list Hash)
// path:			include/cpputils/hash/dllhash.hpp
// created on:		2022 Sep 25
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_HPP

#include <cpputils/export_symbols.h>
#if defined(_MSC_VER) /*&& (_MSC_VER>1929)*/
//#pragma warning(push)
#pragma warning (disable:5267)  // copy constructor for '__p::__i::HashItemBase<KeyType,void>' is deprecated because it has a user-provided destructor
#endif
#include <cpputils/hash/items.hpp>
#include <cpputils/hash/hashbase.hpp>
#include <string>
#include <functional>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


namespace cpputils { namespace hash {


template <typename Input,size_t defSize,TypeMalloc mallocFn,TypeCalloc callocFn,TypeRealloc reallocFn,TypeFree freeFn>
class DllHashApi : public ApiData<Input,defSize,mallocFn,callocFn,freeFn>
{
public:
    class iterator;
    class const_iterator;
    typedef ApiData<Input,defSize,mallocFn,callocFn,freeFn>  ApiDataAdv;
    typedef it::InputPrivate<Input,mallocFn,freeFn> InputPrivate;
    
public:    
	virtual ~DllHashApi() override;
    
    iterator       begin();
	const_iterator begin() const;
    iterator       end();
	const_iterator end() const;
    iterator       lastIter();
    const_iterator lastIter()const;
    
    void    RemoveEntryRaw(const const_iterator& a_cI);
    Input*  AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash);
    
protected:
    void ConstructAfterRoundedTableSizeMin1IsKnown();
    void InitAllToZero();
    void GeFromOther(const DllHashApi&);
    void ClearRaw() CPPUTILS_NOEXCEPT;
    void ReplaceWithOther(DllHashApi*) CPPUTILS_NOEXCEPT;
    
protected:
    struct ListItem;
    
    ListItem *m_pFirstItem, *m_pLastItem;
    
public:
    class iterator_base{
    public:
        iterator_base();
        iterator_base(Input* a_pItem);
        const iterator_base& operator++();
        iterator_base operator++(int);
        const iterator_base& operator--();
        iterator_base operator--(int);
        iterator_base next()const;
        iterator_base previous()const;
        void RemoveFromContainer();
    protected:
        ListItem*      m_pItem;
        friend class DllHashApi;
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
        const_iterator()=default;
        const_iterator(const iterator&);
        const Input* operator->()const;
        operator const Input* ()const;
    }static const s_constNullIter;
    
protected:
    struct ListItem : public InputPrivate{
        DllHashApi**     m_ppParent;
        ListItem    	*prevInTheList, *nextInTheList;
        ListItem(Input&& a_mM, DllHashApi* a_pParent, size_t a_hash);
        ListItem(const ListItem&) = delete;
        ListItem& operator=(const ListItem&) = delete;
    };
};


template <typename Key,typename Data, typename HashT=::std::hash<Key>, typename Equal = ::std::equal_to<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using DllHash = HashBase< Key,HashItem<Key,Data,mFn,fFn>,HashT, Equal,defSize,mFn,cFn,rFn,fFn,
                DllHashApi<HashItem<Key,Data,mFn,fFn>,defSize,mFn,cFn,rFn,fFn> >;


template <typename Key,typename HashT=::std::hash<Key>, typename Equal = ::std::equal_to<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using DllSet = HashBase< Key,SetItem<Key,mFn,fFn>,HashT, Equal,defSize,mFn,cFn,rFn,fFn,
                DllHashApi<SetItem<Key,mFn,fFn>,defSize,mFn,cFn,rFn,fFn> >;


}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_IMPL_HPP
#include "dllhash.impl.hpp"
#endif

#if defined(_MSC_VER) && (_MSC_VER>1929)
//#pragma warning(pop)
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_DLLHASH_HPP
