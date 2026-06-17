//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/mt/purehash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#include <cpputils/export_symbols.h>
#include <cpputils/hash/mt/base.hpp>
#include <cpputils/hash/nl/purehash.hpp>


namespace cpputils { namespace hash{ namespace mt{


typedef hash::mt::BaseMt<hash::nl::PureHash> PureHash;


}}}  //  namespace cpputils { namespace hash{ namespace mt{
