//
// file:			protecteddata.impl.hpp
// path:			include/cpputils/protecteddata.impl.hpp
// created on:		2022 May 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
#define CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
#include <cpputils/protecteddata.hpp>
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <utility>
#include <mutex>
#include <shared_mutex>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils {


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::~ProtectedData()
{
    if(m_bOwnerOfMutex){
        delete m_pMutex;
    }
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData()
    :
    m_pMutex(new RwMutex()),
    m_bOwnerOfMutex(true)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(RwMutex* CPPUTILS_ARG_NN a_pMutex)
    :
    m_pMutex(a_pMutex),
    m_bOwnerOfMutex(false)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(const DataType& a_data)
    :
    m_pMutex(new RwMutex()),
    m_data(a_data),
    m_bOwnerOfMutex(true)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(const DataType& a_data, RwMutex* CPPUTILS_ARG_NN a_pMutex)
    :
    m_pMutex(a_pMutex),
    m_data(a_data),
    m_bOwnerOfMutex(false)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(DataType&& a_data)
    :
    m_pMutex(new RwMutex()),
    m_data(::std::move(a_data)),
    m_bOwnerOfMutex(true)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(DataType&& a_data, RwMutex* CPPUTILS_ARG_NN a_pMutex)
    :
    m_pMutex(a_pMutex),
    m_data(::std::move(a_data)),
    m_bOwnerOfMutex(false)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(const ProtectedData& a_cM)
    :
    m_pMutex(a_cM.m_bOwnerOfMutex ? (new RwMutex()) : a_cM.m_pMutex),
    m_data(a_cM.m_data),
    m_bOwnerOfMutex(a_cM.m_bOwnerOfMutex)
{
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::ProtectedData(ProtectedData&& a_mM)
    :
    m_pMutex(a_mM.m_pMutex),
    m_data(::std::move(a_mM.m_data)),
    m_bOwnerOfMutex(a_mM.m_bOwnerOfMutex)
{
    a_mM.m_bOwnerOfMutex = false;
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>& ProtectedData<DataType,RwMutex>::operator=(const ProtectedData& a_cM)
{
    {  //  lock guard 1
        ::std::lock_guard<RwMutex> unGuard(*m_pMutex);
        {  //  lock guard 2
            ::std::shared_lock<RwMutex> shGuard(*(a_cM.m_pMutex));
            m_data = a_cM.m_data;
        }  //  end of lock guard 2
    }  //  end of lock guard 1
    return *this;
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>& ProtectedData<DataType,RwMutex>::operator=(ProtectedData&& a_mM)
{
    {  //  lock guard
        ::std::lock_guard<RwMutex> unGuard(*m_pMutex);
        m_data = ::std::move(a_mM.m_data);
    }  //  end of lock guard
    return *this;
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>& ProtectedData<DataType,RwMutex>::operator=(const DataType& a_data)
{
    {  //  lock guard
        ::std::lock_guard<RwMutex> unGuard(*m_pMutex);
        m_data = a_data;
    }  //  end of lock guard
    return *this;
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>& ProtectedData<DataType,RwMutex>::operator=(DataType&& a_data)
{
    {  //  lock guard
        ::std::lock_guard<RwMutex> unGuard(*m_pMutex);
        m_data = ::std::move(a_data);
    }  //  end of lock guard
    return *this;
}


template <typename DataType, typename RwMutex>
ProtectedData<DataType,RwMutex>::operator DataType()const
{
    DataType aData;
    {  //  lock guard
        ::std::shared_lock<RwMutex> shGuard(*m_pMutex);
        aData = m_data;
    }  //  end of lock guard
    return aData;
}


}  // namespace cpputils {


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
