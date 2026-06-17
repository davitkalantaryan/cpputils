//
// repo:            cpputils
// file:			cpputils_hash_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_HPP
#include <cpputils/hash/nl/base.hpp>
#endif

namespace cpputils { namespace hash{ namespace nl{


template <typename TypeIterCont>
CinternalHashConst_t BaseNl<TypeIterCont>::getConstHash()const noexcept
{
    return hash::Base<TypeIterCont>::m_clhash_data_p->m_hash;
}


}}}  //  namespace cpputils { namespace hash{ namespace nl{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_IMPL_HPP
