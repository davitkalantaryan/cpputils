//
// file:			bigint.impl.hpp
// path:			include/cpputils/bigint.impl.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_BIGINT_IMPL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_BIGINT_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_CPPUTILS_BIGINT_HPP
//#error do not include this header directly
#include "bigint.hpp"
#endif

#include <cpputils_internal_header.h>
#include <stddef.h>
#include <stdint.h>
#include <ostream>
#include <sstream>
#include <string.h>
//#include <cpputils_endian.h>

namespace __private { namespace __implementation {


union DataU{
	uint64_t	d64;
	uint32_t	d32[2];
};


}}  // namespace __private { namespace __implementation {





/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//
template <uint64_t NUM_QWORDS_DEGR>
::std::string std::to_string(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
	return a_bi.template to_string<char>( ::std::ios_base::dec );
}

template <uint64_t NUM_QWORDS_DEGR>
::std::wstring std::to_wstring(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
	return a_bi.template to_string<wchar_t>( ::std::ios_base::dec );
}

template <typename CharType, uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
	::std::basic_string<CharType> retStr = a_bi.template to_string<CharType>(a_os.flags());
	a_os << retStr;
	return a_os;
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorPlus(&ret, a_lS, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMinus(&ret, a_lS, a_rS);
	return ret;
}


