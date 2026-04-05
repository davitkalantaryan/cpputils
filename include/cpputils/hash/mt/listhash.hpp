//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/mt/listhash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/listhash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <shared_mutex>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


class CPPUTILS_EXPORT MtListHash
{
public:
    template <typename TypeData>
    using Iterator = ::cpputils::hash::ListHash::Iterator<TypeData>;
    template <typename TypeData>
    using TypeIterFunc = ::std::function<bool(TypeData&)>;  // true -> continue, false stop
    template <typename TypeData>
    using TypeIterFuncChng = ::std::function<bool(const Iterator<TypeData>&)>;  // true -> continue, false stop

public:
    MtListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData>
    Iterator<TypeData> findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData>
    inline void RemoveEx(Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    bool Remove(const TypeKey& a_key) noexcept;

    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    void iterateBegToEnd(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept;
    template <typename TypeData>
    void iterateEndToBeg(const TypeIterFunc<TypeData>& a_iterFunc)const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);
    template <typename TypeData>
    void IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc);
    template <typename TypeData>
    void IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc);
    template <typename TypeData>
    inline void RemoveExNoLockFromIterator(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;

protected:
    ::cpputils::hash::ListHash  m_nsHash;
    mutable ::std::shared_mutex m_mutex;

private:
    MtListHash(const MtListHash&) = delete;
    MtListHash(MtListHash&&) = delete;
    MtListHash& operator=(const MtListHash&) = delete;
    MtListHash& operator=(MtListHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP
