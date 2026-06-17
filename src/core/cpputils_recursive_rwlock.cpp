//
// file:			cpputils_recursive_rwlock.cpp
// path:			src/core/cpputils_recursive_rwlock.cpp
// created on:		2026 Jun 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cpputils/recursive_rwlock.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <stdexcept>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {


RecursiveRWLock::~RecursiveRWLock() noexcept
{
    CinternalRecursiveRWLockDelete(m_rec_rw_lock);
}


RecursiveRWLock::RecursiveRWLock()
    :
    m_rec_rw_lock(CinternalRecursiveRWLockCreate())
{
    if (!m_rec_rw_lock) {
        throw ::std::runtime_error("Failed to create recursive rw lock");
    }  //  if (!m_rec_rw_lock) {
}


int  RecursiveRWLock::lock() noexcept
{
    return CinternalRecursiveRWLockUniqueLock(m_rec_rw_lock);
}

    
void RecursiveRWLock::lock_shared() const noexcept
{
    CinternalRecursiveRWLockSharedLock(m_rec_rw_lock);
}


void RecursiveRWLock::unlock() noexcept
{
    CinternalRecursiveRWLockUnlock(m_rec_rw_lock);
}


void RecursiveRWLock::unlock_shared() const noexcept
{
    CinternalRecursiveRWLockUnlock(m_rec_rw_lock);
}


}  // namespace cpputils {
