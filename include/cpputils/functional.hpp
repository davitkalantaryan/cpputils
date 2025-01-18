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
#include <cinternal/macroses.h>

#define CPPUTILS_DECLARE_FUNC_AFTER_CPP11(_type,_ret,...)   ::cpputils::function< CPPUTILS_ID(_ret)(__VA_ARGS__) >   _type
#define CPPUTILS_FUNC_ARGS_AFTER_CPP11(_ret,...)            _ret(__VA_ARGS__)

#if defined(CPPUTILS_CPP_11_DEFINED) && !defined(CPPUTILS_DO_NOT_USE_STD_FUNCTION)
#define CPPUTILS_STD_FUNCTION_IS_USED
#include <cinternal/disable_compiler_warnings.h>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>
#define CPPUTILS_DECLARE_FUNC   CPPUTILS_DECLARE_FUNC_AFTER_CPP11
#define CPPUTILS_FUNC_ARGS      CPPUTILS_FUNC_ARGS_AFTER_CPP11
#else
#include <cpputils/functional_old.hpp>
#define CPPUTILS_DECLARE_FUNC   CPPUTILS_DECLARE_FUNC_BEFORE_CPP11
#define CPPUTILS_FUNC_ARGS      CPPUTILS_FUNC_ARGS_OLD
#endif

namespace cpputils {


#ifdef CPPUTILS_STD_FUNCTION_IS_USED

template <class ...Args>
using  function =  ::std::function<Args...>;

#else


#ifdef CPPUTILS_CPP_11_DEFINED
template <class ...Args>
using  function =  function_old<Args...>;
#else
#define function    function_old
//template <typename IType01,typename IType02, typename IType03, typename IType04>
//class function : public function_old<IType01,IType02, IType03,IType04>
//{
    //
//};
#endif

#endif


}  // namespace cpputils {



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_HPP
