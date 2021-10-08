//
// file:			cpputils_bigint.cpp
// path:			src/core/cpputils_hashtbl.cpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils_internal_header.h>

#ifdef CPPUTILS_CPP_11_DEFINED

#include <cpputils/bigint.hpp>
#include <ctype.h>
#include <stdlib.h>

using namespace ::cpputils;

BigInt<1> operator"" _bi01(const char* a_n)
{
    return BigInt<1>::OperatorBiLiteral(a_n);
}

BigInt<2> operator"" _bi02(const char* a_n)
{
    return BigInt<2>::OperatorBiLiteral(a_n);
}

BigInt<3> operator"" _bi03(const char* a_n)
{
    return BigInt<3>::OperatorBiLiteral(a_n);
}

BigInt<4> operator"" _bi04(const char* a_n)
{
    return BigInt<4>::OperatorBiLiteral(a_n);
}

BigInt<5> operator"" _bi05(const char* a_n)
{
    return BigInt<5>::OperatorBiLiteral(a_n);
}

BigInt<6> operator"" _bi06(const char* a_n)
{
    return BigInt<6>::OperatorBiLiteral(a_n);
}

BigInt<7> operator"" _bi07(const char* a_n)
{
    return BigInt<7>::OperatorBiLiteral(a_n);
}

BigInt<8> operator"" _bi08(const char* a_n)
{
    return BigInt<8>::OperatorBiLiteral(a_n);
}

//

BigUInt<1> operator"" _bui01(const char* a_n)
{
    return BigUInt<1>::OperatorBuiLiteral(a_n);
}

BigUInt<2> operator"" _bui02(const char* a_n)
{
    return BigUInt<2>::OperatorBuiLiteral(a_n);
}

BigUInt<3> operator"" _bui03(const char* a_n)
{
    return BigUInt<3>::OperatorBuiLiteral(a_n);
}

BigUInt<4> operator"" _bui04(const char* a_n)
{
    return BigUInt<4>::OperatorBuiLiteral(a_n);
}

BigUInt<5> operator"" _bui05(const char* a_n)
{
    return BigUInt<5>::OperatorBuiLiteral(a_n);
}

BigUInt<6> operator"" _bui06(const char* a_n)
{
    return BigUInt<6>::OperatorBuiLiteral(a_n);
}

BigUInt<7> operator"" _bui07(const char* a_n)
{
    return BigUInt<7>::OperatorBuiLiteral(a_n);
}

BigUInt<8> operator"" _bui08(const char* a_n)
{
    return BigUInt<8>::OperatorBuiLiteral(a_n);
}

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED
