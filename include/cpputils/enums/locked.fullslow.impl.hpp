//
// file:			full.impl.hpp
// path:			include/cpputils/enums/full.impl.hpp
// created on:		2021 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_HPP
#include "locked.fullslow.hpp"
#endif

#include <stdlib.h>
#include <string.h>
#include <new>


namespace cpputils { namespace enums{

template <typename integralType, int numOfFields, int unqiueNumber>
typename BaseFullSlow<integralType,numOfFields,unqiueNumber>::Data BaseFullSlow<integralType,numOfFields,unqiueNumber>::ms_data;

template <typename integralType, int numOfFields, int unqiueNumber>
BaseFullSlow<integralType, numOfFields, unqiueNumber>::BaseFullSlow(int a_nargs, ...)
{
	if (!ms_data.m_names) {
		va_list argList;
		va_start(argList, a_nargs);
		ms_data.Initialize(a_nargs, argList);
		va_end(argList);
	}
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename integralType, int numOfFields, int unqiueNumber>
BaseFullSlow<integralType, numOfFields, unqiueNumber>::Data::Data()
	:
	m_names(CPPUTILS_NULL)
{
}

template <typename integralType, int numOfFields, int unqiueNumber>
BaseFullSlow<integralType, numOfFields, unqiueNumber>::Data::~Data()
{
	delete m_names;
}

template <typename integralType, int numOfFields, int unqiueNumber>
const char* BaseFullSlow<integralType, numOfFields, unqiueNumber>::Data::getName(int64_t a_index)const
{
	::cpputils::hashtbl::Base< int64_t, ::std::string >::iterator iter = m_names->FindEntry(a_index);
	if (iter) {
		return iter->second.c_str();
	}
	return "Unknown";
}


template <typename integralType, int numOfFields, int unqiueNumber>
size_t BaseFullSlow<integralType, numOfFields, unqiueNumber>::Data::HashFunc(const int64_t& a_key)
{
	return static_cast<size_t>(a_key);
}


template <typename integralType, int numOfFields, int unqiueNumber>
void BaseFullSlow<integralType, numOfFields, unqiueNumber>::Data::Initialize(int a_nargs, va_list a_list)
{
	if (!m_names) {

		::std::string nextStr;
		const char* cpcTerm;
		const size_t cunNumberOfArgs( static_cast<size_t>(a_nargs) );
		SingleArg* pNextArg;

		m_names = new ::cpputils::hashtbl::IntHash< int64_t, ::std::string >(cunNumberOfArgs);

		for (size_t i(0); i < cunNumberOfArgs; ++i) {
			pNextArg = va_arg(a_list, SingleArg*);
			cpcTerm = ::strchr(pNextArg->name,'=');
			if (cpcTerm) { nextStr = ::std::string(pNextArg->name,static_cast<size_t>(cpcTerm- pNextArg->name)); }
			else { nextStr = pNextArg->name; }
			m_names->AddEntryEvenIfExists(pNextArg->val, nextStr);
			delete pNextArg;
		}
	}
}

}}  // namespace cpputils { namespace enums{



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULL_IMPL_HPP
