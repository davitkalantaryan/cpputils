//
// repo:            cpputils
// file:			cpputils_hash_templ_purehash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_templ_purehash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
#include <cpputils/hash/templ/purehash.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash<TypeData, TypeKey, TypeHasher, TypeKeyExt>::Iterator
PureHash<TypeData, TypeKey, TypeHasher, TypeKeyExt>::findNextTheSame(const Iterator&  a_prev)const noexcept
{
    return this->m_hash_p->template findNextTheSame<TypeData>(a_prev);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void PureHash<TypeData, TypeKey, TypeHasher, TypeKeyExt>::RemoveEx(const Iterator& a_iter) noexcept
{
    this->m_hash_p->template RemoveEx<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_IMPL_HPP
