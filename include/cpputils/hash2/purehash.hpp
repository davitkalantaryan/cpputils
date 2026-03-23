//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_HPP


#include <cpputils/export_symbols.h>
#include <cinternal/hash.h>
#include <cinternal/disable_compiler_warnings.h>
#include <memory>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{

#define CPPUTILS_PHCHI(_typeInt)  _typeInt,::std::hash<_typeInt>, ::cpputils::hash::ph::SKeyInt<_typeInt>


namespace ph{

class CPPUTILS_EXPORT Hash_p;

class CKeyBase
{
public:
    virtual ~CKeyBase();
    CKeyBase(int32_t a_dataIndex, int32_t a_keyAndHashIndex);
    virtual uint64_t hash()const = 0;
    virtual bool areTheKeysSame(const CKeyBase& a_key2) const = 0;
    virtual CKeyBase* clone(TypeCinternalAllocator a_allocator)const=0;
public:
    const int32_t   dataIndex;
    const int32_t   keyAndHashIndex;
private:
    //CKeyBase(const CKeyBase&)=default;
    //CKeyBase& operator=(const CKeyBase&)=delete;
    //CKeyBase& operator=(CKeyBase&&)=delete;
};


template <typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
struct SKeyAny : public CKeyBase
{
public:
    SKeyAny(const TypeKey& a_rawKey, int32_t a_dataIndex, int32_t a_keyAndHashIndex);
    uint64_t hash()const override;
    bool areTheKeysSame(const CKeyBase& a_key2) const override;
    CKeyBase* clone(TypeCinternalAllocator a_allocator)const override;
private:
    const TypeKey      rawKey;
private:
    //SKeyAny& operator=(const SKeyAny&)=delete;
    //SKeyAny& operator=(SKeyAny&&)=delete;
};


template <typename TypeIntKey>
struct SKeyInt : public CKeyBase
{
public:
    SKeyInt(const TypeIntKey& a_rawKey, int32_t a_dataIndex, int32_t a_keyAndHashIndex);
    uint64_t hash()const override;
    bool areTheKeysSame(const CKeyBase& a_key2) const override;
    CKeyBase* clone(TypeCinternalAllocator a_allocator)const override;
private:
    const TypeIntKey    rawKey;
private:
    //SKeyAny& operator=(const SKeyAny&)=delete;
    //SKeyAny& operator=(SKeyAny&&)=delete;
};


}  //  namespace ph{


class CPPUTILS_EXPORT PureHash
{
public:
    template <typename TypeData>
    struct Item;
    template <typename TypeData>
    using Iterator = const Item<TypeData>*;

public:
    ~PureHash() noexcept;
    PureHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    inline int32_t getReserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
    inline int32_t getReserveUniqueIdForKeyAndHasherInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData>
    Iterator<TypeData> findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData>
    inline void RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = ph::SKeyAny<TypeKey,TypeHasher> >
    bool Remove(const TypeKey& a_key) noexcept;

    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

public:
    template <typename TypeData>
    struct Item {
        TypeData*    data_p;

    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
    };

protected:
    ph::Hash_p* const   m_clhash_data_p;

private:
    PureHash(const PureHash&) = delete;
    PureHash(PureHash&&) = delete;
    PureHash& operator=(const PureHash&) = delete;
    PureHash& operator=(PureHash&&) = delete;
};


}}  //  namespace cpputils { namespace hash{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_purehash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_PUREHASH_HPP
