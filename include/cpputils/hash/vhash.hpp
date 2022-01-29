//
// file:			vhash.hpp
// path:			include/cpputils/vhash.hpp
// created on:		2022 Jan 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP


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
class VHashApi : public ApiData<Input,defSize,mallocFn,callocFn,freeFn>
{
public:
    class iterator;
    class const_iterator;
    typedef ApiData<Input,defSize,mallocFn,callocFn,freeFn>  ApiDataAdv;
    typedef it::InputPrivate<Input,mallocFn,freeFn> InputPrivate;
    
public:    
    VHashApi(size_t a_unBacketsCount=defSize);
	VHashApi(const VHashApi& cM);
	VHashApi(VHashApi&& cM) CPPUTILS_NOEXCEPT;
	virtual ~VHashApi() override;
    
    VHashApi&      operator=(const VHashApi& cM);
	VHashApi&      operator=(VHashApi&& cM) CPPUTILS_NOEXCEPT;
    iterator       operator[](size_t a_index);
	const_iterator operator[](size_t a_index) const;
    
    void    RemoveEntryRaw(const const_iterator& a_cI);
    Input*  AddEntryWithKnownHashRaw(Input&& a_item, size_t a_hash);
    
protected:
    void InitAllToZero();
    void GeFromOther(const VHashApi&);
    void ClearRaw() CPPUTILS_NOEXCEPT;
    void ReplaceWithOther(VHashApi*) CPPUTILS_NOEXCEPT;
    
private:
    struct TableItem;
    TableItem**     m_ppVector;
    
public:
    class iterator_base{
    public:
        ~iterator_base();
        iterator_base();
        iterator_base(const iterator_base& a_cM);
        iterator_base(VHashApi* a_pParent, Input* a_pItem, size_t a_hash);
        iterator_base(Input* a_pItem);
        const iterator_base& operator++();
        iterator_base operator++(int);
        const iterator_base& operator--();
        iterator_base operator--(int);
        iterator_base operator+(size_t a_offset)const;
        iterator_base operator-(size_t a_offset)const;
        void operator+=(size_t a_offset);
        void operator-=(size_t a_offset);
        void RemoveFromContainer();
    protected:
        Input*          pItem()const;
    protected:
        TableItem*      m_pItem;
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
    
private:
    struct TableItem : public InputPrivate{
        VHashApi*       m_pParent;
        const size_t    m_hash;
        size_t          m_index;
        size_t          m_usageCount;
        TableItem(InputPrivate&& a_mM, VHashApi* a_pParent, size_t a_hash, size_t a_index);
    };
};


template <typename Key,typename Data, typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using VHash = HashBase< Key,HashItem<Key,Data,mFn,fFn>,HashT,defSize,mFn,cFn,rFn,fFn,
                VHashApi<HashItem<Key,Data,mFn,fFn>,defSize,mFn,cFn,rFn,fFn> >;


template <typename Key,typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using VSet = HashBase< Key,SetItem<Key,mFn,fFn>,HashT,defSize,mFn,cFn,rFn,fFn,
                VHashApi<SetItem<Key,mFn,fFn>,defSize,mFn,cFn,rFn,fFn> >;


}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
#include "vhash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
