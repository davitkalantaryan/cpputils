//
// file:			protecteddata.hpp
// path:			include/cpputils/protecteddata.hpp
// created on:		2022 May 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
#define CPPUTILS_INCLUDE_PROTECTEDDATA_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/recursive_rwlock.hpp>


namespace cpputils {


template <typename DataType, typename RwMutex=::cpputils::RecursiveRWLock>
class ProtectedData
{
public:
    ~ProtectedData();
    ProtectedData();
    ProtectedData(RwMutex* CPPUTILS_ARG_NN a_pMutex);
    ProtectedData(const DataType& a_data);
    ProtectedData(const DataType& a_data, RwMutex* CPPUTILS_ARG_NN a_pMutex);
    ProtectedData(DataType&& a_data);
    ProtectedData(DataType&& a_data, RwMutex* CPPUTILS_ARG_NN a_pMutex);
    ProtectedData(const ProtectedData& a_cM);
    ProtectedData(ProtectedData&& a_mM);

    ProtectedData& operator=(const ProtectedData& a_cM);
    ProtectedData& operator=(ProtectedData&& a_mM);
    ProtectedData& operator=(const DataType& a_data);
    ProtectedData& operator=(DataType&& a_data);
    operator DataType()const;

private:
    RwMutex* const          m_pMutex;
    DataType                m_data;
    bool                    m_bOwnerOfMutex;
};

}  // namespace cpputils {

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
#include <cpputils/protecteddata.impl.hpp>
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
