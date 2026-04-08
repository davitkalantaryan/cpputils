//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>
#include <cpputils/hash/purehash.hpp>
#include <cpputils/hash/mt/purehash.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
using MtPureHash = templ::MtBase<hash::mt::PureHash,TypeData, TypeKey, TypeHasher, TypeKeyExt>;


template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
class CPPUTILS_DLL_PUBLIC PureHash : public Base<hash::PureHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>
{
public:
    typedef Base<hash::PureHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>   BaseRaw;

    using Iterator = typename BaseRaw::Iterator;
    using IteratorRaw = typename BaseRaw::IteratorRaw;
    using TypeRawHash = typename BaseRaw::TypeRawHash;

public:
    using Base<hash::PureHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::Base;

    Iterator findNextTheSame(const Iterator& a_prev) const noexcept;
    void RemoveEx(const Iterator& a_iter) noexcept;

private:
    PureHash(const PureHash&) = delete;
    PureHash(PureHash&&) = delete;
    PureHash& operator=(const PureHash&) = delete;
    PureHash& operator=(PureHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_purehash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_HPP
