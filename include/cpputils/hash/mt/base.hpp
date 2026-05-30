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
#include <cpputils/hash/nl/base.hpp>
#ifdef CPPUTILS_USE_CPPUTILS_SHARED_PTR
#include <cpputils/sharedptr.hpp>
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <shared_mutex>
#include <type_traits>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{

template <typename TypeHash>
class CPPUTILS_EXPORT BaseMtListAndVect;

template <typename TypeHash>
class CPPUTILS_EXPORT BaseMt
{
public:
#ifdef CPPUTILS_USE_CPPUTILS_SHARED_PTR
    template <typename TypeData>
    using SharedPtr = cpputils::SharedPtr<TypeData>;
#else
    template <typename TypeData>
    using SharedPtr = ::std::shared_ptr<TypeData>;
#endif
    typedef TypeHash  RawHash;
    typedef ::std::function<void(const RawHash&)> FncConstRawHashCaller;
    template <typename TypeData>
    struct Item;
    template <typename TypeData>
    using Iterator = SharedPtr<const Item<TypeData> >;

public:
    BaseMt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator = nullptr, TypeCinternalDeallocator a_deallocator = nullptr);

    template <typename TypeData>
    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    inline Iterator<TypeData> findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    inline Iterator<TypeData> find(const TypeKey& a_key)const;
    template <typename TypeData>
    inline Iterator<TypeData> findNextTheSame(const Iterator<TypeData>& a_prev) const;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs>
    inline Iterator<TypeData> AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args);
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs>
    inline Iterator<TypeData> AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs>
    inline Iterator<TypeData> AddIfNotExist(const TypeKey& a_key, Targs&&... a_args); 
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey>, typename... Targs>
    inline Iterator<TypeData> AddOrReturnExisting(const TypeKey& a_key, Targs&&... a_args);
    template <typename TypeData >
    inline void RemoveEx(const Iterator<TypeData>& a_iter);
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    inline bool Remove(const TypeKey& a_key);
    CinternalHashConstBasic_t getConstHashBase()const noexcept;

    // specific
    template <typename TypeData >
    inline void RemoveExNoLockFromIterator(const Iterator<TypeData>& a_iter);
    void callConstRawHashFunc(const FncConstRawHashCaller& a_rawHash)const;

protected:
    template <typename TypeData>
    using ItemRaw = typename TypeHash::template Item<TypeData>;

protected:
    TypeHash                            m_nsHash;
    const CinternalHashConstBasic_t     m_hashBs;
    mutable ::std::shared_mutex         m_mutex;

protected:
    BaseMt(const BaseMt&) = delete;
    BaseMt(BaseMt&&) = delete;
    BaseMt& operator=(const BaseMt&) = delete;
    BaseMt& operator=(BaseMt&&) = delete;

public:
    template <typename TypeData>
    struct Item {
        mutable TypeData        data;
        template <typename... Targs>
        Item(Targs&&... a_args) : data(::std::forward<Targs>(a_args)...), iter(nullptr) {}
        template <typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
        const TypeKey& key() const noexcept;
    private:
        template <typename TypeData>
        using IteratorNL = typename TypeHash::template Iterator<Iterator<TypeData> >;
        IteratorNL<TypeData>    iter;
        Item(const Item&) = delete;
        Item(Item&&) = delete;
        Item& operator=(const Item&) = delete;
        Item& operator=(Item&&) = delete;
        friend class BaseMt;
        friend class BaseMtListAndVect<TypeHash>;
    };
};


template <typename TypeHash>
class CPPUTILS_EXPORT BaseMtListAndVect : public hash::mt::BaseMt<TypeHash>
{
public:
    template <typename TypeData>
    using Iterator = typename BaseMt<TypeHash>::template Iterator<TypeData>;
    template <typename TypeData>
    using Item = typename BaseMt<TypeHash>::template Item<TypeData>;
    template <typename TypeData, typename TypeKey>
    using TypeIterFunc = ::std::function<bool(TypeData*,const TypeKey&)>;  // true -> continue, false stop
    template <typename TypeData>
    using TypeIterFuncChng = ::std::function<bool(const Iterator<TypeData>&)>;  // true -> continue, false stop

public:
    using BaseMt<TypeHash>::BaseMt;

    template <typename TypeData>
    Iterator<TypeData> first()const;
    template <typename TypeData>
    Iterator<TypeData> last()const;
    template <typename TypeData>
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);
    template <typename TypeData>
    void MoveToStart(const Iterator<TypeData>& a_iter);
    template <typename TypeData>
    void MoveToEnd(const Iterator<TypeData>& a_iter);
    
    // mt specific
    template <typename TypeData>
    void MoveToStartNoLockFromIterator(const Iterator<TypeData>& a_iter) noexcept;
    template <typename TypeData>
    void MoveToEndNoLockFromIterator(const Iterator<TypeData>& a_iter) noexcept;

protected:
    template <typename TypeData>
    using IteratorRaw = typename TypeHash::template Iterator<TypeData>;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_BASE_HPP
