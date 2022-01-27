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
#include <string>
#include <functional>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


namespace cpputils { namespace hash {


template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
class VHashBase
{
public:
    class iterator;
    class const_iterator;
        
public:
    VHashBase(size_t tableSize= templateDefaultSize);
	VHashBase(const VHashBase& cM);
	VHashBase(VHashBase&& cM) CPPUTILS_NOEXCEPT;
	virtual ~VHashBase();
    
    VHashBase& operator=(const VHashBase& cM);
	VHashBase& operator=(VHashBase&& cM) CPPUTILS_NOEXCEPT;
    
    size_t          size()const;
	void            clear() CPPUTILS_NOEXCEPT;  // number of items before
    iterator        find( const KeyType& key, size_t* a_pHash=CPPUTILS_NULL );
    const_iterator  find( const KeyType& key, size_t* a_pHash=CPPUTILS_NULL )const;
    
    HashItemType*   AddEntryWithKnownHashMv(HashItemType&& a_item, size_t a_hash);
    HashItemType*   AddEntryWithKnownHashC(const HashItemType& a_item, size_t a_hash);
    HashItemType*   AddEntryEvenIfExistsMv(HashItemType&& a_item);
    HashItemType*   AddEntryEvenIfExistsC(const HashItemType& a_item);
    HashItemType*   AddEntryIfNotExistMv(HashItemType&& a_item);
    HashItemType*   AddEntryIfNotExistC(const HashItemType& a_item);
    HashItemType*   findEntry( const KeyType& key, size_t* a_pHash )const;
    HashItemType*   at(size_t a_unIndex) const;
    void RemoveEntry(HashItemType*);
        
public:
    static void* operator new( ::std::size_t a_count );
    static void operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT ;
    
protected:
    inline void GeFromOther(const VHashBase& a_cM);
    
protected:
    struct HashItemPrivate;
    HashItemPrivate**  m_pTable;
	size_t             m_unRoundedTableSizeMin1;
	size_t			   m_unSize;
    
    HashItemPrivate**  m_vectTable;
    
public:
    class iterator{
	public:
		iterator();
        iterator(HashItemType* a_pItem);
		HashItemType* operator->()const;
		operator HashItemType*()const;		
	protected:
		friend VHashBase;
		HashItemType* m_pItem;
	}static const s_endIter;
    
    class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const HashItemType* operator->()const;
		operator const HashItemType* ()const;
	protected:
		friend VHashBase;
		HashItemType* m_pItem;
	}static const s_endConstIter;
    
protected:
    struct HashItemPrivate : public HashItemType{
        //using HashItemType::HashItemType;
        HashItemPrivate(HashItemType&&);
        static void* operator new( ::std::size_t a_count );
        static void operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT ;
        HashItemPrivate *prev, *next;
    };
};



template <typename Key,typename Data, typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using VHash = VHashBase<Key,HashItem<Key,Data>,HashT,defSize,mFn,cFn,rFn,fFn>;


template <typename Key,typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_HASH_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using VSet = VHashBase<Key,SetItem<Key>,HashT,defSize,mFn,cFn,rFn,fFn>;



}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_IMPL_HPP
#include "vhash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VHASH_HPP
