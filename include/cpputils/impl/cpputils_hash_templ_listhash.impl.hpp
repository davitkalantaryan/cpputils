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
    this->m_hash_p->template MoveToStart<TypeData>(a_iter);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::MoveToEnd(const TypeIter& CPPUTILS_ARG_NN a_iter) noexcept
{
    this->m_hash_p->template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
TypeIter ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::first() const noexcept
{
    return this->m_hash_p->template first<TypeData>();
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
TypeIter ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::last() const noexcept
{
    return this->m_hash_p->template last<TypeData>();
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
size_t ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::count() const noexcept
{
    return this->m_hash_p->template count<TypeData>();
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    this->m_hash_p->AllocateListsInAdvance(a_numberOfLists);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::iterateBegToEnd(const TypeIterFunc& a_iterFunc) const noexcept
{
    this->m_hash_p->template iterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::iterateEndToBeg(const TypeIterFunc& a_iterFunc) const noexcept
{
    this->m_hash_p->template iterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::IterateBegToEnd(const TypeIterFuncChng& a_iterFunc)
{
    this->m_hash_p->template IterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::IterateEndToBeg(const TypeIterFuncChng& a_iterFunc)
{
    this->m_hash_p->template IterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void ListHashBase<TypeHash, TypeIter, TypeData, TypeKey, TypeHasher, TypeKeyExt>::RemoveExNoLockFromIterator(const TypeIter& CPPUTILS_ARG_NN a_iter) noexcept
{
    this->m_hash_p->template RemoveExNoLockFromIterator<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_IMPL_HPP
