//
// file:			base.hpp
// path:			include/cpputils/enums/base.hpp
// created on:		2021 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// warning:			for now CPPUTILS_ENUM01 works only if we have enumerated 0,1,...
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_BASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ENUMS_BASE_HPP

#include <cpputils_internal_header.h>
#include <stdint.h>

namespace cpputils { namespace enums{


struct SingleArg{
	int64_t		val;
	const char* name;
	SingleArg(int64_t a_val, const char* a_name):val(a_val),name(a_name){}
};


}}  // namespace cpputils { namespace enums{

#if CPPUTILS_CPP_11_DEFINED
#define CPPUTILS_ENUM_TYPED(_Name,_integralType,...)	enum _Name : _integralType { __VA_ARGS__ }
#else
#define CPPUTILS_ENUM_TYPED(_Name,_integralType,...)	enum _Name { __VA_ARGS__ }
#endif

#define CPPUTILS_MACRO_SINGLE_ARG(_name,_arg)	new ::cpputils::enums::SingleArg(static_cast<int64_t>(_name::_arg),#_arg)
#define CPPUTILS_SINGLE_ARGS(_Name,...)			CPPUTILS_MACRO_APPY(CPPUTILS_MACRO_SINGLE_ARG,_Name,__VA_ARGS__)


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_ENUMS_BASE_HPP
