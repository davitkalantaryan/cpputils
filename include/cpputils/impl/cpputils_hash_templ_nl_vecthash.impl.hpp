//
// repo:            cpputils
// file:			cpputils_hash_templ_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_templ_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_IMPL_HPP 

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_HPP
#include <cpputils/hash/templ/nl/vecthash.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{ namespace nl{


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
const hash::nl::vh::SVectData& VectHashBase<TypeNlHash, TypeData, TypeKey, TypeKeyExt>::getVectDataForTypeData() const noexcept
{
    return hash::templ::nl::BaseTemplNlVect<TypeNlHash, TypeData, TypeKey, TypeKeyExt>::m_hash_p->getVectDataForTypeData<TypeData>();
}


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_IMPL_HPP
