//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/templ/listhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>
#include <cpputils/hash/listhash.hpp>
#include <cpputils/hash/mt/listhash.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeBase, typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class CPPUTILS_DLL_PUBLIC ListHashBase : public TypeBase
{
public:
    typedef mt::ListHash::TypeIterFunc<TypeData>      TypeIterFunc;
    typedef mt::ListHash::TypeIterFuncChng<TypeData>  TypeIterFuncChng;
    typedef TypeBase   BaseRaw;

    using Iterator = typename BaseRaw::Iterator;
    using IteratorRaw = typename BaseRaw::IteratorRaw;
    using TypeRawHash = typename BaseRaw::TypeRawHash;

public:
    using TypeBase::TypeBase;

    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);
    //
    void MoveToStart(const Iterator& a_iter) noexcept;
    void MoveToEnd(const Iterator& a_iter) noexcept;
    Iterator first()const noexcept;
    Iterator last()const noexcept;
    //
    void iterateBegToEnd(const TypeIterFunc& a_iterFunc)const noexcept;
    void iterateEndToBeg(const TypeIterFunc& a_iterFunc)const noexcept;
    void IterateBegToEnd(const TypeIterFuncChng& a_iterFunc);
    void IterateEndToBeg(const TypeIterFuncChng& a_iterFunc);
    inline void RemoveExNoLockFromIterator(const IteratorRaw& a_iter) noexcept;
    inline void MoveToStartNoLockFromIterator(const IteratorRaw& a_iter) noexcept;
    inline void MoveToEndNoLockFromIterator(const IteratorRaw& a_iter) noexcept;

protected:
    ListHashBase(const ListHash&) = delete;
    ListHashBase(ListHash&&) = delete;
    ListHashBase& operator=(const ListHash&) = delete;
    ListHashBase& operator=(ListHash&&) = delete;
};


template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using ListHash = ListHashBase<
    templ::Base<hash::ListHash, TypeData, TypeKey, TypeKeyExt>,
    hash::ListHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using MtListHash = ListHashBase<
    templ::MtBase<hash::mt::ListHash, TypeData, TypeKey, TypeKeyExt>,
    hash::mt::ListHash,TypeData, TypeKey, TypeKeyExt>;



}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP
