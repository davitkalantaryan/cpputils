//
// file:			functional_old.hpp
// path:			include/cpputils/functional_old.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_OLD_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_OLD_HPP

#include <cpputils_internal_header.h>
#include <stddef.h>


#define FUNC_ARGS_OLD(_ret,...)		_ret (*)(__VA_ARGS__)


namespace cpputils {

template <typename Signature>
class function_old_base
{
protected:
	function_old_base(Signature fclbl=CPPUTILS_NULL);
	function_old_base(const function_old_base& cM);
	
public:
	function_old_base& operator=(Signature fclbl);
	function_old_base& operator=(const function_old_base& cM);
	
	operator Signature();
	
protected:
	Signature	m_fclbl;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Signature>
class function_old : public function_old_base<Signature>
{
public:
	function_old(Signature fclbl=CPPUTILS_NULL);
};

template <typename InputType, typename ReturnType>
class function_old< FUNC_ARGS_OLD(ReturnType,InputType) > : public function_old_base< FUNC_ARGS_OLD(ReturnType,InputType) >
{
public:
	typedef ReturnType (*FnType)(InputType);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	ReturnType operator()(InputType inp)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename InputType>
class function_old< FUNC_ARGS_OLD(void,InputType) > : public function_old_base< FUNC_ARGS_OLD(void,InputType) >
{
public:
	typedef void (*FnType)(InputType);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	void operator()(InputType inp)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename ReturnType>
class function_old< FUNC_ARGS_OLD(ReturnType,void) > : public function_old_base< FUNC_ARGS_OLD(ReturnType,void) >
{
public:
	typedef ReturnType (*FnType)(void);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	ReturnType operator()(void)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/


template <typename IType01,typename IType02, typename RType>
class function_old< FUNC_ARGS_OLD(RType,IType01,IType02) > : public function_old_base< FUNC_ARGS_OLD(RType,IType01,IType02) >
{
public:
	typedef RType (*FnType)(IType01,IType02);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	RType operator()(IType01 inp1,IType02 inp2)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02>
class function_old< FUNC_ARGS_OLD(void,IType01,IType02) > : public function_old_base< FUNC_ARGS_OLD(void,IType01,IType02) >
{
public:
	typedef void (*FnType)(IType01,IType02);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	void operator()(IType01 inp1,IType02 inp2)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02, typename IType03, typename RType>
class function_old< FUNC_ARGS_OLD(RType,IType01,IType02,IType03) > : public function_old_base< FUNC_ARGS_OLD(RType,IType01,IType02,IType03) >
{
public:
	typedef RType (*FnType)(IType01,IType02,IType03);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	RType operator()(IType01 inp01,IType02 inp02,IType03 inp3)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02, typename IType03>
class function_old< FUNC_ARGS_OLD(void,IType01,IType02,IType03) > : public function_old_base< FUNC_ARGS_OLD(void,IType01,IType02,IType03) >
{
public:
	typedef void (*FnType)(IType01,IType02,IType03);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	void operator()(IType01 inp01,IType02 inp02,IType03 inp3)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02, typename IType03, typename IType04, typename RType>
class function_old< FUNC_ARGS_OLD(RType,IType01,IType02,IType03,IType04) > : public function_old_base< FUNC_ARGS_OLD(RType,IType01,IType02,IType03,IType04) >
{
public:
	typedef RType (*FnType)(IType01,IType02,IType03,IType04);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	RType operator()(IType01 inp01,IType02 inp02,IType03 inp3,IType04 inp04)const;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02, typename IType03, typename IType04>
class function_old< FUNC_ARGS_OLD(void,IType01,IType02,IType03,IType04) > : public function_old_base< FUNC_ARGS_OLD(void,IType01,IType02,IType03,IType04) >
{
public:
	typedef void (*FnType)(IType01,IType02,IType03,IType04);
	
public:
	function_old(FnType fclbl=CPPUTILS_NULL);
	void operator()(IType01 inp01,IType02 inp02,IType03 inp3,IType04 inp04)const;
};




}  // namespace cpputils {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_OLD_IMPL_HPP
#include "functional_old.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_OLD_HPP
