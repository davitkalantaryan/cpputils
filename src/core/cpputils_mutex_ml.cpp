//
// file:			cpputils_mutex_ml.cpp
// path:			src/core/cpputils_mutex_ml.cpp
// created on:		2021 Nov 09
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cpputils/mutex_ml.hpp>
#define cinternal_lw_recursive_mutex_create_needed
#include <cinternal/lw_mutex_recursive.h>
#include <stddef.h>
#include <stdint.h>

namespace cpputils {

class CPPUTILS_DLL_PRIVATE mutex_ml_p
{
public:
	cinternal_lw_recursive_mutex_t		m_mutex;
};


/*/////////////////////////////////////////////////////////////////////////////////////*/

mutex_ml::mutex_ml()
	:
	m_mutex_ml_data_ptr(new mutex_ml_p())
{
	if (cinternal_lw_recursive_mutex_create(&(m_mutex_ml_data_ptr->m_mutex))) {
		throw "Unable create recursive mutex";
	}
}


mutex_ml::~mutex_ml()
{
	cinternal_lw_recursive_mutex_destroy(&(m_mutex_ml_data_ptr->m_mutex));
	delete m_mutex_ml_data_ptr;
}


void mutex_ml::lock()
{
	cinternal_lw_recursive_mutex_lock(&(m_mutex_ml_data_ptr->m_mutex));
}


void mutex_ml::unlock()
{
	cinternal_lw_recursive_mutex_unlock(&(m_mutex_ml_data_ptr->m_mutex));
}


}  // namespace cpputils {
