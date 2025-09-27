//
// repo:            cpputils
// file:			collectionmap.hpp
// path:			include/cpputils/collectionmap.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONMAP_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONMAP_HPP


#include <cpputils/export_symbols.h>
#include <cinternal/hash.h>


namespace cpputils {
    
class CPPUTILS_DLL_PRIVATE CollectionMap_p;

class CPPUTILS_EXPORT CollectionMap
{
public:
    template <typename DataType>
    struct Item;
    template <typename DataType>
    using Iterator = const Item<DataType>*;

public:
    ~CollectionMap() noexcept;
    CollectionMap(size_t a_numberOfBaskets,TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename DataType>
    Iterator<DataType> first()const noexcept;
    template <typename DataType>
    Iterator<DataType> last()const noexcept;
    template <typename DataType, typename TypeInt=size_t>
    Iterator<DataType> AddBegWithKnownHash(const DataType& a_data, const TypeInt& a_key, size_t a_hash);
    template <typename DataType, typename TypeInt = size_t>
    Iterator<DataType> AddBegWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const TypeInt& a_key, size_t a_hash);
    
    //Iterator AddEndWithKnownHash(const DataType& a_data, const void* a_key, size_t a_keySize, size_t a_hash);
    //Iterator AddEndWithKnownHash(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize, size_t a_hash);
    //Iterator AddBegEvenIfExist(const DataType& a_data, const void* a_key, size_t a_keySize);
    //Iterator AddBegEvenIfExist(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    //Iterator AddEndEvenIfExist(const DataType& a_data, const void* a_key, size_t a_keySize);
    //Iterator AddEndEvenIfExist(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    //Iterator AddBegIfNotExists(const DataType& a_data, const void* a_key, size_t a_keySize);
    //Iterator AddBegIfNotExists(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    //Iterator AddEndIfNotExists(const DataType& a_data, const void* a_key, size_t a_keySize);
    //Iterator AddEndIfNotExists(DataType* CPPUTILS_ARG_NN a_data_p, const void* a_key, size_t a_keySize);
    //inline void RemoveEx(Iterator CPPUTILS_ARG_NN a_iter) noexcept;
    //bool Remove(const void* a_key, size_t a_keySize) noexcept;
    //inline Iterator findEx(const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) const noexcept;
    //Iterator find(const void* a_key, size_t a_keySize) const noexcept;
    //Iterator findNextTheSame(Iterator CPPUTILS_ARG_NN a_prev) const noexcept;

private:
    template <typename DataType>
    static inline int getUniqueIdInline(void) noexcept;

private:
    const Item<void>* getFirstByTypeIndex(int a_typeIndex)const;
    const Item<void>* getLastByTypeIndex(int a_typeIndex)const;
    void AddToTheListBegPrivate(Item<void>* CPPUTILS_ARG_NN a_item_p, int a_typeIndex);

public:
    template <typename DataType>
    struct Item {
        struct Item *prev, *next;
        DataType*    data_p;

    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
        friend class CollectionMap;
    };

private:
    CollectionMap_p* const  m_clmp_data_p;
};


}  //  namespace cpputils 


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONMAP_IMPL_HPP
#include <cpputils/impl/cpputils_collectionmap.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONMAP_HPP
