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
BaseMt<TypeHash>::BaseMt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    m_nsHash(a_numberOfBaskets, a_allocator, a_deallocator),
    m_hashBs(m_nsHash.getConstHashBase())
{
}


template <typename TypeHash>
template <typename TypeData>
inline int32_t BaseMt<TypeHash>::reserveUniqueIdForDataInline(void) const noexcept
{
    return m_nsHash.template reserveUniqueIdForDataInline<Iterator<TypeData> >();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename BaseMt<TypeHash>::template Iterator<TypeData> BaseMt<TypeHash>::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash) const
{
    const ItemRaw<Iterator<TypeData> >* itemRaw;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        itemRaw = m_nsHash.template findEx<Iterator<TypeData>, TypeKey, TypeKeyExt>(a_key, a_pHash);
        if (itemRaw) {
            retIter = itemRaw->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt >
inline typename BaseMt<TypeHash>::template Iterator<TypeData> BaseMt<TypeHash>::find(const TypeKey& a_key)const
{
    size_t unHash;
    return findEx<TypeData, TypeKey, TypeKeyExt>(a_key, &unHash);
}


template <typename TypeHash>
template <typename TypeData >
inline typename BaseMt<TypeHash>::template Iterator<TypeData> BaseMt<TypeHash>::findNextTheSame(const Iterator<TypeData>& a_prev)const
{
    const Item<TypeData>* const pItem = a_prev.get();
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        const ItemRaw<Iterator<TypeData> >* itemRaw = nullptr;
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        if (pItem->iter) {
            itemRaw = m_nsHash.template findNextTheSame<Iterator<TypeData> >(pItem->iter);
            if (itemRaw) {
                retIter = itemRaw->data;
            }
        }  //  if (pItem->iter) {
    }  //  lock guard ends

    return retIter;
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt, typename... Targs>
inline typename BaseMt<TypeHash>::template Iterator<TypeData>
BaseMt<TypeHash>::AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args)
{
    Item<TypeData>* const pNewItem = new Item<TypeData>(::std::forward<Targs>(a_args)...);
    const Iterator<TypeData> newData(pNewItem);

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        pNewItem->iter = m_nsHash.template AddWithKnownHash<Iterator<TypeData>, TypeKey, TypeKeyExt, const Iterator<TypeData>& >(a_hash,a_key, newData);
        if (pNewItem->iter) {
            return newData;
        }
    }  //  lock guard ends

    return Iterator<TypeData>();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt, typename... Targs>
inline typename BaseMt<TypeHash>::template Iterator<TypeData>
BaseMt<TypeHash>::AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args)
{
    Item<TypeData>* const pNewItem = new Item<TypeData>(::std::forward<Targs>(a_args)...);
    const Iterator<TypeData> newData(pNewItem);

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        pNewItem->iter = m_nsHash.template AddEvenIfExist<Iterator<TypeData>, TypeKey, TypeKeyExt, const Iterator<TypeData>& >(a_key, newData);
        if (pNewItem->iter) {
            return newData;
        }
    }  //  lock guard ends

    return Iterator<TypeData>();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt, typename... Targs>
inline typename BaseMt<TypeHash>::template Iterator<TypeData>
BaseMt<TypeHash>::AddIfNotExist(const TypeKey& a_key, Targs&&... a_args)
{
    Item<TypeData>* const pNewItem = new Item<TypeData>(::std::forward<Targs>(a_args)...);
    const Iterator<TypeData> newData(pNewItem);

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        pNewItem->iter = m_nsHash.template AddIfNotExist<Iterator<TypeData>, TypeKey, TypeKeyExt, const Iterator<TypeData>& >(a_key, newData);
        if (pNewItem->iter) {
            return newData;
        }
    }  //  lock guard ends

    return Iterator<TypeData>();
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt, typename... Targs>
inline typename BaseMt<TypeHash>::template Iterator<TypeData>
BaseMt<TypeHash>::AddOrReturnExisting(const TypeKey& a_key, Targs&&... a_args)
{
    Item<TypeData>* const pNewItem = new Item<TypeData>(::std::forward<Targs>(a_args)...);
    const Iterator<TypeData> newData(pNewItem);

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        pNewItem->iter = m_nsHash.template AddIfNotExist<Iterator<TypeData>, TypeKey, TypeKeyExt, const Iterator<TypeData>& >(a_key, newData);
        if (pNewItem->iter) {
            return newData;
        }
    }  //  lock guard ends

    return Iterator<TypeData>();
}


template <typename TypeHash>
template <typename TypeData >
inline void BaseMt<TypeHash>::RemoveEx(const Iterator<TypeData>& a_iter)
{
    Item<TypeData>* const pItem = const_cast<Item<TypeData>*>(a_iter.get());

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        if (pItem->iter) {
            m_nsHash.template RemoveEx<Iterator<TypeData> >(pItem->iter);
            pItem->iter = nullptr;
        }  //  if (pItem->iter) {
    }  //  lock guard ends
}


