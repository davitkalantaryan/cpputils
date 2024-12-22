//
// repo:            cpputils
// file:			named_types.hpp
// path:			include/cpputils/named_types.cpp
// created on:		2024 Dec 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once
#ifndef CPPUTILS_INCLUDE_CPPUTILS_NAMED_TYPES_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_NAMED_TYPES_HPP

#include <cpputils/export_symbols.h>
#include <cinternal/typeinfo.h>

#ifdef _MSC_VER
#pragma warning (disable:4820)  //  '4' bytes padding added after data ...
#pragma warning (disable:4514)  //  unreferenced inline function has been removed
#endif

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

    const char* getName(size_t a_index, int a_value)const;

private:
    CInternalTypeinfoCollectionEnumNames* const m_collection_p;
};


class CPPUTILS_EXPORT StructNamesCollection final
{
public:
    ~StructNamesCollection();
    StructNamesCollection();
    StructNamesCollection(const StructNamesCollection&) = delete;
    StructNamesCollection(StructNamesCollection&&) = delete;
    StructNamesCollection& operator=(const StructNamesCollection&) = delete;
    StructNamesCollection& operator=(StructNamesCollection&&) = delete;

    void AddNamesToCollection(size_t a_index, int a_number, ...);
    void AddNamesToCollectionVA(size_t a_index, int a_number, va_list a_argList);

    const char* getName(size_t a_index, size_t a_offset)const;

private:
    CInternalTypeinfoCollectionStructNames* const m_collection_p;
};


class CPPUTILS_DLL_PRIVATE NamedEnumBase
{
protected:
    ~NamedEnumBase() = default;
    NamedEnumBase() = default;
    NamedEnumBase(const NamedEnumBase&) = default;
    NamedEnumBase(NamedEnumBase&&) = default;
    NamedEnumBase& operator=(const NamedEnumBase&) = default;
    NamedEnumBase& operator=(NamedEnumBase&&) = default;
protected:
    static EnumNamesCollection  sm_collection;
};


template <int NamedEnumBaseSeed>
class CPPUTILS_DLL_PRIVATE NamedEnumBaseTmpl : public NamedEnumBase
{
protected:
    ~NamedEnumBaseTmpl() = default;
    NamedEnumBaseTmpl(int a_number, ...);
    NamedEnumBaseTmpl() = delete;
    NamedEnumBaseTmpl(const NamedEnumBaseTmpl&) = default;
    NamedEnumBaseTmpl(NamedEnumBaseTmpl&&) = default;
    NamedEnumBaseTmpl& operator=(const NamedEnumBaseTmpl&) = default;
    NamedEnumBaseTmpl& operator=(NamedEnumBaseTmpl&&) = default;
};


extern CPPUTILS_DLL_PRIVATE StructNamesCollection  g_structsNamesCollection;


}}  //  namespace cpputils {namespace named_types {


#define CPPUTILS_NAMED_ENUM_TYPED(_Name,_integralType,...)	enum _Name : _integralType { __VA_ARGS__ }
#define CPPUTILS_NAMED_ENUM_RAW(_IntSeed,_Name,_integralType,...)																							\
class _Name : public ::cpputils::named_types::NamedEnumBaseTmpl< _IntSeed > {													                            \
public:																																						\
	CPPUTILS_NAMED_ENUM_TYPED(__Type,_integralType,__VA_ARGS__);																							\
public:																																						\
	_Name(const __Type& a_val) : 																															\
		::cpputils::named_types::NamedEnumBaseTmpl< _IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_ENUM_LIKE_DATA_NAMES(__VA_ARGS__)),			            \
		m_enVal(a_val)																													                    \
	{}																																						\
	_Name() : 																																				\
		::cpputils::named_types::NamedEnumBaseTmpl< _IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_ENUM_LIKE_DATA_NAMES(__VA_ARGS__))			            \
	{}																																						\
	operator const __Type& () const { return m_enVal; }																										\
    operator __Type& () { return m_enVal; }																											        \
	const char* toString()const {																															\
        const size_t unIndex = static_cast<size_t>(_IntSeed);                                                                                          \
		const int nValue = static_cast<int>( static_cast<_integralType>(m_enVal) );																		    \
		return  ::cpputils::named_types::NamedEnumBase::sm_collection.getEnumName(unIndex,nValue);								                            \
	}																																						\
public:																																						\
	__Type	m_enVal;																																		\
}

#define CPPUTILS_NAMED_ENUM_TP(_Name,_integralType,...)     CPPUTILS_NAMED_ENUM_RAW(__COUNTER__,_Name,_integralType,__VA_ARGS__)
#define CPPUTILS_NAMED_ENUM(_Name,...)		                CPPUTILS_NAMED_ENUM_TP(_Name,int,__VA_ARGS__)


#define CPPUTILS_NAMED_STRUCT_RAW(_IntSeed,_Name,...)																							\
struct _Name {													                            \
	_Name()  																																				        \
	{                                                                                                                                                               \
        g_structsNamesCollection.AddNamesToCollection(static_cast<size_t>(_IntSeed),CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_STRUCT_LIKE_DATA_NAMES(__VA_ARGS__),CPPUTILS_VARIABLE_OFFSETOF());      \
    }																																						        \
    CPPUTILS_VAR_MACRO_APPY_OP(CPPUTILS_DEFINE_VARIABLE,;,__VA_ARGS__);                                                                                             \
}


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_CPPUTILS_NAMED_TYPES_HPP
#include <cpputils/impl/cpputils_named_types.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_NAMED_TYPES_HPP
