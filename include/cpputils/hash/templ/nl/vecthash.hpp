//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/templ/vecthash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/nl/base.hpp>
#include <cpputils/hash/nl/vecthash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace nl{ 


template <typename TypeNlHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using VectHashBase = hash::templ::nl::BaseTemplNlVect<TypeNlHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using VectHash = hash::templ::nl::VectHashBase<hash::nl::VectHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace nl{ 
