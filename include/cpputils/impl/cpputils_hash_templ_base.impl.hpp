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


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
typename Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    return m_hash_p->template findEx<TypeData,TypeKey,TypeKeyExt>(a_key,a_pHash);
}


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt >
typename Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Iterator
Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::find(const TypeKey& a_key)const noexcept
{
    return m_hash_p->template find<TypeData,TypeKey,TypeKeyExt>(a_key);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator >::type
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddWithKnownHash<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_hash,a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator >::type
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddEvenIfExist<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
template <typename... Targs>
typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator >::type
Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::AddIfNotExist(const TypeKey& a_key, Targs&&... a_args)
{
    return m_hash_p->template AddIfNotExist<TypeData, TypeKey, TypeKeyExt, Targs&&...>(a_key, ::std::forward<Targs>(a_args)...);
}


template <typename TypeHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
bool Base<TypeHash,TypeData,TypeKey,TypeKeyExt>::Remove(const TypeKey& a_key) noexcept
{
    return m_hash_p->template Remove<TypeData,TypeKey,TypeKeyExt>(a_key);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void 
MtBase<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::AddWithKnownHashIt(size_t a_hash, const TypeKey& a_key, const Iterator& a_iter)
{
    this->m_hash_p->template AddWithKnownHashIt<TypeData, TypeKey, TypeKeyExt>(a_hash, a_key, a_iter);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
void
MtBase<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::AddEvenIfExistIt(const TypeKey& a_key, const Iterator& a_iter)
{
    this->m_hash_p->template AddEvenIfExistIt<TypeData, TypeKey, TypeKeyExt>(a_key, a_iter);
}


template <typename TypeMtHash, typename TypeData, typename TypeKey, typename TypeKeyExt >
typename MtBase<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::Iterator
MtBase<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::AddIfNotExistIt(const TypeKey& a_key, const Iterator& a_iter)
{
    return this->m_hash_p->template AddIfNotExistIt<TypeData, TypeKey, TypeKeyExt>(a_key, a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
