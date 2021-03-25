//
// file:			common_bigint.hpp
// path:			src/common/common_hashtbl.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <common/bigint.hpp>

namespace __private { namespace __implementation {


CPPUTILS_EXPORT void OperatorPlus(uint64_t a_numberOfQwords, uint64_t* a_res, const uint64_t* a_ls, const uint64_t* a_rs)
{
	uint64_t ullnSum,ullnHas,ullnRemn = 0;
	
	for(uint64_t i(0); i<a_numberOfQwords;++i){
		ullnHas=MAX_VALUE_PER_QWORD-a_ls[i];
		
		if(ullnHas>=ullnRemn){
			ullnHas-=ullnRemn;
			ullnSum=a_ls[i]+ullnRemn;
		}
		else {			
			ullnSum=ullnRemn-1;
			ullnHas = MAX_VALUE_PER_QWORD-ullnSum;
		}
		
		ullnRemn = 0;
		
		if(ullnHas>=a_rs[i]){
			ullnSum+=a_rs[i];
		}
		else {
			ullnSum=a_rs[i]-ullnHas-1;
			ullnRemn = 1;
		}
		
		a_res[i] = ullnSum;
		
	}  // for(uint64_t i(0); i<a_numberOfQwords;++i){
}

//void Dummy(void)
//{
//	common::BigInt<1> aInt;
//	static_cast<void>(aInt);
//}


}}  // namespace __private { namespace common {
