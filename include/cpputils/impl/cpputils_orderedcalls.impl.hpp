//
// repo:            cpputils
// file:			orderedcalls.impl.hpp
// path:			include/cpputils/orderedcalls.impl.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#include <cinternal/internal_header.h>
#ifdef CPPUTILS_CPP_17_DEFINED

#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_ORDEREDCALLS_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_ORDEREDCALLS_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_HPP
#include <cpputils/orderedcalls.hpp>
#endif

#ifndef cinternal_gettid_needed
#define cinternal_gettid_needed
#endif

#include <cinternal/gettid.h>
#include <cinternal/disable_compiler_warnings.h>
#include <vector>
#include <deque>
#include <mutex>
#include <thread>
#include <stddef.h>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace orderedcalls{

//#define GetTidMacro     CinternalGetCurrentTid


template <typename CalleeType>
class CalleeData : public OrderedCalls<CalleeType>::Item
{
public:
    CalleeData(OrderedCalls<CalleeType>* a_parent_p, size_t a_index, const typename OrderedCalls<CalleeType>::GenericCallee& a_callee);
public:
    const typename OrderedCalls<CalleeType>::TypeStart  m_starter;
    const typename OrderedCalls<CalleeType>::TypeStop   m_stopper;
    int64_t                                             m_lockerThreadId;
    ptrdiff_t                                           m_lockCount;
    ptrdiff_t                                           m_canBeStoppedCount;
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
    typedef CalleeData<CalleeType>* CalleeDataPtr;
    ~OrderedCalls_p();
    OrderedCalls_p(size_t a_calleesSize);
    const size_t            m_count;
    CalleeDataPtr* const    m_callees;
};


template <typename MutexType>
class Guard_p
{
    friend class Guard<MutexType>;
public:
    Guard_p(MutexType* CPPUTILS_ARG_NN a_mutexes_p);
    
public:
    MutexType* const                m_callees_p;
    ::std::function<void()>         m_unlockFunc;
private:
    bool                            m_isStarted;
    bool                            reserved[(sizeof(ptrdiff_t)-sizeof(bool))/sizeof(bool)];
};


template <typename CalleeType>
static inline void lockSingleMutexInline(CalleeData<CalleeType>* CPPUTILS_ARG_NN a_callee_p, int a_this_id){
    a_callee_p->m_starter(const_cast<CalleeType*>(a_callee_p->m_mutex_p));
    a_callee_p->m_lockerThreadId = a_this_id;
    ++(a_callee_p->m_lockCount);
}


template <typename CalleeType>
static inline void UnlockSingleMutexInline(CalleeData<CalleeType>* CPPUTILS_ARG_NN a_callee_p){
    --(a_callee_p->m_lockCount);
    if((a_callee_p->m_lockCount)<1){
        a_callee_p->m_lockerThreadId = -1;
    }
    a_callee_p->m_stopper(const_cast<CalleeType*>(a_callee_p->m_mutex_p));
}


/*/////////////////////////////////////////////////////////////////////////////////////*/

template <typename CalleeType>
OrderedCalls<CalleeType>::~OrderedCalls()
{
    if(m_orderedCalls_p){
        for(size_t i(0); i<(m_orderedCalls_p->m_count);++i){
            delete m_orderedCalls_p->m_callees[i];
        }
        delete m_orderedCalls_p;
    }
}


template <typename CalleeType>
OrderedCalls<CalleeType>::OrderedCalls(const ::std::vector<GenericCallee>& a_callees)
	:
	m_orderedCalls_p(new OrderedCalls_p<CalleeType>(a_callees.size()))
{
    const ptrdiff_t calleesCount = static_cast<ptrdiff_t>(m_orderedCalls_p->m_count);
    for(ptrdiff_t i(0); i<calleesCount;++i){
        m_orderedCalls_p->m_callees[i] = new CalleeData<CalleeType>(this,size_t(i),a_callees[i]);
        m_orderedCalls_p->m_callees[i]->m_lockCount = 0;
        m_orderedCalls_p->m_callees[i]->m_lockerThreadId = -1;
        m_orderedCalls_p->m_callees[i]->m_canBeStoppedCount = 0;
    }
}


