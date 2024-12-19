//
// file:			full.impl.hpp
// path:			include/cpputils/enums/full.impl.hpp
// created on:		2021 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULL_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULL_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULL_HPP
#include "locked.full.hpp"
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <new>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace enums{

template <typename integralType, int numOfFields, int unqiueNumber>
typename BaseFull<integralType,numOfFields,unqiueNumber>::Data BaseFull<integralType,numOfFields,unqiueNumber>::ms_data;

template <typename integralType, int numOfFields, int unqiueNumber>
BaseFull<integralType, numOfFields, unqiueNumber>::BaseFull(int a_nargs, ...)
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
BaseFull<integralType, numOfFields, unqiueNumber>::Data::Data()
	:
	m_names(CPPUTILS_NULL)
{
}

template <typename integralType, int numOfFields, int unqiueNumber>
BaseFull<integralType, numOfFields, unqiueNumber>::Data::~Data()
{
	delete m_names;
}

template <typename integralType, int numOfFields, int unqiueNumber>
const char* BaseFull<integralType, numOfFields, unqiueNumber>::Data::getName(int64_t a_index)const
{
	::cpputils::hashtbl::Base< int64_t, const char* >::iterator iter = m_names->FindEntry(a_index);
	if (iter) {
		return iter->second;
	}
	return "Unknown";
}


template <typename integralType, int numOfFields, int unqiueNumber>
size_t BaseFull<integralType, numOfFields, unqiueNumber>::Data::HashFunc(const int64_t& a_key)
{
	return static_cast<size_t>(a_key);
}


template <typename integralType, int numOfFields, int unqiueNumber>
void BaseFull<integralType, numOfFields, unqiueNumber>::Data::Initialize(int a_nargs, va_list a_list)
{
	if (!m_names) {

		const size_t cunNumberOfArgs( static_cast<size_t>(a_nargs) );
		SingleArg* pNextArg;

		m_names = new ::cpputils::hashtbl::IntHash< int64_t, const char* >(cunNumberOfArgs);

		for (size_t i(0); i < cunNumberOfArgs; ++i) {
			pNextArg = va_arg(a_list, SingleArg*);
			m_names->AddEntryEvenIfExists(pNextArg->val, pNextArg->name);
			delete pNextArg;
		}
	}
}

}}  // namespace cpputils { namespace enums{



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULL_IMPL_HPP
