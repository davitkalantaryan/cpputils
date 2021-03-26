

#include <common/hashtbl.hpp>
#include <common/bigint.hpp>
#include <type_traits>
#include <common/endian.hpp>
#include <iostream>



int main()
{
	{
		common::hashtbl::Base<int,int> aHash;
		
		aHash.AddEntry(1,1);
		aHash.AddEntryEvenIfExists(1,1);
	}
	
	{
		int a=1;
		common::hashtbl::HashTbl<int> aHash;
		
		aHash.AddEntry({&a,4},1);
		aHash.AddEntryEvenIfExists({&a,4},1);
		aHash.FindEntry({&a,4});
	}
	
	{
		common::hashtbl::Set<int> aHash;
		//common::hashtbl:: Base<int,void> aHash;
		
		size_t unHash;
		aHash.AddEntry(1);
		
		aHash.FindEntry(2,&unHash);
		aHash.AddEntryWithKnownHash(2,unHash);
	}
	
	{
		common::BigInt<1> a1(2);
		common::BigInt<1> a2(5);
		common::BigInt<1> a4 = 100000000000000000000_bi01 / 1000000000000000000_bi01;
		//common::BigInt<1> a3 = ;
		int ia1 = static_cast<int>(a1+a2);
		int ia2 = static_cast<int>(a1-a2);
		//std::make_unsigned< common::BigInt<1> > ua;
		std::cout << "ia1="<<ia1<<std::endl;
		std::cout << "ia2="<<ia2<<std::endl;
		std::cout << "a1+a2="<<a1+a2<<std::endl;
		std::cout << "a1-a2="<<a1-a2<<std::endl;
		std::cout << "2*a1-a2*3="<<2*a1-a2*3<<std::endl;
	}
	
	
	return 0;
}
