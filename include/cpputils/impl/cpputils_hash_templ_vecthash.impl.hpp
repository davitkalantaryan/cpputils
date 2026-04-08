//
// repo:            cpputils
// file:			cpputils_hash_purehash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_purehash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_HPP
#include <cpputils/hash/templ/vecthash.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
size_t VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::count() const noexcept
{
    return this->m_hash_p->template count<TypeData>();
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    this->m_hash_p->AllocateListsInAdvance(a_numberOfLists);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData,TypeKey,TypeHasher,TypeKeyExt>::MoveToStart(const Iterator& a_iter) noexcept
{
    this->m_hash_p->template MoveToStart<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash,typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::MoveToEnd(const Iterator& a_iter) noexcept
{
    this->m_hash_p->template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::Iterator
VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::first() const noexcept
{
    return this->m_hash_p->template first<TypeData>();
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::Iterator
VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::last() const noexcept
{
    return this->m_hash_p->template last<TypeData>();
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::Iterator
VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::at(size_t a_index) const noexcept
{
    return this->m_hash_p->template at<TypeData>(a_index);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::iterateBegToEnd(const TypeIterFunc& a_iterFunc) const noexcept
{
    this->m_hash_p->template iterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::iterateEndToBeg(const TypeIterFunc& a_iterFunc) const noexcept
{
    this->m_hash_p->template iterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::IterateBegToEnd(const TypeIterFuncChng& a_iterFunc)
{
    this->m_hash_p->template IterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::IterateEndToBeg(const TypeIterFuncChng& a_iterFunc)
{
    this->m_hash_p->template IterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::RemoveExNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template RemoveExNoLockFromIterator<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::MoveToStartNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template MoveToStartNoLockFromIterator<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::MoveToEndNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template MoveToEndNoLockFromIterator<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_IMPL_HPP
