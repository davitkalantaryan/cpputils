//
// file:			enums.hpp
// path:			include/cpputils/enums.hpp
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// warning:			for now CPPUTILS_ENUM01 works only if we have enumerated 0,1,...
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP

#include <cpputils_internal_header.h>
#include <cpputils/macroses.h>
#include <stddef.h>
#include <stdarg.h>



namespace cpputils { namespace enums{


template <typename integralType, int numOfFields, int unqiueNumber=0>
class Base
{	
protected:
	Base(int nargs, ...);
protected:
	class Data{
	public:
		Data();
		~Data();
		void Initialize(int nargs, va_list aList);
	private:
		Data(const Data&){}
	public:
		typedef const char* CCharPtr;
		const CCharPtr*	m_names;
		size_t			m_numberOfEnumFields;
	}static ms_data;
	friend class Cleaner;
};




}}  // namespace cpputils { namespace enums{

#if CPPUTILS_CPP_11_DEFINED
#define CPPUTILS_ENUM_TYPED(_Name,_integralType,...)	enum _Name : _integralType { __VA_ARGS__ }
#else
#define CPPUTILS_ENUM_TYPED(_Name,_integralType,...)	enum _Name { __VA_ARGS__ }
#endif

#define CPPUTILS_ENUM_RAW(_IntSeed,_Name,_integralType,...)																												\
class _Name : public ::cpputils::enums::Base< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed > {																	\
public:																																									\
	CPPUTILS_ENUM_TYPED(Type,_integralType,__VA_ARGS__);																												\
public:																																									\
	_Name(Type a_val) : ::cpputils::enums::Base< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_NAMES(__VA_ARGS__)),			\
			m_enVal(a_val)																																				\
	{}																																									\
	_Name() : ::cpputils::enums::Base< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_NAMES(__VA_ARGS__))					\
	{}																																									\
	_Name(const _Name& a_cM) : ::cpputils::enums::Base< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >(CPPUTILS_NARGS(__VA_ARGS__),CPPUTILS_NAMES(__VA_ARGS__)),	\
		m_enVal(a_cM.m_enVal)																																			\
	{}																																									\
	_Name& operator=(const _Name& a_cM) { m_enVal = a_cM.m_enVal; return *this; }																						\
	_Name& operator=(Type a_val) { m_enVal = a_val; return *this; }																										\
	operator _integralType (){return static_cast<_integralType>(m_enVal);}																								\
	bool operator==(const _Name& a_o)const { return m_enVal==a_o.m_enVal; }																								\
	bool operator==(Type a_val)const { return m_enVal==a_val; }																											\
	const char* toString()const {																																		\
		size_t unIndex = static_cast<size_t>( static_cast<_integralType>(m_enVal) );																					\
		if( unIndex< ::cpputils::enums::Base< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >::ms_data.m_numberOfEnumFields ) {									\
			return  ::cpputils::enums::Base< _integralType,CPPUTILS_NARGS(__VA_ARGS__),_IntSeed >::ms_data.m_names[unIndex];											\
		}																																								\
		return "Unknown";																																				\
	}																																									\
public:																																									\
	Type	m_enVal;																																					\
};



#define CPPUTILS_ENUM01(_Name,_integralType,...)		CPPUTILS_ENUM_RAW(0,_Name,_integralType,__VA_ARGS__)


#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_IMPL_HPP
#include "enums.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_HPP
