//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/templ/listhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/nl/base.hpp>
#include <cpputils/hash/nl/listhash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace nl{


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using ListHashBase = hash::templ::nl::BaseTemplNlListAndVect<TypeNlHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using ListHash = hash::templ::nl::ListHashBase<hash::nl::ListHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{
