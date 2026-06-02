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
Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Base(TypeHash* CPPUTILS_ARG_NN a_hash_p)
    :
    m_hash_p(a_hash_p)
{
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline int32_t Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::reserveUniqueIdForDataInline(void) const noexcept
{
    return m_hash_p->template reserveUniqueIdForDataInline<TypeData>();
}


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template findEx<TypeData,TypeKey,TypeKeyExt>(a_key,a_pHash);
}


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::find(const TypeKey& a_key)const noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template find<TypeData,TypeKey,TypeKeyExt>(a_key);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::findNextTheSame(const Iterator& a_prev)const noexcept(is_some_funcs_noexcept)
{
    return this->m_hash_p->template findNextTheSame<TypeData>(a_prev);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddWithKnownHash<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_hash,a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddEvenIfExist<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddIfNotExist(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddIfNotExist<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
inline typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddOrReturnExisting(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddOrReturnExisting<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
bool Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Remove(const TypeKey& a_key) noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template Remove<TypeData,TypeKey,TypeKeyExt>(a_key);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline void Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::RemoveEx(const Iterator& a_iter) noexcept(is_some_funcs_noexcept)
{
    this->m_hash_p->template RemoveEx<TypeData>(a_iter);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::TypeKeyFncRet
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::key(const Iterator& a_iter, bool* a_isValid_p) const noexcept(is_some_funcs_noexcept)
{
    return m_hash_p->template key<TypeData, TypeKey, TypeKeyExt>(a_iter, a_isValid_p);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
CinternalHashConstBasic_t Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::getConstHashBase()const noexcept
{
    return m_hash_p->getConstHashBase();
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
