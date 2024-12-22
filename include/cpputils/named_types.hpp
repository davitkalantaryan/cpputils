//
// repo:            cpputils
// file:			named_types.hpp
// path:			include/cpputils/named_types.cpp
// created on:		2024 Dec 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once

#include <cpputils/export_symbols.h>
#include <cinternal/typeinfo.h>

namespace cpputils {namespace named_types {
    
class CPPUTILS_EXPORT EnumNamesCollection final
{
public:
    ~EnumNamesCollection();
    EnumNamesCollection();
    EnumNamesCollection(const EnumNamesCollection&)=delete;
    EnumNamesCollection(EnumNamesCollection&&) = delete;
    EnumNamesCollection& operator=(const EnumNamesCollection&) = delete;
    EnumNamesCollection& operator=(EnumNamesCollection&&) = delete;

    void AddNamesToCollection(size_t a_index, int a_number, ...);
    void AddNamesToCollectionVA(size_t a_index, int a_number, va_list a_argList);

    const char* getEnumName(size_t a_index, int a_value)const;

private:
    CInternalTypeinfoCollectionEnumNames* const m_collection_p;
};

}}  //  namespace cpputils {namespace named_types {
