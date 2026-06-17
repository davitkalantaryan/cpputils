//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/templ/listhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/mt/base.hpp>
#include <cpputils/hash/mt/listhash.hpp>


namespace cpputils { namespace hash{ namespace templ{ namespace mt{ 


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using ListHashBase = hash::templ::mt::BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using ListHash = hash::templ::mt::ListHashBase<hash::mt::ListHash, TypeData, TypeKey, TypeKeyExt>;


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace mt{
