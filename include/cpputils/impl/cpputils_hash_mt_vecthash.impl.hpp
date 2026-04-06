//
// repo:            cpputils
// file:			cpputils_hash_mt_vecthash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_mt_vecthash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP
#include <cpputils/hash/mt/vecthash.hpp>
#endif


namespace cpputils { namespace hash{ namespace mt{



template <typename TypeData>
void VectHash::MoveToStartNoLockFromIterator(const IteratorRaw<TypeData>& a_iter) noexcept
{
    m_nsHash.template MoveToStart<TypeData>(a_iter);
}


template <typename TypeData>
void VectHash::MoveToEndNoLockFromIterator(const IteratorRaw<TypeData>& a_iter) noexcept
{
    m_nsHash.template MoveToEnd<TypeData>(a_iter);
}


template <typename TypeData>
void VectHash::iterateBegToEnd(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept
{
    bool bContinue = true;
    ptrdiff_t unCountMin1;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<TypeData>();
    const vh::SVectData& vectData = m_nsHash.template getVectDataForTypeData<TypeData>();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        unCountMin1 = (ptrdiff_t)(vectData.m_count) - 1;
        for (ptrdiff_t i(unCountMin1); bContinue && (i >= 0); --i) {
            bContinue = a_iterFunc(((IteratorRaw<TypeData>)vectData.m_items_p[i])->data);
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends
}


template <typename TypeData>
void VectHash::iterateEndToBeg(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept
{
    bool bContinue = true;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<TypeData>();
    const vh::SVectData& vectData = m_nsHash.template getVectDataForTypeData<TypeData>();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        for (size_t i(0); bContinue && (i < (vectData.m_count)); ++i) {
            bContinue = a_iterFunc(((IteratorRaw<TypeData>)vectData.m_items_p[i])->data);
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends
}


template <typename TypeData>
size_t VectHash::count()const noexcept
{
    size_t unCount;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        unCount = m_nsHash.template count<TypeData>();
    }  //  lock guard ends

    return unCount;
}


template <typename TypeData>
void VectHash::IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    bool bContinue = true;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<TypeData>();
    const vh::SVectData& vectData = m_nsHash.template getVectDataForTypeData<TypeData>();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        for (size_t i(0); bContinue && (i < (vectData.m_count)); ++i) {
            bContinue = a_iterFunc((IteratorRaw<TypeData>)vectData.m_items_p[i]);
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends
}


template <typename TypeData>
void VectHash::IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    bool bContinue = true;
    ptrdiff_t unCountMin1;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<TypeData>();
    const vh::SVectData& vectData = m_nsHash.template getVectDataForTypeData<TypeData>();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        unCountMin1 = (ptrdiff_t)(vectData.m_count) - 1;
        for (ptrdiff_t i(unCountMin1); bContinue && (i >=0); --i) {
            bContinue = a_iterFunc((IteratorRaw<TypeData>)vectData.m_items_p[i]);
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends    
}


template <typename TypeData>
inline void VectHash::RemoveExNoLockFromIterator(const IteratorRaw<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept
{
    m_nsHash.template RemoveEx<TypeData>(a_iter);
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::first()const noexcept
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template first<Iterator<TypeData> >();
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::last()const noexcept
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template last<Iterator<TypeData> >();
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::at(size_t a_index)const noexcept
{
    const ItemRaw<Iterator<TypeData> >* retItem;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        retItem = m_nsHash.template at<Iterator<TypeData> >(a_index);
        if (retItem) {
            retIter = retItem->data;
        }
    }  //  lock guard ends

    return retIter;
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_IMPL_HPP
