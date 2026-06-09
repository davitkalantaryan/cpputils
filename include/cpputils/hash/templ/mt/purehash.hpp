//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/templ/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/mt/base.hpp>
#include <cpputils/hash/mt/purehash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace mt{


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using PureHashBase = hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using PureHash = hash::templ::mt::PureHashBase<hash::mt::PureHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace mt{
