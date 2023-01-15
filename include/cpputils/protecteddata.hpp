//
// file:			protecteddata.hpp
// path:			include/cpputils/protecteddata.hpp
// created on:		2022 May 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
#define CPPUTILS_INCLUDE_PROTECTEDDATA_HPP


#include <cpputils/export_symbols.h>
#include <stddef.h>
#include <cinternal/disable_compiler_warnings.h>
#include <mutex>


namespace cpputils {

template <typename DataType, typename Mutex=::std::mutex>
class ProtectedData
{
public:
    template<typename... Targs>
    ProtectedData(Targs... a_args);

    ProtectedData& operator=(const ProtectedData& a_data);
    ProtectedData& operator=(ProtectedData&& a_data);
    operator DataType()const;

    void lock()const;
    void unlock()const;
    const DataType& dataNoLock()const;
    DataType& dataNoLock();
    void SetDataC(const DataType& a_data);
    void SetDataM(DataType& a_data);
    void SetDataM(DataType&& a_data);
    DataType data()const;

private:
    mutable Mutex           m_mutex;
    DataType                m_data;
};


}  // namespace cpputils {

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
#include "protecteddata.impl.hpp"
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
