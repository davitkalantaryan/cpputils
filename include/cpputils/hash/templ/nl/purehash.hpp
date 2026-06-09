//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/templ/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/nl/base.hpp>
#include <cpputils/hash/nl/purehash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace nl{


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using PureHashBase = hash::templ::nl::BaseTemplNl<TypeNlHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using PureHash = hash::templ::nl::PureHashBase<hash::nl::PureHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{
