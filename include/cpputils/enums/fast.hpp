//
// repo:			cpputils
// file:			fast.hpp
// path:			include/cpputils/enums/fast.hpp
// created on:		2021 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// warning:			for now CPPUTILS_ENUM01 works only if we have enumerated 0,1,...
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FAST_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FAST_HPP

#include <cpputils/export_symbols.h>
#include <cinternal/macroses.h>
#include <stddef.h>
#include <stdarg.h>

#ifndef CPPUTILS_ENUM_TYPED
#if CPPUTILS_CPP_11_DEFINED
#define CPPUTILS_ENUM_TYPED(_Name,_integralType,...)	enum _Name : _integralType { __VA_ARGS__ }
#else
#define CPPUTILS_ENUM_TYPED(_Name,_integralType,...)	enum _Name { __VA_ARGS__ }
#endif
#endif

#ifdef _MSC_VER
#pragma warning (disable:4514) // warning C4514: 'focust::p01::core::SOFTWARE_OS::SOFTWARE_OS': unreferenced inline function has been removed
#endif


namespace cpputils { namespace enums{


template <typename integralType, int numOfFields, int unqiueNumber=0>
class BaseFast
{	
protected:
	BaseFast(int nargs, ...);
	BaseFast() {}
protected:
	class Data{
	public:
		Data();
		~Data();
		const char* getName(size_t index)const;
		void Initialize(int nargs, va_list aList);
	private:
		Data(const Data&){}
	public:
		typedef const char* CCharPtr;
		const CCharPtr*	m_names;
		size_t			m_numberOfEnumFields;
	}static ms_data;
};


}}  // namespace cpputils { namespace enums{

#define CPPUTILS_ENUM_FAST_RAW(_IntSeed,_Name,_integralType,...)																							\
class _Name : public ::cpputils::enums::BaseFast< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed > {													\
public:																																						\
	CPPUTILS_ENUM_TYPED(__Type,_integralType,__VA_ARGS__);																									\
public:																																						\
	_Name(_integralType a_val) : 																															\
		::cpputils::enums::BaseFast< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_NAMES(__VA_ARGS__)),			\
		m_enVal(static_cast<__Type>(a_val))																													\
	{}																																						\
	_Name() : 																																				\
		::cpputils::enums::BaseFast< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_NAMES(__VA_ARGS__))			\
	{}																																						\
	_Name(const _Name& a_cM) : /* here no need to create static array, because copy const means other object did this*/ 									\
		::cpputils::enums::BaseFast< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >(),																\
		m_enVal(a_cM.m_enVal)																																\
	{}																																						\
	_Name& operator=(const _Name& a_cM) { m_enVal = a_cM.m_enVal; return *this; }																			\
	_Name& operator=(__Type a_val) { m_enVal = a_val; return *this; }																						\
	operator __Type () const { return m_enVal; }																											\
	bool operator==(const _Name& a_o)const { return m_enVal==a_o.m_enVal; }																					\
	bool operator==(__Type a_val)const { return m_enVal==a_val; }																							\
	const char* toString()const {																															\
		size_t unIndex = static_cast<size_t>( static_cast<_integralType>(m_enVal) );																		\
		return  ::cpputils::enums::BaseFast< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >::ms_data.getName(unIndex);								\
	}																																						\
public:																																						\
	__Type	m_enVal;																																		\
}



#define CPPUTILS_ENUM_FAST(_Name,_integralType,...)		CPPUTILS_ENUM_FAST_RAW(__COUNTER__,_Name,_integralType,__VA_ARGS__)


#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FAST_IMPL_HPP
#include "fast.impl.hpp"
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_FAST_HPP
