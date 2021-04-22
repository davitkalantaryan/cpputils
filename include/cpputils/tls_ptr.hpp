//
// file:			tls_ptr.hpp
// path:			include/cpputils/tls_ptr.hpp
// created on:		2021 Apr 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef INCLUDE_CPPUTILS_TLS_PTR_HPP
#define INCLUDE_CPPUTILS_TLS_PTR_HPP

#include <cpputils_internal_header.h>
#include <cpputils/thread_local.h>

namespace cpputils {

template <typename DataType>
class tls_ptr
{
public:
	tls_ptr();
	~tls_ptr();
	
	DataType* get()const;
	void SetForThisThread(DataType* pData);
	
private:
	tls_ptr(const tls_ptr&){}
	static void CleanupFunction(void* data);
	
private:
	cpputils_thread_key_t	m_key;
};

}  // namespace cpputils {


#ifndef INCLUDE_CPPUTILS_TLS_PTR_IMPL_HPP
#include "tls_ptr.impl.hpp"
#endif


#endif  // #ifndef INCLUDE_CPPUTILS_TLS_PTR_HPP
