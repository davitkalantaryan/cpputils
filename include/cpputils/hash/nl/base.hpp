//
// repo:            cpputils
// file:			base.hpp
// path:			include/cpputils/hash/base.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/base.hpp>


namespace cpputils { namespace hash{ namespace nl{


template <typename TypeIterCont>
class BaseNl : public hash::Base<TypeIterCont>
{
public:
    using hash::Base<TypeIterCont>::Base;

public:
    CinternalHashConst_t getConstHash()const noexcept;

protected:
    BaseNl(const BaseNl&) = delete;
    BaseNl(BaseNl&&) = delete;
    BaseNl& operator=(const BaseNl&) = delete;
    BaseNl& operator=(BaseNl&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace nl{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_nl_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_NL_BASE_HPP
