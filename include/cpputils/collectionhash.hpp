//
// repo:            cpputils
// file:			collectionhash.hpp
// path:			include/cpputils/collectionhash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONHASH_HPP


#include <cpputils/export_symbols.h>
#include <cinternal/hash.h>
#include <cinternal/disable_compiler_warnings.h>
#include <memory>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace collectionhash{

#define CPPUTILS_CHI(_typeInt)  _typeInt,::std::hash<_typeInt>, ::cpputils::collectionhash::SKeyInt<_typeInt>

class CPPUTILS_EXPORT Hash_p;

// below structs shall have following member functions
// 1. constructor(const TypeKey& a_rawKey)
// 2. copy constructor
// 3. size_t hash()const
// 4. void CallKeyDestructor(void* a_rawKey);
// 5. bool areTheKeysSame(const void* a_rawKey1, const void* a_rawKey2);

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


class CPPUTILS_EXPORT Hash
{
public:
    template <typename TypeData>
    struct Item;
    template <typename TypeData>
    using Iterator = const Item<TypeData>*;

public:
    ~Hash() noexcept;
    Hash(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    inline int32_t getReserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeKey, typename TypeHasher = ::std::hash<TypeKey> >
    inline int32_t getReserveUniqueIdForKeyAndHasherInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> find(const TypeKey& a_key)const noexcept;
    template <typename TypeData>
    Iterator<TypeData> findNextTheSame( const Iterator<TypeData>& CPPUTILS_ARG_NN a_prev ) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    Iterator<TypeData> AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    template <typename TypeData>
    inline void RemoveEx(const Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = SKeyAny<TypeKey,TypeHasher> >
    bool Remove(const TypeKey& a_key) noexcept;

    // do not use below function to manipulate hash directly
    ConstCinternalHash_t getHash()const;

public:
    template <typename TypeData>
    struct Item {
        //struct Item *prev, *next;
        TypeData*    data_p;

    protected:
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
    };

protected:
    Hash_p* const   m_clhash_data_p;

private:
    Hash(const Hash&) = delete;
    Hash(Hash&&) = delete;
    Hash& operator=(const Hash&) = delete;
    Hash& operator=(Hash&&) = delete;
};


}}  //  namespace cpputils { namespace collectionhash{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_COLLECTIONHASH_IMPL_HPP
#include <cpputils/impl/cpputils_collectionhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_COLLECTIONHASH_HPP
