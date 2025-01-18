//
// file:			tls_ptr.posix.impl.hpp
// path:			include/cpputils/tls_ptr.posix.impl.hpp
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_TLS_PTR_POSIX_IMPL_HPP
#define INCLUDE_CPPUTILS_TLS_PTR_POSIX_IMPL_HPP

#ifndef _WIN32

#ifndef INCLUDE_CPPUTILS_TLS_DATA_HPP
#include "tls_data.hpp"
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <cinternal/undisable_compiler_warnings.h>

namespace __p{ namespace __i{

struct LockGuard{
	pthread_mutex_t *pmutex;
	LockGuard():pmutex(CPPUTILS_NULL){}
	~LockGuard(){
		if(this->pmutex){ :: pthread_mutex_unlock(pmutex); }
	}
	void Lock(pthread_mutex_t *a_pmutex){
		this->pmutex = a_pmutex;
		:: pthread_mutex_lock(a_pmutex);
	}
	void Unlock(){
		:: pthread_mutex_unlock(this->pmutex);
		this->pmutex = CPPUTILS_NULL;
	}
};

}}  // namespace __p{ namespace __i{


namespace cpputils {

template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::tls_unique_ptr()
	:
      m_key( CINTERNAL_TLS_OUT_OF_INDEXES ),
	  m_pFirst(CPPUTILS_NULL)
{
    if( CinternalTlsAlloc(&m_key,&tls_unique_ptr::CleanupFunctionStatic) ) {
		throw ::std::bad_alloc();
	}
	//m_mutex_for_list
	:: pthread_mutex_init(&m_mutex_for_list,CPPUTILS_NULL);
}

template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::tls_unique_ptr(tls_unique_ptr* a_mv_p)
	:
	  m_key( a_mv_p->m_key ),
	  m_pFirst(a_mv_p->m_pFirst)
{
    a_mv_p->m_key = CINTERNAL_TLS_OUT_OF_INDEXES;
	a_mv_p->m_pFirst = CPPUTILS_NULL;
}

#if CPPUTILS_CPP_11_DEFINED
template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::tls_unique_ptr(tls_unique_ptr&& a_mv)
	:
	  tls_unique_ptr( &a_mv )
{
}
#endif

template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::~tls_unique_ptr()
{
    if(m_key != CINTERNAL_TLS_OUT_OF_INDEXES){
		TlsItem* pItem;
		__p::__i::LockGuard aGuard;
		Deleter aDeleter;
        CinternalTlsDelete(m_key);
		aGuard.Lock(&m_mutex_for_list);
		pItem = m_pFirst;
		while(pItem){
			aDeleter(pItem->pData);
			delete pItem;
			pItem = m_pFirst;
		}
		aGuard.Unlock();
	}
}

template <typename DataType, typename Deleter>
void tls_unique_ptr<DataType,Deleter>::operator=(DataType* a_pData)
{
	__p::__i::LockGuard aGuard;
    TlsItem* pItem = static_cast<TlsItem*>(CinternalTlsGetSpecific(m_key));
	aGuard.Lock(&m_mutex_for_list);
	if(pItem){ // delete old data
		if(pItem->pData!=a_pData){
			Deleter aDeleter;
			aDeleter(pItem->pData);
		}
		if(a_pData){ pItem->pData =a_pData; }
        else { CinternalTlsSetSpecific(m_key,CPPUTILS_NULL);delete pItem; }
	}
	else if(a_pData){
		pItem = new TlsItem(a_pData,this);
        CinternalTlsSetSpecific(m_key,pItem);
	}
	aGuard.Unlock();
}

template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::operator DataType* ()const
{
	return get();
}

template <typename DataType, typename Deleter>
DataType* tls_unique_ptr<DataType,Deleter>::get()const
{
    TlsItem* pItem =  static_cast<TlsItem*>(CinternalTlsGetSpecific(m_key));
	return pItem ? pItem->pData : CPPUTILS_NULL;
}

template <typename DataType, typename Deleter>
DataType& tls_unique_ptr<DataType,Deleter>::operator*()const
{
    return *(static_cast<TlsItem*>(CinternalTlsGetSpecific(m_key))->pData);
}

template <typename DataType, typename Deleter>
DataType* tls_unique_ptr<DataType,Deleter>::operator->()const
{
    return static_cast<TlsItem*>(CinternalTlsGetSpecific(m_key))->pData;
}

template <typename DataType, typename Deleter>
DataType& tls_unique_ptr<DataType,Deleter>::operator[](size_t a_index)const
{
    return (static_cast<TlsItem*>(CinternalTlsGetSpecific(m_key))->pData)[a_index];
}

template <typename DataType, typename Deleter>
void tls_unique_ptr<DataType,Deleter>::CleanupFunctionStatic(void* a_pData)
{
	TlsItem* pItem = static_cast<TlsItem*>(a_pData);
	if(pItem){
		pItem->pParent->CleanupFunction(pItem);
	}	
}


template <typename DataType, typename Deleter>
inline void tls_unique_ptr<DataType,Deleter>::CleanupFunction(TlsItem* a_pItem)
{
	__p::__i::LockGuard aGuard;
	Deleter aDeleter;
	aDeleter(a_pItem->pData);
	aGuard.Lock(&m_mutex_for_list);
	delete a_pItem;
	aGuard.Unlock();	
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::TlsItem::TlsItem(DataType* a_pData, tls_unique_ptr* a_pParent)
	:
	  prev(CPPUTILS_NULL),next(a_pParent->m_pFirst),pData(a_pData),pParent(a_pParent)
{
	if(a_pParent->m_pFirst){
		a_pParent->m_pFirst->prev = this;
	}
	a_pParent->m_pFirst = this;
}

template <typename DataType, typename Deleter>
tls_unique_ptr<DataType,Deleter>::TlsItem::~TlsItem()
{
	if(this->prev){
		this->prev->next = this->next;
	}
	if(this->next){
		this->next->prev = this->prev;
	}
	if(this==(this->pParent->m_pFirst)){
		this->pParent->m_pFirst = this->next;
	}
}


}  // namespace cpputils {


#endif  // #ifndef _WIN32

#endif  // #ifndef INCLUDE_CPPUTILS_TLS_PTR_POSIX_IMPL_HPP
