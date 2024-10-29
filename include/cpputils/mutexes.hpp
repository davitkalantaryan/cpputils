//
// repo:            cpputils
// file:			mutexes.hpp
// path:			include/cpputils/mutex_ml.cpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#pragma once


#include <cpputils/export_symbols.h>
#include <stddef.h>


namespace cpputils { namespace mutexes{


class CPPUTILS_DLL_PRIVATE mutexes_p;

class CPPUTILS_EXPORT Mutexes
{
public:
    ~Mutexes();
	Mutexes(size_t a_numberOfMutexes);
    Mutexes(const Mutexes&) = delete;
    Mutexes& operator=(const Mutexes&) = delete;

	void lock(size_t a_index);
	void unlock(size_t a_index);

private:
	mutexes_p* const m_mutexes_p;
};


class CPPUTILS_EXPORT lock_guard02
{
public:
    ~lock_guard02();
	lock_guard02(Mutexes* CPPUTILS_ARG_NN a_mutexes_p, size_t a_index, bool a_shouldLock=true);
    lock_guard02(const lock_guard02&) = delete;
    lock_guard02& operator=(const lock_guard02&) = delete;

	void lock();

private:
    Mutexes* const  m_mutexes_p;
	const size_t    m_index;
};

}}  //  namespace cpputils { namespace mutexes{
