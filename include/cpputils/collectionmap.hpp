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
#include <cinternal/disable_compiler_warnings.h>
#include <memory>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace collectionmap{ 


class CPPUTILS_EXPORT CollectionMap_p;


class CPPUTILS_EXPORT Base
{
public:
    template <typename TypeData>
    struct Item;
    template <typename TypeData>
    using Iterator = const Item<TypeData>*;

protected:
    ~Base() noexcept;
    Base();

private:
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) = delete;

public:
    template <typename TypeData>
    static inline int getReserveUniqueIdInline(void) noexcept;
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData >
    Iterator<TypeData> findNextTheSame(const Iterator<TypeData>& a_prev)const noexcept;

public:
    template <typename TypeData>
    struct Item {
        struct Item *prev, *next;
        TypeData*    data_p;

    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
        friend class CollectionMap;
    };

protected:
    CollectionMap_p* const  m_clmp_data_p;
};


class CPPUTILS_EXPORT WithIntKey : public Base
{
public:
    WithIntKey(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData, typename TypeInt>
    Iterator<TypeData> findEx(const TypeInt& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeInt>
    Iterator<TypeData> find(const TypeInt& a_key)const noexcept;
    template <typename TypeData, typename TypeInt>
    Iterator<TypeData> AddBegWithKnownHash(const TypeData& a_data, const TypeInt& a_key, size_t a_hash);
    template <typename TypeData, typename TypeInt>
    Iterator<TypeData> AddBegWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeInt& a_key, size_t a_hash);
};


class CPPUTILS_EXPORT WithAnyKey : public Base
{
public:
    WithAnyKey(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
    Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
    Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
    Iterator<TypeData> AddBegWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
    Iterator<TypeData> AddBegWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
};


}}  //  namespace cpputils { namespace collectionmap{ 


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONMAP_IMPL_HPP
#include <cpputils/impl/cpputils_collectionmap.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONMAP_HPP
