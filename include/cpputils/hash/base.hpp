//
// repo:            cpputils
// file:			base.hpp
// path:			include/cpputils/hash/base.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_HPP


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


#define CPPUTILS_HASH_CHI(_typeInt)  _typeInt,::std::hash<_typeInt>, ::cpputils::hash::bh::SKeyInt<_typeInt>

class CPPUTILS_EXPORT Base;

namespace bh{

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
private:
    SKeyAny(const SKeyAny&) = default;
    SKeyAny(SKeyAny&&) = delete;
    SKeyAny& operator=(const SKeyAny&) = delete;
    SKeyAny& operator=(SKeyAny&&) = delete;
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
private:
    SKeyInt(const SKeyInt&) = default;
    SKeyInt(SKeyInt&&) = delete;
    SKeyInt& operator=(const SKeyInt&) = delete;
    SKeyInt& operator=(SKeyInt&&) = delete;
};


class CPPUTILS_EXPORT ItemBase
{
public:
    CinternalHashItem_t     hashIter;

public:
    virtual ~ItemBase() = default;
protected:
    ItemBase() = default;
    ItemBase(const ItemBase&) = delete;
    ItemBase(ItemBase&&) = delete;
    ItemBase& operator=(const ItemBase&) = delete;
    ItemBase& operator=(ItemBase&&) = delete;
    friend class ::cpputils::hash::Base;
};


template <typename TypeData>
struct Item : public ItemBase {
    mutable TypeData    data;

protected:
    Item(TypeData* CPPUTILS_ARG_NN a_data_p);
    Item(const Item&) = delete;
    Item(Item&&) = delete;
    Item& operator=(const Item&) = delete;
    Item& operator=(Item&&) = delete;
    friend class ::cpputils::hash::Base;
};


}  //  namespace bh{


class CPPUTILS_EXPORT Base
{
protected:
    ~Base() noexcept;
    Base(bh::Hash_p* CPPUTILS_ARG_NN a_clhash_data_p);

    template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    inline const TypeIter* findExRaw(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeIter>
    inline const TypeIter* findNextTheSameRaw( const TypeIter* CPPUTILS_ARG_NN a_prev ) const noexcept;
    template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    inline const TypeIter* AddWithKnownHashRaw(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    inline const TypeIter* AddEvenIfExistRaw(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
    inline const TypeIter* AddIfNotExistRaw(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    
public:
    template <typename TypeData>
    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeData>
    inline void RemoveEx(const bh::Item<TypeData>* CPPUTILS_ARG_NN a_iter) noexcept;
    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

protected:
    bh::Hash_p* const   m_clhash_data_p;

private:
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) = delete;
};


}}  //  namespace cpputils { namespace hash{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_BASE_HPP
