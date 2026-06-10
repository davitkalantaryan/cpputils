//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/listhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/nl/base.hpp>


namespace cpputils { namespace hash{ namespace nl{


namespace lh{
class CPPUTILS_EXPORT Hash_p;
}

class CPPUTILS_EXPORT Clh {
public:

    struct CPPUTILS_EXPORT ItemBase : public bh::ItemBase {
        const struct ItemBase* prev, * next;
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
    struct Item : public bh::Item<Clh::ItemBase,TypeData> {
    public:
        using bh::Item<Clh::ItemBase, TypeData>::Item;
    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
    };
};


class CPPUTILS_EXPORT ListHash : public hash::nl::BaseNl<Clh>
{
public:
    ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    // list& vector specific
    void AllocateListsInAdvance(int32_t a_numberOfLists);
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& a_iter) noexcept;

protected:
    ListHash(const ListHash&) = delete;
    ListHash(ListHash&&) = delete;
    ListHash& operator=(const ListHash&) = delete;
    ListHash& operator=(ListHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace nl{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_NL_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_nl_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_LISTHASH_HPP
