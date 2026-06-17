//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/templ/vecthash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/nl/base.hpp>
#include <cpputils/hash/nl/vecthash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace nl{ 



template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class VectHashBase : public hash::templ::nl::BaseTemplNlVect<TypeNlHash, TypeData, TypeKey, TypeKeyExt>
{
public:
    using hash::templ::nl::BaseTemplNlVect<TypeNlHash, TypeData, TypeKey, TypeKeyExt>::BaseTemplNlVect;

    const hash::nl::vh::SVectData& getVectDataForTypeData()const noexcept;
};


template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using VectHash = hash::templ::nl::VectHashBase<hash::nl::VectHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{ 


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_nl_vecthash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_NL_VECTHASH_HPP
