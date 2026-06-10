//
// repo:            cpputils
// file:			cpputils_hash_templ_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_templ_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_IMPL_HPP 

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_MT_BASE_HPP
#include <cpputils/hash/templ/mt/base.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{ namespace mt{


template <typename TypeMtHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMt<TypeMtHash,TypeData,TypeKey,TypeKeyExt>::RemoveExNoLockFromIterator(const Iterator& a_iter)
{
    hash::templ::BaseTempl<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::m_hash_p->template RemoveExNoLockFromIterator<TypeData>(a_iter);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::iterateBegToEnd(const TypeIterFunc& a_iterFunc) const
{
    hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::m_hash_p->template iterateBegToEnd<TypeData, TypeKey, TypeKeyExt>(a_iterFunc);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::iterateEndToBeg(const TypeIterFunc& a_iterFunc) const
{
    hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::m_hash_p->template iterateEndToBeg<TypeData, TypeKey, TypeKeyExt>(a_iterFunc);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::IterateBegToEnd(const TypeIterFuncChng& a_iterFunc)
{
    hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::m_hash_p->template IterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::IterateEndToBeg(const TypeIterFuncChng& a_iterFunc)
{
    hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::m_hash_p->template IterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::MoveToStartNoLockFromIterator(const Iterator& a_iter) noexcept
{
    hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::m_hash_p->template MoveToStartNoLockFromIterator<TypeData>(a_iter);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMtListAndVect<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::MoveToEndNoLockFromIterator(const Iterator& a_iter) noexcept
{
    hash::templ::BaseTemplListAndVect<hash::templ::mt::BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt> >::m_hash_p->template MoveToEndNoLockFromIterator<TypeData>(a_iter);
}


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
