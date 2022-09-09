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

template <typename DataType>
template<typename... Targs>
ProtectedData<DataType>::ProtectedData(Targs... a_args)
    :
      m_data(a_args...)
{
}


template <typename DataType>
void ProtectedData<DataType>::operator=(const DataType& a_data)
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    m_data = a_data;
}

template <typename DataType>
void ProtectedData<DataType>::operator=(DataType&& a_data)
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    m_data = ::std::move(a_data);
}


template <typename DataType>
ProtectedData<DataType>::operator DataType()const
{
    ::std::lock_guard<::std::mutex> aGuard(m_mutex);
    return m_data;
}


template <typename DataType>
void ProtectedData<DataType>::lock()const
{
    m_mutex.lock();
}


template <typename DataType>
void ProtectedData<DataType>::unlock()const
{
    m_mutex.unlock();
}

template <typename DataType>
const DataType& ProtectedData<DataType>::dataNoLock()const
{
    return m_data;
}


template <typename DataType>
DataType& ProtectedData<DataType>::dataNoLock()
{
    return m_data;
}


}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
