//
// repo:			cpputils
// file:			main_deadlockfreemutexes_test.cpp
// path:			src/tests/main_deadlockfreemutexes_test.cpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cpputils/deadlockfreemutexes.hpp>
#include <mutex>
#include <thread>
#include <stdio.h>
#include <stdlib.h>


static void MakeTestsBig(int a_outTestNumber, int a_innerTestCount);


int main(int a_argc, char* a_argv[])
{
    int nNumberOfTests = 1;
    int nInnerTestsCount = 1;
    
    fprintf(stdout,"Press any key, then enter to continue! ");
    fflush(stdout);
    getchar();
    
    if(a_argc>1){
        nNumberOfTests = atoi(a_argv[1]);
        if(nNumberOfTests<1){
            nNumberOfTests = 1;
        }
    }
    
    if(a_argc>2){
        nInnerTestsCount = atoi(a_argv[2]);
        if(nInnerTestsCount<1){
            nInnerTestsCount = 1;
        }
    }
    
    for(int i(0); i<nNumberOfTests; ++i){
        MakeTestsBig(i,nInnerTestsCount);
    }
    
    return 0;
}


static void MakeTests(int a_outTestCount, int a_innerTestNumber);
static ::cpputils::mutex::DeadlockFreeMutexes< ::std::recursive_mutex>* s_pMutexes = nullptr;

static void MakeTestsBig(int a_outTestNumber, int a_innerTestCount)
{
    ::std::recursive_mutex mutex1;
    ::std::recursive_mutex mutex2;
    ::std::recursive_mutex mutex3;
    ::std::recursive_mutex mutex4;
    ::std::recursive_mutex mutex5;
    
    const ::std::vector<::std::recursive_mutex* >  vMutexes({&mutex1,&mutex2,&mutex3,&mutex4,&mutex5});
    
    s_pMutexes = new ::cpputils::mutex::DeadlockFreeMutexes< ::std::recursive_mutex>(vMutexes);
    
    for(int i(0); i<a_innerTestCount; ++i){
        MakeTests(a_outTestNumber,i);
    }
    
    delete s_pMutexes;
    s_pMutexes = nullptr;
    
}


static void ThreadFunction1(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction2(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction3(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction4(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction5(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction6(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction7(int a_outTestNumber, int a_innerTestNumber);
static void ThreadFunction8(int a_outTestNumber, int a_innerTestNumber);


static void MakeTests(int a_outTestCount, int a_innerTestNumber)
{    
    ::std::thread  thread1 = ::std::thread(&ThreadFunction1,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread2 = ::std::thread(&ThreadFunction2,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread3 = ::std::thread(&ThreadFunction1,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread4 = ::std::thread(&ThreadFunction8,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread5 = ::std::thread(&ThreadFunction3,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread6 = ::std::thread(&ThreadFunction4,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread7 = ::std::thread(&ThreadFunction5,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread8 = ::std::thread(&ThreadFunction6,a_outTestCount,a_innerTestNumber);
    ::std::thread  thread9 = ::std::thread(&ThreadFunction7,a_outTestCount,a_innerTestNumber);
    
    thread9.join();
    thread8.join();
    thread7.join();
    thread6.join();
    thread5.join();
    thread4.join();
    thread3.join();
    thread2.join();
    thread1.join();
}


static void ThreadFunction1(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(0);
    s_pMutexes->lock(1);
    s_pMutexes->lock(2);
    s_pMutexes->lock(3);
    s_pMutexes->lock(4);
    
    s_pMutexes->unlock(0);
    s_pMutexes->unlock(1);
    s_pMutexes->unlock(2);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(4);
    
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction2(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    ::cpputils::orderedcalls::Guard<::std::recursive_mutex> aGuard1(s_pMutexes,4);
    ::cpputils::orderedcalls::Guard<::std::recursive_mutex> aGuard2(s_pMutexes,3);
    ::cpputils::orderedcalls::Guard<::std::recursive_mutex> aGuard3(s_pMutexes,2);
    ::cpputils::orderedcalls::Guard<::std::recursive_mutex> aGuard4(s_pMutexes,1);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction3(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(4);
    s_pMutexes->lock(1);
    s_pMutexes->lock(3);
    s_pMutexes->lock(2);
    s_pMutexes->lock(4);
    
    s_pMutexes->unlock(4);
    s_pMutexes->unlock(1);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(2);
    s_pMutexes->unlock(4);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction4(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(0);
    s_pMutexes->lock(0);
    s_pMutexes->lock(3);
    s_pMutexes->lock(3);
    s_pMutexes->lock(2);
    
    s_pMutexes->unlock(0);
    s_pMutexes->unlock(0);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(2);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction5(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(1);
    s_pMutexes->lock(0);
    s_pMutexes->lock(2);
    s_pMutexes->lock(3);
    s_pMutexes->lock(4);
    
    s_pMutexes->unlock(1);
    s_pMutexes->unlock(0);
    s_pMutexes->unlock(2);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(4);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction6(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(0);
    s_pMutexes->lock(1);
    s_pMutexes->lock(2);
    s_pMutexes->lock(3);
    s_pMutexes->lock(2);
    
    s_pMutexes->unlock(0);
    s_pMutexes->unlock(1);
    s_pMutexes->unlock(2);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(2);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction7(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(0);
    s_pMutexes->lock(1);
    s_pMutexes->lock(2);
    s_pMutexes->lock(3);
    s_pMutexes->lock(0);
    
    s_pMutexes->unlock(0);
    s_pMutexes->unlock(1);
    s_pMutexes->unlock(2);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(0);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}


static void ThreadFunction8(int a_outTestNumber, int a_innerTestNumber)
{
    printf("%s starts (out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
    s_pMutexes->lock(4);
    s_pMutexes->lock(1);
    s_pMutexes->lock(2);
    s_pMutexes->lock(3);
    s_pMutexes->lock(4);
    
    s_pMutexes->unlock(4);
    s_pMutexes->unlock(1);
    s_pMutexes->unlock(2);
    s_pMutexes->unlock(3);
    s_pMutexes->unlock(4);
    printf("%s ends(out:%d,in:%d)\n",__FUNCTION__,a_outTestNumber,a_innerTestNumber);
    fflush(stdout);
}
