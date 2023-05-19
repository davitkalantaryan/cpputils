//
// file:			protecteddata.impl.hpp
// path:			include/cpputils/protecteddata.impl.hpp
// created on:		2022 May 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
#define CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
#include "protecteddata.hpp"
#endif

#include <utility>


namespace cpputils {

template <typename DataType, typename Mutex>
template<typename... Targs>
ProtectedData<DataType,Mutex>::ProtectedData(Targs... a_args)
    :
      m_data(a_args...)
{
    m_pMutex = new Mutex();
    m_bOwnerOfMutex = true;
}


template <typename DataType, typename Mutex>
template<typename... Targs>
ProtectedData<DataType, Mutex>::ProtectedData(Mutex* a_pMutex, Targs... a_args)
    :
    m_data(a_args...)
{
    if (a_pMutex) {
        m_pMutex = a_pMutex;
        m_bOwnerOfMutex = false;
    }
    else {
        m_pMutex = new Mutex();
        m_bOwnerOfMutex = true;
    }
}


template <typename DataType, typename Mutex>
ProtectedData<DataType, Mutex>::~ProtectedData()
{
    if (m_bOwnerOfMutex) {
        delete m_pMutex;
    }
}


template <typename DataType, typename Mutex>
ProtectedData<DataType,Mutex>& ProtectedData<DataType,Mutex>::operator=(const ProtectedData& a_data)
{
    {
        ::std::lock_guard<Mutex> aGuard(*(a_data.m_pMutex));

        {
            ::std::lock_guard<Mutex> aGuard(*(m_pMutex));
            m_data = a_data.m_data;
        }
    }

    return *this;
}


template <typename DataType, typename Mutex>
ProtectedData<DataType,Mutex>& ProtectedData<DataType,Mutex>::operator=(ProtectedData&& a_data)
{
    {
        ::std::lock_guard<Mutex> aGuard(*m_pMutex);
        m_data = ::std::move(a_data.m_data);
    }

    return *this;
}


template <typename DataType, typename Mutex>
ProtectedData<DataType,Mutex>::operator DataType()const
{
    ::std::lock_guard<Mutex> aGuard(*m_pMutex);
    return m_data;
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::lock()const
{
    m_pMutex->lock();
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::unlock()const
{
    m_pMutex->unlock();
}

template <typename DataType, typename Mutex>
const DataType& ProtectedData<DataType,Mutex>::dataNoLock()const
{
    return m_data;
}


template <typename DataType, typename Mutex>
DataType& ProtectedData<DataType,Mutex>::dataNoLock()
{
    return m_data;
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::SetDataC(const DataType& a_data)
{
    ::std::lock_guard<Mutex> aGuard(*m_pMutex);
    m_data = a_data;
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::SetDataM(DataType& a_data)
{
    ::std::lock_guard<Mutex> aGuard(*m_pMutex);
    m_data = ::std::move(a_data);
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::SetDataM(DataType&& a_data)
{
    ::std::lock_guard<Mutex> aGuard(*m_pMutex);
    m_data = ::std::move(a_data);
}


template <typename DataType, typename Mutex>
DataType ProtectedData<DataType,Mutex>::data()const
{
    ::std::lock_guard<Mutex> aGuard(*m_pMutex);
    return m_data;
}


}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
