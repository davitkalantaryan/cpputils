//
// file:			bigint.impl.hpp
// path:			include/common/bigint.impl.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP
#define CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP


#ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_HPP
//#error do not include this header directly
#include "bigint.hpp"
#endif

#include <cpputils_internal_header.h>
#include <stddef.h>
#include <stdint.h>
#include <ostream>
#include <string>
#include <sstream>
#include <string.h>
//#include <cpputils_endian.h>

namespace __private { namespace __implementation {


union DataU{
	uint64_t	d64;
	uint32_t	d32[2];
};


}}  // namespace __private { namespace __implementation {

namespace common { 

template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords = 1<<NUM_QWORDS_DEGR;
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfDwords = 1<<(NUM_QWORDS_DEGR+1);
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff = BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords - 1;

#define MAX_VALUE_PER_QWORD		0xffffffffffffffff
#define MASK_SIGN_BIT			0x8000000000000000

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

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>::operator NumType()const
{	
	return static_cast<NumType>(m_u.b64[0]);
}

//
template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator+=(const BigUInt& a_rS)
{
	OperatorPlus(this,*this,a_rS);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator-=(const BigUInt& a_rS)
{
	OperatorMinus(this,*this,a_rS);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator*=(const BigUInt& a_rS)
{
	BigUInt lS(*this);
	OperatorMinus(this,lS,a_rS);
	return *this;	
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator/=(const BigUInt& a_rS)
{
	BigUInt aLs;
	OpratorDiv(a_rS,&aLs);
	*this=aLs;
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator%=(const BigUInt& a_rS)
{
	BigUInt aLs;
	OpratorDiv(a_rS,&aLs);
	return *this;
}
//

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator<<=(uint64_t a_rS)
{
	const uint64_t qwordShift = a_rS / 64;
	const uint64_t bitShift = a_rS % 64;
	uint64_t transferBits=0, singleRes;
	
	if(qwordShift){
		if(qwordShift>=s_numberOfQwords){*this=0;return *this;}
		memmove(m_u.b64+qwordShift,m_u.b64,(s_numberOfQwords-qwordShift)*sizeof(uint64_t));
		memset(m_u.b64,0,qwordShift*sizeof(uint64_t));
	}
	
	const uint64_t transferMask = (MAX_VALUE_PER_QWORD>>bitShift)<<bitShift;
		
	for(uint64_t i(0);i<s_numberOfQwords;++i){
		singleRes = (m_u.b64[0]<<bitShift) | transferBits;
		transferBits = m_u.b64[0]&transferMask;
		m_u.b64[0] = singleRes;
	}
	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator>>=(uint64_t a_rS)
{
	const uint64_t qwordShift = a_rS / 64;
	const uint64_t bitShift = a_rS % 64;
	uint64_t transferBits=0, singleRes;
	
	if(qwordShift){
		if(qwordShift>=s_numberOfQwords){*this=0;return *this;}
		memmove(m_u.b64,m_u.b64+qwordShift,(s_numberOfQwords-qwordShift)*sizeof(uint64_t));
		memset(m_u.b64+s_lastIndexInBuff-qwordShift,0,qwordShift*sizeof(uint64_t));
	}
	
	const uint64_t transferMask = MAX_VALUE_PER_QWORD>>bitShift;
		
	for(uint64_t i(s_lastIndexInBuff);;--i){
		singleRes = (m_u.b64[0]>>bitShift) | (transferBits<<bitShift);
		transferBits = m_u.b64[0]&transferMask;
		m_u.b64[0] = singleRes;
		if(!i){break;}
	}
	
	return *this;
}

//


//
template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator+=(const BigInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator+=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator-=(const BigInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator-=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator*=(const BigInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator*=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator/=(const BigInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator/=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator%=(const BigInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator%=(BigUInt(a_rs));
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator+=(const NumType& a_rs)
{
	return this->operator+=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator-=(const NumType& a_rs)
{
	return this->operator-=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator*=(const NumType& a_rs)
{
	return this->operator*=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator/=(const NumType& a_rs)
{
	return this->operator/=(BigUInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator%=(const NumType& a_rs)
{
	return this->operator%=(BigUInt(a_rs));
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
void BigUInt<NUM_QWORDS_DEGR>::OpratorDiv(BigUInt* a_remn, BigUInt* a_res, const BigUInt& a_lS, const BigUInt& a_rS)
{
	if(!a_rS){
		// handling devide to zero as handles compiler
		a_res->m_u.b64[0] = a_lS.m_u.b64[0] / a_rS.m_u.b64[0];
		a_remn->m_u.b64[0] = a_lS.m_u.b64[0] % a_rS.m_u.b64[0];
		return;
	}
	
	
	BigUInt aMask;
	//aMask.m_u.
	
	
	BigUInt rsTmp(a_rS);
	uint64_t i, biggestIndex, biggestBit;
	
	for(i=s_lastIndexInBuff;;--i){
		if(rsTmp.m_u.b64[i]){
			biggestIndex = i;
			break;
		}
	}
	
	for(i=0;i<64;++i){
		if((rsTmp.m_u.b64[biggestIndex]<<i)&MASK_SIGN_BIT){
			biggestBit = 63-i ;
			break;
		}
	}
	
//	/const uint64_t overallBits = 
	
}

//template <uint64_t NUM_QWORDS_DEGR>
//uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()
//{
//	return m_buff;
//}
//
//template <uint64_t NUM_QWORDS_DEGR>
//const uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()const
//{
//	return m_buff;
//}



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
		this->m_buff[0]=static_cast<uint64_t>(val);
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = 0;
		}
	}
	else{
		this->m_buff[0] = static_cast<uint64_t>(~(-val));
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = MAX_VALUE_PER_QWORD;
		}
		this->operator++();
	}
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt(const BigUInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(this->m_buff,a_cM.buff(),static_cast<size_t>(BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords)*sizeof (uint64_t));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const NumType& a_val)
{
	const int64_t val = static_cast<int64_t>(a_val);
	if(val>=0){
		this->m_buff[0]=static_cast<uint64_t>(val);
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = 0;
		}
	}
	else{
		this->m_buff[0] = static_cast<uint64_t>(~(-val));
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = MAX_VALUE_PER_QWORD;
		}
		this->operator++();
	}
	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(const BigUInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(this->m_buff,a_cM.buff(),BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords*sizeof (uint64_t));
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>::operator NumType()const
{
	return static_cast<NumType>(static_cast<int64_t>(this->m_buff[0]));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR> BigInt<NUM_QWORDS_DEGR>::operator-()const
{
	BigInt<NUM_QWORDS_DEGR> retInt;
	for(uint64_t i(0); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
		retInt.m_buff[i]=~(this->m_buff[i]);
	}
	return retInt.operator++();
}

//
template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator+=(const BigInt& a_rs)
{
	BigUInt<NUM_QWORDS_DEGR>::operator+=(BigUInt<NUM_QWORDS_DEGR>(a_rs));
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator-=(const BigInt& a_rs)
{
	return operator+=(-a_rs);
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator*=(const BigInt& a_rs)
{
	BigInt thisUnsigned, rsUnsigned;
	const uint64_t isMinusThis=this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs=a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRet=isMinusThis^isMinusRs;
	
	if(isMinusThis){thisUnsigned = -(*this);}
	else {thisUnsigned=*this;}
	
	if(isMinusRs){rsUnsigned = -a_rs;}
	else {rsUnsigned = a_rs;}
	
	BigUInt<NUM_QWORDS_DEGR> multRes = BigUInt<NUM_QWORDS_DEGR>(thisUnsigned) * BigUInt<NUM_QWORDS_DEGR>(rsUnsigned) ;
	
	*this = isMinusRet?(-BigInt(multRes)) : BigInt(multRes);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator/=(const BigInt& a_rs)
{
	BigInt thisUnsigned, rsUnsigned;
	const uint64_t isMinusThis=this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs=a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRet=isMinusThis^isMinusRs;
	
	if(isMinusThis){thisUnsigned = -(*this);}
	else {thisUnsigned=*this;}
	
	if(isMinusRs){rsUnsigned = -a_rs;}
	else {rsUnsigned = a_rs;}
	
	BigUInt<NUM_QWORDS_DEGR> divRes = BigUInt<NUM_QWORDS_DEGR>(thisUnsigned) / BigUInt<NUM_QWORDS_DEGR>(rsUnsigned) ;
	
	*this = isMinusRet?(-BigInt(divRes)) : BigInt(divRes);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator%=(const BigInt& a_rs)
{
	BigInt thisUnsigned, rsUnsigned;
	const uint64_t isMinusThis=this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs=a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRet=isMinusThis^isMinusRs;
	
	if(isMinusThis){thisUnsigned = -(*this);}
	else {thisUnsigned=*this;}
	
	if(isMinusRs){rsUnsigned = -a_rs;}
	else {rsUnsigned = a_rs;}
	
	BigUInt<NUM_QWORDS_DEGR> divRes = BigUInt<NUM_QWORDS_DEGR>(thisUnsigned) % BigUInt<NUM_QWORDS_DEGR>(rsUnsigned) ;
	
	*this = isMinusRet?(-BigInt(divRes)) : BigInt(divRes);
	return *this;
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator+=(const BigUInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator+=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator-=(const BigUInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator-=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator*=(const BigUInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator*=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator/=(const BigUInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator/=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator%=(const BigUInt<NUM_QWORDS_DEGR>& a_rs)
{
	return this->operator%=(BigInt(a_rs));
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator+=(const NumType& a_rs)
{
	return this->operator+=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator-=(const NumType& a_rs)
{
	return this->operator-=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator*=(const NumType& a_rs)
{
	return this->operator*=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator/=(const NumType& a_rs)
{
	return this->operator/=(BigInt(a_rs));
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename NumType>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator%=(const NumType& a_rs)
{
	return this->operator%=(BigInt(a_rs));
}
//


template <uint64_t NUM_QWORDS_DEGR>
bool BigInt<NUM_QWORDS_DEGR>::operator<(const BigInt& a_rs)const
{
	const uint64_t isMinusThis=this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs=a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	
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
	const uint64_t isMinusThis=this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs=a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	
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
	const uint64_t isMinusThis = this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs = a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;

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
	const uint64_t isMinusThis = this->m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	const uint64_t isMinusRs = a_rs.m_buff[BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;

	if (isMinusThis == isMinusRs) {
		return BigUInt<NUM_QWORDS_DEGR>::operator>=(a_rs);
	}

	if (isMinusThis) {
		return false;
	}

	return true;
}


}  // namespace common { 


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename CharType, uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const common::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{
	const uint64_t* pbi = a_bi.buff();
	const std::ios_base::fmtflags aFlags = a_os.flags();

	if (aFlags & std::ios_base::dec) {
		// we have decimal
		int nIter = 0;
		std::basic_string<CharType> retStr;
		const common::BigUInt<NUM_QWORDS_DEGR> bi10(10);
		common::BigUInt<NUM_QWORDS_DEGR> value(a_bi), remn;

		while (value) {
			std::basic_stringstream<CharType> osTmp;
			remn = value;
			remn.OpratorDiv(bi10, &value);
			osTmp << static_cast<uint64_t>(remn);
			retStr = osTmp.str() + retStr;
			++nIter;
		}

		if (nIter) { a_os << retStr; }
		else { a_os.put('0'); }
		return a_os;
	}
	else if ((aFlags & std::ios_base::oct) || (aFlags & std::ios_base::hex)) {
		for (uint64_t i(common::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff); ; --i) {
			a_os << pbi[i];
			if (!i) { return a_os; }
		}
	}

	return a_os;
}

//
#if 1
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt += a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt -= a_rS);
}


template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt *= a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt /= a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt %= a_rS);
}
//


//
template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt += common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt -= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}


template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt *= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt /= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt %= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}
//

//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt += common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt -= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt *= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt /= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt %= common::BigUInt<NUM_QWORDS_DEGR>(a_rS));
}
#endif
//

//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const NumType& a_rS, const common::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt += a_lS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const NumType& a_rS, const common::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt -= a_lS);
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const NumType& a_rS, const common::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt *= a_lS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator/(const NumType& a_rS, const common::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt /= a_lS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator%(const NumType& a_rS, const common::BigUInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt %= a_lS);
}
//


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename CharType, uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const common::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
	const uint64_t isMinus = a_bi.buff()[common::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;

	if (isMinus) {
		a_os.put('-');
		a_os << common::BigUInt<NUM_QWORDS_DEGR>(-a_bi);
	}
	else {
		a_os << common::BigUInt<NUM_QWORDS_DEGR>(a_bi);
	}

	return a_os;
}

//
#if 1
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const common::BigInt<NUM_QWORDS_DEGR>& a_lS,const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt += a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const common::BigInt<NUM_QWORDS_DEGR>& a_lS,const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt -= a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const common::BigInt<NUM_QWORDS_DEGR>& a_lS,const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt *= a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const common::BigInt<NUM_QWORDS_DEGR>& a_lS,const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt /= a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const common::BigInt<NUM_QWORDS_DEGR>& a_lS,const common::BigInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt %= a_rS);
}
//

//
template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt += common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt -= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}


template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt *= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt /= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt %= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}
//


//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt += common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt -= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt *= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt /= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const common::BigInt<NUM_QWORDS_DEGR>& a_lS, const NumType& a_rS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_lS);
	return (retInt %= common::BigInt<NUM_QWORDS_DEGR>(a_rS));
}
#endif
//


//
template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator+(const NumType& a_rS, const common::BigInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt += a_lS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator-(const NumType& a_rS, const common::BigInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt -= a_lS);
}


template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator*(const NumType& a_rS, const common::BigInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt *= a_lS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator/(const NumType& a_rS, const common::BigInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt /= a_lS);
}

template <typename NumType, uint64_t NUM_QWORDS_DEGR>
common::BigInt<NUM_QWORDS_DEGR> operator%(const NumType& a_rS, const common::BigInt<NUM_QWORDS_DEGR>& a_lS)
{
	common::BigInt<NUM_QWORDS_DEGR> retInt(a_rS);
	return (retInt %= a_lS);
}
//


#endif  // #ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP
