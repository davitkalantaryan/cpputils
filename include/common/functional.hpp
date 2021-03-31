//
// file:			functional.hpp
// path:			include/common/functional.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_HPP
#define CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_HPP

//#define DO_NOT_USE_STD_FUNCTION

#include <cpputils_internal_header.h>

#define FUNC_ARGS_CPP11(_ret,...)	_ret(__VA_ARGS__)

#if defined(CPPUTILS_CPP_11_DEFINED) && !defined(DO_NOT_USE_STD_FUNCTION)
#define STD_FUNCTION_IS_USED
#include <functional>
#define FUNC_ARGS		FUNC_ARGS_CPP11
#else
#include <common/functional_old.hpp>
#define FUNC_ARGS		FUNC_ARGS_OLD
#endif

namespace common {


#ifdef STD_FUNCTION_IS_USED

template <class ...Args>
using  function =  ::std::function<Args...>;

#else

#define function	function_old

#endif


}  // namespace common {



#endif  // #ifndef CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_HPP
