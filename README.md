# cpputils
Repository for some general purpose classes  
  
## existing classes and utils    
Following is the list of already created classes and utils (macroses)  
  
  
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
Hash table related classes can be found in the header [hashtbl.hpp](include/cpputils/hashtbl.hpp). 
These containers are associative with average constant-time complexity of search, insertion, and removal (`O(1)`).
In general this class will beheave very similar to [`std::unordered_map`](https://en.cppreference.com/w/cpp/container/unordered_map).  
  
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
  
Up to now this class is tested on gcc Linux and on Windows with microsoft compiler. Should work also on other platforms with proper c++ 
compile (will be tested).  
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
Implementation is in the file [enums.hpp](include/cpputils/ens.hpp).  
For similar implementation look  
 1. https://github.com/aantron/better-enums  
 2. https://github.com/Neargye/magic_enum  
  
Cases when you will preffer to use this.  
 1. No c++ 11 or higher (magic enum requires c++ 17 and higher).  
 2. In the case of better enum, there is no possibility to declare enum 
inside class or inside function, because in the macros there is a declaration of namespaces.  
  
#### limitations  
For now thiwl work only in the case if we sequential enumeration  
