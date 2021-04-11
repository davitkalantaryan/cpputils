//
// file:			sharedptr.impl.hpp
// path:			include/cpputils/sharedptr.impl.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_FUNCTIONAL_OLD_HPP
#include "sharedptr.hpp"
#endif


namespace __private{ namespace __implementation{

template <typename PtrType>
class SharedPtrImpl
{
public:
	static void DefaultFunction(void*,PtrType*, size_t, size_t){}
};

}}  // namespace __private{ namespace __implementation{


namespace cpputils {


template <typename PtrType>
SharedPtr<PtrType>::SharedPtr()
	:
	  m_pCore(CPPUTILS_NULL)
{
}

template <typename PtrType>
SharedPtr<PtrType>::SharedPtr(PtrType* a_pCell, TypeClbk a_fnClbk, void* a_clbkData)
	:
	  m_pCore( new Core  )
{	
	m_pCore->m_pData = a_pCell;
	m_pCore->m_pClbkData = a_clbkData;
	m_pCore->m_clbk = a_fnClbk?a_fnClbk:( TypeClbk(&__private::__implementation::SharedPtrImpl<PtrType>::DefaultFunction) );
	m_pCore->m_unReferences = 1;
}

template <typename PtrType>
SharedPtr<PtrType>::SharedPtr(Core* a_pCore)
	:
	  m_pCore(a_pCore)
{
	if(m_pCore){
		const size_t unPrevRef(m_pCore->m_unReferences);
		m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,unPrevRef,++(m_pCore->m_unReferences));
	}
}

template <typename PtrType>
SharedPtr<PtrType>::SharedPtr(const SharedPtr& a_cM) noexcept
	:
	  SharedPtr(a_cM.m_pCore)
{
}

template <typename PtrType>
SharedPtr<PtrType>::SharedPtr(SharedPtr&& a_cM) noexcept
	:
	  m_pCore(a_cM.m_pCore)
{
	a_cM.m_pCore = CPPUTILS_NULL;
}

template <typename PtrType>
SharedPtr<PtrType>::~SharedPtr()
{
	if(m_pCore){
		const size_t unPrevRef(m_pCore->m_unReferences);
		m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,unPrevRef,--(m_pCore->m_unReferences));
		if(!(m_pCore->m_unReferences)){
			delete m_pCore->m_pData;
			delete (m_pCore);
		}
	}
}

template <typename PtrType>
SharedPtr<PtrType>& SharedPtr<PtrType>::operator=(const SharedPtr& a_cM)
{
	if(m_pCore==a_cM.m_pCore){
		return *this;
	}
	
	if(m_pCore){
		const size_t unPrevRef(m_pCore->m_unReferences);
		m_pCore->m_clbk(m_pCore->m_pClbkData, m_pCore->m_pData,unPrevRef,--(m_pCore->m_unReferences));
		if(!(m_pCore->m_unReferences)){
			delete m_pCore->m_pData;
			free(m_pCore);
		}
	}
	m_pCore=a_cM.m_pCore;
	
	if(m_pCore){
		const size_t unPrevRef(m_pCore->m_unReferences);
		m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,unPrevRef,++(m_pCore->m_unReferences));
	}
	
	return *this;
}

template <typename PtrType>
SharedPtr<PtrType>& SharedPtr<PtrType>::operator=(SharedPtr&& a_cM)
{
	if(m_pCore==a_cM.m_pCore){
		return *this;
	}
	
	Core* pThisCore = m_pCore;
	m_pCore = a_cM.m_pCore;
	a_cM.m_pCore = pThisCore;
	return *this;
}

template <typename PtrType>
PtrType* SharedPtr<PtrType>::operator ->()const
{
	if(m_pCore){
		return m_pCore->m_pData;
	}
	
	return CPPUTILS_NULL;
}

template <typename PtrType>
PtrType& SharedPtr<PtrType>::operator *()const
{	
	return *(m_pCore->m_pData);
}

template <typename PtrType>
SharedPtr<PtrType>::operator const PtrType*()const
{
	if(m_pCore){
		return m_pCore->m_pData;
	}
	
	return CPPUTILS_NULL;
}

template <typename PtrType>
typename SharedPtr<PtrType>::Core* SharedPtr<PtrType>::GetCore()
{
	return m_pCore;
}

template <typename PtrType>
int SharedPtr<PtrType>::getReferences()const
{
	if(m_pCore){
		return static_cast<int>(m_pCore->m_unReferences);
	}
	
	return -1;
}


}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_IMPL_HPP
