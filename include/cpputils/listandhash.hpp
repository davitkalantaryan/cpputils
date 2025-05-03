//
// file:			listandhash.hpp
// path:			include/cpputils/listandhash.hpp
// created on:		2025 May 02
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_HPP


#include <cpputils/export_symbols.h>
#include <cinternal/hash.h>


namespace cpputils {


template <typename DataType>
class ListAndHash
{
public:
    struct Item;
    typedef const Item* Iterator;
    enum class Type{None,SmlInt,RawMem};
    
public:
    ~ListAndHash() noexcept;
    ListAndHash(size_t a_numberOfBaskets,
                TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
                TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
                TypeCinternalAllocator a_allocator=nullptr, TypeCinternalDeallocator a_deallocator=nullptr);
    ListAndHash(const Type&  a_type, size_t a_numberOfBaskets=4096,
                TypeCinternalAllocator a_allocator=nullptr, TypeCinternalDeallocator a_deallocator=nullptr);
    
    Iterator first()const;
    Iterator last()const;
    Iterator AddBegWithKnownHash(const DataType& a_data, const void* a_key, size_t a_keySize, size_t a_hash);
    Iterator AddBegWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize, size_t a_hash);
    Iterator AddEndWithKnownHash(const DataType& a_data, const void* a_key, size_t a_keySize, size_t a_hash);
    Iterator AddEndWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize, size_t a_hash);
    Iterator AddBegEvenIfExist(const DataType& a_data, const void* a_key, size_t a_keySize);
    Iterator AddBegEvenIfExist(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    Iterator AddEndEvenIfExist(const DataType& a_data, const void* a_key, size_t a_keySize);
    Iterator AddEndEvenIfExist(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    Iterator AddBegIfNotExists(const DataType& a_data, const void* a_key, size_t a_keySize);
    Iterator AddBegIfNotExists(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    Iterator AddEndIfNotExists(const DataType& a_data, const void* a_key, size_t a_keySize);
    Iterator AddEndIfNotExists(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    inline void RemoveEx(Iterator CPPUTILS_ARG_NN a_iter) noexcept;
    bool Remove(const void* a_key, size_t a_keySize) noexcept;
    inline Iterator findEx( const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) const noexcept;
    Iterator find( const void* a_key, size_t a_keySize) const noexcept;
    Iterator findNextTheSame( Iterator CPPUTILS_ARG_NN a_prev ) const noexcept;
    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;
        
private:
    inline void AddToTheListBegPrivate(Item* CPPUTILS_ARG_NN a_pItem) noexcept;
    inline void AddToTheListEndPrivate(Item* CPPUTILS_ARG_NN a_pItem) noexcept;
    
private:
    Item*                       m_first;
    Item*                       m_last;
    ConstCinternalHash_t        m_hash;
    
public:
    struct Item{
        struct Item         *prev,*next;
        CinternalHashItem_t hashIter;
        void*               reserved01;
        mutable DataType    data;
        
    private:
        Item(DataType* CPPUTILS_ARG_NN a_data_p) noexcept;
        Item(const Item&)=delete;
        Item(Item&&)=delete;
        Item& operator=(const Item&)=delete;
        Item& operator=(Item&&)=delete;
        friend class ListAndHash;
    };
    
private:
    ListAndHash(const ListAndHash&)=delete;
    ListAndHash(ListAndHash&&)=delete;
    ListAndHash& operator=(const ListAndHash&)=delete;
    ListAndHash& operator=(ListAndHash&&)=delete;
};


}  //  namespace cpputils {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_IMPL_HPP
#include <cpputils/listandhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_LISTANDHASH_HPP
