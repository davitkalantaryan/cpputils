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
	bool operator==(const BigUInt& rS)const;
	
public:
	uint64_t* buff();
	const uint64_t* buff()const;
	BigUInt& OpratorDiv(const BigUInt& rS, BigUInt* divResult);
	
protected:
	uint64_t	m_buff[1<<NUM_QWORDS_DEGR];
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
};


}  // namespace common { 


#if 0

template <typename CharType,uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os, const common::BigUInt<NUM_QWORDS_DEGR>& bi);

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& lS,const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& lS,const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& lS,const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const common::BigUInt<NUM_QWORDS_DEGR>& lS,const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const common::BigUInt<NUM_QWORDS_DEGR>& lS,const common::BigUInt<NUM_QWORDS_DEGR>& rS);

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);

template <typename NumType,uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const common::BigUInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const NumType& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const NumType& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const NumType& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const NumType& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const NumType& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);



template <typename CharType,uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& os, const common::BigInt<NUM_QWORDS_DEGR>& bi);

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const common::BigInt<NUM_QWORDS_DEGR>& lS,const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const common::BigInt<NUM_QWORDS_DEGR>& lS,const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const common::BigInt<NUM_QWORDS_DEGR>& lS,const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const common::BigInt<NUM_QWORDS_DEGR>& lS,const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const common::BigInt<NUM_QWORDS_DEGR>& lS,const common::BigInt<NUM_QWORDS_DEGR>& rS);

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const common::BigInt<NUM_QWORDS_DEGR>& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const common::BigInt<NUM_QWORDS_DEGR>& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const common::BigInt<NUM_QWORDS_DEGR>& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const common::BigInt<NUM_QWORDS_DEGR>& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const common::BigInt<NUM_QWORDS_DEGR>& lS, const common::BigUInt<NUM_QWORDS_DEGR>& rS);

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const common::BigInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const common::BigInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const common::BigInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const common::BigInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const common::BigInt<NUM_QWORDS_DEGR>& lS, const NumType& rS);

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const NumType& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const NumType& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const NumType& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const NumType& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const NumType& lS, const common::BigInt<NUM_QWORDS_DEGR>& rS);

#endif


#ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP
#include "bigint.impl.hpp"
#endif



#endif  // #ifndef COMMON_HASHTBL_HPP
