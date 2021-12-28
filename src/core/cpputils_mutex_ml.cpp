//
// file:			cpputils_mutex_ml.cpp
// path:			src/core/cpputils_mutex_ml.cpp
// created on:		2021 Nov 09
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#if 1

#include <cpputils/mutex_ml.hpp>
#include <cpputils/tls_data.hpp>
//#include <mutex>
#include <stddef.h>
#include <stdint.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define GetCurrentThreadIdNew	GetCurrentThreadId
#else
#include <pthread.h>
#define GetCurrentThreadIdNew	pthread_self
#endif

#define CPPUTILS_MUTEX_MT_NOT_LOCKED	-1


namespace cpputils {

class CPPUTILS_DLL_PRIVATE mutex_ml_p
{
	mutex_ml_p(const mutex_ml_p&) = delete;
	mutex_ml_p& operator=(const mutex_ml_p&) = delete;
public:
	mutex_ml_p() = default;
	tls_data<size_t>	usersCount;
	//ptrdiff_t			lockerTid;
	::std::mutex		std_mutex;
};


/*/////////////////////////////////////////////////////////////////////////////////////*/

mutex_ml::mutex_ml()
	:
	m_mutex_ml_data_ptr(new mutex_ml_p())
{
	//m_mutex_ml_data_ptr->lockerTid = CPPUTILS_MUTEX_MT_NOT_LOCKED;
}


mutex_ml::~mutex_ml()
{
	delete m_mutex_ml_data_ptr;
}


void mutex_ml::lock()
{
	size_t unUsersCount = m_mutex_ml_data_ptr->usersCount;
	if (unUsersCount == 0) {
		m_mutex_ml_data_ptr->std_mutex.lock();
		//m_mutex_ml_data_ptr->lockerTid = static_cast<ptrdiff_t>(GetCurrentThreadIdNew());
	}
	m_mutex_ml_data_ptr->usersCount = (unUsersCount+1);
}


void mutex_ml::unlock()
{
	size_t unUsersCount = (m_mutex_ml_data_ptr->usersCount-1);
	if (unUsersCount == 0) {
		//m_mutex_ml_data_ptr->lockerTid = CPPUTILS_MUTEX_MT_NOT_LOCKED;
		m_mutex_ml_data_ptr->std_mutex.unlock();
	}
	m_mutex_ml_data_ptr->usersCount = unUsersCount;
}


size_t mutex_ml::numberOfLocksInThisThread()const
{
	return m_mutex_ml_data_ptr->usersCount;
}


#ifdef CPPUTILS_CPP_11_DEFINED
::std::mutex& mutex_ml::std_mutex()const
{
	return m_mutex_ml_data_ptr->std_mutex;
}
#endif  // #ifdef CPPUTILS_CPP_11_DEFINED


}  // namespace cpputils {


#endif
