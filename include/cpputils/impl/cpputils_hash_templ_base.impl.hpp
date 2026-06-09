//
// repo:            cpputils
// file:			cpputils_hash_templ_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_templ_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
#include <cpputils/hash/templ/base.hpp>
#endif


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::BaseTempl(TypeHash* CPPUTILS_ARG_NN a_hash_p)
    :
    m_hash_p(a_hash_p)
{
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline int32_t BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::reserveUniqueIdForDataInline(void) const noexcept
{
    return m_hash_p->template reserveUniqueIdForDataInline<TypeData>();
}


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template findEx<TypeData,TypeKey,TypeKeyExt>(a_key,a_pHash);
}


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::find(const TypeKey& a_key)const noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template find<TypeData,TypeKey,TypeKeyExt>(a_key);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::findNextTheSame(const Iterator& a_prev)const noexcept(is_some_funcs_noexcept)
{
    return this->m_hash_p->template findNextTheSame<TypeData>(a_prev);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddWithKnownHash<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_hash,a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddEvenIfExist<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::AddIfNotExist(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddIfNotExist<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::AddOrReturnExisting(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddOrReturnExisting<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
bool BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::Remove(const TypeKey& a_key) noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template Remove<TypeData,TypeKey,TypeKeyExt>(a_key);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline void BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::RemoveEx(const Iterator& a_iter) noexcept(is_some_funcs_noexcept)
{
    this->m_hash_p->template RemoveEx<TypeData>(a_iter);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::TypeKeyFncRet
BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::key(const Iterator& a_iter, bool* a_isValid_p) const noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template key<TypeData, TypeKey, TypeKeyExt>(a_iter, a_isValid_p);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
CinternalHashConstBasic_t BaseTempl<TypeHash,TypeData,TypeKey,TypeKeyExt>::getConstHashBase()const noexcept
{
    return m_hash_p->getConstHashBase();
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeBaseCls >
typename BaseTemplListAndVect<TypeBaseCls>::Iterator BaseTemplListAndVect<TypeBaseCls>::first()const noexcept(is_some_funcs_noexcept)
{
    return TypeBaseCls::m_hash_p->template first<TypeDataT>();
}


template <typename TypeBaseCls >
typename BaseTemplListAndVect<TypeBaseCls>::Iterator BaseTemplListAndVect<TypeBaseCls>::last()const noexcept(is_some_funcs_noexcept)
{
    return TypeBaseCls::m_hash_p->template last<TypeDataT>();
}


template <typename TypeBaseCls >
size_t BaseTemplListAndVect<TypeBaseCls>::count()const noexcept
{
    return TypeBaseCls::m_hash_p->template count<TypeDataT>();
}


template <typename TypeBaseCls >
void BaseTemplListAndVect<TypeBaseCls>::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    TypeBaseCls::m_hash_p->AllocateListsInAdvance(a_numberOfLists);
}


template <typename TypeBaseCls >
void BaseTemplListAndVect<TypeBaseCls>::MoveToStart(const Iterator& a_iter) noexcept(is_some_funcs_noexcept)
{
    return TypeBaseCls::m_hash_p->template MoveToStart<TypeDataT>(a_iter);
}


template <typename TypeBaseCls >
void BaseTemplListAndVect<TypeBaseCls>::MoveToEnd(const Iterator& a_iter) noexcept(is_some_funcs_noexcept)
{
    return TypeBaseCls::m_hash_p->template MoveToEnd<TypeDataT>(a_iter);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeBaseCls >
typename BaseTemplVect<TypeBaseCls>::Iterator BaseTemplVect<TypeBaseCls>::at(size_t a_index)const noexcept(is_some_funcs_noexcept)
{
    return hash::templ::BaseTemplListAndVect<TypeBaseCls>::m_hash_p->template at<TypeDataT>(a_index);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
