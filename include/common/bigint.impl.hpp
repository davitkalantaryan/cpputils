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

#include <sstream>
#include <string.h>

namespace __private { namespace __implementation {

CPPUTILS_EXPORT void OperatorPlus(uint64_t a_numberOfQwords, uint64_t* a_res, const uint64_t* a_ls, const uint64_t* a_rs);

}}  // namespace __private { namespace __implementation {

namespace common { 

template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords = 1<<NUM_QWORDS_DEGR;
template <uint64_t NUM_QWORDS_DEGR>
const  uint64_t BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff = BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords - 1;

#define MAX_VALUE_PER_QWORD		0xffffffffffffffff
#define MASK_SIGN_BIT			0x8000000000000000

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt()
{
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt(uint64_t a_val)
{
	m_buff[0] = a_val;
	for(uint64_t i(1); i<s_numberOfQwords; ++i){
		m_buff[i] = 0;
	}	
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>::BigUInt(const BigInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(m_buff,a_cM.buff(),s_numberOfQwords*sizeof (uint64_t));
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator=(uint64_t a_val)
{
	m_buff[0] = a_val;
	for(uint64_t i(1); i<s_numberOfQwords; ++i){
		m_buff[i] = 0;
	}	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator=(const BigInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(m_buff,a_cM.buff(),s_numberOfQwords*sizeof (uint64_t));
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
template <typename IntType>
BigUInt<NUM_QWORDS_DEGR>::operator IntType()const
{	
	return static_cast<IntType>(m_buff[0]);
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR> BigUInt<NUM_QWORDS_DEGR>::operator-()const
{
	BigUInt<NUM_QWORDS_DEGR> retInt;
	for(uint64_t i(0); i<s_numberOfQwords; ++i){
		retInt.m_buff[i]=~m_buff[i];
	}
	return retInt.operator++();
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator+=(const BigUInt& a_rS)
{
	__private::__implementation::OperatorPlus(s_numberOfQwords,m_buff,m_buff,a_rS.m_buff);
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator-=(const BigUInt& a_rS)
{
	return operator+=(-a_rS);
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator*=(const BigUInt& a_rS)
{
	if(!(*this)){
		return *this;
	}
	
	if(!a_rS){
		for(uint64_t i(0); i<s_numberOfQwords; ++i){
			m_buff[i]=0;
		}
	}
	
	const BigUInt thisIn(*this);
	const BigUInt iter = a_rS-1;
	for(BigUInt i(0); i<iter;++i){
		(*this) += thisIn;
	}
	
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

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::operator++()
{
	for(uint64_t i(0); i<s_numberOfQwords;++i){
		if(m_buff[i]<MAX_VALUE_PER_QWORD){
			++m_buff[i];
			return *this;
		}
		m_buff[i] = 0;	
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
		if(m_buff[i]>0){
			--m_buff[i];
			return *this;
		}
		m_buff[i] = MAX_VALUE_PER_QWORD;
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
		if(m_buff[i]<a_rS.m_buff[i]){return true;}
		if(m_buff[i]>a_rS.m_buff[i]){return false;}
		if(!i){break;}
	}
	
	return false;
	
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator>(const BigUInt& a_rS)const
{
	for(uint64_t i(s_lastIndexInBuff); ; --i){
		if(m_buff[i]>a_rS.m_buff[i]){return true;}
		if(m_buff[i]<a_rS.m_buff[i]){return false;}
		if(!i){break;}
	}
		
	return false;
}

template <uint64_t NUM_QWORDS_DEGR>
bool BigUInt<NUM_QWORDS_DEGR>::operator==(const BigUInt& a_rS)const
{
	for(uint64_t i(0);i<s_numberOfQwords; ++i){
		if(m_buff[i]!=a_rS.m_buff[i]){return false;}
	}
	
	return true;
}

template <uint64_t NUM_QWORDS_DEGR>
BigUInt<NUM_QWORDS_DEGR>& BigUInt<NUM_QWORDS_DEGR>::OpratorDiv(const BigUInt& a_rS, BigUInt* a_divisonResult)
{
	if(!a_rS){
		// handling devide to zero as handles compiler
		a_divisonResult->m_buff[0] = m_buff[0] /= a_rS.m_buff[0];
		m_buff[0] %= a_rS.m_buff[0];
		return *this;
	}
	
	*a_divisonResult = 0;
	
	while(a_rS<(*this)){
		a_divisonResult->operator++();
		this->operator-=(a_rS);
	}
	
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()
{
	return m_buff;
}

template <uint64_t NUM_QWORDS_DEGR>
const uint64_t* BigUInt<NUM_QWORDS_DEGR>::buff()const
{
	return m_buff;
}



/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/



template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt()
{
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt(int64_t a_val)
{
	if(a_val>=0){
		this->m_buff[0]=a_val;
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = 0;
		}
	}
	else{
		this->m_buff[0] = ~(-a_val);
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = MAX_VALUE_PER_QWORD;
		}
		this->operator++();
	}
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>::BigInt(const BigUInt<NUM_QWORDS_DEGR>& a_cM)
{
	memcpy(this->m_buff,a_cM.buff(),BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords*sizeof (uint64_t));
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator=(int64_t a_val)
{
	if(a_val>=0){
		this->m_buff[0] = a_val;
		for(uint64_t i(1); i<BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords; ++i){
			this->m_buff[i] = 0;
		}
	}
	else{
		this->m_buff[0] = ~(-a_val);
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
template <typename IntType>
BigInt<NUM_QWORDS_DEGR>::operator IntType()const
{
	return static_cast<IntType>(this->m_buff[0]);
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

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator+=(const BigInt& a_rs)
{
	BigUInt<NUM_QWORDS_DEGR>::operator+=(BigUInt<NUM_QWORDS_DEGR>(a_rs));
	return *this;
}

template <uint64_t NUM_QWORDS_DEGR>
BigInt<NUM_QWORDS_DEGR>& BigInt<NUM_QWORDS_DEGR>::operator-=(const BigInt& a_rs)
{
	BigUInt<NUM_QWORDS_DEGR>::operator-=(BigUInt<NUM_QWORDS_DEGR>(a_rs));
	return *this;
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


}  // namespace common { 


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator+(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt;
	__private::__implementation::OperatorPlus(common::BigUInt<NUM_QWORDS_DEGR>::s_numberOfQwords,retInt.buff(),a_lS.buff(),a_rS.buff());
	return retInt;
}

template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator-(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	return a_lS+(-a_rS);
}


template <uint64_t NUM_QWORDS_DEGR>
common::BigUInt<NUM_QWORDS_DEGR> operator*(const common::BigUInt<NUM_QWORDS_DEGR>& a_lS,const common::BigUInt<NUM_QWORDS_DEGR>& a_rS)
{
	common::BigUInt<NUM_QWORDS_DEGR> retInt(0);
	for(common::BigUInt<NUM_QWORDS_DEGR> i(0); i<a_lS; ++i){
		retInt += a_rS;
	}	
	return retInt;
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

template <typename CharType,uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const common::BigUInt<NUM_QWORDS_DEGR>& a_bi)
{	
	const uint64_t* pbi = a_bi.buff();
	const std::ios_base::fmtflags aFlags = a_os.flags();
	
	if(aFlags&std::ios_base::dec){
		// we have decimal
		int nIter = 0;
		std::basic_string<CharType> retStr;
		const common::BigUInt<NUM_QWORDS_DEGR> bi10(10);
		common::BigUInt<NUM_QWORDS_DEGR> value(a_bi), remn;
		
		while(value){
			std::basic_stringstream<CharType> osTmp;
			remn = value;
			remn.OpratorDiv(bi10,&value);
			osTmp << static_cast<uint64_t>(remn);
			retStr = osTmp.str() + retStr;
			++nIter;
		}
		
		if(nIter){a_os<<retStr;}
		else{a_os.put('0');}
		return a_os;
	}
	else if((aFlags&std::ios_base::oct)||(aFlags&std::ios_base::hex)){
		for(uint64_t i(common::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff); ;--i){
			a_os << pbi[i];
			if(!i){return a_os;}
		}
	}
	
	return a_os;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

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

template <typename CharType,uint64_t NUM_QWORDS_DEGR>
std::basic_ostream<CharType>& operator<<(std::basic_ostream<CharType>& a_os, const common::BigInt<NUM_QWORDS_DEGR>& a_bi)
{
	const uint64_t isMinus=a_bi.buff()[common::BigUInt<NUM_QWORDS_DEGR>::s_lastIndexInBuff] & MASK_SIGN_BIT;
	
	if(isMinus){
		a_os.put('-');
		a_os << common::BigUInt<NUM_QWORDS_DEGR>(-a_bi);
	}
	else{
		a_os << common::BigUInt<NUM_QWORDS_DEGR>(a_bi);
	}
	
	return a_os;
}


#endif  // #ifndef CPPUTILS_INCLUDE_COMMON_BIGINT_IMPL_HPP
