//
// repo:            cpputils
// file:			base.hpp
// path:			include/cpputils/hash/mt/base.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/purehash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <shared_mutex>
#include <type_traits>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


template <typename TypeHash>
class CPPUTILS_EXPORT Base
{
public:
    template <typename TypeData>
    using Iterator = ::std::shared_ptr<TypeData>;
    template <typename TypeData>
    using IteratorRaw = typename TypeHash::template Iterator<Iterator<TypeData> >;

public:
    Base(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
    inline Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
    inline Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
    inline void AddWithKnownHashIt(size_t a_hash, const TypeKey& a_key, const Iterator<TypeData>& a_iter);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
    inline void AddEvenIfExistIt(const TypeKey& a_key, const Iterator<TypeData>& a_iter);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
    inline Iterator<TypeData> AddIfNotExistIt(const TypeKey& a_key, const Iterator<TypeData>& a_iter);
    


    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher>, typename... Targs>
    inline ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash>::template Iterator<TypeData> >::type
        AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args);

    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher>, typename... Targs>
    inline ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash>::template Iterator<TypeData> >::type
        AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args);

    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher>, typename... Targs>
    inline ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash>::template Iterator<TypeData> >::type
        AddIfNotExist(const TypeKey& a_key, Targs&&... a_args);

    
    
    
    

    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey, TypeHasher> >
    inline bool Remove(const TypeKey& a_key) noexcept;
    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

protected:
    template <typename TypeData>
    using ItemRaw = typename TypeHash::template Item<TypeData>;

protected:
    TypeHash                    m_nsHash;
    mutable ::std::shared_mutex m_mutex;

protected:
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_HPP
