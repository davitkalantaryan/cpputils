//
// file:			inscopecleaner.hpp
// path:			include/common/inscopecleaner.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_COMMON_INSCOPECLEANER_HPP
#define CPPUTILS_INCLUDE_COMMON_INSCOPECLEANER_HPP

#include <cpputils_internal_header.h>
#include <common/functional.hpp>



namespace common {


class InScopeCleaner
{
public:
	typedef ::common::function< FUNC_ARGS(void,void*) > TypeDeleteFunc;
	
public:
	InScopeCleaner(TypeDeleteFunc a_func, void* a_pClbkData=CPPUTILS_NULL);
	~InScopeCleaner();
	
private:
	TypeDeleteFunc	m_func;
	void*			m_clbkData;
};


}  // namespace common {




#endif  // #ifndef CPPUTILS_INCLUDE_COMMON_INSCOPECLEANER_HPP
