//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/templ/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>
#include <cpputils/hash/purehash.hpp>
#include <cpputils/hash/mt/purehash.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using MtPureHash = templ::MtBase<hash::mt::PureHash,TypeData, TypeKey, TypeKeyExt>;

template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
using PureHash = Base<hash::PureHash, TypeData, TypeKey, TypeKeyExt>;


}}}  //  namespace cpputils { namespace hash{ namespace templ{
