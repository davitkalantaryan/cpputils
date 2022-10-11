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
}


template <typename DataType, typename Mutex>
ProtectedData<DataType,Mutex>& ProtectedData<DataType,Mutex>::operator=(const ProtectedData& a_data)
{
    {
        ::std::lock_guard<::std::mutex> aGuard(a_data.m_mutex);

        {
            ::std::lock_guard<::std::mutex> aGuard(m_mutex);
            m_data = a_data.m_data;
        }
    }

    return *this;
}


template <typename DataType, typename Mutex>
ProtectedData<DataType,Mutex>& ProtectedData<DataType,Mutex>::operator=(ProtectedData&& a_data)
{
    {
        ::std::lock_guard<::std::mutex> aGuard(m_mutex);
        m_data = ::std::move(a_data.m_data);
    }

    return *this;
}


template <typename DataType, typename Mutex>
ProtectedData<DataType,Mutex>::operator DataType()const
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    return m_data;
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::lock()const
{
    m_mutex.lock();
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::unlock()const
{
    m_mutex.unlock();
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
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    m_data = a_data;
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::SetDataM(DataType& a_data)
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    m_data = ::std::move(a_data);
}


template <typename DataType, typename Mutex>
void ProtectedData<DataType,Mutex>::SetDataM(DataType&& a_data)
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    m_data = ::std::move(a_data);
}


template <typename DataType, typename Mutex>
DataType ProtectedData<DataType,Mutex>::data()const
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    return m_data;
}


}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
