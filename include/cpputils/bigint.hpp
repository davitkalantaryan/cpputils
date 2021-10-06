//
// file:			bigint.hpp
// path:			include/cpputils/bigint.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_BIGINT_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_BIGINT_HPP

#include <cpputils_internal_header.h>
#include <string>
#include <ios>
#include <stdint.h>
#ifdef CPPUTILS_CPP_11_DEFINED
#include <array>
#endif

namespace cpputils {


template <uint64_t NUM_QWORDS_DEGR>
class BigInt;

#define CPPUTILS_MASK_SIGN_BIT			(uint64_t(1)<<uint64_t(63))

//#define CPPUTILS_CONSTEXPR_DBL_CONTR    CPPUTILS_CONSTEXPR
#define CPPUTILS_CONSTEXPR_DBL_CONTR

//#define CPPUTILS_CONSTEXPR_DIV_MSK    CPPUTILS_CONSTEXPR
#define CPPUTILS_CONSTEXPR_DIV_MSK      const

#define CPPUTILS_BINT_EXPR_LAST_IND     ((1<<NUM_QWORDS_DEGR)-1)
#define CPPUTILS_BINT_EXPR_NUM_QW       (1<<NUM_QWORDS_DEGR)
#define CPPUTILS_BINT_EXPR_NUM_DW       (1<<(NUM_QWORDS_DEGR+1))
#define CPPUTILS_BINT_EXPR_NUM_BITS     (CPPUTILS_BINT_EXPR_NUM_QW * sizeof(uint64_t) * 8)


template <uint64_t NUM_QWORDS_DEGR>
class BigUInt
{
	static_assert (NUM_QWORDS_DEGR>0,"In the case if Number of QWORDS is 1 (degree==0), use uint64_t or int64_t instead");
public:
    static CPPUTILS_CONSTEXPR uint64_t	s_lastIndexInBuff CPPUTILS_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_LAST_IND);
    static CPPUTILS_CONSTEXPR uint64_t	s_numberOfQwords  CPPUTILS_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_QW);
    static CPPUTILS_CONSTEXPR uint64_t	s_numberOfDwords  CPPUTILS_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_DW);
    static CPPUTILS_CONSTEXPR uint64_t  s_numberOfBits    CPPUTILS_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_BITS);
    //static CPPUTILS_CONSTEXPR BigUInt	s_bint10  CPPUTILS_CONSTEXPR_EQ(BigUInt(10));
    //static CPPUTILS_CONSTEXPR BigUInt	s_bint2  CPPUTILS_CONSTEXPR_EQ(BigUInt(2));
    //static CPPUTILS_CONSTEXPR BigUInt	s_bint0  CPPUTILS_CONSTEXPR_EQ(BigUInt(0));
    static CPPUTILS_CONSTEXPR BigUInt	s_bint10 ;
    static CPPUTILS_CONSTEXPR BigUInt	s_bint2  ;
    static CPPUTILS_CONSTEXPR BigUInt	s_bint0  ;
    static CPPUTILS_CONSTEXPR_DIV_MSK BigUInt	s_bintDivMaskIn;
public:
	BigUInt();
    CPPUTILS_CONSTEXPR_CONS BigUInt(const BigUInt& cM);
    template <typename NumType>  // any type, that is possible to convert to uint64_t, except double
    CPPUTILS_CONSTEXPR_CONS BigUInt(const NumType& val);
    CPPUTILS_CONSTEXPR_DBL_CONTR BigUInt(const double& val);
    CPPUTILS_CONSTEXPR_CONS BigUInt(const BigInt<NUM_QWORDS_DEGR>& cM);
#ifdef CPPUTILS_CPP_11_DEFINED
    CPPUTILS_CONSTEXPR_CONS BigUInt( const ::std::array<uint64_t,s_numberOfQwords>& );
#endif

    inline CPPUTILS_CONSTEXPR_DBL_CONTR void DoubleToThis(const double& val);
    static inline CPPUTILS_CONSTEXPR BigUInt DivMaskInitial();
		
	// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
	// we have below operator=
    const BigUInt& operator=(const BigUInt& val);
	
    operator double()const;
    operator bool()const;
    template <typename NumType>  // any type, that is possible to convert to uint64_t, except double and bool
	operator NumType()const;

    const BigUInt& operator++();
    const BigUInt& operator--();
    BigUInt  operator++(int);
	BigUInt  operator--(int);

    const BigUInt& operator+=(const BigUInt& rS);
    const BigUInt& operator-=(const BigUInt& rS);
    const BigUInt& operator*=(const BigUInt& rS);
    const BigUInt& operator/=(const BigUInt& rS);
	
	bool operator<(const BigUInt& rS)const;
	bool operator>(const BigUInt& rS)const;
	bool operator<=(const BigUInt& rS)const;
	bool operator>=(const BigUInt& rS)const;
	bool operator==(const BigUInt& rS)const;
	bool operator!=(const BigUInt& rS)const;

	bool isZero()const;
	bool isNotZero()const;

	template <typename CharType>
    ::std::basic_string< CharType > to_stringU( ::std::ios_base::fmtflags fmt = ::std::ios_base::dec )const;
	
