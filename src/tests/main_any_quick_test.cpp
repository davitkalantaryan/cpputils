

#include <cpputils/hashtbl.hpp>
#include <cpputils/bigint.hpp>
#include <cpputils/functional_old.hpp>
#include <cpputils/sharedptr.hpp>
#include <cpputils/endian.hpp>
#include <cpputils/enums.hpp>
#include <cpputils/enums/fast.hpp>
//#include <cpputils/enums/full.hpp>
#include <cpputils/tls_data.hpp>
#include <cpputils/hash/hash.hpp>
#include <cpputils/hash/vhash.hpp>
#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <unordered_map>
#include <thread>
#include <time.h>
#include <stdlib.h>
#ifdef _WIN32
#define sleep(_x)	Sleep(1000*(_x))
#else
#include <unistd.h>
#endif

#define USE_STD_MAP


//#define TESTS_COUNT	150000000

#ifdef TESTS_COUNT

#ifdef	USE_STD_MAP
typedef std::unordered_multimap<int,int> TypeMap;
#define InsertElement(_key,_value)	insert(std::pair<int,int>(_key,_value))
#define MapFindEntry	count
#else
typedef cpputils::hashtbl::IntHash<int,int>	TypeMap;
#define InsertElement				AddEntryEvenIfExists
#define MapFindEntry				FindEntry
#endif

#endif


