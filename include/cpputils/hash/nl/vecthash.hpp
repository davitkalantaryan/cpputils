//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/vecthash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_VECTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_VECTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/nl/base.hpp>


namespace cpputils { namespace hash{ namespace nl{

namespace vh{

struct SVectData;

}

class Cvh {
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


class CPPUTILS_EXPORT VectHash : public hash::nl::BaseNl<Cvh>
{
public:
    VectHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

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
    
    // vector specific
    template <typename TypeData>
    Iterator<TypeData> at(size_t a_index)const noexcept;

    // vector specific no lock specific
    const vh::SVectData& getVectDataForTypeDataRaw(const int32_t a_dataIndex)const noexcept;
    template <typename TypeData>
    const vh::SVectData& getVectDataForTypeData()const noexcept;

protected:
    VectHash(const VectHash&) = delete;
    VectHash(VectHash&&) = delete;
    VectHash& operator=(const VectHash&) = delete;
    VectHash& operator=(VectHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace nl{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_NL_VECTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_nl_vecthash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_VECTHASH_HPP
