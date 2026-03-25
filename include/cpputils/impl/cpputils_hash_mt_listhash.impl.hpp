//
// repo:            cpputils
// file:			cpputils_collectionhash.impl.hpp
// path:			include/cpputils/cpputils_collectionhash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
#include <cpputils/hash/mt/listhash.hpp>
#endif


namespace cpputils { namespace hash{ namespace mt{



template <typename TypeData>
inline int32_t MtListHash::reserveUniqueIdForDataInline(void) const noexcept {
    return m_nsHash.reserveUniqueIdForDataInline();
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    MtListHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template findEx<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, a_pHash);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key, &unHash);
}


template <typename TypeData>
typename MtListHash::Iterator<TypeData>
MtListHash::findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept
{
    MtListHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template findNextTheSame<TypeData>(a_prev);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    MtListHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        retItem = m_nsHash.template AddWithKnownHash<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key, a_hash);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    MtListHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        retItem = m_nsHash.template AddEvenIfExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist(&aData,a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename MtListHash::Iterator<TypeData>
MtListHash::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    MtListHash::Iterator<TypeData> retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template AddIfNotExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt>
bool MtListHash::Remove(const TypeKey& a_key) noexcept
{
    bool retItem;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
        retItem = m_nsHash.template Remove<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key);
    }  //  lock guard ends

    return retItem;
}


template <typename TypeData>
inline void MtListHash::RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
    m_nsHash.template RemoveEx<TypeData>(a_iter);
}


template <typename TypeData>
void MtListHash::MoveToStart(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
    m_nsHash.template MoveToStart<TypeData>(a_iter);
}


template <typename TypeData>
void MtListHash::MoveToEnd(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    ::std::lock_guard<::std::shared_mutex>  aGuard(m_mutex);
    m_nsHash.template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeData>
void MtListHash::iterateBegToEnd(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept
{
    bool bContinue = true;
    MtListHash::Iterator<TypeData> item, itemNext;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        item = m_nsHash.template first<TypeData>();
        while (bContinue && item) {
            itemNext = item->next;
            bContinue = a_iterFunc(item->data);
            item = itemNext;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
void MtListHash::iterateEndToBeg(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept
{
    bool bContinue = true;
    MtListHash::Iterator<TypeData> item, itemPrev;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        item = m_nsHash.template last<TypeData>();
        while (bContinue && item) {
            itemPrev = item->prev;
            bContinue = a_iterFunc(item->data);
            item = itemPrev;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
size_t MtListHash::count()const noexcept
{
    size_t unCount;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        unCount = m_nsHash.template count<TypeData>();
    }  //  lock guard ends

    return unCount;
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
