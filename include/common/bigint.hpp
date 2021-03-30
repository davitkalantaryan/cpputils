//
// file:			bigint.hpp
// path:			include/common/bigint.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_HPP
#define CPPUTILS_INCLUDE_COMMON_BIGINT_HPP

#include <cpputils_internal_header.h>
#include <stdint.h>

namespace common {


template <uint64_t NUM_QWORDS_DEGR>
class BigInt;


template <uint64_t NUM_QWORDS_DEGR>
class BigUInt
{
	static_assert (NUM_QWORDS_DEGR>0,"In the case if Number of QWORDS is 1 (degree==0), use uint64_t or int64_t instead");
public:
	static const uint64_t	s_lastIndexInBuff;
	static const uint64_t	s_numberOfQwords;
	static const uint64_t	s_numberOfDwords;
public:
	BigUInt();
	BigUInt(const BigUInt& cM);
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt(const NumType& val);
	BigUInt(const BigInt<NUM_QWORDS_DEGR>& cM);
	
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt& operator=(const NumType& val);
	BigUInt& operator=(const BigInt<NUM_QWORDS_DEGR>& cM);
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	operator NumType()const;
	
	BigUInt& operator+=(const BigUInt& a_rs);
	BigUInt& operator-=(const BigUInt& a_rs);
	BigUInt& operator*=(const BigUInt& a_rs);
	BigUInt& operator/=(const BigUInt& a_rs);
	BigUInt& operator%=(const BigUInt& a_rs);
	
	BigUInt& operator<<=(uint64_t a_rs);
	BigUInt& operator>>=(uint64_t a_rs);
	
	BigUInt& operator+=(const BigInt<NUM_QWORDS_DEGR>& a_rs);
	BigUInt& operator-=(const BigInt<NUM_QWORDS_DEGR>& a_rs);
	BigUInt& operator*=(const BigInt<NUM_QWORDS_DEGR>& a_rs);
	BigUInt& operator/=(const BigInt<NUM_QWORDS_DEGR>& a_rs);
	BigUInt& operator%=(const BigInt<NUM_QWORDS_DEGR>& a_rs);
	
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt& operator+=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt& operator-=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt& operator*=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt& operator/=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	BigUInt& operator%=(const NumType& a_rs);
	
	BigUInt& operator++();
	BigUInt  operator++(int);
	BigUInt& operator--();
	BigUInt  operator--(int);
	
	bool operator<(const BigUInt& rS)const;
	bool operator>(const BigUInt& rS)const;
	bool operator<=(const BigUInt& rS)const;
	bool operator>=(const BigUInt& rS)const;
	bool operator==(const BigUInt& rS)const;
	
public:
	static void OperatorPlus(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorMinus(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorMult(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OpratorDiv(BigUInt* remn, BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorBtwAnd(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	
public:
	uint64_t* buff2();
	const uint64_t* buff2()const;
	
protected:
	union{
		uint64_t	b64[1<<NUM_QWORDS_DEGR];
		uint32_t	b32[1<<(NUM_QWORDS_DEGR+1)];
	}m_u;
};


template <uint64_t NUM_QWORDS_DEGR>
class BigInt : public BigUInt<NUM_QWORDS_DEGR>
{
public:
	BigInt();
	BigInt(const BigInt& cM);
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt(const NumType& val);
	BigInt(const BigUInt<NUM_QWORDS_DEGR>& cM);
	
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt& operator=(const NumType& val);
	BigInt& operator=(const BigUInt<NUM_QWORDS_DEGR>& val);
	template <typename NumType>  // any type, that is possible to convert to int64_t
	operator NumType()const;
	BigInt  operator-()const;
	
	BigInt& operator+=(const BigInt& a_rs);
	BigInt& operator-=(const BigInt& a_rs);
	BigInt& operator*=(const BigInt& a_rs);
	BigInt& operator/=(const BigInt& a_rs);
	BigInt& operator%=(const BigInt& a_rs);
	
	BigInt& operator+=(const BigUInt<NUM_QWORDS_DEGR>& a_rs);
	BigInt& operator-=(const BigUInt<NUM_QWORDS_DEGR>& a_rs);
	BigInt& operator*=(const BigUInt<NUM_QWORDS_DEGR>& a_rs);
	BigInt& operator/=(const BigUInt<NUM_QWORDS_DEGR>& a_rs);
	BigInt& operator%=(const BigUInt<NUM_QWORDS_DEGR>& a_rs);
	
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt& operator+=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt& operator-=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt& operator*=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt& operator/=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to int64_t
	BigInt& operator%=(const NumType& a_rs);
	
	bool operator<(const BigInt& rS)const;
	bool operator>(const BigInt& rS)const;
	bool operator<=(const BigInt& rS)const;
	bool operator>=(const BigInt& rS)const;

	uint64_t isMinus()const;
};


}  // namespace common { 

#ifdef CPPUTILS_CPP_11_DEFINED

common::BigInt<1> operator"" _bi01(const char* n);
common::BigInt<2> operator"" _bi02(const char* n);
common::BigInt<3> operator"" _bi03(const char* n);
common::BigInt<4> operator"" _bi04(const char* n);
common::BigInt<5> operator"" _bi05(const char* n);
common::BigInt<6> operator"" _bi06(const char* n);
common::BigInt<7> operator"" _bi07(const char* n);
common::BigInt<8> operator"" _bi08(const char* n);
//
common::BigUInt<1> operator"" _bui01(const char* n);
common::BigUInt<2> operator"" _bui02(const char* n);
common::BigUInt<3> operator"" _bui03(const char* n);
common::BigUInt<4> operator"" _bui04(const char* n);
common::BigUInt<5> operator"" _bui05(const char* n);
common::BigUInt<6> operator"" _bui06(const char* n);
common::BigUInt<7> operator"" _bui07(const char* n);
common::BigUInt<8> operator"" _bui08(const char* n);

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED


#ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP
#include "bigint.impl.hpp"
#endif



#endif  // #ifndef COMMON_HASHTBL_HPP
