//
// repo:            cpputils
// file:			templ.hpp
// path:			include/cpputils/hash/templ.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/base.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeHash,typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
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
    Iterator AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    Iterator AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    Iterator AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    Iterator AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    Iterator AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    Iterator AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    bool Remove(const TypeKey& a_key) noexcept;

protected:
    TypeHash* const m_hash_p;

protected:
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) = delete;
};


template <typename TypeMtHash,typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
class MtBase : public templ::Base<TypeMtHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>
{
public:
    using Iterator = typename TypeMtHash::template Iterator<TypeData>;
    using IteratorRaw = typename TypeMtHash::template IteratorRaw<TypeData>;

public:
    using Base<TypeMtHash, TypeData, TypeKey, TypeHasher, TypeKeyExt>::Base;

    void AddWithKnownHashIt(const Iterator& a_iter, const TypeKey& a_key, size_t a_hash);
    void AddEvenIfExistIt(const Iterator& a_iter, const TypeKey& a_key);
    Iterator AddIfNotExistIt(const Iterator& a_iter, const TypeKey& a_key);

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
