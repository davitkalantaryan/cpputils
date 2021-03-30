# cpputils
Repository for some general purpose classes  
  
## existing classes  
Following is the list of already created classes  
  
### Hash tables  
Hash table related classes can be found in the header [hashtbl.hpp](include/common/hashtbl.hpp). 
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
(see [bigint.hpp](include/common/bigint.hpp)). The meaning of template argument one can see from code snippet below  
  
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
  
common::BigInt<1> a4 = 100000000000000000000_bi01; // = 10^20
    
```  

All (or almost all, you see something missing, please inform and it will be implemented) opreators valid for builtin 
integers valid also for these classes.  
  
Example of using these classes one can find in test source file [0002_bigint.cpp](src/tests/googletest/0002_bigint.cpp) .
