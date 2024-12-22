//
// repo:            cpputils
// file:			orderedcalls.impl.hpp
// path:			include/cpputils/orderedcalls.impl.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_CPPUTILS_NAMED_TYPES_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_CPPUTILS_NAMED_TYPES_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_NAMED_TYPES_HPP
#include <cpputils/named_types.hpp>
#endif


namespace cpputils {namespace named_types {


template <int NamedEnumBaseSeed>
NamedEnumBaseTmpl<NamedEnumBaseSeed>::NamedEnumBaseTmpl(int a_number, ...)
{
    va_list argList;
    va_start(argList, a_number);
    sm_collection.AddNamesToCollectionVA(static_cast<size_t>(NamedEnumBaseSeed), a_number, argList);
    va_end(argList);
}


template <int NamedStructBaseSeed>
NamedStructBaseTmpl<NamedStructBaseSeed>::NamedStructBaseTmpl(int a_number, ...)
{
    va_list argList;
    va_start(argList, a_number);
    sm_collection.AddNamesToCollectionVA(static_cast<size_t>(NamedStructBaseSeed), a_number, argList);
    va_end(argList);
}


template <int NamedStructBaseSeed>
const char* NamedStructBaseTmpl<NamedStructBaseSeed>::getOffsetFieldName(size_t a_offset)
{
    return sm_collection.getName(static_cast<size_t>(NamedStructBaseSeed), a_offset);
}


}}  //  namespace cpputils {namespace named_types {


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_CPPUTILS_NAMED_TYPES_HPP