template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMult(&ret, a_lS, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorDiv(&remn, &ret, a_lS, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorDiv(&remn, &ret, a_lS, a_rS);
	return remn;
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorPlus(&ret, a_lS, aRs);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMinus(&ret, a_lS, aRs);
	return ret;
}


template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMult(&ret, a_lS, aRs);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorDiv(&remn ,&ret, a_lS, aRs);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorDiv(&remn, &ret, a_lS, aRs);
	return remn;
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorPlus(&ret, aLs, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMinus(&ret, aLs, a_rS);
	return ret;
}


template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMult(&ret, aLs, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorDiv(&remn, &ret, aLs, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorDiv(&remn, &ret, aLs, a_rS);
	return remn;
}
//


//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorPlus(&ret, a_lS, aRs);
	return ret;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMinus(&ret, a_lS, aRs);
	return ret;
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMult(&ret, a_lS, aRs);
	return ret;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorDiv(&remn ,&ret, a_lS, aRs);
	return ret;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aRs(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorDiv(&remn, &ret, a_lS, aRs);
	return remn;
}
//

//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator+(const NumType& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorPlus(&ret,aLs,a_rS);
	return ret;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator-(const NumType& a_rS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMinus(&ret, aLs, a_rS);
	return ret;
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator*(const NumType& a_rS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorMult(&ret, aLs, a_rS);
	return ret;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator/(const NumType& a_rS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorDiv(&remn ,&ret, aLs, a_rS);
	return ret;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator%(const NumType& a_rS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	const cpputils::BigUInt<NUM_QWORDS_DEGR> aLs(a_lS);
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OpreatorDiv(&remn, &ret, aLs, a_rS);
	return remn;
}
//


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//
template <uint64_t NUM_QWORDS_DEGR>
::std::string std::to_string(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
	return a_bi.template to_string<char>( ::std::ios_base::dec );
}

template <uint64_t NUM_QWORDS_DEGR>
::std::wstring std::to_wstring(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
	return a_bi.template to_string<wchar_t>( ::std::ios_base::dec );
}

template <typename CharType, uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
	a_os << a_bi.template to_string<CharType>(a_os.flags());
	return a_os;
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return retInt.operator+=(a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return retInt.operator-=(a_rS);
}


template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return retInt.operator*=(a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return retInt.operator/=(a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return retInt.operator%=(a_rS);
}
//


//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator+=(a_rS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator-=(a_rS);
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator*=(a_rS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator/=(a_rS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator%=(a_rS);
}
//


//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator+(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator+=(a_rS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator-(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator-=(a_rS);
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator*(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator*=(a_rS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator/(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator/=(a_rS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator%(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return  retInt.operator%=(a_rS);
}
//



namespace cpputils { 

template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords = 1<<NUM_QWORDS_DEGR;
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfDwords = 1<<(NUM_QWORDS_DEGR+1);
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff = BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords - 1;

#define MAX_VALUE_PER_QWORD		0xffffffffffffffff
//#define MASK_SIGN_BIT			0x8000000000000000
#define MASK_SIGN_BIT			(uint64_t(1)<<uint64_t(63))

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt()
{
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt(const BigUInt& a_cM)
{
	memcpy(&m_u,&(a_cM.m_u), sizeof(m_u));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>::BigUInt(const NumType& a_val)
{
	m_u.b64[0] = static_cast<uint64_t>(a_val);
	for(uint64_t i(1); i<s_numberOfQwords; ++i){
		m_u.b64[i] = 0;
	}	
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt(const BigInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(&m_u,&(a_cM.m_u), sizeof(m_u));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator=(const NumType& a_val)
{
	m_u.b64[0] = static_cast<uint64_t>(a_val);
	for(uint64_t i(1); i<s_numberOfQwords; ++i){
		m_u.b64[i] = 0;
	}	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator=(const BigInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(&m_u,&(a_cM.m_u), sizeof(m_u));
	return *this;
}

// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
// we have below operator=
template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator=(const BigUInt& a_cM)
{
	memcpy(&m_u,&(a_cM.m_u), sizeof(m_u));
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>::operator NumType()const
{	
	return static_cast<NumType>(m_u.b64[0]);
}


//
template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator+=(const NumType& a_Rs)
{
	BigUInt aLs(*this), aRs(a_Rs);
	OperatorPlus(this, aLs, aRs);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator-=(const NumType& a_Rs)
{
	BigUInt aLs(*this), aRs(a_Rs);
	OperatorMinus(this, aLs, aRs);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator*=(const NumType& a_Rs)
{
	BigUInt aLs(*this), aRs(a_Rs);
	OperatorMult(this, aLs, aRs);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator/=(const NumType& a_Rs)
{
	BigUInt aLs(*this), aRs(a_Rs),aRes;
	OperatorDiv(&aRes,this, aLs, aRs);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator%=(const NumType& a_Rs)
{
	BigUInt aLs(*this), aRs(a_Rs), aRes;
	OperatorDiv(this, &aRes, aLs, aRs);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator<<=(const NumType& a_Rs)
{
	const BigUInt shiftsCount(a_Rs);
	for(uint64_t i(1); i<s_numberOfQwords;++i){
		if(shiftsCount.m_u.b64[i]){
			*this = 0;
			return *this;
		}
	}
	OperatorLeftShift(this, BigUInt(*this), shiftsCount.m_u.b64[0]);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator>>=(const NumType& a_Rs)
{
	const BigUInt shiftsCount(a_Rs);
	for (uint64_t i(1); i < s_numberOfQwords; ++i) {
		if (shiftsCount.m_u.b64[i]) {
			*this = 0;
			return *this;
		}
	}
	OperatorRightShift(this, BigUInt(*this), shiftsCount.m_u.b64[0]);
	return *this;
}

//


template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator++()
{
	for(uint64_t i(0); i<s_numberOfQwords;++i){
		if(m_u.b64[i]<MAX_VALUE_PER_QWORD){
			++m_u.b64[i];
			return *this;
		}
		m_u.b64[i] = 0;
	}
	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::operator++(int)
{
	BigUInt valToRet(*this);
	this->operator++();
	return valToRet;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator--()
{
	for(uint64_t i(0); i<s_numberOfQwords;++i){
		if(m_u.b64[i]>0){
			--m_u.b64[i];
			return *this;
		}
		m_u.b64[i] = MAX_VALUE_PER_QWORD;
	}
	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::operator--(int)
{
	BigUInt valToRet(*this);
	this->operator--();
	return valToRet;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator<(const BigUInt& a_rS)const
{
	for(uint64_t i(s_lastIndexInBuff); ; --i){
		if(m_u.b64[i]<a_rS.m_u.b64[i]){return true;}
		if(m_u.b64[i]>a_rS.m_u.b64[i]){return false;}
		if(!i){break;}
	}
	
	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator>(const BigUInt& a_rS)const
{
	for(uint64_t i(s_lastIndexInBuff); ; --i){
		if(m_u.b64[i]>a_rS.m_u.b64[i]){return true;}
		if(m_u.b64[i]<a_rS.m_u.b64[i]){return false;}
		if(!i){break;}
	}
		
	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator<=(const BigUInt& a_rS)const
{
	for (uint64_t i(s_lastIndexInBuff); ; --i) {
		if (m_u.b64[i] < a_rS.m_u.b64[i]) { return true; }
		if (m_u.b64[i] > a_rS.m_u.b64[i]) { return false; }
		if (!i) { break; }
	}

	return true;

}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator>=(const BigUInt& a_rS)const
{
	for (uint64_t i(s_lastIndexInBuff); ; --i) {
		if (m_u.b64[i] > a_rS.m_u.b64[i]) { return true; }
		if (m_u.b64[i] < a_rS.m_u.b64[i]) { return false; }
		if (!i) { break; }
	}

	return true;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator==(const BigUInt& a_rS)const
{
	for(uint64_t i(0);i<s_numberOfQwords; ++i){
		if(m_u.b64[i]!=a_rS.m_u.b64[i]){return false;}
	}
	
	return true;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator!=(const BigUInt& a_rS)const
{
	for(uint64_t i(0);i<s_numberOfQwords; ++i){
		if(m_u.b64[i]!=a_rS.m_u.b64[i]){return true;}
	}
	
	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorPlus(BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	uint64_t ullnSum, ullnHas, ullnRemn = 0;

	for (uint64_t i(0); i < s_numberOfQwords; ++i) {
		ullnHas = MAX_VALUE_PER_QWORD - a_lS.m_u.b64[i];

		if (ullnHas >= ullnRemn) {
			ullnHas -= ullnRemn;
			ullnSum = a_lS.m_u.b64[i] + ullnRemn;
		}
		else {
			ullnSum = ullnRemn - 1;
			ullnHas = MAX_VALUE_PER_QWORD - ullnSum;
		}

		ullnRemn = 0;

		if (ullnHas >= a_rS.m_u.b64[i]) {
			ullnSum += a_rS.m_u.b64[i];
		}
		else {
			ullnSum = a_rS.m_u.b64[i] - ullnHas - 1;
			ullnRemn = 1;
		}

		(a_res->m_u.b64)[i] = ullnSum;

	}  // for(uint64_t i(0); i<a_numberOfQwords;++i){

}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	uint64_t ullnDif, lsTmp, ullnDept = 0;

	for (uint64_t i(0); i < s_numberOfQwords; ++i) {

		lsTmp = a_lS.m_u.b64[i];
		if (lsTmp >= ullnDept) {
			lsTmp -= ullnDept;
			ullnDept = 0;
		}
		else {
			// partq
			lsTmp = MAX_VALUE_PER_QWORD - lsTmp;
		}

		if (lsTmp < a_rS.m_u.b64[i]) { // no dept yet. We have to make one
			++ullnDept; // this will make current quad word equal (MAX_VALUE_PER_QWORD+1+lsTmp)
			ullnDif = (MAX_VALUE_PER_QWORD - a_rS.m_u.b64[i]) + lsTmp + 1;
			//ullnDif = (MAX_VALUE_PER_QWORD - (a_rS.m_data2)[i].d64) + lsTmp + 1;
		}
		else {
			ullnDif = lsTmp - a_rS.m_u.b64[i];
			//ullnDif = lsTmp - (a_rS.m_data2)[i].d64;
		}

		//m_buff[i] = ullnDif;
		a_res->m_u.b64[i] = ullnDif;
		//(a_res->m_data2)[i].d64 = ullnDif;

	}  // for(uint64_t i(0); i<a_numberOfQwords;++i){

}


template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorMult(BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	__private::__implementation::DataU tmpSingleMult;
	BigUInt tmpMult;
	uint64_t j,ind, lsTmp, rsTmp;
	uint32_t tmpSingleMultPrev;
	
	memset(&(a_res->m_u),0,sizeof (a_res->m_u));
	
	for (uint64_t i(0); i < s_numberOfDwords; ++i) {
		rsTmp = static_cast<uint64_t>(a_rS.m_u.b32[i]);
		memset(&(tmpMult.m_u),0,sizeof (tmpMult.m_u));
		tmpSingleMultPrev = 0;
		for(j=i;j<s_numberOfDwords;++j){
			ind = j-i;
			lsTmp = static_cast<uint64_t>(a_lS.m_u.b32[ind]);
			tmpSingleMult.d64 = lsTmp * rsTmp;
			tmpMult.m_u.b32[j] = tmpSingleMult.d32[0] + tmpSingleMultPrev;
			tmpSingleMultPrev = tmpSingleMult.d32[1];
		}
		
		(*a_res) += tmpMult;
		
	}
}


template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorDiv(BigUInt* a_remn, BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	if (a_rS.isZero()) {
		// handling devide to zero as handles compiler
		a_res->m_u.b64[0] = a_lS.m_u.b64[0] / a_rS.m_u.b64[0];
		a_remn->m_u.b64[0] = a_lS.m_u.b64[0] % a_rS.m_u.b64[0];
		return;
	}
	
	//uint64_t shiftCount = s_numberOfQwords * sizeof(uint64_t) * 8 - 1;
	const uint64_t numberOfBits = s_numberOfQwords * sizeof(uint64_t) * 8;
	BigUInt takenValueIn;
	BigUInt aMask;

	for(uint64_t i(0);i<s_lastIndexInBuff;++i){aMask.m_u.b64[i] = 0;}
	aMask.m_u.b64[s_lastIndexInBuff] = MASK_SIGN_BIT;

	*a_remn = 0;
	*a_res = 0;

	for (uint64_t i(0);i< numberOfBits;++i) {
		OperatorBtwAnd(&takenValueIn, a_lS, aMask);
		//OperatorRightShift(&takenValueFn, takenValueIn, shiftCount);
		(*a_remn) *= 2;
		//(*a_remn) += takenValueFn;
		if (takenValueIn.isNotZero()) {
			++(*a_remn);
		}
		*a_res *= 2;
		if ((*a_remn) >= a_rS) {
			++(*a_res);
			(*a_remn) -= a_rS;
		}

		aMask >>= 1;
	}	
}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorBtwAnd(BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	for(uint64_t i(0);i<s_numberOfQwords;++i){
		a_res->m_u.b64[i] = a_lS.m_u.b64[i] & a_rS.m_u.b64[i];
	}
}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorBtwOr(BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	for (uint64_t i(0); i < s_numberOfQwords; ++i) {
		a_res->m_u.b64[i] = a_lS.m_u.b64[i] | a_rS.m_u.b64[i];
	}
}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorBtwXor(BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	for (uint64_t i(0); i < s_numberOfQwords; ++i) {
		a_res->m_u.b64[i] = a_lS.m_u.b64[i] ^ a_rS.m_u.b64[i];
	}
}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorRightShift(BigUInt* a_res, const BigUInt& a_lS, uint64_t a_shiftCount)
{
	const uint64_t qwordShift = a_shiftCount / 64;
	const uint64_t bitShift = a_shiftCount % 64;
	uint64_t transferBits = 0, singleRes;
	const uint64_t* pLs= a_lS.m_u.b64;

	if (qwordShift) {
		if (qwordShift >= s_numberOfQwords) { *a_res = 0; return; }
		//memmove(a_res->m_u.b64 + qwordShift, a_lS.m_u.b64, (s_numberOfQwords - qwordShift) * sizeof(uint64_t));
		//memset(a_res->m_u.b64 + s_numberOfQwords - qwordShift, 0, qwordShift * sizeof(uint64_t));

		const uint64_t maxFor(s_numberOfQwords - qwordShift);
		for (uint64_t i(0);i<maxFor ; ++i) {
			a_res->m_u.b64[i] = a_lS.m_u.b64[i + qwordShift];
		}
		for (uint64_t i(maxFor); i < s_numberOfQwords; ++i) {
			a_res->m_u.b64[i] = 0;
		}

		pLs = a_res->m_u.b64;
	}

	if (!bitShift) { return; }

	const uint64_t bitShiftInTransfer = 64 - bitShift;
	const uint64_t transferMask = ~(MAX_VALUE_PER_QWORD << bitShift);

	for (uint64_t i(s_lastIndexInBuff);; --i) {
		singleRes = (pLs[i] >> bitShift) | (transferBits << bitShiftInTransfer);
		transferBits = pLs[i] & transferMask;
		a_res->m_u.b64[i] = singleRes;
		if (!i) { break; }
	}
}

template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorLeftShift(BigUInt* a_res, const BigUInt& a_lS, uint64_t a_shiftCount)
{
	const uint64_t qwordShift = a_shiftCount / 64;
	const uint64_t bitShift = a_shiftCount % 64;
	uint64_t transferBits = 0, singleRes;
	const uint64_t* pLs = a_lS.m_u.b64;

	if (qwordShift) {
		if (qwordShift >= s_numberOfQwords) { *a_res = 0; return; }
		//memmove(a_res->m_u.b64 + qwordShift, a_lS.m_u.b64, (s_numberOfQwords - qwordShift) * sizeof(uint64_t));
		//memset(a_res->m_u.b64, 0, qwordShift * sizeof(uint64_t));

		const uint64_t maxFor(s_numberOfQwords - qwordShift);
		for (uint64_t i(maxFor-1); ; --i) {
			a_res->m_u.b64[i+ qwordShift] = a_lS.m_u.b64[i];
			if (!i) { break; }
		}
		for (uint64_t i(0); i < maxFor; ++i) {
			a_res->m_u.b64[i] = 0;
		}

		pLs = a_res->m_u.b64;
	}

	if (!bitShift) { return ; }

	const uint64_t transferMask = ~(MAX_VALUE_PER_QWORD >> bitShift);

	for (uint64_t i(0); i < s_numberOfQwords; ++i) {
		singleRes = (pLs[i] << bitShift) | transferBits;
		transferBits = pLs[i] & transferMask;
		a_res->m_u.b64[i] = singleRes;
	}

}


template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::isZero()const
{
	for(uint64_t i(0);i<s_numberOfQwords;++i){
		if(m_u.b64[i]){return false;}
	}

	return true;
}


template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::isNotZero()const
{
	for (uint64_t i(0); i < s_numberOfQwords; ++i) {
		if (m_u.b64[i]) { return true; }
	}

	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename CharType>
::std::basic_string< CharType > BigUInt<NUM_QWORDS_DEGR>::to_string( ::std::ios_base::fmtflags a_fmt )const
{
	std::basic_string<CharType> retStr;

	if (a_fmt & ::std::ios_base::dec) {
		// we have decimal
		int nIter = 0;
		const cpputils::BigUInt<NUM_QWORDS_DEGR> bi10(10);
		cpputils::BigUInt<NUM_QWORDS_DEGR> value(*this),valueIn, remn;

		while (value) {
			std::basic_stringstream<CharType> osTmp;
			valueIn = value;
			remn.OperatorDiv(&remn, &value,valueIn, bi10);
			osTmp << static_cast<uint64_t>(remn);
			retStr = osTmp.str() + retStr;
			++nIter;
		}

		if (nIter) { return retStr; }
		else { retStr.push_back('0'); }
		return retStr;
	}
	else if ((a_fmt & std::ios_base::oct) || (a_fmt & std::ios_base::hex)) {
		// we have hexadecimal
		std::basic_stringstream<CharType> osTmp;
		for (uint64_t i(cpputils::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff); ; --i) {
			osTmp << m_u.b64[i];
			retStr += osTmp.str();
			if (!i) { return retStr; }
		}
	}

	return retStr;
}


template <uint64_t NUM_QWORDS_DEGR>
uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()
{
	return m_u.b64;
}

template <uint64_t NUM_QWORDS_DEGR>
const uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()const
{
	return m_u.b64;
}

#define cpputils_toDigit(__c) (static_cast<uint64_t>(__c)-static_cast<uint64_t>('0'))

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteral(const ::std::string& a_n)
{
	const size_t cunStrLen = a_n.length();
	const char* cpcBuf = a_n.c_str();
	bool bFirstDigitNotFound = true;
	uint64_t nextDigit;
	BigUInt retInt(0);

	for(size_t i(0);i<cunStrLen;++i){

		if(isdigit(cpcBuf[i])){
			nextDigit = cpputils_toDigit(cpcBuf[i]);
			retInt *= 10;
			retInt += nextDigit;
			bFirstDigitNotFound = false;
		}
		else {
			if (bFirstDigitNotFound) {
			}
			else {
				break;
			}
		}
	}

	return retInt;
}



/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/



template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt()
{
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt(const BigInt& a_cM)
    :
      BigUInt<NUM_QWORDS_DEGR>(a_cM)
{
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>::BigInt(const NumType& a_val)
{
	const int64_t val = static_cast<int64_t>(a_val);
	if(val >=0){
		this->m_u.b64[0]=static_cast<uint64_t>(val);
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_u.b64[i] = 0;
		}
	}
	else{
		this->m_u.b64[0] = static_cast<uint64_t>(~(-val));
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_u.b64[i] = MAX_VALUE_PER_QWORD;
		}
		this->operator++();
	}
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt(const BigUInt<NUM_QWORDS_DEGR>& a_cM)
	:
	  BigUInt<NUM_QWORDS_DEGR>(a_cM)
{
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const NumType& a_val)
{
	const int64_t val = static_cast<int64_t>(a_val);
	if(val>=0){
		this->m_u.b64[0]=static_cast<uint64_t>(val);
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_u.b64[i] = 0;
		}
	}
	else{
		this->m_u.b64[0] = static_cast<uint64_t>(~(-val));
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_u.b64[i] = MAX_VALUE_PER_QWORD;
		}
		this->operator++();
	}
	
	return *this;
}

// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
// we have these 2 operator=
// the point is, that will be nice if derived class BigInt inherits these operators from BigUInt
template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const BigUInt<NUM_QWORDS_DEGR>& a_cM)
{
	BigUInt<NUM_QWORDS_DEGR>::operator=(a_cM);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const BigInt& a_cM)
{
	BigUInt<NUM_QWORDS_DEGR>::operator=(a_cM);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>::operator NumType()const
{
	return static_cast<NumType>(static_cast<int64_t>(this->m_u.b64[0]));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR> BigInt<NUM_QWORDS_DEGR>::operator-()const
{
	BigInt<NUM_QWORDS_DEGR> retInt;
	for(uint64_t i(0); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
		retInt.m_u.b64[i]=~(this->m_u.b64[i]);
	}
	return retInt.operator++();
}

//
template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator+=(const NumType& a_Rs)
{
	BigUInt<NUM_QWORDS_DEGR>::operator+=(BigUInt<NUM_QWORDS_DEGR>(a_Rs));
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator-=(const NumType& a_Rs)
{
	return operator+=(-BigInt(a_Rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator*=(const NumType& a_Rs)
{
	const BigInt aRs(a_Rs);
	BigInt thisUnsigned, rsUnsigned;
	const uint64_t isMinusThis=this->isMinus();
	const uint64_t isMinusRs= aRs.isMinus();
	const uint64_t isMinusRet=isMinusThis^isMinusRs;
	
	if(isMinusThis){thisUnsigned = -(*this);}
	else {thisUnsigned=*this;}
	
	if(isMinusRs){rsUnsigned = -aRs;}
	else {rsUnsigned = aRs;}
	
	BigUInt<NUM_QWORDS_DEGR> multRes = BigUInt<NUM_QWORDS_DEGR>(thisUnsigned) * BigUInt<NUM_QWORDS_DEGR>(rsUnsigned) ;
	
	*this = isMinusRet?(-BigInt(multRes)) : BigInt(multRes);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator/=(const NumType& a_Rs)
{
	const BigInt aRs(a_Rs);
	BigInt thisUnsigned, rsUnsigned;
	const uint64_t isMinusThis=this->isMinus();
	const uint64_t isMinusRs= aRs.isMinus();
	const uint64_t isMinusRet=isMinusThis^isMinusRs;
	
	if(isMinusThis){thisUnsigned = -(*this);}
	else {thisUnsigned=*this;}
	
	if(isMinusRs){rsUnsigned = -aRs;}
	else {rsUnsigned = aRs;}
	
	BigUInt<NUM_QWORDS_DEGR> divRes = BigUInt<NUM_QWORDS_DEGR>(thisUnsigned) / BigUInt<NUM_QWORDS_DEGR>(rsUnsigned) ;
	
	*this = isMinusRet?(-BigInt(divRes)) : BigInt(divRes);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator%=(const NumType& a_Rs)
{
	const BigInt aRs(a_Rs);
	BigInt thisUnsigned, rsUnsigned;
	const uint64_t isMinusThis=this->isMinus();
	const uint64_t isMinusRs= aRs.isMinus();
	const uint64_t isMinusRet=isMinusThis^isMinusRs;
	
	if(isMinusThis){thisUnsigned = -(*this);}
	else {thisUnsigned=*this;}
	
	if(isMinusRs){rsUnsigned = -aRs;}
	else {rsUnsigned = aRs;}
	
	BigUInt<NUM_QWORDS_DEGR> divRes = BigUInt<NUM_QWORDS_DEGR>(thisUnsigned) % BigUInt<NUM_QWORDS_DEGR>(rsUnsigned) ;
	
	*this = isMinusRet?(-BigInt(divRes)) : BigInt(divRes);
	return *this;
}
//

template <uint64_t NUM_QWORDS_DEGR>
bool BigInt<NUM_QWORDS_DEGR>::operator<(const BigInt& a_rs)const
{
	const uint64_t isMinusThis=this->isMinus();
	const uint64_t isMinusRs=a_rs.isMinus();
	
	if(isMinusThis==isMinusRs){
		return BigUInt<NUM_QWORDS_DEGR>::operator<(a_rs);
	}
	
	if(isMinusThis){
		return true;
	}
	
	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigInt<NUM_QWORDS_DEGR>::operator>(const BigInt& a_rs)const
{
	const uint64_t isMinusThis=this->isMinus();
	const uint64_t isMinusRs=a_rs.isMinus();
	
	if(isMinusThis==isMinusRs){
		return BigUInt<NUM_QWORDS_DEGR>::operator>(a_rs);
	}
	
	if(isMinusThis){
		return false;
	}
	
	return true;
}


template <uint64_t NUM_QWORDS_DEGR>
bool BigInt<NUM_QWORDS_DEGR>::operator<=(const BigInt& a_rs)const
{
	const uint64_t isMinusThis = this->isMinus();
	const uint64_t isMinusRs = a_rs.isMinus();

	if (isMinusThis == isMinusRs) {
		return BigUInt<NUM_QWORDS_DEGR>::operator<=(a_rs);
	}

	if (isMinusThis) {
		return true;
	}

	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigInt<NUM_QWORDS_DEGR>::operator>=(const BigInt& a_rs)const
{
	const uint64_t isMinusThis = this->isMinus();
	const uint64_t isMinusRs = a_rs.isMinus();

	if (isMinusThis == isMinusRs) {
		return BigUInt<NUM_QWORDS_DEGR>::operator>=(a_rs);
	}

	if (isMinusThis) {
		return false;
	}

	return true;
}

//
template <uint64_t NUM_QWORDS_DEGR>
uint64_t BigInt<NUM_QWORDS_DEGR>::isMinus()const
{
	return this->m_u.b64[cpputils::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename CharType>
::std::basic_string< CharType > BigInt<NUM_QWORDS_DEGR>::to_string( ::std::ios_base::fmtflags a_fmt )const
{
	::std::basic_string<CharType> retStr;
	const uint64_t isMinus = this->isMinus();

	if (isMinus) {
		retStr.push_back('-');
		retStr += ::cpputils::BigUInt<NUM_QWORDS_DEGR>(-::cpputils::BigInt<NUM_QWORDS_DEGR>(*this)).template to_string<CharType>(a_fmt);
	}
	else {
		retStr =  reinterpret_cast<const cpputils::BigUInt<NUM_QWORDS_DEGR>*>(this)->template to_string<CharType>(a_fmt);
	}

	return retStr;
}


template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR> BigInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteral(const ::std::string& a_n)
{
	const size_t cunStrLen = a_n.length();
	const char* cpcBuf = a_n.c_str();
	bool bFirstDigitNotFound = true;
	int isMinus = 0;
	uint64_t nextDigit;
	BigInt retInt(0);

	for(size_t i(0);i<cunStrLen;++i){

		if(isdigit(cpcBuf[i])){
			nextDigit = cpputils_toDigit(cpcBuf[i]);
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
		retInt *= BigInt(-1);
	}

	return retInt;
}


}  // namespace cpputils 





#ifdef CPPUTILS_CPP_11_DEFINED

cpputils::BigInt<1> operator"" _bi01(const char* n);
cpputils::BigInt<2> operator"" _bi02(const char* n);
cpputils::BigInt<3> operator"" _bi03(const char* n);
cpputils::BigInt<4> operator"" _bi04(const char* n);
cpputils::BigInt<5> operator"" _bi05(const char* n);
cpputils::BigInt<6> operator"" _bi06(const char* n);
cpputils::BigInt<7> operator"" _bi07(const char* n);
cpputils::BigInt<8> operator"" _bi08(const char* n);
//
cpputils::BigUInt<1> operator"" _bui01(const char* n);
cpputils::BigUInt<2> operator"" _bui02(const char* n);
cpputils::BigUInt<3> operator"" _bui03(const char* n);
cpputils::BigUInt<4> operator"" _bui04(const char* n);
cpputils::BigUInt<5> operator"" _bui05(const char* n);
cpputils::BigUInt<6> operator"" _bui06(const char* n);
cpputils::BigUInt<7> operator"" _bui07(const char* n);
cpputils::BigUInt<8> operator"" _bui08(const char* n);

#endif  // #ifdef CPPUTILS_CPP_11_DEFINED


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_BIGINT_IMPL_HPP
