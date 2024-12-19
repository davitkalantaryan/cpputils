//
// file:			sharedptr.hpp
// path:			include/cpputils/sharedptr.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/functional.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {

#ifdef _MSC_VER
#pragma warning (disable:4820)
#endif


template <typename PtrType>
class SharedPtr
{
public:
	struct Core;
	typedef ::cpputils::function< FUNC_ARGS(void,void* clbkData,PtrType* pData,size_t numberOfPreviousReferences,size_t numberOfReferences) > TypeClbk;
public:
	SharedPtr();
	SharedPtr(PtrType* pPtr, TypeClbk a_fnClbk=CPPUTILS_NULL, void* clbkData=CPPUTILS_NULL);
	SharedPtr(Core* pCore);
	SharedPtr(const SharedPtr& cM) CPPUTILS_NOEXCEPT;
	SharedPtr(SharedPtr&& cM) CPPUTILS_NOEXCEPT;
	~SharedPtr();
	
	SharedPtr& operator=(const SharedPtr& cM);
	SharedPtr& operator=(SharedPtr&& cM);
	PtrType* operator ->()const;
	PtrType& operator *()const;
	operator const PtrType*()const;
	
	Core* GetCore();
	int getReferences()const;
    PtrType* get()const;
	
public:
	struct Core{
		PtrType*	m_pData;
		void*		m_pClbkData;
		TypeClbk	m_clbk;
		size_t		m_unReferences;
	}*m_pCore;
};


}  // namespace cpputils {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_IMPL_HPP
#include "sharedptr.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_HPP