template <typename CalleeType>
void OrderedCalls<CalleeType>::lock(size_t a_index)
{
    // first let's check the range of index
    const ptrdiff_t mutexesCount = static_cast<ptrdiff_t>(m_orderedCalls_p->m_count);
    if(static_cast<ptrdiff_t>(a_index)>=mutexesCount){
        return;  // or make some error report
    }
    
    // check maybe this mutex is already locked by this thread
    const int64_t this_id = CinternalGetCurrentTid();
    if(m_orderedCalls_p->m_callees[a_index]->m_lockerThreadId==this_id){
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
        if(m_orderedCalls_p->m_callees[i]->m_lockerThreadId==this_id){
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
    const ptrdiff_t mutexesCount = static_cast<ptrdiff_t>(m_orderedCalls_p->m_count);
    if(cnIndex>=mutexesCount){
        return;  // or make some error report
    }
    
    CalleeData<CalleeType>* const pMutexData = m_orderedCalls_p->m_callees[a_index];
    if(pMutexData->m_lockCount>1){
        UnlockSingleMutexInline(pMutexData);
        return;
    }
    
    // in case mutex with higher index is locked by this thread we can not unlock this
    const int64_t this_id = CinternalGetCurrentTid();
    ptrdiff_t i;
    for(i = mutexesCount - 1; i>cnIndex; --i){
        if(m_orderedCalls_p->m_callees[i]->m_lockerThreadId==this_id){
            // we have mutex with higher index still locked, we should wait
            ++(pMutexData->m_canBeStoppedCount);
            return;
        }
    }  //  for(i = mutexesCount - 1; i>cnIndex; --i){
    
	// if we are here, then all mutexes with higher indexes were unlocked
    // let's unlock this mutex
    UnlockSingleMutexInline(pMutexData);
    
    // let's check mutexes with lower indexes, 
    // if there is mutex belonging to this thread and marked canBeUnlocked let's unlock them
    for(i = cnIndex - 1; i>-1; --i){
        if(m_orderedCalls_p->m_callees[i]->m_lockerThreadId==this_id){
            // we have mutex with higher index still locked, we should wait
            while(m_orderedCalls_p->m_callees[i]->m_canBeStoppedCount>0){
                UnlockSingleMutexInline(m_orderedCalls_p->m_callees[i]);
                --(m_orderedCalls_p->m_callees[i]->m_canBeStoppedCount);
            }
            if((m_orderedCalls_p->m_callees[i]->m_lockCount)>0){
                return;  // do not leave a gap
            }
        }  //  if(m_orderedCalls_p->m_callees[i]->m_lockerThreadId==this_id){
    }  //  for(i = cnIndex - 1; i>=0; ++i){
    
}


template <typename CalleeType>
size_t OrderedCalls<CalleeType>::size()const
{
    return m_orderedCalls_p->m_count;
}


template <typename CalleeType>
typename OrderedCalls<CalleeType>::Item* OrderedCalls<CalleeType>::getSingleMutex(size_t a_index)const
{
    if(a_index>=(m_orderedCalls_p->m_count)){
        return nullptr;  // or make some error report
    }
    
    return m_orderedCalls_p->m_callees[a_index];
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#define UNLOCK_FNC_GET()    \
    [this, args_tuple = ::std::move(args_tuple)]() mutable {                                                \
        ::std::apply([this](auto&&... unpacked_args) {                                                      \
            m_lockGuard_p->m_callees_p->unlock(std::forward<decltype(unpacked_args)>(unpacked_args)...);    \
        }, args_tuple);                                                                                     \
    }

template <typename MutexType>
Guard<MutexType>::~Guard()
{
    if(m_lockGuard_p->m_isStarted){
        m_lockGuard_p->m_unlockFunc();
    }
    delete m_lockGuard_p;
}


template <typename MutexType>
template<typename... Targs>
Guard<MutexType>::Guard(MutexType* CPPUTILS_ARG_NN a_callees_p, Targs... a_args)
    :
      m_lockGuard_p(new Guard_p<MutexType>(a_callees_p))
{
    m_lockGuard_p->m_callees_p->lock(a_args...);
    auto args_tuple = ::std::make_tuple( ::std::forward<Targs>(a_args)...);
    m_lockGuard_p->m_unlockFunc = UNLOCK_FNC_GET();
    m_lockGuard_p->m_isStarted = true;
}


template <typename MutexType>
Guard<MutexType>::Guard( const defer_lock_t& a_def, MutexType* CPPUTILS_ARG_NN a_callees_p)
    :
      m_lockGuard_p(new Guard_p<MutexType>(a_callees_p))
{
    static_cast<void>(a_def);
    m_lockGuard_p->m_isStarted = false;
}


template <typename MutexType>
template<typename... Targs>
void Guard<MutexType>::lock(Targs... a_args)
{
    if(!(m_lockGuard_p->m_isStarted)){
        m_lockGuard_p->m_callees_p->lock(a_args...);
        m_lockGuard_p->m_isStarted = true;        
        auto args_tuple = ::std::make_tuple( ::std::forward<Targs>(a_args)...);
        m_lockGuard_p->m_unlockFunc = UNLOCK_FNC_GET();
    }
}


template <typename MutexType>
template<typename... Targs>
void Guard<MutexType>::unlock(Targs... a_args)
{
    if(m_lockGuard_p->m_isStarted){
        m_lockGuard_p->m_callees_p->unlock(a_args...);
        m_lockGuard_p->m_isStarted = false;
    }
}


template <typename MutexType>
void Guard<MutexType>::unlock(const symetric_unlock_t&)
{
    if(m_lockGuard_p->m_isStarted){
        m_lockGuard_p->m_unlockFunc();
        m_lockGuard_p->m_isStarted = false;
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename MutexType>
Guard_p<MutexType>::Guard_p(MutexType* CPPUTILS_ARG_NN a_mutexes_p)
    :
      m_callees_p(a_mutexes_p)
{
    static_cast<void>(this->reserved);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename CalleeType>
void OrderedCalls<CalleeType>::Item::lock()
{
    m_parent_p->lock(m_index);
}


template <typename CalleeType>
void OrderedCalls<CalleeType>::Item::unlock()
{
    m_parent_p->unlock(m_index);
}


template <typename CalleeType>
OrderedCalls<CalleeType>::Item::~Item()
{
}


template <typename CalleeType>
OrderedCalls<CalleeType>::Item::Item(OrderedCalls* a_parent_p, size_t a_index, const CalleeType* a_mutex_p)
    :
      m_parent_p(a_parent_p),
      m_index(a_index),
      m_mutex_p(a_mutex_p)
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename CalleeType>
OrderedCalls_p<CalleeType>::~OrderedCalls_p()
{
    delete [] m_callees;
}


template <typename CalleeType>
OrderedCalls_p<CalleeType>::OrderedCalls_p(size_t a_calleesSize)
    :
      m_count(a_calleesSize),
      m_callees(new CalleeDataPtr[a_calleesSize])
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
template <typename CalleeType>
CalleeData<CalleeType>::CalleeData(OrderedCalls<CalleeType>* a_parent_p, size_t a_index, const typename OrderedCalls<CalleeType>::GenericCallee& a_callee)
    :
      OrderedCalls<CalleeType>::Item(a_parent_p,a_index,a_callee.callee_p),
      m_starter(a_callee.starter),
      m_stopper(a_callee.stopper)
{
}


}}  //  namespace cpputils { namespace genericmutexes{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_ORDEREDCALLS_IMPL_HPP
#endif  //  #ifdef CPPUTILS_CPP_17_DEFINED
