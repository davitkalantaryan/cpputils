//
// file:			protecteddata.hpp
// path:			include/cpputils/protecteddata.hpp
// created on:		2022 May 27
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
#define CPPUTILS_INCLUDE_PROTECTEDDATA_HPP


#include <cpputils_internal_header.h>
#include <stddef.h>
#include <cpputils/disable_compiler_warnings.h>
#include <mutex>


namespace cpputils {

template <typename DataType>
class ProtectedData
{
public:
    template<typename... Targs>
    ProtectedData(Targs... a_args);

    void operator=(const DataType& a_data);
    void operator=(DataType&& a_data);
    operator DataType()const;

private:
    mutable ::std::mutex    m_mutex;
    DataType        m_data;
};


}  // namespace cpputils {

#ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_IMPL_HPP
#include "protecteddata.impl.hpp"
#endif


#endif  // #ifndef CPPUTILS_INCLUDE_PROTECTEDDATA_HPP
