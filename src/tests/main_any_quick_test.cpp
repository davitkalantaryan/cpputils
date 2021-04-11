

#include <cpputils/hashtbl.hpp>
#include <cpputils/bigint.hpp>
#include <cpputils/functional_old.hpp>
#include <cpputils/sharedptr.hpp>
#include <cpputils/endian.hpp>
#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <memory>



int main()
{
	{
		cpputils::hashtbl::Base<int,int> aHash;
		
		aHash.AddEntry(1,1);
		aHash.AddEntryEvenIfExists(1,1);
	}
	
	{
		int a=1;
		cpputils::hashtbl::HashTbl<int> aHash;
		
		aHash.AddEntry({&a,4},1);
		aHash.AddEntryEvenIfExists({&a,4},1);
		aHash.FindEntry({&a,4});
	}
	
	{
		cpputils::hashtbl::Set<int> aHash;
		//cpputils::hashtbl:: Base<int,void> aHash;
		
		size_t unHash;
		aHash.AddEntry(1);
		
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
	
	
	return 0;
}
