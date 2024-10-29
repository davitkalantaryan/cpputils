//
// repo:            cpputils
// file:			genericmutexes.hpp
// path:			include/cpputils/genericmutexes.cpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#pragma once


#include <cpputils/export_symbols.h>
#include <functional>
#include <vector>
#include <stddef.h>


namespace cpputils { namespace genericmutexes{


struct GenericMutex{
    ::std::function<void (void)>    locker;
    ::std::function<void (void)>    unlocker;
};


class CPPUTILS_DLL_PRIVATE mutexes_p;
class CPPUTILS_DLL_PRIVATE LockGuard_p;


class CPPUTILS_EXPORT Mutexes
{
public:
    ~Mutexes();
	Mutexes(const ::std::vector<GenericMutex>& a_mutexes);
    Mutexes(const Mutexes&) = delete;
    Mutexes& operator=(const Mutexes&) = delete;

	void lock(size_t a_index);
	void unlock(size_t a_index);

private:
	mutexes_p* const m_mutexes_p;
};


class CPPUTILS_EXPORT LockGuard
{
public:
    ~LockGuard();
	LockGuard(Mutexes* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index, bool a_shouldLock=true);
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;

	void lock();
    void unlock();

private:
    LockGuard_p* const      m_lockGuard_p;
};

}}  //  namespace cpputils { namespace mutexes{
