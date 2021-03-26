//
// file:			common_bigint.hpp
// path:			src/common/common_hashtbl.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <common/bigint.hpp>
#include <ctype.h>
#include <stdlib.h>

namespace __private { namespace __implementation {

#define toDigit(__c) (static_cast<uint64_t>(__c)-static_cast<uint64_t>('0'))


//void Dummy(void)
//{
//	common::BigInt<1> aInt;
//	static_cast<void>(aInt);
//}


#ifdef CPPUTILS_CPP_11_DEFINED

template <typename AnyInt>
static AnyInt OperatorAnyIntLiteral(const std::string& a_n)
{
	const size_t cunStrLen = a_n.length();
	const char* cpcBuf = a_n.c_str();
	bool bFirstDigitNotFound = true;
	int isMinus = 0;
	uint64_t nextDigit;
	AnyInt retInt(0);

	for(size_t i(0);i<cunStrLen;++i){

		if(isdigit(cpcBuf[i])){
			nextDigit = toDigit(cpcBuf[i]);
			retInt *= 10;
			retInt += nextDigit;
			bFirstDigitNotFound = false;
		}
		else {
			if (bFirstDigitNotFound) {
				if (cpcBuf[i] == '-') { isMinus = ~isMinus; }
			}
			else {
				break;
			}
		}
	}

	if(isMinus){
		retInt *= AnyInt(-1);
	}

	return retInt;
}

template <uint64_t NUM_QWORDS_DEGR>
static common::BigInt<NUM_QWORDS_DEGR> OperatorBiLiteral(const std::string& a_n)
{
	return OperatorAnyIntLiteral< common::BigInt<NUM_QWORDS_DEGR> >(a_n);
}


template <uint64_t NUM_QWORDS_DEGR>
static common::BigUInt<NUM_QWORDS_DEGR> OperatorBuiLiteral(const std::string& a_n)
{
	return OperatorAnyIntLiteral< common::BigUInt<NUM_QWORDS_DEGR> >(a_n);
}

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED

}}  // namespace __private { namespace common {



#ifdef CPPUTILS_CPP_11_DEFINED

common::BigInt<1> operator"" _bi01(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<1>(a_n);
}

common::BigInt<2> operator"" _bi02(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<2>(a_n);
}

common::BigInt<3> operator"" _bi03(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<3>(a_n);
}

common::BigInt<4> operator"" _bi04(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<4>(a_n);
}

common::BigInt<5> operator"" _bi05(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<5>(a_n);
}

common::BigInt<6> operator"" _bi06(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<6>(a_n);
}

common::BigInt<7> operator"" _bi07(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<7>(a_n);
}

common::BigInt<8> operator"" _bi08(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<8>(a_n);
}

//
common::BigUInt<1> operator"" _bui01(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<1>(a_n);
}

common::BigUInt<2> operator"" _bui02(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<2>(a_n);
}

common::BigUInt<3> operator"" _bui03(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<3>(a_n);
}

common::BigUInt<4> operator"" _bui04(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<4>(a_n);
}

common::BigUInt<5> operator"" _bui05(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<5>(a_n);
}

common::BigUInt<6> operator"" _bui06(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<6>(a_n);
}

common::BigUInt<7> operator"" _bui07(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<7>(a_n);
}

common::BigUInt<8> operator"" _bui08(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<8>(a_n);
}

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
