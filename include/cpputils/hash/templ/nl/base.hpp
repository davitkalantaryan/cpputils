//
// repo:            cpputils
// file:			base.hpp
// path:			include/cpputils/hash/templ/base.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace nl{


template <typename TypeNlHash,typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class BaseTemplNl : public hash::templ::BaseTempl<TypeNlHash, TypeData, TypeKey, TypeKeyExt>
{
public:
    using BaseTempl<TypeNlHash, TypeData, TypeKey, TypeKeyExt>::BaseTempl;

    CinternalHashConst_t getConstHash()const noexcept;
};


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using BaseTemplNlListAndVect = hash::templ::BaseTemplListAndVect<hash::templ::nl::BaseTemplNl<TypeNlHash, TypeData, TypeKey, TypeKeyExt> >;


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using BaseTemplNlVect = hash::templ::BaseTemplVect<hash::templ::nl::BaseTemplNlListAndVect<TypeNlHash, TypeData, TypeKey, TypeKeyExt> >;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_nl_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_HPP
