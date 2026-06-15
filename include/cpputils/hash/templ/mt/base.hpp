//
// repo:            cpputils
// file:			base.hpp
// path:			include/cpputils/hash/templ/base.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace mt{


template <typename TypeMtHash,typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class BaseTemplMt : public hash::templ::BaseTempl<TypeMtHash, TypeData, TypeKey, TypeKeyExt>
{
public:
    using RawHash = typename TypeMtHash::RawHash;
    using FncLockedCaller = typename TypeMtHash::FncLockedCaller;
    using Iterator = typename BaseTempl<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::Iterator;
    static constexpr bool is_some_funcs_noexcept = TypeMtHash::is_some_funcs_noexcept;

public:
    using BaseTempl<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::BaseTempl;

    void callConstHashFuncs(const FncLockedCaller& a_sharedLockedCalee)const;
    void CallHashFuncs(const FncLockedCaller& a_uniqueLockedCalee);

protected:
    BaseTemplMt(const BaseTemplMt&) = delete;
    BaseTemplMt(BaseTemplMt&&) = delete;
    BaseTemplMt& operator=(const BaseTemplMt&) = delete;
    BaseTemplMt& operator=(BaseTemplMt&&) = delete;
};


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class BaseTemplMtListAndVect : public hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >
{
public:
    using Iterator = typename BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::Iterator;
    using TypeIterFunc = typename TypeMtHash::template TypeIterFunc<TypeData, TypeKey>;
    using TypeIterFuncChng = typename TypeMtHash::template TypeIterFuncChng<TypeData>;

public:
    using BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::BaseTemplListAndVect;

    // mt specific
    void iterateBegToEnd(const TypeIterFunc& a_iterFunc)const;
    void iterateEndToBeg(const TypeIterFunc& a_iterFunc)const;
    void IterateBegToEnd(const TypeIterFuncChng& a_iterFunc);
    void IterateEndToBeg(const TypeIterFuncChng& a_iterFunc);
};


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using BaseTemplMtVect = hash::templ::BaseTemplVect<hash::templ::mt::BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_mt_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_HPP
