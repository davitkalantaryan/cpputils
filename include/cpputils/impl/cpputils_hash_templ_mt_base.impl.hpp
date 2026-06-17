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


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::callConstHashFuncs(const FncLockedCaller& a_sharedLockedCalee) const
{
    hash::templ::BaseTempl<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::m_hash_p->callConstHashFuncs(a_sharedLockedCalee);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void BaseTemplMt<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::CallHashFuncs(const FncLockedCaller& a_uniqueLockedCalee)
{
    hash::templ::BaseTempl<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::m_hash_p->CallHashFuncs(a_uniqueLockedCalee);
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


}}}}  //  namespace cpputils { namespace hash{ namespace templ{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
