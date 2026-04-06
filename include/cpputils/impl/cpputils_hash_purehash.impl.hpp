//
// repo:            cpputils
// file:			cpputils_hash_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_HPP
#include <cpputils/hash/purehash.hpp>
#endif


namespace cpputils { namespace hash{


template <typename TypeData>
Cph::Item<TypeData>::Item(TypeData* CPPUTILS_ARG_NN a_data_p)
    :
    data(::std::move(*a_data_p))
{
}


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
