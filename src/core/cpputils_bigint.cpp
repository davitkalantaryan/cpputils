//
// file:			cpputils_bigint.cpp
// path:			src/core/cpputils_hashtbl.cpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/bigint.hpp>
#include <ctype.h>
#include <stdlib.h>

namespace __private { namespace __implementation {


//void Dummy(void)
//{
//	cpputils::BigInt<1> aInt;
//	static_cast<void>(aInt);
//}


#ifdef CPPUTILS_CPP_11_DEFINED

template <uint64_t NUM_QWORDS_DEGR>
static cpputils::BigInt<NUM_QWORDS_DEGR> OperatorBiLiteral(const ::std::string& a_n)
{
    return ::cpputils::BigInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralS(a_n);
}


template <uint64_t NUM_QWORDS_DEGR>
static cpputils::BigUInt<NUM_QWORDS_DEGR> OperatorBuiLiteral(const ::std::string& a_n)
{
    return ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralU(a_n);
}

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED

}}  // namespace __private { namespace cpputils {



#ifdef CPPUTILS_CPP_11_DEFINED

cpputils::BigInt<1> operator"" _bi01(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<1>(a_n);
}

cpputils::BigInt<2> operator"" _bi02(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<2>(a_n);
}

cpputils::BigInt<3> operator"" _bi03(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<3>(a_n);
}

cpputils::BigInt<4> operator"" _bi04(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<4>(a_n);
}

cpputils::BigInt<5> operator"" _bi05(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<5>(a_n);
}

cpputils::BigInt<6> operator"" _bi06(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<6>(a_n);
}

cpputils::BigInt<7> operator"" _bi07(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<7>(a_n);
}

cpputils::BigInt<8> operator"" _bi08(const char* a_n)
{
	return __private::__implementation::OperatorBiLiteral<8>(a_n);
}

//
cpputils::BigUInt<1> operator"" _bui01(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<1>(a_n);
}

cpputils::BigUInt<2> operator"" _bui02(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<2>(a_n);
}

cpputils::BigUInt<3> operator"" _bui03(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<3>(a_n);
}

cpputils::BigUInt<4> operator"" _bui04(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<4>(a_n);
}

cpputils::BigUInt<5> operator"" _bui05(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<5>(a_n);
}

cpputils::BigUInt<6> operator"" _bui06(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<6>(a_n);
}

cpputils::BigUInt<7> operator"" _bui07(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<7>(a_n);
}

cpputils::BigUInt<8> operator"" _bui08(const char* a_n)
{
	return __private::__implementation::OperatorBuiLiteral<8>(a_n);
}

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
