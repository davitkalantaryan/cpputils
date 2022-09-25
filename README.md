# cpputils
Repository for some general purpose classes and macroses. 
Up to now these classes and macroses are tested on gcc Linux, Windows microsoft compiler, Mac with clang and emscripten. 
Should work also on other platforms with proper c++ compiler
  
## existing classes and utils    
Following is the list of already created classes and utils (macroses)  
  
  
### tls_unique_ptr  
This is temlate class that will hold pointer to object of temlate argument. The pointer will vary 
from thread to thread. This is somehow smart pointer and thread specific pointer will be 
deleted on thread exit or when the object of `tls_unique_ptr` destroyed. This is a
bit similar to `c++11` `thread_local`, or compiler specific `__thread` (for gcc and family) 
or `__declspec(thread)` (for MC). 
The difference of this class is that this class can be declared as class member. 
All classes on thread local storage are in the header [tls_data.hpp](include/cpputils/tls_data.hpp)  

``` cpp  

#include <thread>
#include <iostream>
#include <cpputils/tls_data.hpp>

int main()
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
    return 0;  // during main thread cleanup we will see second destructor called
}
```  

To organize shared TLS ptr, use following:  

``` cpp  
template <typename TlsType>
using tls_shared_ptr = std::shared_ptr< cpputils::tls_unique_ptr<TlsType> > ;
```  

For more examples check the file [0007_tls_data.cpp](src/tests/googletest/0007_tls_data.cpp)
  
  
### Macroses  
There are some macroses can be used to ease several problems. These macroses are 
defined in the header [macroses.h](include/cpputils/macroses.h). Following is the list of macroses those 
can be usefull  
 1. `CPPUTILS_NARGS`. This macros calculates number of argumets. `CPPUTILS_NARGS(1,a,"hi")` is `3`. Number of 
args will be properly calculated is in this range `[1..99]`.  
 2. `CPPUTILS_NAMES`. This macros stringifies all provided arguments and delimates thgem by coma.
