//
// repo:            cpputils
// file:			cpputils_hash_purehash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_purehash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP
#include <cpputils/hash/templ/listhash.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter,TypeData,TypeKey,TypeHasher,TypeKeyExt>::MoveToStart(const TypeIter& CPPUTILS_ARG_NN a_iter) noexcept
{
    BaseR::m_hash_p->template MoveToStart<TypeData>(a_iter);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::MoveToEnd(const TypeIter& CPPUTILS_ARG_NN a_iter) noexcept
{
    BaseR::m_hash_p->template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
TypeIter ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::first() const noexcept
{
    BaseR::m_hash_p->template first<TypeData>();
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
TypeIter ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::last() const noexcept
{
    BaseR::m_hash_p->template last<TypeData>();
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
size_t ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::count() const noexcept
{
    return BaseR::m_hash_p->template count<TypeData>();
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    BaseR::m_hash_p->AllocateListsInAdvance(a_numberOfLists);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_IMPL_HPP
