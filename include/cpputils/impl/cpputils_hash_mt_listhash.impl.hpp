//
// repo:            cpputils
// file:			cpputils_hash_mt_listhash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_mt_listhash.impl.hpp
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


template <typename TypeData, typename TypeKey, typename TypeKeyExt>
void ListHash::iterateBegToEnd(const TypeIterFunc<TypeData, TypeKey>& a_iterFunc)const
{
    bool bContinue = true;
    IteratorRaw<Iterator<TypeData> > item, itemNext;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        item = m_nsHash.template first<Iterator<TypeData> >();
        while (bContinue && item) {
            itemNext = (IteratorRaw<Iterator<TypeData> >)item->next;
            bContinue = a_iterFunc(&(item->data.get()->data), item->data->key<TypeKey, TypeKeyExt>());
            item = itemNext;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData, typename TypeKey, typename TypeKeyExt>
void ListHash::iterateEndToBeg(const TypeIterFunc<TypeData, TypeKey>& a_iterFunc)const
{
    bool bContinue = true;
    IteratorRaw<Iterator<TypeData> > item, itemPrev;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        item = m_nsHash.template last<Iterator<TypeData> >();
        while (bContinue && item) {
            itemPrev = (IteratorRaw<Iterator<TypeData> >)item->prev;
            bContinue = a_iterFunc(&(item->data.get()->data), item->data->key<TypeKey, TypeKeyExt>());
            item = itemPrev;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
void ListHash::IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    bool bContinue = true;
    IteratorRaw<Iterator<TypeData> > item, itemNext;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        item = m_nsHash.template first<Iterator<TypeData> >();
        while (bContinue && item) {
            itemNext = (IteratorRaw<Iterator<TypeData> >)item->next;
            bContinue = a_iterFunc(item->data);
            item = itemNext;
        }  //  while (item) {
    }  //  lock guard ends
}


template <typename TypeData>
void ListHash::IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    bool bContinue = true;
    IteratorRaw<Iterator<TypeData> > item, itemPrev;

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        item = m_nsHash.template last<Iterator<TypeData> >();
        while (bContinue && item) {
            itemPrev = (IteratorRaw<Iterator<TypeData> >)item->prev;
            bContinue = a_iterFunc(item->data);
            item = itemPrev;
        }  //  while (item) {
    }  //  lock guard ends
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
