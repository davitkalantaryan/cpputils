//
// repo:            cpputils
// file:			listhash.hpp
// path:			include/cpputils/hash/mt/listhash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/mt/base.hpp>
#include <cpputils/hash/nl/listhash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


class ListHash : public hash::mt::BaseMtListAndVect<hash::nl::ListHash>
{
public:
    using mt::BaseMtListAndVect<hash::nl::ListHash>::BaseMtListAndVect;

    // mt specific
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    void iterateBegToEnd(const TypeIterFunc<TypeData,TypeKey>& a_iterFunc)const;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    void iterateEndToBeg(const TypeIterFunc<TypeData,TypeKey>& a_iterFunc)const;
    template <typename TypeData>
    void IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc);
    template <typename TypeData>
    void IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc);

protected:
    ListHash(const ListHash&) = delete;
    ListHash(ListHash&&) = delete;
    ListHash& operator=(const ListHash&) = delete;
    ListHash& operator=(ListHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_listhash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_LISTHASH_HPP
