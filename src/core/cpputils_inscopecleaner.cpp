//
// file:			cpputils_inscopecleaner.cpp
// path:			src/core/cpputils_inscopecleaner.cpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/inscopecleaner.hpp>

namespace __private { namespace __implementation {
}}  // namespace __private { namespace __implementation {


namespace cpputils {

InScopeCleaner::InScopeCleaner(TypeDeleteFunc a_func, void* a_pClbkData)
	:
	  m_func(a_func),
	  m_clbkData(a_pClbkData)
{
}


InScopeCleaner::~InScopeCleaner()
{
	m_func(m_clbkData);
}

}  // namespace cpputils {
