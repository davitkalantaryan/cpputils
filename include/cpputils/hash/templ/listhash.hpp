//
// repo:            cpputils
// file:			purehash.hpp
// path:			include/cpputils/hash/purehash.hpp
// created on:		2025 Jul 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/templ/base.hpp>
#include <cpputils/hash/listhash.hpp>


namespace cpputils { namespace hash{ namespace templ{


template <typename TypeData, typename TypeKey, typename TypeHasher = ::std::hash<TypeKey>, typename TypeKeyExt = bh::SKeyAny<TypeKey,TypeHasher> >
class CPPUTILS_DLL_PUBLIC ListHash : public Base<hash::ListHash,hash::ListHash::Iterator<TypeData>,TypeData,TypeKey,TypeHasher,TypeKeyExt>
{
public:
    using Base<hash::ListHash, hash::ListHash::Iterator<TypeData>, TypeData, TypeKey, TypeHasher, TypeKeyExt>::Base;
    void MoveToStart(const hash::ListHash::Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    void MoveToEnd(const typename hash::ListHash::Iterator<TypeData>& CPPUTILS_ARG_NN a_iter) noexcept;
    hash::ListHash::Iterator<TypeData> first()const noexcept;
    hash::ListHash::Iterator<TypeData> last()const noexcept;
    size_t count()const noexcept;
    void AllocateListsInAdvance(int32_t a_numberOfLists);

private:
    ListHash(const ListHash&) = delete;
    ListHash(ListHash&&) = delete;
    ListHash& operator=(const ListHash&) = delete;
    ListHash& operator=(ListHash&&) = delete;

private:
    using BaseR = Base<hash::ListHash,hash::ListHash::Iterator<TypeData>,TypeData,TypeKey,TypeHasher,TypeKeyExt>;
};



}}}  //  namespace cpputils { namespace hash{ namespace templ{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_templ_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_TEMPL_LISTHASH_HPP
