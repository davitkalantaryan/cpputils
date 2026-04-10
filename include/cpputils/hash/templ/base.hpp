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
    using IteratorRaw = typename TypeHash::template IteratorRaw<TypeData>;
    using TypeRawHash = TypeHash;

public:
    Base(TypeHash* CPPUTILS_ARG_NN a_hash_p);

    Iterator findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    Iterator find(const TypeKey& a_key)const noexcept;    
    template <typename... Targs>
    typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator >::type
        AddWithKnownHash(size_t a_hash, const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator >::type
        AddEvenIfExist(const TypeKey& a_key, Targs&&... a_args);
    template <typename... Targs>
    typename ::std::enable_if< ::std::is_constructible<TypeData, Targs&&...>::value, typename Base<TypeHash, TypeData, TypeKey, TypeKeyExt>::Iterator >::type
        AddIfNotExist(const TypeKey& a_key, Targs&&... a_args);
    bool Remove(const TypeKey& a_key) noexcept;

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
    using Iterator = typename TypeMtHash::template Iterator<TypeData>;
    using IteratorRaw = typename TypeMtHash::template IteratorRaw<TypeData>;

public:
    using Base<TypeMtHash, TypeData, TypeKey, TypeKeyExt>::Base;

    void AddWithKnownHashIt(size_t a_hash, const TypeKey& a_key, const Iterator& a_iter);
    void AddEvenIfExistIt(const TypeKey& a_key, const Iterator& a_iter);
    Iterator AddIfNotExistIt(const TypeKey& a_key, const Iterator& a_iter);

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