template <typename TypeHash>
template <typename TypeData, typename TypeKey, typename TypeKeyExt >
inline bool BaseMt<TypeHash>::Remove(const TypeKey& a_key)
{
    bool bRet;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        bRet = m_nsHash.template Remove<Iterator<TypeData>, TypeKey, TypeKeyExt>(a_key);
    }  //  lock guard ends

    return bRet;
}


template <typename TypeHash>
CinternalHashConstBasic_t BaseMt<TypeHash>::getConstHashBase()const noexcept
{
    return m_hashBs;
}


template <typename TypeHash>
template <typename TypeData >
inline void BaseMt<TypeHash>::RemoveExNoLockFromIterator(const Iterator<TypeData>& a_iter)
{
    Item* const pItem = const_cast<Item*>(a_iter.get());
    if (pItem->iter) {
        m_nsHash.template RemoveEx<Iterator<TypeData> >(pItem->iter);
        pItem->iter = nullptr;
    }  //  if (pItem->iter) {
}


template <typename TypeHash>
void BaseMt<TypeHash>::callConstRawHashFunc(const FncConstRawHashCaller& a_rawHash)const
{
    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        a_rawHash(m_nsHash);
    }  //  lock guard ends
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename TypeHash>
template <typename TypeData>
typename BaseMtListAndVect<TypeHash>::template Iterator<TypeData>
BaseMtListAndVect<TypeHash>::first()const
{
    ::std::shared_lock<::std::shared_mutex>  shGuard(hash::mt::BaseMt<TypeHash>::m_mutex);
    return hash::mt::BaseMt<TypeHash>::m_nsHash.template first<Iterator<TypeData> >();
}


template <typename TypeHash>
template <typename TypeData>
typename BaseMtListAndVect<TypeHash>::template Iterator<TypeData>
BaseMtListAndVect<TypeHash>::last()const
{
    ::std::shared_lock<::std::shared_mutex>  shGuard(hash::mt::BaseMt<TypeHash>::m_mutex);
    return hash::mt::BaseMt<TypeHash>::m_nsHash.template last<Iterator<TypeData> >();
}


template <typename TypeHash>
template <typename TypeData>
size_t BaseMtListAndVect<TypeHash>::count()const noexcept
{
    return hash::mt::BaseMt<TypeHash>::m_nsHash.template count<Iterator<TypeData> >();
}


template <typename TypeHash>
void BaseMtListAndVect<TypeHash>::AllocateListsInAdvance(int32_t a_numberOfLists)
{
    ::std::lock_guard<::std::shared_mutex>  unGuard(hash::mt::BaseMt<TypeHash>::m_mutex);
    hash::mt::BaseMt<TypeHash>::m_nsHash.AllocateListsInAdvance(a_numberOfLists);
}


template <typename TypeHash>
template <typename TypeData>
void BaseMtListAndVect<TypeHash>::MoveToStart(const Iterator<TypeData>& a_iter)
{
    Item<TypeData>* const pItem = const_cast<Item<TypeData>*>(a_iter.get());

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(hash::mt::BaseMt<TypeHash>::m_mutex);
        if (pItem->iter) {
            hash::mt::BaseMt<TypeHash>::m_nsHash.template MoveToStart<Iterator<TypeData> >(pItem->iter);
        }  //  if (pItem->iter) {
    }  //  lock guard ends
}


template <typename TypeHash>
template <typename TypeData>
void BaseMtListAndVect<TypeHash>::MoveToEnd(const Iterator<TypeData>& a_iter)
{
    Item<TypeData>* const pItem = const_cast<Item<TypeData>*>(a_iter.get());

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(hash::mt::BaseMt<TypeHash>::m_mutex);
        if (pItem->iter) { 
            hash::mt::BaseMt<TypeHash>::m_nsHash.template MoveToEnd<Iterator<TypeData> >(pItem->iter);
        }  //  if (pItem->iter) {
    }  //  lock guard ends
}


template <typename TypeHash>
template <typename TypeData>
void BaseMtListAndVect<TypeHash>::MoveToStartNoLockFromIterator(const Iterator<TypeData>& a_iter) noexcept
{
    Item* const pItem = const_cast<Item*>(a_iter.get());
    if (pItem->iter) {
        hash::mt::BaseMt<TypeHash>::m_nsHash.template MoveToStart<Iterator<TypeData> >(pItem->iter);
    }  //  if (pItem->iter) {
}


template <typename TypeHash>
template <typename TypeData>
void BaseMtListAndVect<TypeHash>::MoveToEndNoLockFromIterator(const Iterator<TypeData>& a_iter) noexcept
{
    Item* const pItem = const_cast<Item*>(a_iter.get());
    if (pItem->iter) {
        hash::mt::BaseMt<TypeHash>::m_nsHash.template MoveToEnd<Iterator<TypeData> >(pItem->iter);
    }  //  if (pItem->iter) {
}


template <typename TypeHash>
template <typename TypeData>
template <typename TypeKey, typename TypeKeyExt >
const TypeKey& BaseMt<TypeHash>::Item<TypeData>::key() const noexcept
{
    return this->iter->template key<TypeKey, TypeKeyExt>();
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_IMPL_HPP
