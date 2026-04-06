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
    return m_nsHash.reserveUniqueIdForDataInline<TypeData>();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash) const noexcept
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template findEx<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt>(a_key, a_pHash);
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, &unHash);
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;
    Iterator<TypeData> newData(new TypeData(::std::move(*a_data_p)));

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        retItem = m_nsHash.template AddWithKnownHash<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt>(&newData,a_key, a_hash);
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHash<TypeData,TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key, a_hash);
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;
    Iterator<TypeData> newData(new TypeData(::std::move(*a_data_p)));

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        retItem = m_nsHash.template AddEvenIfExist<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt>(&newData, a_key);
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key);
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;
    Iterator<TypeData> newData(new TypeData(::std::move(*a_data_p)));

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        retItem = m_nsHash.template AddIfNotExist<Iterator<TypeData>, TypeKey, TypeHasher, TypeKeyExt>(&newData, a_key);
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline Base<TypeHash>::Iterator<TypeData> Base<TypeHash>::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExist<TypeData, TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key);
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
