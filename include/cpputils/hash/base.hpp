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
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>

#ifdef _MSC_VER
#pragma warning(disable: 4820)
#endif


namespace cpputils { namespace hash{


#define CPPUTILS_HASH_CHI(_typeInt)  _typeInt,::cpputils::hash::bh::SKeyInt<_typeInt>


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


template <typename TypeChild, typename TypeKey>
struct SKeyExtBase : public CKeyBase
{
public:
    virtual CKeyBase* clone(TypeCinternalAllocator a_allocator)const override;
    virtual uint64_t hash()const override;
    virtual bool areTheKeysSame(const CKeyBase& a_key2) const override;

protected:
    const TypeKey      rawKey;
public:
    SKeyExtBase(const TypeKey& a_rawKey, int32_t a_dataIndex);
protected:
    virtual ~SKeyExtBase() override = default;
    SKeyExtBase(const SKeyExtBase&) = default;
    SKeyExtBase(SKeyExtBase&&) = delete;
    SKeyExtBase& operator=(const SKeyExtBase&) = delete;
    SKeyExtBase& operator=(SKeyExtBase&&) = delete;
};


template <typename TypeKey>
struct SKeyAny : public SKeyExtBase<SKeyAny<TypeKey>, TypeKey>
{
public:
    using SKeyExtBase<SKeyAny<TypeKey>, TypeKey>::SKeyExtBase;
};


template <typename TypeIntKey>
struct SKeyInt : public SKeyAny<TypeIntKey>
{
public:
    using SKeyAny<TypeIntKey>::SKeyAny;
    uint64_t hash()const override;
private:
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
};


template <typename TypeBase, typename TypeData>
class Item : public TypeBase
{
public:
    mutable TypeData    data;
public:
    virtual ~Item() override = default;
    template<typename... Targs>
    Item(Targs... a_args);
protected:
    Item() = default;
    Item(const Item&) = delete;
    Item(Item&&) = delete;
    Item& operator=(const Item&) = delete;
    Item& operator=(Item&&) = delete;
};


}  //  namespace bh{


template <typename TypeIterCont>
class CPPUTILS_EXPORT Base
{
public:
    template <typename TypeData>
    using Item = typename TypeIterCont::template Item<TypeData>;
    template <typename TypeData>
    using Iterator = const Item<TypeData>*;
    template <typename TypeData>
    using IteratorRaw = Iterator<TypeData>;

public:
    ~Base() noexcept;
    Base(bh::Hash_p* CPPUTILS_ARG_NN a_clhash_data_p);

public:
    template <typename TypeData>
    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    inline const Item<TypeData>* findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    inline const Item<TypeData>* find(const TypeKey& a_key)const noexcept;
    template <typename TypeData>
    inline const Item<TypeData>* findNextTheSame( const Iterator<TypeData>& a_prev ) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs >
    inline const Item<TypeData>* AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args);
    template <typename TypeData, typename TypeKey,  typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs >
    inline const Item<TypeData>* AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename TypeData, typename TypeKey,  typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs >
    inline const Item<TypeData>* AddIfNotExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename TypeData>
    inline void RemoveEx(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData, typename TypeKey,  typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    inline bool Remove(const TypeKey& a_key) noexcept;
    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

protected:
    bh::Hash_p* const   m_clhash_data_p;

protected:
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
