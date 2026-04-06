//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/vecthash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VECTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_VECTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/base.hpp>


namespace cpputils { namespace hash{


class Cvh {
public:

    template <typename TypeData>
    struct Item : public bh::ItemBase {
        mutable TypeData    data;

    public:
        Item(TypeData* CPPUTILS_ARG_NN a_data_p);
    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
    };
};


class CPPUTILS_EXPORT VectHash : public Base<Cvh>
{
public:
    VectHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> at(size_t a_index)const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);

private:
    VectHash(const VectHash&) = delete;
    VectHash(VectHash&&) = delete;
    VectHash& operator=(const VectHash&) = delete;
    VectHash& operator=(VectHash&&) = delete;
};


}}  //  namespace cpputils { namespace hash{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_VECTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_vecthash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_VECTHASH_HPP
