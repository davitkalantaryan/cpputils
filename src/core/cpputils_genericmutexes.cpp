//
// repo:            cpputils
// file:			cpputils_genericmutexes.cpp
// path:			src/core/cpputils_mutex_ml.cpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/genericmutexes.hpp>
#include <vector>
#include <deque>
#include <mutex>
#include <thread>
#include <stddef.h>
#include <stdint.h>

namespace cpputils { namespace genericmutexes{


struct MutexData{
    ::std::thread::id                   m_lockerThread;
    GenericMutex                        m_mutex;
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


class CPPUTILS_EXPORT LockGuard_p
{
    friend class LockGuard;
public:
    LockGuard_p(Mutexes* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index);
    
public:
    Mutexes* const  m_mutexes_p;
	const size_t    m_index;
private:
    bool            m_isLocked;
    bool            reserved[(sizeof(size_t)-sizeof(bool))/sizeof(bool)];
};


static inline void lockSingleMutexInline(MutexData* CPPUTILS_ARG_NN a_mutex_p, const ::std::thread::id& a_this_id){
    a_mutex_p->m_mutex.locker();
    a_mutex_p->m_lockerThread = a_this_id;
    ++(a_mutex_p->m_lockCount);
}


static inline void UnlockSingleMutexInline(MutexData* CPPUTILS_ARG_NN a_mutex_p){
    --(a_mutex_p->m_lockCount);
    if(!(a_mutex_p->m_lockCount)){
        a_mutex_p->m_canBeUnlocked = false;
        a_mutex_p->m_lockerThread = ::std::thread::id();
    }
    a_mutex_p->m_mutex.unlocker();
}


/*/////////////////////////////////////////////////////////////////////////////////////*/

Mutexes::~Mutexes()
{
    if(m_mutexes_p){
        const size_t mutexesCount = m_mutexes_p->m_mutexes.size();
        for(size_t i(0); i<mutexesCount;++i){
            delete m_mutexes_p->m_mutexes[i];
        }
        delete m_mutexes_p;
    }
}


Mutexes::Mutexes(const ::std::vector<GenericMutex>& a_mutexes)
	:
	m_mutexes_p(new mutexes_p())
{
    const size_t mutexesCount = a_mutexes.size();
    m_mutexes_p->m_mutexes.resize(mutexesCount);
    for(size_t i(0); i<mutexesCount;++i){
        m_mutexes_p->m_mutexes[i] = new MutexData();
        m_mutexes_p->m_mutexes[i]->m_lockCount = 0;
        m_mutexes_p->m_mutexes[i]->m_canBeUnlocked = false;
        m_mutexes_p->m_mutexes[i]->m_mutex = a_mutexes[i];
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

LockGuard::~LockGuard()
{
    if(m_lockGuard_p->m_isLocked){
        m_lockGuard_p->m_mutexes_p->unlock(m_lockGuard_p->m_index);
    }
    delete m_lockGuard_p;
}


LockGuard::LockGuard(Mutexes* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index, bool a_bShouldLock)
    :
      m_lockGuard_p(new LockGuard_p(a_mutexes_p,a_index))
{
    if(a_bShouldLock){
        m_lockGuard_p->m_mutexes_p->lock(a_index);
    }
    m_lockGuard_p->m_isLocked = a_bShouldLock;
}


void LockGuard::lock()
{
    if(!(m_lockGuard_p->m_isLocked)){
        m_lockGuard_p->m_mutexes_p->lock(m_lockGuard_p->m_index);
        m_lockGuard_p->m_isLocked = true;
    }
}


void LockGuard::unlock()
{
    if(m_lockGuard_p->m_isLocked){
        m_lockGuard_p->m_mutexes_p->lock(m_lockGuard_p->m_index);
        m_lockGuard_p->m_isLocked = false;
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

LockGuard_p::LockGuard_p(Mutexes* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index)
    :
      m_mutexes_p(a_mutexes_p),
      m_index(a_index)
{
    static_cast<void>(this->reserved);
}


}}  //  namespace cpputils { namespace genericmutexes{
