//
// file:			recursive_rwlock.hpp
// path:			include/cpputils/recursive_rwlock.hpp
// created on:		2026 Jun 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#pragma once


#include <cpputils/export_symbols.h>
#include <cinternal/recursive_rwlock.h>
//#include <cinternal/disable_compiler_warnings.h>
//#include <stddef.h>
//#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {


class CPPUTILS_EXPORT RecursiveRWLock
{
public:
    ~RecursiveRWLock() noexcept;
    RecursiveRWLock();

    int  lock() noexcept;
    void lock_shared() const noexcept;
    void unlock() noexcept;
    void unlock_shared() const noexcept;

private:
    const CinternalRecursiveRWLockT     m_rec_rw_lock;

private:
    RecursiveRWLock(const RecursiveRWLock&) = delete;
    RecursiveRWLock(RecursiveRWLock&&) = delete;
    RecursiveRWLock& operator=(const RecursiveRWLock&) = delete;
    RecursiveRWLock& operator=(RecursiveRWLock&&) = delete;
};


}  //  namespace cpputils {
