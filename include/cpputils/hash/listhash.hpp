//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/listhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/base.hpp>


namespace cpputils { namespace hash{


class CPPUTILS_EXPORT ListHash : public Base
{
public:
    template <typename TypeData>
    struct Item;
    template <typename TypeData>
    using Iterator = const Item<TypeData>*;

public:
    ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    inline Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData>
    Iterator<TypeData> findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    bool Remove(const TypeKey& a_key) noexcept;

    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);

public:
    template <typename TypeData>
    struct Item : public bh::Item<TypeData> {
        struct Item* prev, * next;
    protected:
        using bh::Item<TypeData>::Item;
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
        friend class ::cpputils::hash::Base;
    };

private:
    ListHash(const ListHash&) = delete;
    ListHash(ListHash&&) = delete;
    ListHash& operator=(const ListHash&) = delete;
    ListHash& operator=(ListHash&&) = delete;
};


}}  //  namespace cpputils { namespace hash{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
