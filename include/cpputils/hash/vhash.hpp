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


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
class VHashApi : public ApiData<HashItemType,mallocFn,callocFn,freeFn>
{
protected:
    struct HashItemPrivate;
    typedef ApiData<HashItemType,mallocFn,callocFn,freeFn>  ApiDataAdv;
    typedef it::HashItemPrivate<HashItemType,mallocFn,freeFn> HashItemPrivateBase;
    
public:
    HashItemType*   AddEntryWithKnownHashRaw(HashItemType&& a_item, size_t a_hash);
    
    VHashApi(size_t a_unBacketsCount=0);
	VHashApi(const VHashApi& cM);
	VHashApi(VHashApi&& cM) CPPUTILS_NOEXCEPT;
	virtual ~VHashApi() override;
    
    VHashApi& operator=(const VHashApi& cM);
	VHashApi& operator=(VHashApi&& cM) CPPUTILS_NOEXCEPT;
    
protected:
    void InitAllToZero();
    void GeFromOther(const VHashApi&);
    void ClearRaw() CPPUTILS_NOEXCEPT;
    void ReplaceWithOther(VHashApi*) CPPUTILS_NOEXCEPT;
    
protected:
    HashItemPrivate**  m_ppVector;
    
protected:
    struct HashItemPrivate : public HashItemPrivateBase{
        HashItemPrivate(HashItemType&&, size_t a_hash, size_t a_index, VHashApi* a_pParent);
        size_t index;
        VHashApi*const m_pParent;
    };
    
public:
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
        size_t m_index;
    };
    
    class const_iterator{
    public:
        virtual ~const_iterator();
        const_iterator();
        const_iterator(const HashItemType* a_pItem);
        const_iterator(const iterator& iter);
        virtual const HashItemType* operator->()const;
        virtual operator const HashItemType* ()const;
    public:
        static const const_iterator s_endConstIter;
    protected:
        HashItemType* m_pItem;
    };
};


template <typename Key,typename Data, typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using VHash = HashBase<Key,HashItem<Key,Data>,HashT,defSize,mFn,cFn,rFn,fFn,
                VHashApi<Key,HashItem<Key,Data>,HashT,defSize,mFn,cFn,rFn,fFn> >;


template <typename Key,typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using VSet = HashBase<Key,SetItem<Key>,HashT,defSize,mFn,cFn,rFn,fFn,VHashApi<Key,SetItem<Key>,HashT,defSize,mFn,cFn,rFn,fFn> >;


}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
#include "vhash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
