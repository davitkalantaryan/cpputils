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


template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
using PureHash = Base<hash::PureHash,hash::PureHash::Iterator<TypeData>,TypeData,TypeKey,TypeHasher,TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
using MtPureHash = Base<hash::mt::PureHash, hash::mt::PureHash::Iterator<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>;


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_HPP
