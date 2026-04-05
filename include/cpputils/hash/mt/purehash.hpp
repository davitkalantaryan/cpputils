//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/mt/purehash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/purehash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <shared_mutex>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


class CPPUTILS_EXPORT MtPureHash
{
public:
    template <typename TypeData>
    using Iterator = ::cpputils::hash::PureHash::Iterator<TypeData>;
    template <typename TypeData>
    using TypeIterFunc = ::std::function<bool(TypeData&)>;  // true -> continue, false stop

public:
    MtPureHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

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
    inline void RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    bool Remove(const TypeKey& a_key) noexcept;

    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

protected:
    ::cpputils::hash::PureHash  m_nsHash;
    mutable ::std::shared_mutex m_mutex;

private:
    MtPureHash(const MtPureHash&) = delete;
    MtPureHash(MtPureHash&&) = delete;
    MtPureHash& operator=(const MtPureHash&) = delete;
    MtPureHash& operator=(MtPureHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_purehash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_PUREHASH_HPP
