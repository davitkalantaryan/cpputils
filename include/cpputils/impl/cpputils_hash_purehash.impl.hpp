//
// repo:            cpputils
// file:			cpputils_hash_purehash.impl.hpp
// path:			include/cpputils/impl/cpputils_hash_purehash.impl.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_HPP
#include <cpputils/hash/purehash.hpp>
#endif


namespace cpputils { namespace hash{



template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
inline typename PureHash::Iterator<TypeData>
PureHash::findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept
{
    return findExRaw<Item<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_key, a_pHash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::find(const TypeKey& a_key)const noexcept
{
    size_t unHash;
    return findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key, &unHash);
}


template <typename TypeData>
typename PureHash::Iterator<TypeData>
PureHash::findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept
{
    return findNextTheSameRaw<Item<TypeData> >(a_prev);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash)
{
    TypeData aData(a_data);
    return AddWithKnownHashRaw<Item<TypeData>,TypeData,TypeKey,TypeHasher,TypeKeyExt>(&aData, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash)
{
    return AddWithKnownHashRaw<Item<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key, a_hash);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddEvenIfExistRaw<Item<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    return AddEvenIfExistRaw<Item<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddIfNotExist(const TypeData& a_data, const TypeKey& a_key)
{
    TypeData aData(a_data);
    return AddIfNotExistRaw<Item<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>(&aData, a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt >
typename PureHash::Iterator<TypeData>
PureHash::AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key)
{
    return AddIfNotExistRaw<Item<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>(a_data_p, a_key);
}


template <typename TypeData, typename TypeKey, typename TypeHasher, typename TypeKeyExt>
bool PureHash::Remove(const TypeKey& a_key) noexcept
{
    size_t unHash;
    const Iterator<TypeData> iter = findEx<TypeData,TypeKey,TypeHasher,TypeKeyExt>(a_key,&unHash);
    if(iter){
        RemoveEx<TypeData>(iter);
        return true;
    }
    return false;
}


}}  //  namespace cpputils { namespace collectionhash{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
