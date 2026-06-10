//
// repo:            cpputils
// file:			cpputils_hash_templ_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_templ_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_IMPL_HPP 

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_HPP
#include <cpputils/hash/templ/nl/base.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{ namespace nl{


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
CinternalHashConst_t BaseTemplNl<TypeNlHash,TypeData,TypeKey,TypeKeyExt>::getConstHash() const noexcept
{
    return hash::templ::BaseTempl<TypeNlHash, TypeData, TypeKey, TypeKeyExt>::m_hash_p->getConstHash();
}


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_BASE_IMPL_HPP
