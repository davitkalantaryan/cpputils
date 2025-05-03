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
SharedPtrBase<PtrType>::SharedPtrBase() CPPUTILS_NOEXCEPT
	:
	  m_pCore(CPPUTILS_NULL)
{
}

template <typename PtrType>
SharedPtrBase<PtrType>::SharedPtrBase(PtrType* a_pCell, TypeClbk a_fnClbk, void* a_clbkData)
	:
	  m_pCore( CPPUTILS_NULL  )
{
    if(a_pCell){
        m_pCore = new Core();
        m_pCore->m_pData = a_pCell;
        m_pCore->m_pClbkData = a_clbkData;
        m_pCore->m_clbk = a_fnClbk?a_fnClbk:( TypeClbk(&__private::__implementation::SharedPtrImpl<PtrType>::DefaultFunction) );
        m_pCore->m_unReferences = 1;
        m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,0,1);
    }
}

template <typename PtrType>
SharedPtrBase<PtrType>::SharedPtrBase(Core* a_pCore) CPPUTILS_NOEXCEPT
	:
	  m_pCore(a_pCore)
{
	if(m_pCore){
		const size_t unRefsAfter(++(m_pCore->m_unReferences));
		m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,unRefsAfter-1,unRefsAfter);
	}
}

template <typename PtrType>
SharedPtrBase<PtrType>::SharedPtrBase(const SharedPtrBase& a_cM) CPPUTILS_NOEXCEPT
	:
	  SharedPtrBase(a_cM.m_pCore)
{
}

template <typename PtrType>
SharedPtrBase<PtrType>::SharedPtrBase(SharedPtrBase&& a_cM) CPPUTILS_NOEXCEPT
	:
	  m_pCore(a_cM.m_pCore)
{
	a_cM.m_pCore = CPPUTILS_NULL;
}

template <typename PtrType>
SharedPtrBase<PtrType>::~SharedPtrBase() CPPUTILS_NOEXCEPT
{
	this->reset();
}

template <typename PtrType>
void SharedPtrBase<PtrType>::reset() CPPUTILS_NOEXCEPT
{
    if(m_pCore){
		const size_t unRefsAfter(--(m_pCore->m_unReferences));
		m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,unRefsAfter+1,unRefsAfter);
		if(unRefsAfter<1){
			delete (m_pCore);
		}
        m_pCore = nullptr;
	}
}

template <typename PtrType>
SharedPtrBase<PtrType>& SharedPtrBase<PtrType>::operator=(const SharedPtrBase& a_cM) CPPUTILS_NOEXCEPT
{
	if(m_pCore==a_cM.m_pCore){
		return *this;
	}
	
	this->reset();
	m_pCore=a_cM.m_pCore;
	
	if(m_pCore){
		const size_t unRefsAfter(++(m_pCore->m_unReferences));
		m_pCore->m_clbk(m_pCore->m_pClbkData,m_pCore->m_pData,unRefsAfter-1,unRefsAfter);
	}
	
	return *this;
}

template <typename PtrType>
SharedPtrBase<PtrType>& SharedPtrBase<PtrType>::operator=(SharedPtrBase&& a_cM)CPPUTILS_NOEXCEPT
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
PtrType* SharedPtrBase<PtrType>::get()const CPPUTILS_NOEXCEPT 
{
    if(m_pCore){
        return m_pCore->m_pData;
    }

    return CPPUTILS_NULL;
}

template <typename PtrType>
PtrType* SharedPtrBase<PtrType>::operator ->()const CPPUTILS_NOEXCEPT
{
	if(m_pCore){
		return m_pCore->m_pData;
	}
	
	return CPPUTILS_NULL;
}

template <typename PtrType>
PtrType& SharedPtrBase<PtrType>::operator *()const CPPUTILS_NOEXCEPT
{	
	return *(m_pCore->m_pData);
}

template <typename PtrType>
SharedPtrBase<PtrType>::operator const PtrType*()const CPPUTILS_NOEXCEPT
{
	if(m_pCore){
		return m_pCore->m_pData;
	}
	
	return CPPUTILS_NULL;
}

template <typename PtrType>
SharedPtrBase<PtrType>::operator bool () const CPPUTILS_NOEXCEPT
{
    return m_pCore && (m_pCore->m_pData);
}

template <typename PtrType>
const typename SharedPtrBase<PtrType>::Core* 
SharedPtrBase<PtrType>::GetCore() CPPUTILS_NOEXCEPT
{
	return m_pCore;
}

template <typename PtrType>
int SharedPtrBase<PtrType>::getReferences()const CPPUTILS_NOEXCEPT
{
	if(m_pCore){
		return static_cast<int>(m_pCore->m_unReferences);
	}
	
	return -1;
}


/*///////////////////////////////////////////////////////////////////////////////////////*/

template <typename PtrType>
SharedPtr<PtrType>::~SharedPtr() CPPUTILS_NOEXCEPT
{
}


template <typename PtrType>
template<typename... Targs>
SharedPtr<PtrType>::SharedPtr(Targs... a_args)
    :
      SharedPtrBase<PtrType>(a_args...)
{
    if(SharedPtrBase<PtrType>::m_pCore){
        SharedPtrBase<PtrType>::m_pCore->m_clbk = [](void*,PtrType* a_pData,size_t a_referencesBefore, size_t a_referencesAfter){
            if((a_referencesBefore>0) && (a_referencesAfter<1)){
                delete a_pData;
            }
        };
    }
}


}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_SHAREDPTR_IMPL_HPP
