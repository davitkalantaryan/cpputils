//
// repo:            cpputils
// file:			cpputils_hash_templ_vecthash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_templ_vecthash.impl.hpp
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


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
size_t VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::count() const noexcept
{
    return this->m_hash_p->template count<TypeData>();
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    this->m_hash_p->AllocateListsInAdvance(a_numberOfLists);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData,TypeKey,TypeKeyExt>::MoveToStart(const Iterator& a_iter) noexcept
{
    this->m_hash_p->template MoveToStart<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::MoveToEnd(const Iterator& a_iter) noexcept
{
    this->m_hash_p->template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
typename VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::first() const noexcept
{
    return this->m_hash_p->template first<TypeData>();
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
typename VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::last() const noexcept
{
    return this->m_hash_p->template last<TypeData>();
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
typename VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::at(size_t a_index) const noexcept
{
    return this->m_hash_p->template at<TypeData>(a_index);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::iterateBegToEnd(const TypeIterFunc& a_iterFunc) const noexcept
{
    this->m_hash_p->template iterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::iterateEndToBeg(const TypeIterFunc& a_iterFunc) const noexcept
{
    this->m_hash_p->template iterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::IterateBegToEnd(const TypeIterFuncChng& a_iterFunc)
{
    this->m_hash_p->template IterateBegToEnd<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::IterateEndToBeg(const TypeIterFuncChng& a_iterFunc)
{
    this->m_hash_p->template IterateEndToBeg<TypeData>(a_iterFunc);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::RemoveExNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template RemoveExNoLockFromIterator<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::MoveToStartNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template MoveToStartNoLockFromIterator<TypeData>(a_iter);
}


template <typename TypeBase, typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline void VectHashBase<TypeBase, TypeHash, TypeData, TypeKey, TypeKeyExt>::MoveToEndNoLockFromIterator(const IteratorRaw& a_iter) noexcept
{
    this->m_hash_p->template MoveToEndNoLockFromIterator<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_VECTHASH_IMPL_HPP