`CPPUTILS_NAMES(a,b,c)` is `"a","b","c"`. Number of arguments properly handled by this macros is `[0..99]`. 
be aware, if you have `CPPUTILS_NAMES(a,b,"c")`, then resulting string will be `"ab\"c\""`. 
See examples in [0005_macroses.cpp](src/tests/googletest/0005_macroses.cpp)
  
  
### Hash tables  
Hash table related classes can be found in the header [hashtbl.hpp](include/cpputils/hashtbl.hpp). The Hashes in this header will be soon depricated and later on removed.  
The newer headers for different type of hashes one can find in the forder `include/cpputils/hash`.  
These containers are associative with average constant-time complexity of search, insertion, and removal (`O(1)`).
In general this class will beheave very similar to [`std::unordered_map`](https://en.cppreference.com/w/cpp/container/unordered_map).  
  
  
#### Advantage over std hash  
 1. These classes make possible to search data and cache hash value meanwhile, then there is a possinilty to add data with the hash found during the search.
 This API is looks like following:  

  
```cpp  
Output   find( const Key& key, size_t* a_pHash=CPPUTILS_NULL )const;  
Output   AddEntryWithKnownHashC(const Input& a_item, size_t a_hash);  
```  

This will lead to performance boost, when data for hash should not be created if it is already added (for example creation is heavy thing, or 
for each key second instance should not be created). In this case first thing to do is asking if data with the interested key is present (call `find`),
then if data for the key is not there data should be created and added. With standard `std::unordered_map` hashing for the same key will be done second time,
while with the Hashes from here this will be skipped.  
If the application is heavy depends on this kind of situations (check then create and add), then there willl be quite good performance boost.  
Better approach of this will be to have variable number of arguments for functions requiring hash calculation (`find`,`insert`,...). In this case the constructor of the 
`Hash` instance to calculate hash of the key
should be called with that variable number of arguments in the hash table implementetion 
(hashes here or will be nice to have similar feature for `::std::unordered_map` and friends) (see example code below)  
  
```cpp  
class AnyHash
{
    ...
	template<typename... Targs>
	Output  find(const Key& a_key,Targs... a_args){
	   Hash fnHash(a_args...);
	   const size_t unHash = fnHash(a_item.first)&m_unRoundedTableSizeMin1;
	   ...
	}

	Output  AddEntryWithKnownHash(const Key& a_key, const Data& a_data, Targs... a_args){
	   Hash fnHash(a_args...);
	   const size_t unHash = fnHash(a_item.first)&m_unRoundedTableSizeMin1;
	   ...
	}
};
```  
  
This method will be more generic implementation and may be will have some more use cases (than described above (necessity to check then add))  

  
 2. Stop iterators (equivalent to `end`, `cend`, `rend`, `crend` for std containers) are constant definations and working with them is faster
 than in the case of standard containers.  
   
   
#### example code  
See the file [0012_hash_dllhash.cpp](src/tests/googletest/0012_hash_dllhash.cpp). DllHash stands for Double linked list Hash.  
  
```cpp  
TEST(f_0012_hash_dllhash, t0002)
{
	typedef ::cpputils::hash::DllHash<int,::std::string> TypeHash1;
	TypeHash1 aHash;
	size_t unHash0, unHash;

	const TypeHash1::const_iterator iter1 = aHash.find(1,&unHash0);
	if (iter1 == TypeHash1::s_constNullIter) {
		// we have to create ::std::string object
		aHash.AddEntryWithKnownHashMv(::std::pair<int, ::std::string>(1, "One"), unHash0);
	}

	
	const TypeHash1::const_iterator iter2 = aHash.find(1, &unHash);
	ASSERT_FALSE(iter2== TypeHash1::s_constNullIter);
	ASSERT_EQ(unHash, unHash0);
	ASSERT_STREQ("One", iter2->second.c_str());
}
```  
  
  
#### Types of hash tables and sets  
In order to iterate over hash table elements quickly there are some hash tables and sets that elements 
are not stored in the hash table buckets, but also stored like vecrores or like list(s).  
  
 1. Hash,    Set   => Pure hash and pure set. Has related operd memory layout is the best but iterations are very slow. File: [hash.hpp](include/cpputils/hash/hash.hpp)  
 2. LHash,   LSet  => Elements are ordered as single linked link, last added element is the firs in the list. File: [lhash.hpp](include/cpputils/hash/lhash.hpp)  
 3. DllHash, llSet => Double linked list Hash. File: [dllhash.hpp](include/cpputils/hash/dllhash.hpp)  
 4. VHash,   VSet  => Elements are layed out also as vector data, so one can access them also using idexes. File: [dllhash.hpp](include/cpputils/hash/dllhash.hpp)
  
#### Use cases  
In the case if `C++ 11` or upper is used, one can use [`std::unordered_map`](https://en.cppreference.com/w/cpp/container/unordered_map) 
for most of cases. So the cases, when these containers will be usefull are following  
 1. when older than `C++ 11` compiler is used  
 2. when we have complex data as key with difficulty to have properer hash for it.  
   
Example of using these classes one can find in test source file [0001_hash.cpp](src/tests/googletest/0001_hash.cpp) .  
  
  
### Big integers  
Implemented compatible big integers (signed and unsigned). The clases are template classes, with `size_t` template argument 
(see [bigint.hpp](include/cpputils/bigint.hpp)). The meaning of template argument one can see from code snippet below  
  
``` cpp  
  
template <uint64_t NUM_QWORDS_DEGR>  
class BigUInt  
{  
	// ...  
private:  
	uint64_t	m_buff[1<<NUM_QWORDS_DEGR];  
};  
  
```  
  
This class is possible to cast to any number type and vise versa any numeric type is possible to cast to this class. 
In the case if `C++ 11` or newer compiler is used, one can also use literals for these classes (see code snippet below)   
  
``` cpp  
  
cpputils::BigInt<1> a4 = 100000000000000000000_bi01; // = 10^20
    
```  

All (or almost all, you see something missing, please inform and it will be implemented) opreators valid for builtin 
integers valid also for these classes.  
  
Example of using these classes one can find in test source file [0002_bigint.cpp](src/tests/googletest/0002_bigint.cpp) .  
  
  
### function class  
This is like c++ 11 [`std::function`](https://en.cppreference.com/w/cpp/utility/functional/function). 
This class defined in the header [`cpputils/functional_old.hpp`](include/cpputils/functional_old.hpp). 
One can use this when old compiler is in use. The header [`cpputils/functional.hpp`](include/cpputils/functional.hpp) makes 
corresponding calcutaion of compiler version and uses `std::function` when c++11 or higher is used. In this file you will find something like this  
```cpp  
    
#ifdef CPPUTILS_CPP_11_DEFINED  
  
template <class ...Args>  
using  function =  ::std::function<Args...>;  
  
#else  
  
#define function	function_old  

#endif  
  
```  
  
Example of usage  
``` cpp  
  
// this is bad example, because lambda function is used, this means you can use std::function  
cpputils::function_old< FUNC_ARGS_OLD(size_t,const int&) > aFn01([](const int& a_val){  
	return static_cast<size_t>(a_val);  
});  
  
static size_t SumStatic(int a_val1, int a_val2, int a_val3)   
{  
	return static_cast<size_t>(a_val1+a_val2+a_val3);  
}  
  
int main()  
{  
	cpputils::function_old< FUNC_ARGS_OLD(size_t,int,int,int) > aFn02;  
	aFn02 = &SumStatic;  
	  
	std::cout<<aFn02(1,2,3);  // this will output 6  
	  
	return 0;  
}  
  
```  
  
Example that illustrates of usage header  [`cpputils/functional.hpp`](include/cpputils/functional.hpp)  
``` cpp  
  
#include <cpputils/functional.hpp>  
  
static size_t SumStatic(int a_val1, int a_val2, int a_val3)  
{  
	return static_cast<size_t>(a_val1+a_val2+a_val3);  
}  
  
int main()  
{  
	// line below will use std::function for c++11 and newer compiler and cpputils::function_old for old compilers    
	cpputils::function< FUNC_ARGS_OLD(size_t,int,int,int) > aFn02(&SumStatic);  
  	  
	std::cout<<aFn02(1,2,3);  // this will output 6  
	  
	return 0;  
}  
  
```  
Other examples one can find from [`0003_function_old.cpp`](src/tests/googletest/0003_function_old.cpp)  
  
  
### SharedPtr class  
This is like [`std:;shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr). 
Use cases of this:  
 1. cppstandard is olller than c++ 11  
 2. Callback is needed for all number of references  
 
  
Details will be provided later.  
  
### InScopeCleaner class  
Will be documented later  
  
  
### macros CPPUTILS_ENUM01  
Implementation is in the file [enums.hpp](include/cpputils/enums.hpp).  
For similar implementation look  
 1. https://github.com/aantron/better-enums  
 2. https://github.com/Neargye/magic_enum  
  
Cases when you will preffer to use this.  
 1. No c++ 11 or higher (magic enum requires c++ 17 and higher).  
 2. In the case of better enum, there is no possibility to declare enum 
inside class or inside function, because in the macros there is a declaration of namespaces.  
  
  
#### limitations  
For now this willl work only in the case if we sequential enumeration.  
This means not possible to declare enum like `enum Type{a=1,b,c};` (not possible to use `=` in declaration).  
