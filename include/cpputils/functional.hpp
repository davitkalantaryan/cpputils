//
// file:			functional.hpp
// path:			include/cpputils/functional.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_HPP

//#define CPPUTILS_DO_NOT_USE_STD_FUNCTION

#include <cpputils/export_symbols.h>

#define FUNC_ARGS_CPP11(_ret,...)	_ret(__VA_ARGS__)

#if defined(CINTERNAL_CPP_11_DEFINED) && !defined(CPPUTILS_DO_NOT_USE_STD_FUNCTION)
#define CPPUTILS_STD_FUNCTION_IS_USED
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable:4365)
#endif
#include <functional>
#ifdef _MSC_VER
#pragma warning (pop)
#endif
#define FUNC_ARGS		FUNC_ARGS_CPP11
#else
#include <cpputils/functional_old.hpp>
#define FUNC_ARGS		FUNC_ARGS_OLD
#endif

namespace cpputils {


#ifdef CPPUTILS_STD_FUNCTION_IS_USED

template <class ...Args>
using  function =  ::std::function<Args...>;

#else

//#define function	function_old
typedef function_old function;

#endif


}  // namespace cpputils {



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_HPP
