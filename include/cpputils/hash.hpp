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
#include <cpputils/functional.hpp>
#include <string>
#include <functional>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "hash.def.hpp"


namespace cpputils { namespace hash {

typedef void* (*TypeMalloc)  ( size_t );
typedef void* (*TypeCalloc)  ( size_t,size_t );
typedef void* (*TypeRealloc)  ( void*,size_t );
typedef void  (*TypeFree)  ( void* );

template <typename KeyType,typename HashItemType, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn>
class HashBase
{
public:
    class iterator;
    class const_iterator;
    
protected:
    virtual HashItemType*   AddEntryWithKnownHashRaw(HashBase* a_pContainer, HashItemType&& a_item, size_t a_hash);
    
public:
    HashBase(size_t tableSize= templateDefaultSize);
	HashBase(const HashBase& cM);
	HashBase(HashBase&& cM) CPPUTILS_NOEXCEPT;
	virtual ~HashBase();
    
    HashBase& operator=(const HashBase& cM);
	HashBase& operator=(HashBase&& cM) CPPUTILS_NOEXCEPT;
    
    size_t          size()const;
	virtual void    clear() CPPUTILS_NOEXCEPT;
    iterator        find( const KeyType& key, size_t* a_pHash=CPPUTILS_NULL );
    const_iterator  find( const KeyType& key, size_t* a_pHash=CPPUTILS_NULL )const;
    
    HashItemType*   AddEntryWithKnownHashMv(HashItemType&& a_item, size_t a_hash);
    HashItemType*   AddEntryWithKnownHashC(const HashItemType& a_item, size_t a_hash);
    HashItemType*   AddEntryEvenIfExistsMv(HashItemType&& a_item);
    HashItemType*   AddEntryEvenIfExistsC(const HashItemType& a_item);
    HashItemType*   AddEntryIfNotExistMv(HashItemType&& a_item);
    HashItemType*   AddEntryIfNotExistC(const HashItemType& a_item);
    HashItemType*   findEntry( const KeyType& key, size_t* a_pHash )const;
    void RemoveEntry(HashItemType*);
        
public:
    static void* operator new( ::std::size_t a_count );
    static void operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT ;
    
protected:
    inline void GeFromOther(const HashBase& a_cM);
    
private:
    HashItemType**  m_pTable;
	size_t          m_unRoundedTableSizeMin1;
	size_t			m_unSize;
    
public:
    class iterator{
	public:
		iterator();
        iterator(HashItemType* a_pItem);
		HashItemType* operator->()const;
		operator HashItemType*()const;		
	protected:
		friend HashBase;
		HashItemType* m_pItem;
	}static const s_endIter;
    
    class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const HashItemType* operator->()const;
		operator const HashItemType* ()const;
	protected:
		friend HashBase;
		HashItemType* m_pItem;
	}static const s_endConstIter;
    
private:
    struct HashItemPrivate : public HashItemType{
        //using HashItemType::HashItemType;
        HashItemPrivate(HashItemType&&);
        static void* operator new( ::std::size_t a_count );
        static void operator delete  ( void* a_ptr ) CPPUTILS_NOEXCEPT ;
    private:
        HashItemPrivate *prev, *next;
        friend HashBase;
    };
};



template <typename Key,typename Data, typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using Hash = HashBase<Key,HashItem<Key,Data>,HashT,defSize,mFn,cFn,rFn,fFn>;


template <typename Key,typename HashT=::std::hash<Key>, size_t defSize=CPPUTILS_DEFAULT_TABLE_SIZE,
          TypeMalloc mFn=::malloc, TypeCalloc cFn=::calloc, TypeRealloc rFn=::realloc, TypeFree fFn=::free>
using Set = HashBase<Key,SetItem<Key>,HashT,defSize,mFn,cFn,rFn,fFn>;



}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_IMPL_HPP
#include "hash.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HPP
