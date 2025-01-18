//
// repo:            cpputils
// file:			deadlockfreemutexes.hpp
// path:			include/cpputils/orderedcalls.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#pragma once

#include <cinternal/internal_header.h>
#ifdef CPPUTILS_CPP_17_DEFINED

#ifndef CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/orderedcalls.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <vector>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace mutex{


template <typename MutexType>
class DeadlockFreeMutexes : public orderedcalls::OrderedCalls<MutexType>
{    
public:
	DeadlockFreeMutexes(const ::std::vector<MutexType*>& a_mutexes);
    DeadlockFreeMutexes(const DeadlockFreeMutexes&) = delete;
    DeadlockFreeMutexes& operator=(const DeadlockFreeMutexes&) = delete;
};


template <typename MutexType>
class DeadlockFreeMutexesOwn : public DeadlockFreeMutexes<MutexType>
{    
public:
    virtual ~DeadlockFreeMutexesOwn() override;
    template <typename... Targs>
    DeadlockFreeMutexesOwn(size_t a_count, Targs... a_args);
    DeadlockFreeMutexesOwn(const ::std::vector<MutexType*>& a_mutexes);
    DeadlockFreeMutexesOwn( ::std::vector<MutexType*>&& a_mutexes );
    DeadlockFreeMutexesOwn(const DeadlockFreeMutexesOwn&) = delete;
    DeadlockFreeMutexesOwn& operator=(const DeadlockFreeMutexesOwn&) = delete;
    
protected:
    const ::std::vector<MutexType*>     m_mutexes;
};


}}  //  namespace cpputils { namespace orderedcalls{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_DEALOCKFREEMUTEXES_IMPL_HPP
#include <cpputils/impl/cpputils_deadlockfreemutexes.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_DEALOCKFREEMUTEXES_HPP
#endif  //  #ifdef CPPUTILS_CPP_17_DEFINED
