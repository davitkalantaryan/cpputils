//
// file:			tls_data.impl.hpp
// path:			include/cpputils/tls_data.impl.hpp
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_TLS_DATA_IMPL_HPP
#define INCLUDE_CPPUTILS_TLS_DATA_IMPL_HPP


#ifndef INCLUDE_CPPUTILS_TLS_DATA_HPP
#include "tls_data.hpp"
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {

template <typename DataType, typename Deleter>
tls_ptr_fast<DataType,Deleter>::tls_ptr_fast()
	:
	  m_key(CINTERNAL_TLS_OUT_OF_INDEXES)
{
	if(CinternalTlsAlloc(&m_key,&tls_ptr_fast::CleanupFunction) ) {
		throw ::std::bad_alloc();
	}
}

template <typename DataType, typename Deleter>
tls_ptr_fast<DataType,Deleter>::tls_ptr_fast(tls_ptr_fast* a_mv_p)
	:
	  m_key( a_mv_p->m_key )
{
	a_mv_p->m_key = CINTERNAL_TLS_OUT_OF_INDEXES;
}

#if CPPUTILS_CPP_11_DEFINED
template <typename DataType, typename Deleter>
tls_ptr_fast<DataType,Deleter>::tls_ptr_fast(tls_ptr_fast&& a_mv)
	:
	  m_key( a_mv.m_key )
{
	a_mv.m_key = CINTERNAL_TLS_OUT_OF_INDEXES;
}
#endif

template <typename DataType, typename Deleter>
tls_ptr_fast<DataType,Deleter>::~tls_ptr_fast()
{
	if(m_key != CINTERNAL_TLS_OUT_OF_INDEXES){
		CinternalTlsDelete(m_key);
	}
}

template <typename DataType, typename Deleter>
void tls_ptr_fast<DataType,Deleter>::operator=(DataType* a_pData)
{
	DataType* pData = static_cast<DataType*>(CinternalTlsGetSpecific(m_key));
	CinternalTlsSetSpecific(m_key,a_pData);
	if(pData){ // delete old data
		Deleter aDeleter;
		aDeleter(pData);
	}
}

template <typename DataType, typename Deleter>
tls_ptr_fast<DataType,Deleter>::operator DataType* ()const
{
	return static_cast<DataType*>(CinternalTlsGetSpecific(m_key));
}

template <typename DataType, typename Deleter>
DataType* tls_ptr_fast<DataType,Deleter>::get()const
{
	return static_cast<DataType*>(CinternalTlsGetSpecific(m_key));
}

template <typename DataType, typename Deleter>
DataType& tls_ptr_fast<DataType,Deleter>::operator*()const
{
	return *static_cast<DataType*>(CinternalTlsGetSpecific(m_key));
}

template <typename DataType, typename Deleter>
DataType* tls_ptr_fast<DataType,Deleter>::operator->()const
{
	return static_cast<DataType*>(CinternalTlsGetSpecific(m_key));
}

template <typename DataType, typename Deleter>
DataType& tls_ptr_fast<DataType,Deleter>::operator[](size_t a_index)const
{
	return static_cast<DataType*>(CinternalTlsGetSpecific(m_key))[a_index];
}

template <typename DataType, typename Deleter>
void tls_ptr_fast<DataType,Deleter>::CleanupFunction(void* a_pData)
{
	Deleter aDeleter;
	DataType* pData = static_cast<DataType*>(a_pData);
	aDeleter(pData);
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename DataType>
tls_data<DataType>::tls_data()
	:
	  m_key( CINTERNAL_TLS_OUT_OF_INDEXES )
{
	static_assert (sizeof(DataType)<=sizeof(void*),"unable to store bigger data" );
	if(CinternalTlsAlloc(&m_key,CPPUTILS_NULL) ) {
		throw ::std::bad_alloc();
	}
}

template <typename DataType>
tls_data<DataType>::~tls_data()
{
	if(m_key != CINTERNAL_TLS_OUT_OF_INDEXES){
		CinternalTlsDelete(m_key);
	}
}

template <typename DataType>
tls_data<DataType>::operator DataType ()const
{
	//return static_cast<DataType>(reinterpret_cast<size_t>(CinternalTlsGetSpecific(m_key)));
	return (DataType)((size_t)CinternalTlsGetSpecific(m_key));
}

template <typename DataType>
void tls_data<DataType>::operator=(const DataType& a_data)
{
	//CinternalTlsSetSpecific(m_key, reinterpret_cast<void*>(static_cast<size_t>(a_data))  );
	CinternalTlsSetSpecific(m_key, (void*)((size_t)a_data) );
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
template <typename DataType>
void DefaultDeleter<DataType>::operator()(DataType* a_pData)
{
	delete a_pData;
}

template <typename DataType>
void DefaultDeleter<DataType[]>::operator()(DataType* a_pData)
{
	delete [] a_pData;
}


}  // namespace cpputils {


#endif  // #ifndef INCLUDE_CPPUTILS_TLS_PTR_IMPL_HPP
