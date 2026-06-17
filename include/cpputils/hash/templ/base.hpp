//
// repo:            cpputils
// file:			base.hpp
// path:			include/cpputils/hash/templ/base.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/base.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class BaseTempl
{
public:
    using TypeRawHash = TypeHash;
    using TypeDataT = TypeData;
    using TypeKeyT = TypeKey;
    using TypeKeyExtT = TypeKeyExt;
    using Item = typename TypeHash::template Item<TypeData>;
    using Iterator = typename TypeHash::template Iterator<TypeData>;
    using TypeKeyFncRet = typename TypeHash::template TypeKeyFncRet<TypeKey>;
    static constexpr bool is_some_funcs_noexcept = TypeHash::is_some_funcs_noexcept;

public:
    BaseTempl(TypeHash* CPPUTILS_ARG_NN a_hash_p);

    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    inline Iterator findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept(is_some_funcs_noexcept);
    inline Iterator find(const TypeKey& a_key)const noexcept(is_some_funcs_noexcept);
    inline Iterator findNextTheSame(const Iterator& a_prev) const noexcept(is_some_funcs_noexcept);
    template <typename... Targs>
    inline Iterator AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    inline Iterator AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    inline Iterator AddIfNotExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    inline Iterator AddOrReturnExisting(const TypeKey& a_key, Targs&&... a_args);
    inline void RemoveEx(const Iterator& a_iter) noexcept(is_some_funcs_noexcept);
    inline bool Remove(const TypeKey& a_key) noexcept(is_some_funcs_noexcept);
    inline TypeKeyFncRet key(const Iterator& a_iter, bool* a_isValid_p = nullptr) const noexcept(is_some_funcs_noexcept);
    CinternalHashConstBasic_t getConstHashBase()const noexcept;

protected:
    TypeHash* const m_hash_p;

protected:
    BaseTempl(const BaseTempl&) = delete;
    BaseTempl(BaseTempl&&) = delete;
    BaseTempl& operator=(const BaseTempl&) = delete;
    BaseTempl& operator=(BaseTempl&&) = delete;
};


template <typename TypeBaseCls >
class BaseTemplListAndVect : public TypeBaseCls
{
public:
    using Iterator = typename TypeBaseCls::Iterator;
    using TypeDataT = typename TypeBaseCls::TypeDataT;
    static constexpr bool is_some_funcs_noexcept = TypeBaseCls::is_some_funcs_noexcept;

public:
    using TypeBaseCls::TypeBaseCls;

    void AllocateListsInAdvance(int32_t a_numberOfLists);
    Iterator first()const noexcept(is_some_funcs_noexcept);
    Iterator last()const noexcept(is_some_funcs_noexcept);
    size_t count()const noexcept;
    void MoveToStart(const Iterator& a_iter) noexcept(is_some_funcs_noexcept);
    void MoveToEnd(const Iterator& a_iter) noexcept(is_some_funcs_noexcept);
};


template <typename TypeBaseCls >
class BaseTemplVect : public hash::templ::BaseTemplListAndVect<TypeBaseCls>
{
public:
    using Iterator = typename hash::templ::BaseTemplListAndVect<TypeBaseCls>::Iterator;
    using TypeDataT = typename hash::templ::BaseTemplListAndVect<TypeBaseCls>::TypeDataT;
    static constexpr bool is_some_funcs_noexcept = hash::templ::BaseTemplListAndVect<TypeBaseCls>::is_some_funcs_noexcept;

public:
    using hash::templ::BaseTemplListAndVect<TypeBaseCls>::BaseTemplListAndVect;

    Iterator at(size_t a_index)const noexcept(is_some_funcs_noexcept);
};


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
