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
#include <atomic>
#include <stddef.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {

#ifdef _MSC_VER
#pragma warning (disable:4820)
#endif


template <typename PtrType>
class SharedPtrBase
{
public:
	struct Core;
	typedef ::cpputils::function< CPPUTILS_FUNC_ARGS(void,void* clbkData,PtrType* pData,size_t referencesBefore, size_t referencesAfter) > TypeClbk;
public:
    virtual ~SharedPtrBase() CPPUTILS_NOEXCEPT;
	SharedPtrBase() CPPUTILS_NOEXCEPT;
	SharedPtrBase(PtrType* pPtr, TypeClbk a_fnClbk=CPPUTILS_NULL, void* clbkData=CPPUTILS_NULL);
	SharedPtrBase(Core* pCore) CPPUTILS_NOEXCEPT;
	SharedPtrBase(const SharedPtrBase& cM) CPPUTILS_NOEXCEPT;
	SharedPtrBase(SharedPtrBase&& cM) CPPUTILS_NOEXCEPT;
	
	SharedPtrBase& operator=(const SharedPtrBase& cM) CPPUTILS_NOEXCEPT;
	SharedPtrBase& operator=(SharedPtrBase&& cM) CPPUTILS_NOEXCEPT;
	PtrType* operator ->()const CPPUTILS_NOEXCEPT;
	PtrType& operator *()const CPPUTILS_NOEXCEPT;
	operator const PtrType*()const CPPUTILS_NOEXCEPT;
    operator bool () const CPPUTILS_NOEXCEPT ;
	
	Core* GetCore() CPPUTILS_NOEXCEPT;
	int getReferences()const CPPUTILS_NOEXCEPT;
    PtrType* get()const CPPUTILS_NOEXCEPT;
    void reset() CPPUTILS_NOEXCEPT;
	
public:
	struct Core{
		PtrType*                m_pData;
		void*                   m_pClbkData;
		TypeClbk                m_clbk;
        ::std::atomic<size_t>   m_unReferences;
	};
    
protected:
    Core*   m_pCore;
};

// todo: implement below class in such a way, that it is almost the same as ::std::shared_ptr
//template <typename PtrType>
//class SharedPtr : public SharedPtrBase<PtrType>
//{};


}  // namespace cpputils {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_IMPL_HPP
#include "sharedptr.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_HPP
