//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/templ/vecthash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/mt/base.hpp>
#include <cpputils/hash/mt/vecthash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace mt{ 


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using VectHashBase = hash::templ::mt::BaseTemplMtVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using VectHash = hash::templ::mt::VectHashBase<hash::mt::VectHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace mt{ 
