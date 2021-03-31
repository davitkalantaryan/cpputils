//
// file:			functional_old.impl.hpp
// path:			include/common/functional_old.impl.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_OLD_IMPL_HPP
#define CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_OLD_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_OLD_HPP
#include "functional_old.hpp"
#endif


namespace common {

template <typename Signature>
function_old_base<Signature>::function_old_base(Signature a_fclbl)
	:
	  m_fclbl(a_fclbl)
{
}

template <typename Signature>
function_old_base<Signature>::function_old_base(const function_old_base& a_cM)
	:
	  m_fclbl(a_cM.m_fclbl)
{
}

template <typename Signature>
function_old_base<Signature>& function_old_base<Signature>::operator=(Signature a_fclbl)
{
	m_fclbl = a_fclbl;
	return* this;
}

template <typename Signature>
function_old_base<Signature>& function_old_base<Signature>::operator=(const function_old_base& a_cM)
{
	m_fclbl=(a_cM.m_fclbl);
	return* this;
}

template <typename Signature>
function_old_base<Signature>::operator Signature()
{
	return m_fclbl;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename Signature>
function_old<Signature>::function_old(Signature a_fclbl)
	:
	  function_old_base<Signature>(a_fclbl)
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename InputType, typename ReturnType>
function_old< FUNC_ARGS_OLD(ReturnType,InputType) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(ReturnType,InputType) > (a_fclbl)
{
}

template <typename InputType, typename ReturnType>
ReturnType function_old< FUNC_ARGS_OLD(ReturnType,InputType) >::operator()(InputType a_inp)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	return this->m_fclbl(a_inp);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename InputType>
function_old< FUNC_ARGS_OLD(void,InputType) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(void,InputType) > (a_fclbl)
{
}

template <typename InputType>
void function_old< FUNC_ARGS_OLD(void,InputType) >::operator()(InputType a_inp)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	this->m_fclbl(a_inp);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename ReturnType>
function_old< FUNC_ARGS_OLD(ReturnType,void) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(ReturnType,void) > (a_fclbl)
{
}

template <typename ReturnType>
ReturnType function_old< FUNC_ARGS_OLD(ReturnType,void) >::operator()(void)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	return this->m_fclbl();
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02, typename RType>
function_old< FUNC_ARGS_OLD(RType,IType01,IType02) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(RType,IType01,IType02) > (a_fclbl)
{
}

template <typename IType01,typename IType02, typename RType>
RType function_old< FUNC_ARGS_OLD(RType,IType01,IType02) >::operator()(IType01 a_inp01,IType02 a_inp02)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	return this->m_fclbl(a_inp01,a_inp02);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02>
function_old< FUNC_ARGS_OLD(void,IType01,IType02) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(void,IType01,IType02) > (a_fclbl)
{
}

template <typename IType01,typename IType02>
void function_old< FUNC_ARGS_OLD(void,IType01,IType02) >::operator()(IType01 a_inp01,IType02 a_inp02)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	this->m_fclbl(a_inp01,a_inp02);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02,typename IType03, typename RType>
function_old< FUNC_ARGS_OLD(RType,IType01,IType02,IType03) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(RType,IType01,IType02,IType03) > (a_fclbl)
{
}

template <typename IType01,typename IType02,typename IType03, typename RType>
RType function_old< FUNC_ARGS_OLD(RType,IType01,IType02,IType03) >::operator()(IType01 a_inp01,IType02 a_inp02,IType03 a_inp03)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	return this->m_fclbl(a_inp01,a_inp02,a_inp03);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02,typename IType03>
function_old< FUNC_ARGS_OLD(void,IType01,IType02,IType03) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(void,IType01,IType02,IType03) > (a_fclbl)
{
}

template <typename IType01,typename IType02,typename IType03>
void function_old< FUNC_ARGS_OLD(void,IType01,IType02,IType03) >::operator()(IType01 a_inp01,IType02 a_inp02,IType03 a_inp03)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	this->m_fclbl(a_inp01,a_inp02,a_inp03);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02,typename IType03,typename IType04, typename RType>
function_old< FUNC_ARGS_OLD(RType,IType01,IType02,IType03,IType04) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(RType,IType01,IType02,IType03,IType04) > (a_fclbl)
{
}

template <typename IType01,typename IType02,typename IType03, typename IType04, typename RType>
RType function_old< FUNC_ARGS_OLD(RType,IType01,IType02,IType03,IType04) >::operator()(IType01 a_inp01,IType02 a_inp02,IType03 a_inp03, IType04 a_inp04)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	return this->m_fclbl(a_inp01,a_inp02,a_inp03, a_inp04);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename IType01,typename IType02,typename IType03,typename IType04>
function_old< FUNC_ARGS_OLD(void,IType01,IType02,IType03,IType04) >::function_old(FnType a_fclbl)
	:
	  function_old_base< FUNC_ARGS_OLD(void,IType01,IType02,IType03,IType04) > (a_fclbl)
{
}

template <typename IType01,typename IType02,typename IType03, typename IType04>
void function_old< FUNC_ARGS_OLD(void,IType01,IType02,IType03,IType04) >::operator()(IType01 a_inp01,IType02 a_inp02,IType03 a_inp03, IType04 a_inp04)const
{
	if(!this->m_fclbl){
		throw "bad function call";  // todo: replace this with proper exception
	}
	
	this->m_fclbl(a_inp01,a_inp02,a_inp03, a_inp04);
}



}  // namespace common {


#endif  // #ifndef CPPUTILS_INCLUDE_COMMON_FUNCTIONAL_IMPL_HPP
