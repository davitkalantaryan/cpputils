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
#include <string>
#include <ios>

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
	
	// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
	// we have below operator=
	BigUInt& operator=(const BigUInt& val);
	
	template <typename NumType>  // any type, that is possible to convert to uint64_t
	operator NumType()const;
		
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator+=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator-=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator*=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator/=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator%=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator<<=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigUInt
	BigUInt& operator>>=(const NumType& a_rs);
	
	BigUInt& operator++();
	BigUInt  operator++(int);
	BigUInt& operator--();
	BigUInt  operator--(int);
	
	bool operator<(const BigUInt& rS)const;
	bool operator>(const BigUInt& rS)const;
	bool operator<=(const BigUInt& rS)const;
	bool operator>=(const BigUInt& rS)const;
	bool operator==(const BigUInt& rS)const;

	bool isZero()const;
	bool isNotZero()const;

	template <typename CharType>
	::std::basic_string< CharType > to_string( ::std::ios_base::fmtflags fmt = ::std::ios_base::dec )const;
	
public:
	static void OperatorPlus(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorMinus(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorMult(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorDiv(BigUInt* remn, BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorBtwAnd(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorBtwOr(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorBtwXor(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void OperatorRightShift(BigUInt* res, const BigUInt& ls, uint64_t shiftCount);
	static void OperatorLeftShift(BigUInt* res, const BigUInt& ls, uint64_t shiftCount);
	
public:
	uint64_t* buff();
	const uint64_t* buff()const;
	
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
	
	//// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
	//// we have below operator=
	//BigInt& operator=(const BigInt& val);
	
	template <typename NumType>  // any type, that is possible to convert to int64_t
	operator NumType()const;
	BigInt  operator-()const;
		
	template <typename NumType>  // any type, that is possible to convert to BigInt
	BigInt& operator+=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigInt
	BigInt& operator-=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigInt
	BigInt& operator*=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigInt
	BigInt& operator/=(const NumType& a_rs);
	template <typename NumType>  // any type, that is possible to convert to BigInt
	BigInt& operator%=(const NumType& a_rs);
	
	bool operator<(const BigInt& rS)const;
	bool operator>(const BigInt& rS)const;
	bool operator<=(const BigInt& rS)const;
	bool operator>=(const BigInt& rS)const;

	uint64_t isMinus()const;

	template <typename CharType>
	::std::basic_string< CharType > to_string( ::std::ios_base::fmtflags fmt= ::std::ios_base::dec )const;
};


}  // namespace common { 


namespace std {

template <uint64_t NUM_QWORDS_DEGR>
::std::string to_string( const common::BigUInt<NUM_QWORDS_DEGR>& ubi);
template <uint64_t NUM_QWORDS_DEGR>
::std::wstring to_wstring(const common::BigUInt<NUM_QWORDS_DEGR>& ubi);

template <uint64_t NUM_QWORDS_DEGR>
::std::string to_string(const common::BigInt<NUM_QWORDS_DEGR>& ubi);
template <uint64_t NUM_QWORDS_DEGR>
::std::wstring to_wstring(const common::BigInt<NUM_QWORDS_DEGR>& ubi);

}  // namespace std {



#ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP
#include "bigint.impl.hpp"
#endif



#endif  // #ifndef COMMON_HASHTBL_HPP
