//
// repo:            cpputils
// file:			cpputils_hash_mt_base.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_mt_base.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_HPP
#include <cpputils/hash/mt/base.hpp>
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <mutex>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


template <typename TypeHash>
Base<TypeHash>::Base(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_nsHash(a_numberOfBaskets, a_allocator, a_deallocator)
{
}


template <typename TypeHash>
template <typename TypeData>
inline int32_t Base<TypeHash>::reserveUniqueIdForDataInline(void) const noexcept
{
    return m_nsHash.template reserveUniqueIdForDataInline<Iterator<TypeData> >();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline typename Base<TypeHash>::template Iterator<TypeData> Base<TypeHash>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash) const noexcept
{
    const ItemRaw<Iterator<TypeData> >* itemRaw;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        itemRaw = m_nsHash.template findEx<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt>(a_key, a_pHash);
        if (itemRaw) {
            retIter = itemRaw->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline typename Base<TypeHash>::template Iterator<TypeData> Base<TypeHash>::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, &unHash);
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline void Base<TypeHash>::AddWithKnownHashIt(size_t a_hash, const TypeKey& a_key, const Iterator<TypeData>& a_iter)
{
    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        m_nsHash.template AddWithKnownHash<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt, const Iterator<TypeData>& >(a_hash, a_key,a_iter);
    }  //  lock guard ends
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline void Base<TypeHash>::AddEvenIfExistIt(const TypeKey& a_key, const Iterator<TypeData>& a_iter)
{
    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        m_nsHash.template AddEvenIfExist<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt, const Iterator<TypeData>& >(a_key, a_iter);
    }  //  lock guard ends
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline typename Base<TypeHash>::template Iterator<TypeData> Base<TypeHash>::AddIfNotExistIt(const TypeKey& a_key, const Iterator<TypeData>& a_iter)
{
    const ItemRaw<Iterator<TypeData> >* itemRaw;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        itemRaw = m_nsHash.template AddIfNotExist<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt, const Iterator<TypeData>& >(a_key, a_iter);
        if (itemRaw) {
            return itemRaw->data;
        }
    }  //  lock guard ends

    return Iterator<TypeData>();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt, typename... Targs >
inline typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash>::template Iterator<TypeData> > ::type
Base<TypeHash>::AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args)
{
    Iterator<TypeData> newData(new TypeData(::std::forward<Targs>(a_args)...) );
    AddWithKnownHashIt<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_hash,a_key, newData);
    return newData;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt, typename... Targs >
inline typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash>::template Iterator<TypeData> > ::type
Base<TypeHash>::AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args)
{
    Iterator<TypeData> newData(new TypeData(::std::forward<Targs>(a_args)...));
    AddEvenIfExistIt<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, newData);
    return newData;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt, typename... Targs >
inline typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash>::template Iterator<TypeData> > ::type
Base<TypeHash>::AddIfNotExist(const TypeKey& a_key, Targs&&... a_args)
{
    Iterator<TypeData> newData(new TypeData(::std::forward<Targs>(a_args)...));
    return AddIfNotExistIt<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, newData);
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline bool Base<TypeHash>::Remove(const TypeKey& a_key) noexcept
{
    bool bRet;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        bRet = m_nsHash.template Remove<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt>(a_key);
    }  //  lock guard ends

    return bRet;
}


template <typename TypeHash>
ConstCinternalHash_t Base<TypeHash>::getHash()const
{
    return m_nsHash.getHash();
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_IMPL_HPP
