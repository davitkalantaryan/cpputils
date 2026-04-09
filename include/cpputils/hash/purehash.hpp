//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#include <cpputils/export_symbols.h>
#include <cpputils/hash/base.hpp>


namespace cpputils { namespace hash{


class Cph {
public:
    template <typename TypeData>
    struct Item : public bh::Item<bh::ItemBase, TypeData> {
    public:
        using bh::Item<bh::ItemBase, TypeData>::Item;
    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
    };
};


class CPPUTILS_EXPORT PureHash : public Base<Cph>
{
public:
    PureHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

protected:
    PureHash(const PureHash&) = delete;
    PureHash(PureHash&&) = delete;
    PureHash& operator=(const PureHash&) = delete;
    PureHash& operator=(PureHash&&) = delete;
};


}}  //  namespace cpputils { namespace hash{
