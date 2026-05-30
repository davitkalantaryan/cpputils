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
class Base
{
public:
    using Iterator = typename TypeHash::template Iterator<TypeData>;
    using TypeRawHash = TypeHash;

public:
    Base(TypeHash* CPPUTILS_ARG_NN a_hash_p);

    inline int32_t reserveUniqueIdForDataInline(void) const noexcept;
    inline Iterator findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const;
    inline Iterator find(const TypeKey& a_key)const;
    inline Iterator findNextTheSame(const Iterator& a_prev) const;
    template <typename... Targs>
    inline Iterator AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    inline Iterator AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    inline Iterator AddIfNotExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    inline Iterator AddOrReturnExisting(const TypeKey& a_key, Targs&&... a_args);
    inline void RemoveEx(const Iterator& a_iter);
    inline bool Remove(const TypeKey& a_key);
    CinternalHashConstBasic_t getConstHashBase()const noexcept;

protected:
    TypeHash* const m_hash_p;

protected:
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) = delete;
};


template <typename TypeMtHash,typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
class MtBase : public templ::Base<TypeMtHash, TypeData, TypeKey, TypeKeyExt>
{
public:
    using FncRawHashCaller = typename TypeMtHash::FncRawHashCaller;
    using FncRawConstHashCaller = typename TypeMtHash::FncRawConstHashCaller;

public:
    using Base<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::Base;

    void CallRawHashFunc(const FncRawHashCaller& a_rawHash);
    void callConstRawHashFunc(const FncRawConstHashCaller& a_rawHash)const;

protected:
    MtBase(const MtBase&) = delete;
    MtBase(MtBase&&) = delete;
    MtBase& operator=(const MtBase&) = delete;
    MtBase& operator=(MtBase&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
