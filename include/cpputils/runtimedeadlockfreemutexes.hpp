//
// repo:            cpputils
// file:			runtimedeadlockfreemutexes.hpp
// path:			include/cpputils/runtimedeadlockfreemutexes.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_RUNTIMEDEALOCKFREEMUTEXES_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_RUNTIMEDEALOCKFREEMUTEXES_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/deadlockfreemutexes.hpp>
#include <cpputils/orderedcalls.hpp>


namespace cpputils { namespace mutex{ namespace runtimedeadlockfreemutexes{


class CPPUTILS_EXPORT Base
{
public:
    virtual ~Base();
    virtual void lock()=0;
    virtual void unlock()=0;
};


class CPPUTILS_EXPORT Mutexes : public DeadlockFreeMutexesOwn<Base>
{
public:
    using DeadlockFreeMutexesOwn<Base>::DeadlockFreeMutexesOwn;
    Mutexes(const Mutexes&)=delete;
    Mutexes& operator=(const Mutexes&)=delete;        
};



}}}  //  namespace cpputils { namespace mutex{ namespace runtimedeadlockfreemutexes{


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_RUNTIMEDEALOCKFREEMUTEXES_HPP
