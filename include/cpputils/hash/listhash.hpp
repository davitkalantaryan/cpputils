//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/listhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cinternal/hash.h>
#include <cinternal/disable_compiler_warnings.h>
#include <memory>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>

#ifdef _MSC_VER
#pragma warning(disable: 4820)
#endif


namespace cpputils { namespace hash{

#define CPPUTILS_LHCHI(_typeInt)  _typeInt,::std::hash<_typeInt>, ::cpputils::hash::lh::SKeyInt<_typeInt>

class CPPUTILS_EXPORT ListHash;

namespace lh{

class CPPUTILS_EXPORT Hash_p;

class CPPUTILS_EXPORT CKeyBase
{
public:
    virtual ~CKeyBase() = default;

protected:
    CKeyBase(int32_t a_dataIndex);

public:
    virtual uint64_t hash()const = 0;
    virtual bool areTheKeysSame(const CKeyBase& a_key2) const = 0;
    virtual CKeyBase* clone(TypeCinternalAllocator a_allocator)const=0;
public:
    const int32_t   dataIndex;

protected:
    CKeyBase(const CKeyBase&)=default;
    CKeyBase(CKeyBase&&) = delete;
    CKeyBase& operator=(const CKeyBase&) = delete;
    CKeyBase& operator=(CKeyBase&&) = delete;
};


template <typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
struct SKeyAny : public CKeyBase
{
public:
    SKeyAny(const TypeKey& a_rawKey, int32_t a_dataIndex);
    uint64_t hash()const override;
    bool areTheKeysSame(const CKeyBase& a_key2) const override;
    CKeyBase* clone(TypeCinternalAllocator a_allocator)const override;
private:
    const TypeKey      rawKey;
};


template <typename TypeIntKey>
struct SKeyInt : public CKeyBase
{
public:
    SKeyInt(const TypeIntKey& a_rawKey, int32_t a_dataIndex);
    uint64_t hash()const override;
    bool areTheKeysSame(const CKeyBase& a_key2) const override;
    CKeyBase* clone(TypeCinternalAllocator a_allocator)const override;
private:
    const TypeIntKey    rawKey;
};


class CPPUTILS_EXPORT ItemBase
{
protected:
    CinternalHashItem_t     hashIter;

protected:
    virtual ~ItemBase() = default;
    ItemBase() = default;
    ItemBase(const ItemBase&) = delete;
    ItemBase(ItemBase&&) = delete;
    ItemBase& operator=(const ItemBase&) = delete;
    ItemBase& operator=(ItemBase&&) = delete;
    friend class Hash_p;
    friend class ListHash;
};


}  //  namespace lh{


class CPPUTILS_EXPORT ListHash
{
public:
    template <typename TypeData>
    struct Item;
    template <typename TypeData>
    using Iterator = const Item<TypeData>*;

public:
    ~ListHash() noexcept;
    ListHash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData>
    Iterator<TypeData> findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData>
    inline void RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = lh::SKeyAny<TypeKey,TypeHasher> >
    bool Remove(const TypeKey& a_key) noexcept;

    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData>
    Iterator<TypeData> first()const noexcept;
    template <typename TypeData>
    Iterator<TypeData> last()const noexcept;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);

public:
    template <typename TypeData>
    struct Item : public lh::ItemBase {
        struct Item *prev, *next;
        mutable TypeData    data;

    protected:
        Item(TypeData* CPPUTILS_ARG_NN a_data_p);
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
        friend class ListHash;
    };

protected:
    lh::Hash_p* const   m_clhash_data_p;

private:
    ListHash(const ListHash&) = delete;
    ListHash(ListHash&&) = delete;
    ListHash& operator=(const ListHash&) = delete;
    ListHash& operator=(ListHash&&) = delete;
};


}}  //  namespace cpputils { namespace hash{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_LISTHASH_HPP
