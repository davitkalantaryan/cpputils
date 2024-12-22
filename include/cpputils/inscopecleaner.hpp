//
// file:			inscopecleaner.hpp
// path:			include/cpputils/inscopecleaner.hpp
// created on:		2021 Mar 31
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_INSCOPECLEANER_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_INSCOPECLEANER_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/functional.hpp>



namespace cpputils {


class CPPUTILS_EXPORT InScopeCleaner
{
public:
	typedef ::cpputils::function< CPPUTILS_FUNC_ARGS(void,void*) > TypeDeleteFunc;
	
public:
	InScopeCleaner(TypeDeleteFunc a_func, void* a_pClbkData=CPPUTILS_NULL);
	~InScopeCleaner();

#ifdef CPPUTILS_CPP_11_DEFINED
    InScopeCleaner(const InScopeCleaner&) = delete;
    InScopeCleaner(InScopeCleaner&&) = delete;
    InScopeCleaner& operator=(const InScopeCleaner&) = delete;
    InScopeCleaner& operator=(InScopeCleaner&&) = delete;
#endif
	
public:
    const TypeDeleteFunc	m_func;
    void*const              m_clbkData;
private:
#ifdef CPPUTLS_32_BIT
	char			m_vcCh[4];
#endif
};


}  // namespace cpputils {




#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_INSCOPECLEANER_HPP
