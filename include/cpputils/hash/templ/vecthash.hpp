//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/templ/vecthash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>
#include <cpputils/hash/vecthash.hpp>
#include <cpputils/hash/mt/vecthash.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
class CPPUTILS_DLL_PUBLIC VectHashBase : public Base<TypeHash,TypeData,TypeKey,TypeHasher,TypeKeyExt>
{
public:
    typedef mt::VectHash::TypeIterFunc<TypeData>      TypeIterFunc;
    typedef mt::VectHash::TypeIterFuncChng<TypeData>  TypeIterFuncChng;
    typedef Base<TypeHash,TypeData,TypeKey,TypeHasher,TypeKeyExt>   BaseRaw;

    using Iterator = typename BaseRaw::Iterator;
    using IteratorRaw = typename BaseRaw::IteratorRaw;
    using TypeRawHash = typename BaseRaw::TypeRawHash;

public:
    using Base<TypeHash,TypeData, TypeKey, TypeHasher, TypeKeyExt>::Base;

    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);
    //
    void MoveToStart(const Iterator& a_iter) noexcept;
    void MoveToEnd(const Iterator& a_iter) noexcept;
    Iterator first()const noexcept;
    Iterator last()const noexcept;
    Iterator at(size_t a_index)const noexcept;

    //
    void iterateBegToEnd(const TypeIterFunc& a_iterFunc)const noexcept;
    void iterateEndToBeg(const TypeIterFunc& a_iterFunc)const noexcept;
    void IterateBegToEnd(const TypeIterFuncChng& a_iterFunc);
    void IterateEndToBeg(const TypeIterFuncChng& a_iterFunc);
    inline void RemoveExNoLockFromIterator(const IteratorRaw& a_iter) noexcept;
    inline void MoveToStartNoLockFromIterator(const IteratorRaw& a_iter) noexcept;
    inline void MoveToEndNoLockFromIterator(const IteratorRaw& a_iter) noexcept;

private:
    VectHashBase(const VectHashBase&) = delete;
    VectHashBase(VectHashBase&&) = delete;
    VectHashBase& operator=(const VectHashBase&) = delete;
    VectHashBase& operator=(VectHashBase&&) = delete;
};


template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
using VectHash = VectHashBase<hash::VectHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
using MtVectHash = ListHashBase<hash::mt::VectHash,TypeData, TypeKey, TypeHasher, TypeKeyExt>;



}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_vecthash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_HPP