public:
    static inline bool    HasAnyCommonBit(const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorPlus(BigUInt* CPPUTILS_MAY_ALIAS res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorMinus(BigUInt* CPPUTILS_MAY_ALIAS res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorMultU(BigUInt* CPPUTILS_RESTRICT res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorDivU(BigUInt* CPPUTILS_RESTRICT remn, BigUInt* CPPUTILS_RESTRICT res, const BigUInt& ls, const BigUInt& rs);
    static void    OperatorBtwAnd2(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void    OperatorBtwOr(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void    OperatorBtwXor(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
    static void    RightShiftByOneBit(BigUInt* inOut);
	static void    OperatorRightShift(BigUInt* res, const BigUInt& ls, uint64_t shiftCount);
	static void    OperatorLeftShift(BigUInt* res, const BigUInt& ls, uint64_t shiftCount);
    static BigUInt OperatorAnyIntLiteralU(const ::std::string& a_n);
	
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
    CPPUTILS_CONSTEXPR_CONS BigInt(const BigInt& cM);
    CPPUTILS_CONSTEXPR_DBL_CONTR BigInt(const double& val);
    template <typename NumType>  // any type, that is possible to convert to int64_t, except double
    CPPUTILS_CONSTEXPR_CONS BigInt(const NumType& val);
    CPPUTILS_CONSTEXPR_CONS BigInt(const BigUInt<NUM_QWORDS_DEGR>& cM);
		
	// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
	// we have these 2 operator=
	// the point is, that will be nice if derived class BigInt inherits these operators from BigUInt
    const BigInt& operator=(const BigUInt<NUM_QWORDS_DEGR>& val);
    const BigInt& operator=(const BigInt& val);
	
    operator double()const;
    operator bool()const;
    template <typename NumType>  // any type, that is possible to convert to int64_t, except double and bool
	operator NumType()const;
	BigInt  operator-()const;

    const BigInt& operator++();
    const BigInt& operator--();
    const BigInt& AlertSign();

    const BigInt& operator+=(const BigInt& rS);
    const BigInt& operator-=(const BigInt& rS);
    const BigInt& operator*=(const BigInt& rS);
    const BigInt& operator/=(const BigInt& rS);

	bool operator<(const BigInt& rS)const;
	bool operator>(const BigInt& rS)const;
	bool operator<=(const BigInt& rS)const;
	bool operator>=(const BigInt& rS)const;

	uint64_t isMinus()const;

	template <typename CharType>
    ::std::basic_string< CharType > to_stringS( ::std::ios_base::fmtflags fmt= ::std::ios_base::dec )const;
public:
    static inline void    OperatorMultS(BigInt* CPPUTILS_RESTRICT res, const BigInt& ls, const BigInt& rs);
    static inline void    OperatorDivS(BigInt* CPPUTILS_RESTRICT remn, BigInt* CPPUTILS_RESTRICT res, const BigInt& ls, const BigInt& rs);
    static BigInt OperatorAnyIntLiteralS(const ::std::string& a_n);

private:
    template <typename CharType>
    ::std::basic_string< CharType > to_stringU( ::std::ios_base::fmtflags = ::std::ios_base::dec )const CPPUTILS_DELETE
    static inline void    OperatorMultU(BigInt* CPPUTILS_RESTRICT , const BigInt& , const BigInt& ) CPPUTILS_DELETE
    static inline void    OperatorDivU(BigInt* CPPUTILS_RESTRICT , BigInt* CPPUTILS_RESTRICT , const BigInt& , const BigInt& ) CPPUTILS_DELETE
    static BigInt OperatorAnyIntLiteralU(const ::std::string& ) CPPUTILS_DELETE
};


}  // namespace cpputils { 


namespace std {

template <uint64_t NUM_QWORDS_DEGR>
::std::string to_string( const cpputils::BigUInt<NUM_QWORDS_DEGR>& ubi);
template <uint64_t NUM_QWORDS_DEGR>
::std::wstring to_wstring(const cpputils::BigUInt<NUM_QWORDS_DEGR>& ubi);

template <uint64_t NUM_QWORDS_DEGR>
::std::string to_string(const cpputils::BigInt<NUM_QWORDS_DEGR>& ubi);
template <uint64_t NUM_QWORDS_DEGR>
::std::wstring to_wstring(const cpputils::BigInt<NUM_QWORDS_DEGR>& ubi);

}  // namespace std {



#ifndef CPPUTILS_INCLUDE_CPPUTILS_BIGINT_IMPL_HPP
#include "bigint.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_HASHTBL_HPP
