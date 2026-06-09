//
// repo:            cpputils
// file:			vecthash.hpp
// path:			include/cpputils/hash/mt/vecthash.hpp
// created on:		2026 Mar 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/hash/mt/base.hpp>
#include <cpputils/hash/nl/vecthash.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace hash{ namespace mt{


class CPPUTILS_EXPORT VectHash : public hash::mt::BaseMtListAndVect<hash::nl::VectHash>
{
public:
    using hash::mt::BaseMtListAndVect<hash::nl::VectHash>::BaseMtListAndVect;

    // mt specific
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    void iterateBegToEnd(const TypeIterFunc<TypeData, TypeKey>& a_iterFunc)const;
    template <typename TypeData, typename TypeKey, typename TypeKeyExt = bh::SKeyAny<TypeKey> >
    void iterateEndToBeg(const TypeIterFunc<TypeData, TypeKey>& a_iterFunc)const;
    template <typename TypeData>
    void IterateBegToEnd(const TypeIterFuncChng<TypeData>& a_iterFunc);
    template <typename TypeData>
    void IterateEndToBeg(const TypeIterFuncChng<TypeData>& a_iterFunc);
    
    // vector specific
    template <typename TypeData>
    Iterator<TypeData> at(size_t a_index)const;

protected:
    VectHash(const VectHash&) = delete;
    VectHash(VectHash&&) = delete;
    VectHash& operator=(const VectHash&) = delete;
    VectHash& operator=(VectHash&&) = delete;
};


}}}  //  namespace cpputils { namespace hash{ namespace mt{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_IMPL_HPP
#include <cpputils/impl/cpputils_hash_mt_vecthash.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_MT_VECTHASH_HPP
