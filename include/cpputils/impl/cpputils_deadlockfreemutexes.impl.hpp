//
// repo:            cpputils
// file:			cpputils_deadlockfreemutexes.impl.hpp
// path:			include/cpputils/impl/cpputils_deadlockfreemutexes.impl.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_DEALOCKFREEMUTEXES_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_IMPL_DEALOCKFREEMUTEXES_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP
#include <cpputils/deadlockfreemutexes.hpp>
#endif


namespace cpputils { namespace mutex{


template <typename MutexType>
static inline ::std::vector< typename orderedcalls::OrderedCalls<MutexType>::GenericCallee > 
GetMutexCalleesInline(const ::std::vector<MutexType*>& a_mutexes){
    const size_t mutexesCount = a_mutexes.size();
    const typename orderedcalls::OrderedCalls<MutexType>::TypeStart mutexStart = [](MutexType* CPPUTILS_ARG_NN a_mutex_p){a_mutex_p->lock();};
    const typename orderedcalls::OrderedCalls<MutexType>::TypeStop  mutexStop = [](MutexType* CPPUTILS_ARG_NN a_mutex_p){a_mutex_p->unlock();};
    ::std::vector< typename orderedcalls::OrderedCalls<MutexType>::GenericCallee > vCallees(mutexesCount,{CPPUTILS_NULL,mutexStart,mutexStop});
    for(size_t i(0); i<mutexesCount; ++i){
        vCallees[i].callee_p = a_mutexes[i];
    }
    return vCallees;
}


template <typename MutexType, typename... Targs>
static inline ::std::vector<MutexType*> 
CreateMutexCalleesInline(size_t a_count, Targs... a_args){
    ::std::vector<MutexType*> retMutexes(a_count);
    for(size_t i(0); i<a_count; ++i){
        retMutexes[i] = new MutexType(a_args...);
    }
    
    return retMutexes;
}


template <typename MutexType>
DeadlockFreeMutexes<MutexType>::DeadlockFreeMutexes(const ::std::vector<MutexType*>& a_mutexes) 
    : 
      orderedcalls::OrderedCalls<MutexType>(GetMutexCalleesInline(a_mutexes)) 
{
}


template <typename MutexType>
DeadlockFreeMutexesOwn<MutexType>::~DeadlockFreeMutexesOwn()
{
    const size_t mutexesCount = m_mutexes.size();
    for(size_t i(0); i<mutexesCount; ++i){
        delete m_mutexes[i];
    }
}


template <typename MutexType>
DeadlockFreeMutexesOwn<MutexType>::DeadlockFreeMutexesOwn(const ::std::vector<MutexType*>& a_mutexes)
    :
      DeadlockFreeMutexes<MutexType>(a_mutexes),
      m_mutexes(a_mutexes)
{
}


template <typename MutexType>
DeadlockFreeMutexesOwn<MutexType>::DeadlockFreeMutexesOwn(::std::vector<MutexType*>&& a_mutexes)
    :
      DeadlockFreeMutexes<MutexType>(a_mutexes),
      m_mutexes(a_mutexes)
{
}


template <typename MutexType>
template <typename... Targs>
DeadlockFreeMutexesOwn<MutexType>::DeadlockFreeMutexesOwn(size_t a_count, Targs... a_args)
    :
      DeadlockFreeMutexesOwn(CreateMutexCalleesInline(a_count,a_args...))
{
}


}}  //  namespace cpputils { namespace mutex{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_DEALOCKFREEMUTEXES_IMPL_HPP
