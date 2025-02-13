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
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdint.h>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <string.h>
#include <math.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace __private { namespace __implementation {


union DataU{
	uint64_t	d64;
	uint32_t	d32[2];
};


}}  // namespace __private { namespace __implementation {





/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//
template <typename CharType, uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
    a_bi.template toStreamU<CharType>(&a_os);
    return a_os;
}

template <uint64_t NUM_QWORDS_DEGR>
::std::string std::to_string(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
    std::basic_stringstream<char> osTmp;
    a_bi.toStreamU(&osTmp);
    return osTmp.str();
}

template <uint64_t NUM_QWORDS_DEGR>
::std::wstring std::to_wstring(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
    std::basic_stringstream<wchar_t> osTmp;
    a_bi.toStreamU(&osTmp);
    return osTmp.str();
}

//


//
template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator+(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
    cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorPlus(&ret, a_lS, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator-(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(&ret, a_lS, a_rS);
	return ret;
}


template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator*(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMultU(&ret, a_lS, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(&remn, &ret, a_lS, a_rS);
	return ret;
}

template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> ret, remn;
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(&remn, &ret, a_lS, a_rS);
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
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(&ret, a_lS, aRs);
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
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(&ret, aLs, a_rS);
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
cpputils::BigUInt<NUM_QWORDS_DEGR> operator/(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const cpputils::BigUInt<NUM_QWORDS_DEGR>& a_rS)
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


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//
template <uint64_t NUM_QWORDS_DEGR>
::std::string std::to_string(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
    std::basic_stringstream<char> osTmp;
    a_bi.toStreamS(&osTmp);
    return osTmp.str();
}

template <uint64_t NUM_QWORDS_DEGR>
::std::wstring std::to_wstring(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
    std::basic_stringstream<wchar_t> osTmp;
    a_bi.toStreamS(&osTmp);
    return osTmp.str();
}

template <typename CharType, uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
    a_bi.toStreamS(&a_os);
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
	cpputils::BigUInt<NUM_QWORDS_DEGR> retu;
	const cpputils::BigUInt<NUM_QWORDS_DEGR> lS(a_lS);
	const cpputils::BigUInt<NUM_QWORDS_DEGR> rS(a_rS);
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(&retu, lS, rS);
	return cpputils::BigInt<NUM_QWORDS_DEGR>(retu);
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
	cpputils::BigUInt<NUM_QWORDS_DEGR> retu;
	const cpputils::BigUInt<NUM_QWORDS_DEGR> lS(a_lS);
	const cpputils::BigUInt<NUM_QWORDS_DEGR> rS0(a_rS);
	const cpputils::BigUInt<NUM_QWORDS_DEGR> rS( rS0 );
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(&retu, lS, rS);
	return cpputils::BigInt<NUM_QWORDS_DEGR>(retu);	
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
    cpputils::BigInt<NUM_QWORDS_DEGR> remn, res;
    cpputils::BigInt<NUM_QWORDS_DEGR>::OperatorDivS(&remn,&res,a_lS,a_rS);
    return res;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator%(const cpputils::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
    cpputils::BigInt<NUM_QWORDS_DEGR> remn, res;
    cpputils::BigInt<NUM_QWORDS_DEGR>::OperatorDivS(&remn,&res,a_lS,a_rS);
    return remn;
}
//


//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator+(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
    cpputils::BigInt<NUM_QWORDS_DEGR>::OperatorPlus(&retInt,retInt,a_rS);
    return retInt;
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
cpputils::BigInt<NUM_QWORDS_DEGR> operator-(const NumType& a_lS, const cpputils::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	cpputils::BigUInt<NUM_QWORDS_DEGR> retu;
	const cpputils::BigInt<NUM_QWORDS_DEGR> lS0(a_lS);
	const cpputils::BigUInt<NUM_QWORDS_DEGR> lS(lS0);
	const cpputils::BigUInt<NUM_QWORDS_DEGR> rS( a_rS );
	cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(&retu, lS, rS);
	return cpputils::BigInt<NUM_QWORDS_DEGR>(retu);
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

#define CPPUTILS_MAX_TENTH_QWORD    uint64_t(1000000000000000000)

#ifndef CPPUTILS_CPP_11_DEFINED
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords = CPPUTILS_BINT_EXPR_NUM_QW;
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfDwords = CPPUTILS_BINT_EXPR_NUM_DW;
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfBits = CPPUTILS_BINT_EXPR_NUM_BITS;
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff = CPPUTILS_BINT_EXPR_LAST_IND;
//template <uint64_t NUM_QWORDS_DEGR>
//const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_maxOf64bits = CPPUTILS_MAX_VALUE_PER_QWORD;
//template <uint64_t NUM_QWORDS_DEGR>
//const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bint10 ( 10 );
//template <uint64_t NUM_QWORDS_DEGR>
//const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bint2 ( 2 );
//template <uint64_t NUM_QWORDS_DEGR>
//const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bint0 ( 0 );
//template <uint64_t NUM_QWORDS_DEGR>
//const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bintDivMaskIn = BigUInt<NUM_QWORDS_DEGR>:: CPPUTILS_BINT_EXPR_DIV_MASK;
#endif

template <uint64_t NUM_QWORDS_DEGR>
const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bint0 ( 0 );
template <uint64_t NUM_QWORDS_DEGR>
const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bint1 ( 1 );
template <uint64_t NUM_QWORDS_DEGR>
const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bint2 ( 2 );
template <uint64_t NUM_QWORDS_DEGR>
const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_biqwMaxTenth(CPPUTILS_MAX_TENTH_QWORD);
template <uint64_t NUM_QWORDS_DEGR>
const  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_maxOf64bits(CPPUTILS_MAX_VALUE_PER_QWORD);

template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FUT  BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::s_bintDivMaskIn = BigUInt<NUM_QWORDS_DEGR>::DivMaskInitial();

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::s_bGlobalsInited = InitGlobalVars();

#define CPPUTILS_MAX_VALUE_PER_DWORD_PLUS1		0x100000000

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt()
{
}


template <uint64_t NUM_QWORDS_DEGR>
//template <uint64_t NUM_QWORDS_DEGR_OTHER>
CPPUTILS_CONSTEXPR_CONS BigUInt<NUM_QWORDS_DEGR>::BigUInt(const BigUInt<NUM_QWORDS_DEGR_OTHER>& a_cM)
{
    OtherBigUIntToThis(a_cM);
}


template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FLOAT_CONTR BigUInt<NUM_QWORDS_DEGR>::BigUInt(const float& a_lfValue)
{
    BiggerToThis(a_lfValue);
}

template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FLOAT_CONTR BigUInt<NUM_QWORDS_DEGR>::BigUInt(const double& a_lfValue)
{
    BiggerToThis(a_lfValue);
}

template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FLOAT_CONTR BigUInt<NUM_QWORDS_DEGR>::BigUInt(const long double& a_lfValue)
{
    BiggerToThis(a_lfValue);
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
CPPUTILS_CONSTEXPR_CONS BigUInt<NUM_QWORDS_DEGR>::BigUInt(const NumType& a_val)
{
	m_u.b64[0] = static_cast<uint64_t>(a_val);
	for(uint64_t i(1); i<s_numberOfQwords; ++i){
		m_u.b64[i] = 0;
	}	
}


template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_CONS BigUInt<NUM_QWORDS_DEGR>::BigUInt(const BigInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(&m_u,&(a_cM.m_u), sizeof(m_u));
}


#ifdef CPPUTILS_CPP_11_DEFINED
template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_CONS BigUInt<NUM_QWORDS_DEGR>::BigUInt( const ::std::array<uint64_t,s_numberOfQwords>& a_array)
{
    for(uint64_t i(0); i<s_numberOfQwords; ++i){
        m_u.b64[i] = a_array[i];
    }
}
#endif


template <uint64_t NUM_QWORDS_DEGR>
template <uint64_t NUM_QWORDS_DEGR_OTHER2>
inline void BigUInt<NUM_QWORDS_DEGR>::OtherBigUIntToThis(const BigUInt<NUM_QWORDS_DEGR_OTHER2>& a_cM)
{
    //static_assert(NUM_QWORDS_DEGR_OTHER_SMALL<=NUM_QWORDS_DEGR_OTHER_SMALL,"use small or equal big intereger as constructor input");
    static CPPUTILS_CONSTEXPR size_t scMemcpySize((BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords > BigUInt<NUM_QWORDS_DEGR_OTHER2>::s_numberOfQwords)?
                                             static_cast<size_t>(BigUInt<NUM_QWORDS_DEGR_OTHER2>::s_numberOfQwords)*sizeof(uint64_t) :
                                             static_cast<size_t>(BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords)*sizeof(uint64_t) );
    static CPPUTILS_CONSTEXPR size_t scRemainSizeToReset(
                (BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords > BigUInt<NUM_QWORDS_DEGR_OTHER2>::s_numberOfQwords)?
                    static_cast<size_t>(((BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords - BigUInt<NUM_QWORDS_DEGR_OTHER2>::s_numberOfQwords))*sizeof(uint64_t)):0);
    memcpy(&m_u,&(a_cM.m_u), scMemcpySize);
    memset(reinterpret_cast<char*>(&m_u)+sizeof(sizeof(a_cM.m_u)),0,scRemainSizeToReset);
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename BiggerType>
inline CPPUTILS_CONSTEXPR_FLOAT_CONTR void BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(BiggerType a_lfValue)
{
    static CPPUTILS_CONSTEXPR BiggerType scflValue(static_cast<BiggerType>(CPPUTILS_MAX_VALUE_PER_QWORD));

    memset(&(m_u),0,sizeof (m_u));

    uint64_t i(0);
    for(; (i<s_lastIndexInBuff)&&(a_lfValue>scflValue);++i){
        a_lfValue /= scflValue;
        m_u.b64[i] = static_cast<uint64_t>(scflValue * ::std::modf(a_lfValue,&a_lfValue));
    }
    m_u.b64[i] = static_cast<uint64_t>(a_lfValue);
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename BiggerType>
inline void BigUInt<NUM_QWORDS_DEGR>::thisToBigger(BiggerType* a_plfValue)const
{
    static CPPUTILS_CONSTEXPR BiggerType scflValue(static_cast<BiggerType>(CPPUTILS_MAX_VALUE_PER_QWORD));
    BiggerType lfMult(scflValue);

    *a_plfValue = static_cast<BiggerType>(m_u.b64[0]);
    for(uint64_t i(1); i<s_numberOfQwords;++i){
        (*a_plfValue) += lfMult * static_cast<BiggerType>(m_u.b64[i]);
    }
}


template <uint64_t NUM_QWORDS_DEGR>
inline CPPUTILS_CONSTEXPR_FNC_CPP14 BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::DivMaskInitial(){
    BigUInt rs;
    for(uint64_t i(0);i<s_lastIndexInBuff;++i){rs.m_u.b64[i] = 0;}
    rs.m_u.b64[s_lastIndexInBuff] = CPPUTILS_MASK_SIGN_BIT;
    return rs;
}


// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
// we have below operator=
template <uint64_t NUM_QWORDS_DEGR>
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator=(const BigUInt& a_cM)
{
	memcpy(&m_u,&(a_cM.m_u), sizeof(m_u));
	return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::operator float()const
{
    double fRet;
    thisToBigger(&fRet);
    return fRet;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::operator double()const
{
    double fRet;
    thisToBigger(&fRet);
    return fRet;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::operator long double()const
{
    double fRet;
    thisToBigger(&fRet);
    return fRet;
}


template <uint64_t NUM_QWORDS_DEGR>
template <uint64_t NUM_QWORDS_DEGR_OTHER2>
BigUInt<NUM_QWORDS_DEGR>::operator BigUInt<NUM_QWORDS_DEGR_OTHER2>()const
{
    BigUInt<NUM_QWORDS_DEGR_OTHER> ret;
    ret.OtherBigUIntToThis(*this);
    return ret;
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>::operator NumType()const
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning( disable : 4800 )
#endif
	return static_cast<NumType>(m_u.b64[0]);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}


template <uint64_t NUM_QWORDS_DEGR>
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator++()
{
	for(uint64_t i(0); i<s_numberOfQwords;++i){
        if(m_u.b64[i]<CPPUTILS_MAX_VALUE_PER_QWORD){
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
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator--()
{
	for(uint64_t i(0); i<s_numberOfQwords;++i){
		if(m_u.b64[i]>0){
			--m_u.b64[i];
			return *this;
		}
        m_u.b64[i] = CPPUTILS_MAX_VALUE_PER_QWORD;
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
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator+=(const BigUInt& a_rS)
{
    OperatorPlus(this,*this,a_rS);
    return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator-=(const BigUInt& a_rS)
{
    OperatorMinus(this,*this,a_rS);
    return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator*=(const BigUInt& a_rS)
{
    BigUInt thisConst(*this);
    BigUInt::OperatorMultU(this,thisConst,a_rS);
    return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
const BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator/=(const BigUInt& a_rS)
{
    BigUInt remn;
    BigUInt thisConst(*this);
    BigUInt::OperatorDivU(&remn,this,thisConst,a_rS);
    return *this;
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
inline bool BigUInt<NUM_QWORDS_DEGR>::HasAnyCommonBit(const BigUInt& a_lS, const BigUInt& a_rS)
{
    for(uint64_t i(0);i<s_numberOfQwords;++i){
        if(a_lS.m_u.b64[i] & a_rS.m_u.b64[i]){return true;}
    }
    return false;
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigUInt<NUM_QWORDS_DEGR>::OperatorPlus(BigUInt* CPPUTILS_MAY_ALIAS a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
    uint64_t ullnSum, ullnHas, ullnRemn = 0;
    for (uint64_t i(0); i < s_numberOfQwords; ++i) {
        ullnHas = CPPUTILS_MAX_VALUE_PER_QWORD - a_lS.m_u.b64[i];
        if (ullnHas >= ullnRemn) {
            ullnHas -= ullnRemn;
            ullnSum = a_lS.m_u.b64[i] + ullnRemn;
        }
        else {
            ullnSum = ullnRemn - 1;
            ullnHas = CPPUTILS_MAX_VALUE_PER_QWORD - ullnSum;
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
inline void BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(BigUInt* CPPUTILS_MAY_ALIAS a_res, const BigUInt& a_lS, const BigUInt& a_rS)
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
            lsTmp = CPPUTILS_MAX_VALUE_PER_QWORD - lsTmp;
		}

		if (lsTmp < a_rS.m_u.b64[i]) { // no dept yet. We have to make one
            ++ullnDept; // this will make current quad word equal (CPPUTILS_MAX_VALUE_PER_QWORD+1+lsTmp)
            ullnDif = (CPPUTILS_MAX_VALUE_PER_QWORD - a_rS.m_u.b64[i]) + lsTmp + 1;
            //ullnDif = (CPPUTILS_MAX_VALUE_PER_QWORD - (a_rS.m_data2)[i].d64) + lsTmp + 1;
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
inline void BigUInt<NUM_QWORDS_DEGR>::OperatorMultU(BigUInt* CPPUTILS_RESTRICT a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
    __private::__implementation::DataU tmpSingleMult;
	BigUInt tmpMult;
    uint64_t j,indInSum, lsTmp, rsTmp;
    uint64_t tmpSingleMultPrev;
	
	memset(&(a_res->m_u),0,sizeof (a_res->m_u));
	
	for (uint64_t i(0); i < s_numberOfDwords; ++i) {
		rsTmp = static_cast<uint64_t>(a_rS.m_u.b32[i]);
        if(rsTmp){
            memset(&(tmpMult.m_u),0,sizeof (tmpMult.m_u));
            tmpSingleMultPrev = 0;
            for(indInSum=i,j=0;indInSum<s_numberOfDwords;++indInSum,++j){
                lsTmp = static_cast<uint64_t>(a_lS.m_u.b32[j]);
                //tmpSingleMult.d64 = lsTmp * rsTmp;
                //tmpMult.m_u.b32[j] = tmpSingleMult.d32[0] + tmpSingleMultPrev;
                // tmpSingleMultPrev = tmpSingleMult.d32[1];
                tmpSingleMult.d64 = lsTmp * rsTmp + tmpSingleMultPrev;
                tmpMult.m_u.b32[indInSum] = tmpSingleMult.d32[0];
                tmpSingleMultPrev = static_cast<uint64_t>(tmpSingleMult.d32[1]);
            }
            (*a_res) += tmpMult;
        } // if(rsTmp){
    }  // for (uint64_t i(0); i < s_numberOfDwords; ++i) {
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(BigUInt* a_remn, BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	if (a_rS.isZero()) {
		// handling devide to zero as handles compiler
		a_res->m_u.b64[0] = a_lS.m_u.b64[0] / a_rS.m_u.b64[0];
		a_remn->m_u.b64[0] = a_lS.m_u.b64[0] % a_rS.m_u.b64[0];
		return;
	}
	
    BigUInt aMask(s_bintDivMaskIn);

	*a_remn = 0;
	*a_res = 0;

    for (uint64_t i(0);i< s_numberOfBits;++i) {
        (*a_remn) *= 2;
        (*a_res) *= 2;
        if(HasAnyCommonBit(a_lS,aMask)){
            ++(*a_remn);
        }
        if ((*a_remn) >= a_rS) {
            ++(*a_res);
            (*a_remn) -= a_rS;
        }
        aMask.RightShiftByOneBit();
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
void BigUInt<NUM_QWORDS_DEGR>::RightShiftByOneBit()
{
    uint64_t transferBits = 0, singleRes;

    for (uint64_t i(s_lastIndexInBuff);; --i) {
        singleRes = (m_u.b64[i] >> 1) | (transferBits << 63);
        transferBits = m_u.b64[i] & 0x1;
        m_u.b64[i] = singleRes;
        if(i==0){break;}
    }
}


template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::LeftShiftByOneBit()
{
    uint64_t transferBits = 0, singleRes;

    for (uint64_t i(0);i<s_numberOfQwords; ++i) {
        singleRes = (m_u.b64[i] << 1) | (transferBits >> 63);
        transferBits = m_u.b64[i] & 0x8000000000000000;
        m_u.b64[i] = singleRes;
    }
}


template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorRightShift(BigUInt* a_res, const BigUInt& a_lS, uint64_t a_shiftCount)
{
    static CPPUTILS_CONSTEXPR uint64_t numberOfBits = s_numberOfQwords * sizeof(uint64_t) * 8;
    if(a_shiftCount>=numberOfBits){memset(&(a_res->m_u),0,sizeof (a_res->m_u));}
    *a_res = a_lS;
    for(uint64_t i(0); i<a_shiftCount;++i){
        a_res->RightShiftByOneBit();
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

    const uint64_t transferMask = ~(CPPUTILS_MAX_VALUE_PER_QWORD >> bitShift);

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
uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()
{
	return m_u.b64;
}

template <uint64_t NUM_QWORDS_DEGR>
const uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()const
{
	return m_u.b64;
}


template <uint64_t NUM_QWORDS_DEGR>
void BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralU(BigUInt* a_res, const ::std::string& a_n, int a_base)
{
    ::std::string aNewStr( a_n );
    BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(a_res,const_cast<char*>(aNewStr.data()),aNewStr.length(),a_base);
}


template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::InitGlobalVars()
{
    return true;
}


template <uint64_t NUM_QWORDS_DEGR>
cpputils::BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::OperatorBuiLiteral(const ::std::string& a_n)
{
    ::cpputils::BigUInt<NUM_QWORDS_DEGR> res;
    ::std::string numStr(a_n);
    size_t unStrLen(numStr.length());
    char* pcNumStr = const_cast<char*>(numStr.data());
    switch(pcNumStr[0]){
    case '0':{
        switch(unStrLen){
        case 0: case 1:
            res = ::cpputils::BigUInt<NUM_QWORDS_DEGR>::s_bint0;
            break;
        default:{
            ++pcNumStr;
            --unStrLen;
            switch(pcNumStr[0]){
            case 'x': case 'X':
                ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(&res, ++pcNumStr,--unStrLen, 16);
                break;
            default:
                ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(&res, pcNumStr,unStrLen, 8);
                break;
            }  // switch(pcNumStr[1]){
        }break;
        }  // switch(unStrLen){
    }break;
    default:
        ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(&res, pcNumStr,unStrLen, 10);
        break;
    }  // switch(pcNumStr[0]){
    return res;
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename CharType>
inline void BigUInt<NUM_QWORDS_DEGR>::toStreamU( ::std::basic_ostream<CharType>* a_pStream )const
{
    ::std::ios_base::fmtflags fmt = a_pStream->flags();

    if (fmt & ::std::ios_base::dec) {
        // we have decimal
        BigUInt bintCopy(*this);
        BigUInt remn, res;
        bool bIterate = false;
        uint64_t i;
        uint64_t ullnCount = 0;
		CPPUTILS_CONSTEXPR_STACK_ARRAY(uint64_t,vValues,s_numberOfTenths);

        for(i=1;i<s_numberOfQwords;++i){
            if(bintCopy.m_u.b64[i]){bIterate=true;break;}
        }

        while(bIterate){
            OperatorDivU(&remn,&res,bintCopy,s_biqwMaxTenth);
            vValues[ullnCount++] = remn.m_u.b64[0];
            bintCopy.OtherBigUIntToThis(res);

            bIterate = false;
            for(i=1;i<s_numberOfQwords;++i){
                if(bintCopy.m_u.b64[i]){bIterate=true;break;}
            }
        }

        (*a_pStream) << bintCopy.m_u.b64[0];

        if(ullnCount){
            const size_t initialWidth  = static_cast<size_t>(a_pStream->width());
            const CharType initialFill = a_pStream->fill();
            a_pStream->width(18);
            a_pStream->fill('0');
            while(ullnCount){
                (*a_pStream) << vValues[--ullnCount];
            }
            a_pStream->width(static_cast<std::streamsize>(initialWidth));
            a_pStream->fill(initialFill);
        }

        return;
    }
    else if ((fmt & std::ios_base::oct) || (fmt & std::ios_base::hex)) {
        // we have hexadecimal
        for (uint64_t i(cpputils::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff); ; --i) {
            (*a_pStream) << m_u.b64[i];
            if (!i) { return; }
        }
    }
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(BigUInt* a_res, char* a_pStr, size_t a_strLen, int a_base)
{
    switch(a_base){
    case 10:{
        char dataTmp;
        char* pcTerm;
        BigUInt tmpMult;
        uint64_t lastUint64Value=0;
		size_t numberOfLastValueDigits=0;
		size_t ullnCount = 0;
		CPPUTILS_CONSTEXPR_STACK_ARRAY(uint64_t,vValues,s_numberOfTenths);

        memset(&(a_res->m_u),0,sizeof (a_res->m_u));

        while((a_strLen>18)&&(ullnCount<s_numberOfTenths)){
            dataTmp = a_pStr[18];
            a_pStr[18]=0;
            vValues[ullnCount] = ::std::strtoull(a_pStr,&pcTerm,10);
            if(a_pStr==pcTerm){
                goto lastValuePoint;
            }
			numberOfLastValueDigits = static_cast<uint64_t>(pcTerm-a_pStr);
            if(numberOfLastValueDigits<18){
                lastUint64Value = vValues[ullnCount];
                goto lastValuePoint;
            }
            ++ullnCount;
            a_pStr += 18;
            *a_pStr = dataTmp;
            a_strLen -= 18;
        }

        lastUint64Value = ::std::strtoull(a_pStr,&pcTerm,10);
		numberOfLastValueDigits = static_cast<uint64_t>(pcTerm-a_pStr);
        if(a_pStr==pcTerm){
            lastUint64Value = 0;
        }

lastValuePoint:
        uint64_t firstMultValueInt64 = 1;
        size_t i(0);
        for(; i<numberOfLastValueDigits;++i){
            firstMultValueInt64 *= 10;
        }

        BigUInt multValue(firstMultValueInt64), multValueTmp;
		size_t ind(ullnCount-1);

        for(i=0; i<ullnCount;++i,--ind){
            OperatorMultU(&multValueTmp,BigUInt(vValues[ind]),multValue);
            OperatorPlus(a_res,*a_res,multValueTmp);
            OperatorMultU(&multValueTmp,s_biqwMaxTenth,multValue);
            multValue.OtherBigUIntToThis(multValueTmp);
        }
		
		OperatorPlus(a_res,*a_res,BigUInt(lastUint64Value));

        return;

    }break;
    default:
        // todo: implement other cases. For non implemented cases make error
        *a_res = 0;
        break;
    }  // switch(a_base){
}



/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/



template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt()
{
}


template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FLOAT_CONTR BigInt<NUM_QWORDS_DEGR>::BigInt(const float& a_lfValue)
{
    if(a_lfValue<0.0){
        BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(-a_lfValue);
        AlertSign();
    }
    else{
        BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(a_lfValue);
    }
}


template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FLOAT_CONTR BigInt<NUM_QWORDS_DEGR>::BigInt(const long double& a_lfValue)
{
    if(a_lfValue<0.0){
        BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(-a_lfValue);
        AlertSign();
    }
    else{
        BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(a_lfValue);
    }
}


template <uint64_t NUM_QWORDS_DEGR>
CPPUTILS_CONSTEXPR_FLOAT_CONTR BigInt<NUM_QWORDS_DEGR>::BigInt(const double& a_lfValue)
{
    if(a_lfValue<0.0){
        BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(-a_lfValue);
        AlertSign();
    }
    else{
        BigUInt<NUM_QWORDS_DEGR>::BiggerToThis(a_lfValue);
    }
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
CPPUTILS_CONSTEXPR_CONS BigInt<NUM_QWORDS_DEGR>::BigInt(const NumType& a_val)
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
            this->m_u.b64[i] = CPPUTILS_MAX_VALUE_PER_QWORD;
		}
		this->operator++();
	}
}

template <uint64_t NUM_QWORDS_DEGR>
//template <uint64_t NUM_QWORDS_DEGR_OTHER>
CPPUTILS_CONSTEXPR_CONS BigInt<NUM_QWORDS_DEGR>::BigInt(const BigInt<NUM_QWORDS_DEGR_OTHER>& a_cM)
	:
      BigUInt<NUM_QWORDS_DEGR>(static_cast<const BigUInt<NUM_QWORDS_DEGR_OTHER>&>(a_cM))
{
}


template <uint64_t NUM_QWORDS_DEGR>
template <uint64_t NUM_QWORDS_DEGR_OTHER2>
CPPUTILS_CONSTEXPR_CONS BigInt<NUM_QWORDS_DEGR>::BigInt(const BigUInt<NUM_QWORDS_DEGR_OTHER2>& a_cM)
{
    BigUInt<NUM_QWORDS_DEGR_OTHER>::OtherBigUIntToThis(a_cM);
}


template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::operator float()const
{
    if(isMinus()){
        return BigUInt<NUM_QWORDS_DEGR>(-(*this)).operator float();
    }
    return BigUInt<NUM_QWORDS_DEGR>::operator float();
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::operator double()const
{
    if(isMinus()){
        return BigUInt<NUM_QWORDS_DEGR>(-(*this)).operator double();
    }
    return BigUInt<NUM_QWORDS_DEGR>::operator double();
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::operator long double()const
{
    if(isMinus()){
        return BigUInt<NUM_QWORDS_DEGR>(-(*this)).operator long double();
    }
    return BigUInt<NUM_QWORDS_DEGR>::operator long double();
}


// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
// we have these 2 operator=
// the point is, that will be nice if derived class BigInt inherits these operators from BigUInt
template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const BigUInt<NUM_QWORDS_DEGR>& a_cM)
{
	BigUInt<NUM_QWORDS_DEGR>::operator=(a_cM);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const BigInt& a_cM)
{
	BigUInt<NUM_QWORDS_DEGR>::operator=(a_cM);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>::operator NumType()const
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning( disable : 4800 )
#endif
	return static_cast<NumType>(static_cast<int64_t>(this->m_u.b64[0]));
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR> BigInt<NUM_QWORDS_DEGR>::operator-()const
{
    BigInt retInt;
	for(uint64_t i(0); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
		retInt.m_u.b64[i]=~(this->m_u.b64[i]);
	}
    return BigInt(retInt.operator++());
}


template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator++()
{
    return static_cast<const BigInt&>(BigUInt<NUM_QWORDS_DEGR>::operator++());
}


template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator--()
{
    return static_cast<const BigInt&>(BigUInt<NUM_QWORDS_DEGR>::operator--());
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigInt<NUM_QWORDS_DEGR>::AlertSign()
{
    const BigInt thisConst(*this);
    for(uint64_t i(0); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
        this->m_u.b64[i]=~(thisConst.m_u.b64[i]);
    }
    BigUInt<NUM_QWORDS_DEGR>::operator++();
}


template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator+=(const BigInt& a_rS)
{
    BigUInt<NUM_QWORDS_DEGR>::OperatorPlus(this,static_cast<BigUInt<NUM_QWORDS_DEGR>&>(*this),static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_rS));
    return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator-=(const BigInt& a_rS)
{
    BigUInt<NUM_QWORDS_DEGR>::OperatorMinus(this,static_cast<BigUInt<NUM_QWORDS_DEGR>&>(*this),static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_rS));
    return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator*=(const BigInt& a_rS)
{
    BigInt thisConst(*this);
    BigInt<NUM_QWORDS_DEGR>::OperatorMultS(this,thisConst,a_rS);
    return *this;
}


template <uint64_t NUM_QWORDS_DEGR>
const BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator/=(const BigInt& a_rS)
{
    BigInt remn;
    BigInt thisConst(*this);
    BigInt::OperatorDivS(&remn,this,thisConst,a_rS);
    return *this;
}


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
inline uint64_t BigInt<NUM_QWORDS_DEGR>::isMinus()const
{
    return this->m_u.b64[cpputils::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & CPPUTILS_MASK_SIGN_BIT;
}


template <uint64_t NUM_QWORDS_DEGR>
template <typename CharType>
inline void BigInt<NUM_QWORDS_DEGR>::toStreamS( ::std::basic_ostream<CharType>* a_pStream )const
{
    if(isMinus()){
        //a_pStream->write("-",1);
        (*a_pStream)<<'-';
        BigInt res(*this);
        res.AlertSign();
        static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(res).toStreamU(a_pStream);
    }
    else{
        static_cast<const BigUInt<NUM_QWORDS_DEGR>*>(this)->toStreamU(a_pStream);
    }
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigInt<NUM_QWORDS_DEGR>::OperatorMultS(BigInt* CPPUTILS_RESTRICT a_res, const BigInt& a_lS, const BigInt& a_rS)
{
    const uint64_t isThisMinus(a_lS.isMinus()), isRsMinus(a_rS.isMinus());
    if(isThisMinus){
        if(isRsMinus){
            BigUInt<NUM_QWORDS_DEGR>::OperatorMultU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_lS),
                                                    static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_rS));
        }
        else{
            BigUInt<NUM_QWORDS_DEGR>::OperatorMultU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_lS),
                                                    static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_rS));
            a_res->AlertSign();
        }
    }
    else{
        if(isRsMinus){
            BigUInt<NUM_QWORDS_DEGR>::OperatorMultU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_lS),
                                                    static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_rS));
            a_res->AlertSign();
        }
        else{
            BigUInt<NUM_QWORDS_DEGR>::OperatorMultU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_lS),
                                                    static_cast<const BigUInt<NUM_QWORDS_DEGR>& >(a_rS));
        }
    }
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigInt<NUM_QWORDS_DEGR>::OperatorDivS(BigInt* a_remn, BigInt* a_res, const BigInt& a_lS, const BigInt& a_rS)
{
    const uint64_t isThisMinus(a_lS.isMinus()), isRsMinus(a_rS.isMinus());
    if(isThisMinus){
        if(isRsMinus){
            BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_remn),static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),
                                                   static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_lS),static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_rS));
        }
        else{
            BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_remn),static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),
                                                   static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_lS),static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_rS));
            a_res->AlertSign();
        }
    }
    else{
        if(isRsMinus){
            BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_remn),static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),
                                                   static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_lS),static_cast<BigUInt<NUM_QWORDS_DEGR> >(-a_rS));
            a_res->AlertSign();
        }
        else{
            BigUInt<NUM_QWORDS_DEGR>::OperatorDivU(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_remn),static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),
                                                   static_cast<const BigUInt<NUM_QWORDS_DEGR>&>(a_lS),static_cast<const BigUInt<NUM_QWORDS_DEGR>& >(a_rS));
        }
    }
}


template <uint64_t NUM_QWORDS_DEGR>
inline void BigInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralSinline(BigInt* a_res, char* a_pStr, size_t a_strLen, int a_base)
{
    char* pcMinusPos = strchr(a_pStr,'-');

    if(pcMinusPos){
        BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),pcMinusPos,
                                                               a_strLen-static_cast<size_t>(pcMinusPos-a_pStr),a_base);
    }
    else{
        BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(static_cast<BigUInt<NUM_QWORDS_DEGR>*>(a_res),a_pStr,a_strLen,a_base);
    }
}


template <uint64_t NUM_QWORDS_DEGR>
void BigInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralS(BigInt* a_res, const ::std::string& a_n,int a_base)
{
    ::std::string aNewStr( a_n );
    BigInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralSinline(a_res,const_cast<char*>(aNewStr.data()),aNewStr.length(),a_base);
}


template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR> BigInt<NUM_QWORDS_DEGR>::OperatorBiLiteral(const ::std::string& a_n2)
{
    ::cpputils::BigInt<NUM_QWORDS_DEGR> res;
    ::std::string numStr(a_n2);
    size_t unStrLen(numStr.length());
    char* pcNumStr = const_cast<char*>(numStr.data());
    switch(pcNumStr[0]){
    case '-':
        ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(static_cast<::cpputils::BigUInt<NUM_QWORDS_DEGR>*>(&res),
                                                                           ++pcNumStr,--unStrLen, 10);
        res.AlertSign();
        break;
    case '0':{
        switch(unStrLen){
        case 0: case 1:
            res = static_cast<const ::cpputils::BigInt<NUM_QWORDS_DEGR>&>(::cpputils::BigUInt<NUM_QWORDS_DEGR>::s_bint0);
            break;
        default:{
            ++pcNumStr;
            --unStrLen;
            switch(pcNumStr[0]){
            case 'x': case 'X':
                ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(static_cast<::cpputils::BigUInt<NUM_QWORDS_DEGR>*>(&res),
                                                                                   ++pcNumStr,--unStrLen, 16);
                break;
            default:
                ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(static_cast<::cpputils::BigUInt<NUM_QWORDS_DEGR>*>(&res),
                                                                                   pcNumStr,unStrLen, 8);
                break;
            }  // switch(pcNumStr[1]){
        }break;
        }  // switch(unStrLen){
    }break;
    default:
        ::cpputils::BigUInt<NUM_QWORDS_DEGR>::OperatorAnyIntLiteralUinline(static_cast<::cpputils::BigUInt<NUM_QWORDS_DEGR>*>(&res),
                                                                           pcNumStr,unStrLen, 10);
        break;
    }  // switch(pcNumStr[0]){
    return res;
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
