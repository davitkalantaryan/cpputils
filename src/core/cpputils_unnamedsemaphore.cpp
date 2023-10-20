//
// file:			cpputils_unnamedsemaphore.cpp
// path:			src/core/cpputils_unnamedsemaphore.cpp
// created on:		2022 Jan 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/unnamedsemaphore.hpp>
#define cinternal_unnamed_sema_wait_ms_needed
#include <cinternal/unnamed_semaphore.h>


namespace cpputils {


class CPPUTILS_DLL_PRIVATE UnnamedSemaphore_p
{
public:
    cinternal_unnamed_sema_t m_sema;
};

/*///////////////////////////////////////////////////////////////////////////*/

UnnamedSemaphore::UnnamedSemaphore(size_t a_initialValue)
    :
      m_sema_data_p(new UnnamedSemaphore_p())
{
    if (cinternal_unnamed_sema_create(&(m_sema_data_p->m_sema), a_initialValue)) {
        throw "Unable to create semaphore";
    }
}


UnnamedSemaphore::~UnnamedSemaphore()
{
    cinternal_unnamed_sema_destroy(&(m_sema_data_p->m_sema));
    delete m_sema_data_p;
}


void UnnamedSemaphore::Post()
{
    cinternal_unnamed_sema_post(&(m_sema_data_p->m_sema));
}


void UnnamedSemaphore::Post(size_t a_postCount)
{
#ifdef _WIN32
    cinternal_unnamed_sema_post_cnt_get_cnt( &(m_sema_data_p->m_sema), a_postCount, nullptr  );
#else
    for(size_t i(0); i<a_postCount; ++i){
        cinternal_unnamed_sema_post( &(m_sema_data_p->m_sema) );
    }
#endif
}


void UnnamedSemaphore::Wait()
{
    cinternal_unnamed_sema_wait(&(m_sema_data_p->m_sema));
}


void UnnamedSemaphore::Wait(size_t a_waitTimeMs)
{
    cinternal_unnamed_sema_wait_ms(&(m_sema_data_p->m_sema), a_waitTimeMs);
}


}  // namespace cpputils {
