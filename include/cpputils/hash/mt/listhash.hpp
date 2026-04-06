//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/mt/listhash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/mt/base.hpp>
#include <cpputils/hash/listhash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


class CPPUTILS_EXPORT ListHash : public Base<hash::ListHash>
{
public:
    template <typename TypeData>
    using Iterator = ::cpputils::hash::ListHash::Iterator<TypeData>;
    template <typename TypeData>
    using TypeIterFunc = ::std::function<bool(TypeData&)>;  // true -> continue, false stop
    template <typename TypeData>
    using TypeIterFuncChng = ::std::function<bool(const Iterator<TypeData>&)>;  // true -> continue, false stop

public:
    ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    void MoveToStartNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    void MoveToEndNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    void iterateBegToEnd(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept;
    template <typename TypeData>
    void iterateEndToBeg(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);
    template <typename TypeData>
    void IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc);
    template <typename TypeData>
    void IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc);
    template <typename TypeData>
    inline void RemoveExNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;

private:
    ListHash(const ListHash&) = delete;
    ListHash(ListHash&&) = delete;
    ListHash& operator=(const ListHash&) = delete;
    ListHash& operator=(ListHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP
