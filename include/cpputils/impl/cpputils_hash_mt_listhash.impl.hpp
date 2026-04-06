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
void ListHash::MoveToStartNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    m_nsHash.template MoveToStart<TypeData>(a_iter);
}


template <typename TypeData>
void ListHash::MoveToEndNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    m_nsHash.template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeData>
void ListHash::iterateBegToEnd(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept
{
    bool bContinue = true;
    Iterator<TypeData> item, itemNext;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        item = m_nsHash.template first<TypeData>();
        while (bContinue && item) {
            itemNext = (Iterator<TypeData>)item->next;
            bContinue = a_iterFunc(item->data);
            item = itemNext;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
void ListHash::iterateEndToBeg(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept
{
    bool bContinue = true;
    Iterator<TypeData> item, itemPrev;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        item = m_nsHash.template last<TypeData>();
        while (bContinue && item) {
            itemPrev = (Iterator<TypeData>)item->prev;
            bContinue = a_iterFunc(item->data);
            item = itemPrev;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
size_t ListHash::count()const noexcept
{
    size_t unCount;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        unCount = m_nsHash.template count<TypeData>();
    }  //  lock guard ends

    return unCount;
}


template <typename TypeData>
void ListHash::IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    bool bContinue = true;
    Iterator<TypeData> item, itemNext;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        item = m_nsHash.template first<TypeData>();
        while (bContinue && item) {
            itemNext = (Iterator<TypeData>)item->next;
            bContinue = a_iterFunc(item);
            item = itemNext;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
void ListHash::IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    bool bContinue = true;
    Iterator<TypeData> item, itemPrev;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        item = m_nsHash.template last<TypeData>();
        while (bContinue && item) {
            itemPrev = (Iterator<TypeData>)item->prev;
            bContinue = a_iterFunc(item);
            item = itemPrev;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
inline void ListHash::RemoveExNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    m_nsHash.template RemoveEx<TypeData>(a_iter);
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
