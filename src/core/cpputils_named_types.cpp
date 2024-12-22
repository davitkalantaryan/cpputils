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


EnumNamesCollection  NamedEnumBase::sm_collection;
CPPUTILS_DLL_PRIVATE StructNamesCollection  g_structsNamesCollection;

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


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


const char* EnumNamesCollection::getName(size_t a_index, int a_value)const
{
    return CInternalTypeinfoGetEnumNameFromCollection(m_collection_p, a_index, a_value);
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

StructNamesCollection::~StructNamesCollection()
{
    CInternalTypeinfoCleanCollectionStructNames(m_collection_p);
}


StructNamesCollection::StructNamesCollection()
    :
    m_collection_p(CInternalTypeinfoCreateCollectionStructNames())
{
    if (!m_collection_p) {
        throw ::std::bad_alloc();
    }
}


void StructNamesCollection::AddNamesToCollection(size_t a_index, int a_number, ...)
{
    va_list argList;
    va_start(argList, a_number);
    CInternalTypeinfoStructNames* const pNames = CInternalTypeinfoSetStructNamesToCollectionVA(m_collection_p, a_index, a_number, argList);
    va_end(argList);

    if (!pNames) {
        throw ::std::bad_alloc();
    }
}


void StructNamesCollection::AddNamesToCollectionVA(size_t a_index, int a_number, va_list a_argList)
{
    CInternalTypeinfoStructNames* const pNames = CInternalTypeinfoSetStructNamesToCollectionVA(m_collection_p, a_index, a_number, a_argList);
    if (!pNames) {
        throw ::std::bad_alloc();
    }
}


const char* StructNamesCollection::getName(size_t a_index, size_t a_offset)const
{
    return CInternalTypeinfoGetStructNameFromCollection(m_collection_p, a_index, a_offset);
}


}}  //  namespace cpputils {namespace named_types {
