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


template <typename TypeData, typename TypeKey, typename TypeKeyExt>
void VectHash::iterateBegToEnd(const TypeIterFunc<TypeData, TypeKey>& a_iterFunc)const
{
    IteratorRaw<Iterator<TypeData> > item;
    bool bContinue = true;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<Iterator<TypeData> >();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        const nl::vh::SVectData& vectData = m_nsHash.getVectDataForTypeData(dataIndex);
        for (size_t i(0); bContinue && (i < (vectData.m_count)); ++i) {
            item = (IteratorRaw<Iterator<TypeData> >)vectData.m_items_p[i];
            bContinue = a_iterFunc(&(item->data.get()->data), item->data->key<TypeKey, TypeKeyExt>());
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends
}


template <typename TypeData, typename TypeKey, typename TypeKeyExt>
void VectHash::iterateEndToBeg(const TypeIterFunc<TypeData, TypeKey>& a_iterFunc)const
{
    IteratorRaw<Iterator<TypeData> > item;
    bool bContinue = true;
    ptrdiff_t unCountMin1;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<Iterator<TypeData> >();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        const nl::vh::SVectData& vectData = m_nsHash.getVectDataForTypeData(dataIndex);
        unCountMin1 = (ptrdiff_t)(vectData.m_count) - 1;
        for (ptrdiff_t i(unCountMin1); bContinue && (i >= 0); --i) { 
            item = (IteratorRaw<Iterator<TypeData> >)vectData.m_items_p[i];
            bContinue = a_iterFunc(&(item->data.get()->data), item->data->key<TypeKey, TypeKeyExt>());
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends
}


template <typename TypeData>
void VectHash::IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    IteratorRaw<Iterator<TypeData> > item;
    bool bContinue = true;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<Iterator<TypeData> >();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        const nl::vh::SVectData& vectData = m_nsHash.getVectDataForTypeData(dataIndex);
        for (size_t i(0); bContinue && (i < (vectData.m_count)); ++i) {
            item = (IteratorRaw<Iterator<TypeData> >)vectData.m_items_p[i];
            bContinue = a_iterFunc(item->data);
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends
}


template <typename TypeData>
void VectHash::IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc)
{
    IteratorRaw<Iterator<TypeData> > item;
    bool bContinue = true;
    ptrdiff_t unCountMin1;
    const int32_t dataIndex = m_nsHash.template reserveUniqueIdForDataInline<Iterator<TypeData> >();

    {  //  lock guard starts
        ::std::lock_guard<::std::shared_mutex>  unGuard(m_mutex);
        const nl::vh::SVectData& vectData = m_nsHash.getVectDataForTypeData(dataIndex);
        unCountMin1 = (ptrdiff_t)(vectData.m_count) - 1;
        for (ptrdiff_t i(unCountMin1); bContinue && (i >=0); --i) {
            item = (IteratorRaw<Iterator<TypeData> >)vectData.m_items_p[i];
            bContinue = a_iterFunc(item->data);
        }  //  for (size_t i(0); i < (m_vects_p[a_dataIndex].m_count); ++i) {
    }  //  lock guard ends    
}


template <typename TypeData>
typename VectHash::Iterator<TypeData> VectHash::at(size_t a_index)const noexcept
{
    const ItemRaw<Iterator<TypeData> >* itemRaw;
    Iterator<TypeData> retIter;

    {  //  lock guard starts
        ::std::shared_lock<::std::shared_mutex>  shGuard(m_mutex);
        itemRaw = m_nsHash.template at<Iterator<TypeData> >(a_index);
        if (itemRaw) {
            retIter = itemRaw->data;
        }
    }  //  lock guard ends

    return retIter;
}


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_IMPL_HPP
