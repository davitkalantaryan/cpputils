//
// file:			common_inscopecleaner.cpp
// path:			src/common/common_inscopecleaner.cpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <common/inscopecleaner.hpp>

namespace __private { namespace __implementation {
}}  // namespace __private { namespace __implementation {


namespace common {

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

}  // namespace common {
