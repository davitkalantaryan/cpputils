//
// file:			mutex_ml.hpp
// path:			include/cpputils/mutex_ml.cpp
// created on:		2021 Nov 08
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_CPPUTILS_MUTEX_ML_HPP
#define CPPUTILS_CPPUTILS_MUTEX_ML_HPP


#include <cpputils_internal_header.h>


namespace cpputils {

class CPPUTILS_DLL_PRIVATE mutex_ml_p;

class CPPUTILS_EXPORT mutex_ml
{
public:
	mutex_ml();
	~mutex_ml();

	void lock();
	void unlock();

private:
	mutex_ml_p* const m_mutex_ml_data_ptr;
};

}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_CPPUTILS_MUTEX_ML_HPP
