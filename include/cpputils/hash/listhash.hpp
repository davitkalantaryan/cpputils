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


namespace lh{
class CPPUTILS_EXPORT Hash_p;
}

class Clh {
public:

    struct ItemBase : public bh::ItemBase {
        struct ItemBase* prev, * next;
    protected:
        virtual ~ItemBase() override = default;
        ItemBase() = default;
        ItemBase(const ItemBase&) = delete;
        ItemBase(ItemBase&&) = delete;
        ItemBase& operator=(const ItemBase&) = delete;
        ItemBase& operator=(ItemBase&&) = delete;
    private:
        friend class lh::Hash_p;
    };

    template <typename TypeData>
    struct Item : public ItemBase {
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


class CPPUTILS_EXPORT ListHash : public Base<Clh>
{
public:
    ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);

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
