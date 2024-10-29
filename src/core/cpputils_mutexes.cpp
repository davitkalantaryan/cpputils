//
// repo:            cpputils
// file:			cpputils_mutexes.cpp
// path:			src/core/cpputils_mutex_ml.cpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/mutexes.hpp>
#define cinternal_lw_recursive_mutex_create_needed
#include <cinternal/lw_mutex_recursive.h>
#include <vector>
#include <deque>
#include <mutex>
#include <thread>
#include <stddef.h>
#include <stdint.h>

namespace cpputils { namespace mutexes{


struct MutexData{
    ::std::thread::id                   m_lockerThread;
    cinternal_lw_recursive_mutex_t		m_mutex;
    size_t                              m_lockCount;
    bool                                m_canBeUnlocked;
    bool                                reserved[(sizeof(size_t)-sizeof(bool))/sizeof(bool)];
};


struct MutexAndCount{
    MutexData*  mutex_p;
    size_t      count;
};


class CPPUTILS_DLL_PRIVATE mutexes_p
{
public:
    ::std::vector<MutexData*>  m_mutexes;
};


static inline void lockSingleMutexInline(MutexData* CPPUTILS_ARG_NN a_mutex_p, const ::std::thread::id& a_this_id){
    cinternal_lw_recursive_mutex_lock(&(a_mutex_p->m_mutex));
    a_mutex_p->m_lockerThread = a_this_id;
    ++(a_mutex_p->m_lockCount);
}


static inline void UnlockSingleMutexInline(MutexData* CPPUTILS_ARG_NN a_mutex_p){
    --(a_mutex_p->m_lockCount);
    if(!(a_mutex_p->m_lockCount)){
        a_mutex_p->m_canBeUnlocked = false;
        a_mutex_p->m_lockerThread = ::std::thread::id();
    }
    cinternal_lw_recursive_mutex_unlock(&(a_mutex_p->m_mutex));
}


/*/////////////////////////////////////////////////////////////////////////////////////*/

Mutexes::~Mutexes()
{
    if(m_mutexes_p){
        const size_t mutexesCount = m_mutexes_p->m_mutexes.size();
        for(size_t i(0); i<mutexesCount;++i){
            cinternal_lw_recursive_mutex_destroy(&(m_mutexes_p->m_mutexes[i]->m_mutex));
            delete m_mutexes_p->m_mutexes[i];
        }
        delete m_mutexes_p;
    }
}


Mutexes::Mutexes(size_t a_numberOfMutexes)
	:
	m_mutexes_p(new mutexes_p())
{
    m_mutexes_p->m_mutexes.resize(a_numberOfMutexes);
    for(size_t i(0); i<a_numberOfMutexes;++i){
        m_mutexes_p->m_mutexes[i] = new MutexData();
        m_mutexes_p->m_mutexes[i]->m_lockCount = 0;
        m_mutexes_p->m_mutexes[i]->m_canBeUnlocked = false;
        if (cinternal_lw_recursive_mutex_create(&(m_mutexes_p->m_mutexes[i]->m_mutex))) {
            throw "Unable create recursive mutex";
        }
    }
}


void Mutexes::lock(size_t a_index)
{
    // first let's check the range of index
    const size_t mutexesCount = m_mutexes_p->m_mutexes.size();
    if(a_index>=mutexesCount){
        return;  // or make some error report
    }
    
    // check maybe this mutex is already locked by this thread
    const std::thread::id this_id = std::this_thread::get_id();
    if(m_mutexes_p->m_mutexes[a_index]->m_lockerThread==this_id){
        lockSingleMutexInline(m_mutexes_p->m_mutexes[a_index],this_id);
        return;
    }

    // first let's make sure that no mutex with index higher than this index
    // is owned by this thread, then we should unlock all these mutexes
    // and lock them on correct order
    size_t i, j;
    MutexAndCount nextLocked;
    std::deque<MutexAndCount>  vLockedMutexes;
    for(i = mutexesCount - 1; i>a_index; --i){
        if(m_mutexes_p->m_mutexes[i]->m_lockerThread==this_id){
            nextLocked.count = m_mutexes_p->m_mutexes[i]->m_lockCount;
            nextLocked.mutex_p = m_mutexes_p->m_mutexes[i];
            for(j=0; j<nextLocked.count; ++j){
                UnlockSingleMutexInline(nextLocked.mutex_p);
            }
            vLockedMutexes.push_front(nextLocked);
        }
    }  //  for(i = a_index+1; i<mutexesCount; ++i){

    lockSingleMutexInline(m_mutexes_p->m_mutexes[a_index],this_id);
    const size_t lockableMutexesCount = vLockedMutexes.size();
    for(i = 0; i<lockableMutexesCount; ++i){
        const MutexAndCount& nextLockedIn = vLockedMutexes[i];
        for(j=0; j<nextLockedIn.count; ++j){
            lockSingleMutexInline(nextLocked.mutex_p,this_id);
        }
    }
}


void Mutexes::unlock(size_t a_index)
{
    // first let's check the range of index
    const size_t mutexesCount = m_mutexes_p->m_mutexes.size();
    if(a_index>=mutexesCount){
        return;  // or make some error report
    }
    
    MutexData* const pMutexData = m_mutexes_p->m_mutexes[a_index];
    if(pMutexData->m_lockCount>1){
        UnlockSingleMutexInline(pMutexData);
        return;
    }
    
    // in case mutex with higher index is locked by this thread we can not unlock this
    const std::thread::id this_id = std::this_thread::get_id();
    size_t i;
    for(i = mutexesCount - 1; i>a_index; --i){
        if(m_mutexes_p->m_mutexes[i]->m_lockerThread==this_id){
            // we have mutex with higher index still locked, we should wait
            pMutexData->m_canBeUnlocked = true;
            return;
        }
    }  //  for(i = a_index+1; i<mutexesCount; ++i){
    
	// if we are here, then all mutexes with higher indexes were unlocked
    // let's unlock this mutex
    UnlockSingleMutexInline(pMutexData);
    
    // let's check mutexes with lower indexes, 
    // if tehre is mutex belonging to this thread and marked canBeUnlocked let's unlock them
    for(i = 0; i<a_index; ++i){
        if(m_mutexes_p->m_mutexes[i]->m_lockerThread==this_id){
            // we have mutex with higher index still locked, we should wait
            if(pMutexData->m_canBeUnlocked){
                UnlockSingleMutexInline(m_mutexes_p->m_mutexes[i]);
            }
        }
    }  //  for(i = a_index+1; i<mutexesCount; ++i){
    
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

lock_guard02::~lock_guard02()
{
    m_mutexes_p->unlock(m_index);
}


lock_guard02::lock_guard02(Mutexes* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index, bool a_bShouldLock)
    :
      m_mutexes_p(a_mutexes_p),
      m_index(a_index)
{
    if(a_bShouldLock){
        m_mutexes_p->lock(m_index);
    }
}


void lock_guard02::lock()
{
    m_mutexes_p->lock(m_index);
}


}}  //  namespace cpputils { namespace mutexes{
