//
// repo:            cpputils
// file:			cpputils_hash_mt_purehash.impl.hpp
// path:			include/cpputils/cpputils_hash_mt_purehash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_HPP
#include <cpputils/hash/purehash.hpp>
#endif


namespace cpputils { namespace hash{ namespace mt{



template <typename TypeData>
inline int32_t MtPureHash::reserveUniqueIdForDataInline(void) const noexcept {
    return m_nsHash.reserveUniqueIdForDataInline();
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    MtPureHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template findEx<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, a_pHash);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key, &unHash);
}


template <typename TypeData>
typename MtPureHash::Iterator<TypeData>
MtPureHash::findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept
{
    MtPureHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template findNextTheSame<TypeData>(a_prev);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    MtPureHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        retItem = m_nsHash.template AddWithKnownHash<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key, a_hash);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    MtPureHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        retItem = m_nsHash.template AddEvenIfExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtPureHash::Iterator<TypeData>
MtPureHash::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    MtPureHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template AddIfNotExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt>
bool MtPureHash::Remove(const TypeKey& a_key) noexcept
{
    bool retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        retItem = m_nsHash.template Remove<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData>
inline void MtPureHash::RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
    m_nsHash.template RemoveEx<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_IMPL_HPP
