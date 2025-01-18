//
// file:			0007_tls_ptr.cpp
// created on:		2021 Apr 22
//

#include <cpputils/export_symbols.h>
#ifdef CPPUTILS_CPP_11_DEFINED
#include <cinternal/unit_test.h>
#include <cpputils/tls_data.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <stdlib.h>  
#include <stdio.h>  
#include <time.h>
#include <cinternal/undisable_compiler_warnings.h>

#define MAX_NUMBER_OF_THREADS	100
static size_t s_nNumberOfCreated = 0;
static size_t s_nNumberOfDeleted = 0;
static ::std::mutex s_mutex;


class TestClass{
public:
	TestClass();
	~TestClass();
};



TEST(f_0007_tls_data, t0000_tls_data)
{
	cpputils::tls_data<int> aData;
	cpputils::tls_data<int>* pData=&aData;
	
	ASSERT_EQ(static_cast<int>(aData),0);
	aData = 1;
	ASSERT_EQ(static_cast<int>(aData),1);
	
	std::thread aThread([&aData,pData, CINTERNAL_UNIT_TEST_FN_ARGS_CAPTURE](){
		ASSERT_EQ(&aData,pData);
		ASSERT_EQ(static_cast<int>(aData),0); // we have other value inside thread
		aData = 2;
		ASSERT_EQ(static_cast<int>(aData),2);
	});
	
	aThread.join();
	ASSERT_EQ(static_cast<int>(aData),1); // we have old value, thread changed its own copy
}


TEST(f_0007_tls_data, t0001_tls_unique_ptr)
{
	size_t i, nNumberOfThreads;
	time_t currentTime;
	::std::vector< ::std::thread*>	vThreads;
	cpputils::tls_unique_ptr<TestClass>* pTlsPtr = new cpputils::tls_unique_ptr<TestClass>;
	
	*pTlsPtr = new TestClass;  // we have something
	ASSERT_NE(pTlsPtr->get(),nullptr);
	
	time(&currentTime);
	srand(static_cast<unsigned int>(currentTime));
	nNumberOfThreads = static_cast<size_t>(rand() % MAX_NUMBER_OF_THREADS);
	::std::cout << "number of threads: " << nNumberOfThreads << ::std::endl;
	vThreads.resize(nNumberOfThreads);
	for(i=0;i<nNumberOfThreads;++i){
		vThreads[i] = new ::std::thread([pTlsPtr, CINTERNAL_UNIT_TEST_FN_ARGS_CAPTURE](){
			ASSERT_EQ(pTlsPtr->get(),nullptr);  // we here have null
			*pTlsPtr = new TestClass;
		});
	}
	for(i=0;i<nNumberOfThreads;++i){
		vThreads[i]->join();
	}
	ASSERT_EQ(nNumberOfThreads,s_nNumberOfDeleted);
	ASSERT_EQ(s_nNumberOfCreated,s_nNumberOfDeleted+1);  // each thread deleted its copy
	// so we have one instance that not deleted, it will be deleted after ptr deletion
	delete pTlsPtr;
	ASSERT_EQ(s_nNumberOfCreated,s_nNumberOfDeleted);  // everything deleted
}


TEST(f_0007_tls_data, t0001_second)
{
	ASSERT_GE(s_nNumberOfCreated,s_nNumberOfDeleted);
}


TestClass::TestClass()
{
	::std::lock_guard< ::std::mutex> aGuard(s_mutex);
	++s_nNumberOfCreated;
}

TestClass::~TestClass()
{
	::std::lock_guard< ::std::mutex> aGuard(s_mutex);
	++s_nNumberOfDeleted;
}


#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
