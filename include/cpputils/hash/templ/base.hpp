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


template <typename TypeHash, typename TypeIter, typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
class Base
{
public:
    Base(TypeHash* CPPUTILS_ARG_NN a_hash_p);

    TypeIter findEx(const TypeKey& a_key, size_t* CPPUTILS_ARG_NN a_pHash)const noexcept;
    TypeIter find(const TypeKey& a_key)const noexcept;
    TypeIter findNextTheSame( const TypeIter& CPPUTILS_ARG_NN a_prev ) const noexcept;
    TypeIter AddWithKnownHash(const TypeData& a_data, const TypeKey& a_key, size_t a_hash);
    TypeIter AddWithKnownHash(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key, size_t a_hash);
    TypeIter AddEvenIfExist(const TypeData& a_data, const TypeKey& a_key);
    TypeIter AddEvenIfExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    TypeIter AddIfNotExist(const TypeData& a_data, const TypeKey& a_key);
    TypeIter AddIfNotExist(TypeData* CPPUTILS_ARG_NN a_data_p, const TypeKey& a_key);
    bool Remove(const TypeKey& a_key) noexcept;
    void RemoveEx(const TypeIter& CPPUTILS_ARG_NN a_iter) noexcept;

protected:
    TypeHash* const m_hash_p;

public:
    typedef TypeHash TypeRawHash;
    typedef TypeIter Iterator;

protected:
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_base.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_BASE_HPP
