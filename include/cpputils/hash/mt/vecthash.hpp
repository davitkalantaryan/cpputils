//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/mt/vecthash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/mt/base.hpp>
#include <cpputils/hash/vecthash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


class CPPUTILS_EXPORT VectHash : public mt::Base<hash::VectHash>
{
public:
    template <typename TypeData>
    using TypeIterFunc = ::std::function<bool(const Iterator<TypeData>&)>;  // true -> continue, false stop
    template <typename TypeData>
    using TypeIterFuncChng = ::std::function<bool(const IteratorRaw<TypeData>&)>;  // true -> continue, false stop

public:
    using Base<hash::VectHash>::Base;

    template <typename TypeData>
    void MoveToStartNoLockFromIterator(const IteratorRaw<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    void MoveToEndNoLockFromIterator(const IteratorRaw<TypeData>& a_iter) noexcept;
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
    inline void RemoveExNoLockFromIterator(const IteratorRaw<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> at(size_t a_index)const noexcept;

private:
    VectHash(const VectHash&) = delete;
    VectHash(VectHash&&) = delete;
    VectHash& operator=(const VectHash&) = delete;
    VectHash& operator=(VectHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_vecthash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP
