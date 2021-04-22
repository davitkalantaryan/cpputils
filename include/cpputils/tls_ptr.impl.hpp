//
// file:			tls_ptr.impl.hpp
// path:			include/cpputils/tls_ptr.impl.hpp
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_TLS_PTR_IMPL_HPP
#define INCLUDE_CPPUTILS_TLS_PTR_IMPL_HPP


#ifndef INCLUDE_CPPUTILS_TLS_PTR_HPP
#include "tls_ptr.hpp"
#endif
#include <new>




namespace cpputils {

template <typename DataType>
tls_ptr<DataType>::tls_ptr()
	:
	  m_key( CPPUTILS_TLS_OUT_OF_INDEXES )
{
	if( ::cpputils_thread_key_create(&m_key,&tls_ptr::CleanupFunction) ) {
		throw ::std::bad_alloc();
	}
}

template <typename DataType>
tls_ptr<DataType>::~tls_ptr()
{
	if(m_key != CPPUTILS_TLS_OUT_OF_INDEXES){
		cpputils_thread_key_delete(m_key);
	}
}

template <typename DataType>
DataType* tls_ptr<DataType>::get()const
{
	return static_cast<DataType*>(cpputils_thread_getspecific(m_key));
}

template <typename DataType>
void tls_ptr<DataType>::SetForThisThread(DataType* a_pData)
{
	cpputils_thread_setspecific(m_key,a_pData);
}

template <typename DataType>
void tls_ptr<DataType>::CleanupFunction(void* a_pData)
{
	DataType* pData = static_cast<DataType*>(a_pData);
	delete pData;
}


}  // namespace cpputils {


#endif  // #ifndef INCLUDE_CPPUTILS_TLS_PTR_IMPL_HPP
