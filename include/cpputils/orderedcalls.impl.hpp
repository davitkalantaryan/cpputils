//
// repo:            cpputils
// file:			orderedcalls.impl.hpp
// path:			include/cpputils/orderedcalls.impl.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_HPP
#include <cpputils/orderedcalls.hpp>
#endif

#include <cpputils/orderedcalls.hpp>
#include <vector>
#include <deque>
#include <mutex>
#include <thread>
#include <stddef.h>
#include <stdint.h>

namespace cpputils { namespace orderedcalls{


template <typename CalleeType>
struct CalleeData{
    ::std::thread::id                                   m_lockerThread;
    typename OrderedCalls<CalleeType>::GenericCallee    m_genericCallee;
    ptrdiff_t                                           m_lockCount;
    bool                                                m_canBeStopped;
    bool                                                reserved[(sizeof(ptrdiff_t)-sizeof(bool))/sizeof(bool)];
};


template <typename CalleeType>
struct CalleeAndCount{
    CalleeData<CalleeType>* callee_p;
    ptrdiff_t               count;
};


template <typename CalleeType>
class OrderedCalls_p
{
public:
    ::std::vector<CalleeData<CalleeType>*>  m_callees;
};


template <typename CalleeType>
class Guard_p
{
    friend class Guard<CalleeType>;
public:
    Guard_p(OrderedCalls<CalleeType>* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index);
    
public:
    OrderedCalls<CalleeType>* const m_callees_p;
	const size_t                    m_index;
private:
    bool                            m_isStarted;
    bool                            reserved[(sizeof(ptrdiff_t)-sizeof(bool))/sizeof(bool)];
};


template <typename CalleeType>
static inline void lockSingleMutexInline(CalleeData<CalleeType>* CPPUTILS_ARG_NN a_callee_p, const ::std::thread::id& a_this_id){
    a_callee_p->m_genericCallee.starter(a_callee_p->m_genericCallee.callee_p);
    a_callee_p->m_lockerThread = a_this_id;
    ++(a_callee_p->m_lockCount);
}


template <typename CalleeType>
static inline void UnlockSingleMutexInline(CalleeData<CalleeType>* CPPUTILS_ARG_NN a_callee_p){
    --(a_callee_p->m_lockCount);
    if(!(a_callee_p->m_lockCount)){
        a_callee_p->m_canBeStopped = false;
        a_callee_p->m_lockerThread = ::std::thread::id();
    }
    a_callee_p->m_genericCallee.stopper(a_callee_p->m_genericCallee.callee_p);
}


/*/////////////////////////////////////////////////////////////////////////////////////*/

template <typename CalleeType>
OrderedCalls<CalleeType>::~OrderedCalls()
{
    if(m_orderedCalls_p){
        const size_t calleesCount = m_orderedCalls_p->m_callees.size();
        for(size_t i(0); i<calleesCount;++i){
            delete m_orderedCalls_p->m_callees[i];
        }
        delete m_orderedCalls_p;
    }
}


template <typename CalleeType>
OrderedCalls<CalleeType>::OrderedCalls(const ::std::vector<GenericCallee>& a_callees)
	:
	m_orderedCalls_p(new OrderedCalls_p<CalleeType>())
{
    const ptrdiff_t calleesCount = static_cast<ptrdiff_t>(a_callees.size());
    m_orderedCalls_p->m_callees.resize(calleesCount);
    for(ptrdiff_t i(0); i<calleesCount;++i){
        m_orderedCalls_p->m_callees[i] = new CalleeData<CalleeType>();
        m_orderedCalls_p->m_callees[i]->m_lockCount = 0;
        m_orderedCalls_p->m_callees[i]->m_canBeStopped = false;
        m_orderedCalls_p->m_callees[i]->m_genericCallee = a_callees[i];
    }
}


template <typename CalleeType>
void OrderedCalls<CalleeType>::lock(size_t a_index)
{
    // first let's check the range of index
    const ptrdiff_t mutexesCount = static_cast<ptrdiff_t>(m_orderedCalls_p->m_callees.size());
    if(static_cast<ptrdiff_t>(a_index)>=mutexesCount){
        return;  // or make some error report
    }
    
    // check maybe this mutex is already locked by this thread
    const std::thread::id this_id = std::this_thread::get_id();
    if(m_orderedCalls_p->m_callees[a_index]->m_lockerThread==this_id){
        lockSingleMutexInline(m_orderedCalls_p->m_callees[a_index],this_id);
        return;
    }

    // first let's make sure that no mutex with index higher than this index
    // is owned by this thread, then we should unlock all these mutexes
    // and lock them on correct order
    ptrdiff_t i, j;
    CalleeAndCount<CalleeType> nextLocked;
    std::deque< CalleeAndCount<CalleeType> >  vLockedMutexes;
    for(i = mutexesCount - 1; i>static_cast<ptrdiff_t>(a_index); --i){
        if(m_orderedCalls_p->m_callees[i]->m_lockerThread==this_id){
            nextLocked.count = m_orderedCalls_p->m_callees[i]->m_lockCount;
            nextLocked.callee_p = m_orderedCalls_p->m_callees[i];
            for(j=0; j<nextLocked.count; ++j){
                UnlockSingleMutexInline(nextLocked.callee_p);
            }
            vLockedMutexes.push_front(nextLocked);
        }
    }  //  for(i = mutexesCount - 1; i>static_cast<ptrdiff_t>(a_index); --i){

    lockSingleMutexInline(m_orderedCalls_p->m_callees[a_index],this_id);
    const ptrdiff_t lockableMutexesCount = vLockedMutexes.size();
    for(i = 0; i<lockableMutexesCount; ++i){
        const CalleeAndCount<CalleeType>& nextLockedIn = vLockedMutexes[i];
        for(j=0; j<nextLockedIn.count; ++j){
            lockSingleMutexInline(nextLockedIn.callee_p,this_id);
        }
    }
}


template <typename CalleeType>
void OrderedCalls<CalleeType>::unlock(size_t a_index)
{
    // first let's check the range of index
    const ptrdiff_t cnIndex = static_cast<ptrdiff_t>(a_index);
    const ptrdiff_t mutexesCount = static_cast<ptrdiff_t>(m_orderedCalls_p->m_callees.size());
    if(cnIndex>=mutexesCount){
        return;  // or make some error report
    }
    
    CalleeData<CalleeType>* const pMutexData = m_orderedCalls_p->m_callees[a_index];
    if(pMutexData->m_lockCount>1){
        UnlockSingleMutexInline(pMutexData);
        return;
    }
    
    // in case mutex with higher index is locked by this thread we can not unlock this
    const std::thread::id this_id = std::this_thread::get_id();
    ptrdiff_t i;
    for(i = mutexesCount - 1; i>cnIndex; --i){
        if(m_orderedCalls_p->m_callees[i]->m_lockerThread==this_id){
            // we have mutex with higher index still locked, we should wait
            pMutexData->m_canBeStopped = true;
            return;
        }
    }  //  for(i = mutexesCount - 1; i>cnIndex; --i){
    
	// if we are here, then all mutexes with higher indexes were unlocked
    // let's unlock this mutex
    UnlockSingleMutexInline(pMutexData);
    
    // let's check mutexes with lower indexes, 
    // if there is mutex belonging to this thread and marked canBeUnlocked let's unlock them
    for(i = cnIndex - 1; i>=0; --i){
        if(m_orderedCalls_p->m_callees[i]->m_lockerThread==this_id){
            // we have mutex with higher index still locked, we should wait
            if(m_orderedCalls_p->m_callees[i]->m_canBeStopped){
                UnlockSingleMutexInline(m_orderedCalls_p->m_callees[i]);
            }
            else{
                return;  // do not leave a gap
            }
        }
    }  //  for(i = cnIndex - 1; i>=0; ++i){
    
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename CalleeType>
Guard<CalleeType>::~Guard()
{
    if(m_lockGuard_p->m_isStarted){
        m_lockGuard_p->m_callees_p->unlock(m_lockGuard_p->m_index);
    }
    delete m_lockGuard_p;
}


template <typename CalleeType>
Guard<CalleeType>::Guard(OrderedCalls<CalleeType>* CPPUTILS_ARG_NN a_callees_p, size_t a_index, bool a_bShouldLock)
    :
      m_lockGuard_p(new Guard_p<CalleeType>(a_callees_p,a_index))
{
    if(a_bShouldLock){
        m_lockGuard_p->m_callees_p->lock(a_index);
    }
    m_lockGuard_p->m_isStarted = a_bShouldLock;
}


template <typename CalleeType>
void Guard<CalleeType>::lock()
{
    if(!(m_lockGuard_p->m_isLocked)){
        m_lockGuard_p->m_callees_p->lock(m_lockGuard_p->m_index);
        m_lockGuard_p->m_isStarted = true;
    }
}


template <typename CalleeType>
void Guard<CalleeType>::unlock()
{
    if(m_lockGuard_p->m_isStarted){
        m_lockGuard_p->m_callees_p->unlock(m_lockGuard_p->m_index);
        m_lockGuard_p->m_isStarted = false;
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename CalleeType>
Guard_p<CalleeType>::Guard_p(OrderedCalls<CalleeType>* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index)
    :
      m_callees_p(a_mutexes_p),
      m_index(a_index)
{
    static_cast<void>(this->reserved);
}


}}  //  namespace cpputils { namespace genericmutexes{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_IMPL_HPP
