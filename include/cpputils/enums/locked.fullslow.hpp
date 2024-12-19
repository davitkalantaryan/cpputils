//
// file:			fullslow.hpp
// path:			include/cpputils/enums/fullslow.hpp
// created on:		2021 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// warning:			for now CPPUTILS_ENUM01 works only if we have enumerated 0,1,...
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/enums/locked.base.hpp>
#include <cinternal/macroses.h>
#include <cpputils/hashtbl.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <string>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace enums{


template <typename integralType, int numOfFields,int unqiueNumber=0>
class BaseFullSlow
{	
protected:
	BaseFullSlow(int nargs, ...);
	BaseFullSlow() {}
protected:
	class Data{
	public:
		Data();
		~Data();
		void Initialize(int nargs, va_list aList);
		const char* getName(int64_t index)const;
	private:
		Data(const Data&){}
		static size_t HashFunc(const int64_t& key);
	public:
		::cpputils::hashtbl::IntHash<int64_t, ::std::string >*	m_names;
	}static ms_data;
};



}}  // namespace cpputils { namespace enums{


#define CPPUTILS_ENUM_FULLSLOW_RAW(_ISeed,_Name,_iType,...)																									\
class _Name : public ::cpputils::enums::BaseFullSlow< _iType,CPPUTILS_NARGS(__VA_ARGS__),_ISeed > {															\
public:																																						\
	CPPUTILS_ENUM_TYPED(__Type,_iType,__VA_ARGS__);																											\
public:																																						\
	_Name(__Type a_val) : 																																	\
		::cpputils::enums::BaseFullSlow< _iType,CPPUTILS_NARGS(__VA_ARGS__),_ISeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_SINGLE_ARGS(_Name,__VA_ARGS__)),	\
		m_enVal(a_val)																																		\
	{}																																						\
	_Name() : 																																				\
		::cpputils::enums::BaseFullSlow< _iType,CPPUTILS_NARGS(__VA_ARGS__),_ISeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_SINGLE_ARGS(_Name,__VA_ARGS__))	\
	{}																																						\
	_Name(const _Name& a_cM) : /* here no need to create static array, because copy const means other object did this*/ 									\
		::cpputils::enums::BaseFullSlow< _iType,CPPUTILS_NARGS(__VA_ARGS__),_ISeed >(),																		\
		m_enVal(a_cM.m_enVal)																																\
	{}																																						\
	_Name& operator=(const _Name& a_cM) { m_enVal = a_cM.m_enVal; return *this; }																			\
	_Name& operator=(__Type a_val) { m_enVal = a_val; return *this; }																						\
	operator _iType () const {return static_cast<_iType>(m_enVal);}																							\
	bool operator==(const _Name& a_o)const { return m_enVal==a_o.m_enVal; }																					\
	bool operator==(__Type a_val)const { return m_enVal==a_val; }																							\
	const char* toString()const {																															\
		int64_t unIndex = static_cast<int64_t>( static_cast<_iType>(m_enVal) );																				\
		return ::cpputils::enums::BaseFullSlow< _iType,CPPUTILS_NARGS(__VA_ARGS__),_ISeed >::ms_data.getName( unIndex ) ;									\
	}																																						\
public:																																						\
	__Type	m_enVal;																																		\
}



#define CPPUTILS_ENUM_FULLSLOW(_Name,_iType,...)		CPPUTILS_ENUM_FULLSLOW_RAW(0,_Name,_iType,__VA_ARGS__)


#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_IMPL_HPP
#include "fullslow.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FULLSLOW_HPP
