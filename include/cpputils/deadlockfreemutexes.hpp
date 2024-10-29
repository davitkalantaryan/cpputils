//
// repo:            cpputils
// file:			deadlockfreemutexes.hpp
// path:			include/cpputils/orderedcalls.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/orderedcalls.hpp>


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


template <typename MutexType>
class DeadlockFreeMutexes : public orderedcalls::OrderedCalls<MutexType>
{    
public:
	DeadlockFreeMutexes(const ::std::vector<MutexType*>& a_mutexes) : orderedcalls::OrderedCalls<MutexType>(GetMutexCalleesInline(a_mutexes)) {}
    DeadlockFreeMutexes(const DeadlockFreeMutexes&) = delete;
    DeadlockFreeMutexes& operator=(const DeadlockFreeMutexes&) = delete;
};

}}  //  namespace cpputils { namespace orderedcalls{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_IMPL_HPP
#include <cpputils/orderedcalls.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP
