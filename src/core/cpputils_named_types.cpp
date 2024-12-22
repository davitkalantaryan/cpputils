//
// repo:            cpputils
// file:			cpputils_named_types.cpp
// path:			src/core/cpputils_named_types.cpp
// created on:		2024 Dec 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cpputils/named_types.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils {namespace named_types {


EnumNamesCollection::~EnumNamesCollection()
{
    CInternalTypeinfoCleanCollectionEnumNames(m_collection_p);
}


EnumNamesCollection::EnumNamesCollection()
    :
    m_collection_p(CInternalTypeinfoCreateCollectionEnumNames())
{
    if (!m_collection_p) {
        throw ::std::bad_alloc();
    }
}


void EnumNamesCollection::AddNamesToCollection(size_t a_index, int a_number, ...)
{
    va_list argList;
    va_start(argList, a_number);
    CInternalTypeinfoEnumNames* const pNames = CInternalTypeinfoSetEnumNamesToCollectionVA(m_collection_p, a_index, a_number, argList);
    va_end(argList);
    
    if (!pNames) {
        throw ::std::bad_alloc();
    }
}


void EnumNamesCollection::AddNamesToCollectionVA(size_t a_index, int a_number, va_list a_argList)
{
    CInternalTypeinfoEnumNames* const pNames = CInternalTypeinfoSetEnumNamesToCollectionVA(m_collection_p, a_index, a_number, a_argList);
    if (!pNames) {
        throw ::std::bad_alloc();
    }
}


const char* EnumNamesCollection::getEnumName(size_t a_index, int a_value)const
{
    return CInternalTypeinfoGetEnumNameFromCollection(m_collection_p, a_index, a_value);
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

EnumNamesCollection  NamedEnumBase::sm_collection;


}}  //  namespace cpputils {namespace named_types {