int main()
{
    //{
    //    cpputils::hash::VHash<int,int> aHash;
    //    
    //    aHash.AddEntryIfNotExistC(std::pair<int,int>(1,1));
    //    aHash.AddEntryIfNotExistC(std::pair<int,int>(1,1));
    //    aHash.AddEntryIfNotExistC(std::pair<int,int>(2,1));
    //    aHash.AddEntryIfNotExistC(std::pair<int,int>(3,1));
    //    
    //    cpputils::hash::VSet<int> aSet;
    //    
    //    aSet.AddEntryIfNotExistC(1);
    //    aSet.AddEntryIfNotExistC(1);
    //    aSet.AddEntryIfNotExistC(1);
    //    aSet.AddEntryIfNotExistC(1);
    //    
    //    ::std::cout<<aSet.at(0)->first<<std::endl;
    //    
    //    return 0;
    //}
    
    
    {
        cpputils::hash::VHash<int,int> aHash;
        
        ::std::cout<<aHash.AddEntryIfNotExistC(std::pair<int,int>(1,1))<<::std::endl;
        ::std::cout<<aHash.AddEntryIfNotExistC(std::pair<int,int>(1,1))<<::std::endl;
        ::std::cout<<aHash.AddEntryIfNotExistC(std::pair<int,int>(2,1))<<::std::endl;
        ::std::cout<<aHash.AddEntryIfNotExistC(std::pair<int,int>(3,1))<<::std::endl;
        
        cpputils::hash::VSet<int> aSet;
        
        ::std::cout<<aSet.AddEntryIfNotExistC(1)<<::std::endl;
        ::std::cout<<aSet.AddEntryIfNotExistC(1)<<::std::endl;
        ::std::cout<<aSet.AddEntryIfNotExistC(1)<<::std::endl;
        ::std::cout<<aSet.AddEntryIfNotExistC(1)<<::std::endl;
        
        ::std::cout<<aSet[0]<<std::endl;
        
        //cpputils::hash::VHash<int,int> aVHash;
        //::std::cout<<aVHash.AddEntryIfNotExistC(std::pair<int,int>(1,1))<<::std::endl;
        
        for(const auto& aElem : aSet){
            ::std::cout<<aElem.first<<std::endl;
        }
        
        return 0;
    }
    
    
	{
		void* pPtr = nullptr;
		int nData     = static_cast<int>(reinterpret_cast<size_t>(pPtr));
		size_t unData = static_cast<size_t>(reinterpret_cast<size_t>(pPtr));
		int* pData = ((int*)((size_t)pPtr));
		
		std::cout << pData << unData << nData << std::endl;
		pPtr = reinterpret_cast<void*>( static_cast<size_t>(nData) );
		//pPtr = (void*)((size_t)pData);
		
		std::cout << pPtr << std::endl;
	}
	
	
	{
		cpputils::tls_data<int> aPtr;
		std::cout << aPtr << std::endl;
		aPtr = 1; 
		std::cout << aPtr << std::endl;
	}
	
	{
		bool bWait = true;
		struct TestClass{
		~TestClass(){std::cout<< __FUNCTION__ <<std::endl;}
		};
		cpputils::tls_unique_ptr<TestClass>* pTlsPtr = new cpputils::tls_unique_ptr<TestClass>;
		cpputils::tls_unique_ptr<TestClass>& tlsPtr = *pTlsPtr;
		tlsPtr = new TestClass;
		std::cout << "tlsPtr[fromMain]="<<tlsPtr.get()<<std::endl;  // here we see some value
		std::thread aThread([&tlsPtr,&bWait](){
			std::cout << "tlsPtr[other1]="<<tlsPtr.get()<<std::endl; // here we see null, and this shows diff.
			tlsPtr = new TestClass;
			std::cout << "tlsPtr[other1]="<<tlsPtr.get()<<std::endl; // here we see some value
			bWait = false;
			sleep(10);
		});
		while(bWait){
			sleep(1);
		}
		delete pTlsPtr;
		aThread.join(); // after join we will see one destructor called, this is because of thread exit
	}
	
	{
		struct TestClass{
		~TestClass(){std::cout<< __FUNCTION__ <<std::endl;}
		};
		cpputils::tls_unique_ptr<TestClass> tlsPtr;
		tlsPtr = new TestClass;
		std::cout << "tlsPtr[fromMain]="<<tlsPtr.get()<<std::endl;  // here we see some value
		std::thread aThread([&tlsPtr](){
			std::cout << "tlsPtr[other1]="<<tlsPtr.get()<<std::endl; // here we see null, and this shows diff.
			tlsPtr = new TestClass;
			std::cout << "tlsPtr[other1]="<<tlsPtr.get()<<std::endl; // here we see some value
		});
		aThread.join(); // after join we will see one destructor called, this is because of thread exit
	}
	
	{
		// todo: implement this
		//struct TestClass{
		//~TestClass(){std::cout<< __FUNCTION__ <<std::endl;}
		//};
		//cpputils::tls_unique_ptr<TestClass[]> tlsPtr;
		//tlsPtr = new TestClass[5];
		//std::cout << "tlsPtr[fromMain]="<<tlsPtr.get()<<std::endl;  // here we see some value
		//std::thread aThread([&tlsPtr](){
		//	std::cout << "tlsPtr[other1]="<<tlsPtr.get()<<std::endl; // here we see null, and this shows diff.
		//	tlsPtr = new TestClass;
		//	std::cout << "tlsPtr[other1]="<<tlsPtr.get()<<std::endl; // here we see some value
		//});
		//aThread.join(); // after join we will see one destructor called, this is because of thread exit
	}
	
#ifdef TESTS_COUNT
	{
		int i, acurances=0;
		TypeMap aMap(1000000);
		time_t begTime, finTime;
		
		begTime = time(&begTime);
		
		for(i=0;i<TESTS_COUNT;++i){
			aMap.InsertElement( i,i);
		}
		
		for(i=0;i<1000000;++i){
			if(aMap.MapFindEntry( rand() )){++acurances;}
		}
		
		finTime = time(&finTime);
		
		printf("(finTime-begTime)=%d, acurances=%d, press '1' then enter to continue",static_cast<int>(finTime-begTime),acurances);
		fflush(stdout);
		while(getchar()!='1')
			;
		
		aMap.clear();
		printf("aMap.size()=%d, press '1' then enter to continue", static_cast<int>(aMap.size()));fflush(stdout);
		while(getchar()!='1')
			;
	}
	
	printf("Map deleted, press '1' then enter to continue");fflush(stdout);
	while(getchar()!='1')
		;
	
#endif // #ifdef TESTS_COUNT
	
	{
		cpputils::hashtbl::Base<int,int> aHash;
		
		aHash.AddEntryIfNotExist(1,1);
		aHash.AddEntryEvenIfExists(1,1);
	}
	
	{
		cpputils::hashtbl::Base<int,int> aHash;
		
		aHash.AddEntryIfNotExist(1,1);
		aHash.AddEntryEvenIfExists(1,1);
	}
	
	{
		cpputils::hashtbl::Base<int,void> aHash;
		
		aHash.AddEntryIfNotExist(1);
		aHash.AddEntryIfNotExist(2);
	}
	
	
	{
		int a=1;
		cpputils::hashtbl::VoidPtrHash<int> aHash;
		
		aHash.AddEntryIfNotExist({&a,4},1);
		aHash.AddEntryEvenIfExists({&a,4},1);
		aHash.FindEntry({&a,4});
	}
	
	{
		cpputils::hashtbl::Set<int> aHash;
		//cpputils::hashtbl:: Base<int,void> aHash;
		
		size_t unHash;
		aHash.AddEntryIfNotExist(1);
		
		aHash.FindEntry(2,&unHash);
		aHash.AddEntryWithKnownHash(2,unHash);
	}
	
	{
		cpputils::BigInt<1> a1(2);
		cpputils::BigInt<1> a2(5);
		cpputils::BigInt<1> a4 = 100000000000000000000_bi01 / 1000000000000000000_bi01;
		//cpputils::BigInt<1> a3 = ;
		int ia1 = static_cast<int>(a1+a2);
		int ia2 = static_cast<int>(a1-a2);
		//std::make_unsigned< cpputils::BigInt<1> > ua;
		std::cout << "ia1="<<ia1<<std::endl;
		std::cout << "ia2="<<ia2<<std::endl;
		std::cout << "a1+a2="<<a1+a2<<std::endl;
		std::cout << "a1-a2="<<a1-a2<<std::endl;
		std::cout << "2*a1-a2*3="<<2*a1-a2*3<<std::endl;
		std::cout << "a4=" << a4 << std::endl;
	}

#if 0
	{
		cpputils::BigUInt<1> aMask2, aMask;

		for (uint64_t i(0); i < cpputils::BigUInt<1>::s_lastIndexInBuff; ++i) { aMask.buff()[i] = 0; }
		aMask.buff()[cpputils::BigUInt<1>::s_lastIndexInBuff] = MASK_SIGN_BIT;
		
		aMask2 = aMask;

		aMask = aMask2;
		aMask >>= 63;

		aMask = aMask2;
		aMask >>= 127;

		aMask2 = aMask;

		aMask = aMask2;
		aMask <<= 63;

		aMask = aMask2;
		aMask <<= 127;

		cpputils::BigUInt<1> bui1 = 100000000000000000000_bui01;
		bui1 /= 10;
		std::cout << bui1/10;
	}
	
	{
		long a = 1;
		unsigned long int b = 1;
		decltype (a+b) c = 3;
		decltype (a-b) d = 3;
		decltype (a*b) e = 3;
		decltype (a/b) f = 3;
		
		decltype (b+a) g = 3;
		decltype (b-a) h = 3;
		decltype (b*a) i = 3;
		decltype (b/a) j = 3;
		
		std::cout<<"\n\n";
		
		std::cout << "typeid(a).name() = "<<typeid (a).name() << std::endl;
		std::cout << "typeid(b).name() = "<<typeid (b).name() << std::endl;
		
		std::cout << "typeid(c).name() = "<<typeid (c).name() << std::endl;
		std::cout << "typeid(d).name() = "<<typeid (d).name() << std::endl;
		std::cout << "typeid(e).name() = "<<typeid (e).name() << std::endl;
		std::cout << "typeid(f).name() = "<<typeid (f).name() << std::endl;
		
		std::cout << "typeid(g).name() = "<<typeid (g).name() << std::endl;
		std::cout << "typeid(h).name() = "<<typeid (h).name() << std::endl;
		std::cout << "typeid(i).name() = "<<typeid (i).name() << std::endl;
		std::cout << "typeid(j).name() = "<<typeid (j).name() << std::endl;
	}
	
	{		
		cpputils::function_old< FUNC_ARGS_OLD(size_t,const int&) > aFn([](const int& a_val){
			return static_cast<size_t>(a_val);
		});
		
		aFn(1);
	}
	
	{
		cpputils::SharedPtr<int> aPtr02 ( new int);
		
		*aPtr02 = 1;
		
		std::cout << *aPtr02 << std::endl;
	}
	
	{
		CPPUTILS_ENUM_FAST(Enum1,int,Red,Blue);		
		Enum1 aBlue = Enum1::Blue;
		std::cout << aBlue.toString() << std::endl;

		//CPPUTILS_ENUM_FULL(Enum2, int, Red, Blue);
	}
	
	{
		//enum class TestEnum : char {a,b,c};
		//TestEnum a = TestEnum::a;
	}
    
#endif
	
	
	return 0;
}
