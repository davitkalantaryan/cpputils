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


template <typename TypeData, typename TypeKey, typename TypeKeyExt >
typename PureHash<TypeData, TypeKey, TypeKeyExt>::IteratorRaw
PureHash<TypeData, TypeKey, TypeKeyExt>::findNextTheSameNoLockFromIterator(const IteratorRaw&  a_prev)const noexcept
{
    return this->m_hash_p->template findNextTheSameNoLockFromIterator<TypeData>(a_prev);
}


template <typename TypeData, typename TypeKey, typename TypeKeyExt >
void PureHash<TypeData, TypeKey, TypeKeyExt>::RemoveExNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template RemoveExNoLockFromIterator<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_PUREHASH_IMPL_HPP
