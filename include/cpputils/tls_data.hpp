//
// file:			tls_data.hpp
// path:			include/cpputils/tls_data.hpp
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_TLS_DATA_HPP
#define INCLUDE_CPPUTILS_TLS_DATA_HPP

#include <cpputils/export_symbols.h>
#include <cinternal/thread_local_sys.h>
#include <stddef.h>

namespace cpputils {

template <typename DataType>
struct DefaultDeleter{
	void operator()(DataType* pData);
};

template <typename DataType>
struct DefaultDeleter<DataType[]>{
	void operator()(DataType* pData);
};

// this is the case when developer is sure
// that all threads will exit, before
// destructor of this class called
// in the case of windows, this class is not necessary
template <typename DataType, typename Deleter=DefaultDeleter<DataType> >
class tls_ptr_fast
{
public:
	tls_ptr_fast();
	explicit tls_ptr_fast(tls_ptr_fast* mv);
#ifdef CPPUTILS_CPP_11_DEFINED
	tls_ptr_fast(tls_ptr_fast&& mv);
	tls_ptr_fast(const tls_ptr_fast&) = delete;
	tls_ptr_fast& operator=(const tls_ptr_fast&) = delete;
#endif
	~tls_ptr_fast();
	
	void operator=(DataType* pData);
	operator DataType* ()const;
	DataType* get()const;
	DataType& operator*()const;
	DataType* operator->()const;
	DataType& operator[](size_t index)const;
		
private:
#ifndef CPPUTILS_CPP_11_DEFINED
	tls_ptr_fast(const tls_ptr_fast&){}
#endif
	static void CleanupFunction(void* data);
	
protected:
	CinternalTlsData	m_key;
};


#ifdef _WIN32
#ifdef CPPUTILS_CPP_11_DEFINED
template <typename DataType >
using tls_unique_ptr = tls_ptr_fast< DataType >;
#else
#define tls_unique_ptr	tls_ptr_fast
#endif
#else
template <typename DataType, typename Deleter=DefaultDeleter<DataType> >
class tls_unique_ptr
{
public:
	tls_unique_ptr();
	explicit tls_unique_ptr(tls_unique_ptr* mv);
#ifdef CPPUTILS_CPP_11_DEFINED
	tls_unique_ptr(tls_unique_ptr&& mv);
#endif
	~tls_unique_ptr();
	
	void operator=(DataType* pData);
	operator DataType* ()const;
	DataType* get()const;
	DataType& operator*()const;
	DataType* operator->()const;
	DataType& operator[](size_t index)const;
	
private:
	struct TlsItem;
	tls_unique_ptr(const tls_unique_ptr&){}
	static void CleanupFunctionStatic(void* data);
	inline void CleanupFunction(TlsItem* data);
	
private:
	pthread_mutex_t			m_mutex_for_list;
    CinternalTlsData        m_key;
	struct TlsItem{
		TlsItem *prev,*next;
		DataType* pData;
		tls_unique_ptr* pParent;
		TlsItem(DataType* a_pData, tls_unique_ptr* a_pParent);
		~TlsItem();
	} *m_pFirst;
	friend struct TlsItem;
};
#endif  // #ifdef _WIN32


// this is the case of data that is castable to void*
// and no destructor required
template <typename DataType>
class tls_data
{
public:
	tls_data();
	~tls_data();
	
	operator DataType ()const;
	void operator=(const DataType& aData);
	
private:
	tls_data(const tls_data&){}
protected:
	tls_data(bool){}
	
protected:
	CinternalTlsData	m_key;
};

// todo: implement this
//template <typename DataType, typename Deleter >
//class tls_unique_ptr<DataType[],Deleter>
//{
//	//
//};


}  // namespace cpputils {


#ifndef INCLUDE_CPPUTILS_TLS_DATA_IMPL_HPP
#include "tls_data.impl.hpp"
#endif

#ifndef _WIN32
#ifndef INCLUDE_CPPUTILS_TLS_PTR_POSIX_IMPL_HPP
#include "tls_ptr.posix.impl.hpp"
#endif
#endif

#ifdef _WIN32
#ifndef INCLUDE_CPPUTILS_TLS_PTR_WINDOWS_IMPL_HPP
#include "tls_ptr.windows.impl.hpp"
#endif
#endif


#endif  // #ifndef INCLUDE_CPPUTILS_TLS_PTR_HPP
