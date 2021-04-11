//
// file:			enums.hpp
// path:			include/cpputils/enums.hpp
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP
#include "enums.hpp"
#endif

#include <stdlib.h>
#include <new>


namespace cpputils { namespace enums{

//template <typename integralType, int numOfFields, int unqiueNumber>
//const typename Base<integralType,numOfFields,unqiueNumber>::CCharPtr* Base<integralType,numOfFields,unqiueNumber>::ms_names = CPPUTILS_NULL;
//template <typename integralType, int numOfFields, int unqiueNumber>
//size_t Base<integralType,numOfFields,unqiueNumber>::ms_numberOfEnumFields = 0;
template <typename integralType, int numOfFields, int unqiueNumber>
typename Base<integralType,numOfFields,unqiueNumber>::Data Base<integralType,numOfFields,unqiueNumber>::ms_data;



template <typename integralType, int numOfFields, int unqiueNumber>
Base<integralType,numOfFields,unqiueNumber>::Base(int a_nargs, ...)
{
	if(!ms_data.m_names){
		va_list argList;
		va_start(argList,a_nargs);
		ms_data.Initialize(a_nargs,argList);
		va_end(argList);		
	}
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename integralType, int numOfFields, int unqiueNumber>
Base<integralType,numOfFields,unqiueNumber>::Data::Data()
	:
	  m_names(CPPUTILS_NULL),
	  m_numberOfEnumFields(0)
{
}

template <typename integralType, int numOfFields, int unqiueNumber>
Base<integralType,numOfFields,unqiueNumber>::Data::~Data()
{
	CCharPtr* pTmpBuffer = const_cast<CCharPtr*>(m_names);
	free(pTmpBuffer);
}

template <typename integralType, int numOfFields, int unqiueNumber>
void Base<integralType,numOfFields,unqiueNumber>::Data::Initialize(int a_nargs, va_list a_list)
{
	if(!ms_data.m_names){
		const char* nextArg;
		
		m_numberOfEnumFields = static_cast<size_t>(a_nargs);
		CCharPtr* pTmpBuffer = static_cast<CCharPtr*>( malloc(sizeof(CCharPtr)*m_numberOfEnumFields) );
		if(!pTmpBuffer){ m_numberOfEnumFields=0;throw ::std::bad_alloc(); }
				
		for(size_t i(0);i<m_numberOfEnumFields;++i){
			nextArg = va_arg(a_list,const char*);
			pTmpBuffer[i] = nextArg;
		}
		
		m_names = pTmpBuffer;
	}
}


}}  // namespace cpputils { namespace enums{



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_IMPL_HPP
