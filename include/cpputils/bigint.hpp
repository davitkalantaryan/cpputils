//
// file:			bigint.hpp
// path:			include/cpputils/bigint.hpp
// created on:		2021 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_BIGINT_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_BIGINT_HPP

#include <cpputils/export_symbols.h>
#include <string>
#include <ios>
#include <stdint.h>
#ifdef CINTERNAL_CPP_11_DEFINED
#include <array>
#else
#include <malloc.h>
#ifndef _WIN32
#include <alloca.h>
#endif
#endif

namespace cpputils {


template <uint64_t NUM_QWORDS_DEGR>
class BigInt;

#define CPPUTILS_MAX_VALUE_PER_QWORD            0xffffffffffffffff
#define CPPUTILS_MASK_SIGN_BIT			(uint64_t(1)<<uint64_t(63))

//#define CINTERNAL_CONSTEXPR_FLOAT_CONTR    CINTERNAL_CONSTEXPR
#define CINTERNAL_CONSTEXPR_FLOAT_CONTR
#define CINTERNAL_CONSTEXPR_CONS

//#define CINTERNAL_CONSTEXPR_DIV_MSK    CINTERNAL_CONSTEXPR
#define CINTERNAL_CONSTEXPR_FUT      const

#define CPPUTILS_BINT_EXPR_LAST_IND     ((1<<NUM_QWORDS_DEGR)-1)
#define CPPUTILS_BINT_EXPR_NUM_QW       (1<<NUM_QWORDS_DEGR)
#define CPPUTILS_BINT_EXPR_NUM_DW       (1<<(NUM_QWORDS_DEGR+1))
#define CPPUTILS_BINT_EXPR_NUM_TENTHS   (1<<(NUM_QWORDS_DEGR+1))
#define CPPUTILS_BINT_EXPR_NUM_BITS     (CPPUTILS_BINT_EXPR_NUM_QW * sizeof(uint64_t) * 8)

#define NUM_QWORDS_DEGR_OTHER   NUM_QWORDS_DEGR


template <uint64_t NUM_QWORDS_DEGR>
class BigUInt
{
	//static_assert (NUM_QWORDS_DEGR>0,"In the case if Number of QWORDS is 1 (degree==0), use uint64_t or int64_t instead");
public:
    static CINTERNAL_CONSTEXPR uint64_t	s_lastIndexInBuff CINTERNAL_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_LAST_IND);
    static CINTERNAL_CONSTEXPR uint64_t	s_numberOfQwords  CINTERNAL_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_QW);
    static CINTERNAL_CONSTEXPR uint64_t	s_numberOfDwords  CINTERNAL_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_DW);
    static CINTERNAL_CONSTEXPR uint64_t  s_numberOfBits    CINTERNAL_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_BITS);
	static CINTERNAL_CONSTEXPR uint64_t	s_numberOfTenths  CINTERNAL_CONSTEXPR_EQ(CPPUTILS_BINT_EXPR_NUM_TENTHS);
    //static CINTERNAL_CONSTEXPR BigUInt	s_bint10  CINTERNAL_CONSTEXPR_EQ(BigUInt(10));
    //static CINTERNAL_CONSTEXPR BigUInt	s_bint2  CINTERNAL_CONSTEXPR_EQ(BigUInt(2));
    //static CINTERNAL_CONSTEXPR BigUInt	s_bint0  CINTERNAL_CONSTEXPR_EQ(BigUInt(0));
    static CINTERNAL_CONSTEXPR_FUT BigUInt	s_bint0  ;
	static CINTERNAL_CONSTEXPR_FUT BigUInt	s_bint1  ;
	static CINTERNAL_CONSTEXPR_FUT BigUInt	s_bint2  ;
    static CINTERNAL_CONSTEXPR_FUT BigUInt   s_biqwMaxTenth;
    static CINTERNAL_CONSTEXPR_FUT BigUInt	s_bintDivMaskIn;
    static CINTERNAL_CONSTEXPR_FUT BigUInt	s_maxOf64bits;
protected:
    static bool     s_bGlobalsInited;
public:
	BigUInt();
    //template <uint64_t NUM_QWORDS_DEGR_OTHER>
    CINTERNAL_CONSTEXPR_CONS BigUInt(const BigUInt<NUM_QWORDS_DEGR_OTHER>& cM);
    template <typename NumType>  // any type, that is possible to convert to uint64_t, except double
    CINTERNAL_CONSTEXPR_CONS BigUInt(const NumType& val);
    CINTERNAL_CONSTEXPR_FLOAT_CONTR BigUInt(const float& val);
    CINTERNAL_CONSTEXPR_FLOAT_CONTR BigUInt(const double& val);
    CINTERNAL_CONSTEXPR_FLOAT_CONTR BigUInt(const long double& val);
    CINTERNAL_CONSTEXPR_CONS BigUInt(const BigInt<NUM_QWORDS_DEGR>& cM);
#ifdef CINTERNAL_CPP_11_DEFINED
    CINTERNAL_CONSTEXPR_CONS BigUInt( const ::std::array<uint64_t,s_numberOfQwords>& );
#endif

    template <uint64_t NUM_QWORDS_DEGR_OTHER2>
    inline void OtherBigUIntToThis(const BigUInt<NUM_QWORDS_DEGR_OTHER2>&);
    template <typename BiggerType>
    inline CINTERNAL_CONSTEXPR_FLOAT_CONTR void BiggerToThis(BiggerType val);
    template <typename BiggerType>
    inline void thisToBigger(BiggerType* pVal)const;
    static inline CINTERNAL_CONSTEXPR_FNC_CPP14 BigUInt DivMaskInitial();
		
	// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
	// we have below operator=
    const BigUInt& operator=(const BigUInt& val);
	
    operator float()const;
    operator double()const;
    operator long double()const;
    operator bool()const;
    template <uint64_t NUM_QWORDS_DEGR_OTHER2>
    operator BigUInt<NUM_QWORDS_DEGR_OTHER2>()const;
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
	
	void    LeftShiftByOneBit();
	void    RightShiftByOneBit();

    template <typename CharType>
    inline void toStreamU( ::std::basic_ostream<CharType>* a_pStream )const;
	
public:
    static inline bool    HasAnyCommonBit(const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorPlus(BigUInt* CINTERNAL_MAY_ALIAS res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorMinus(BigUInt* CINTERNAL_MAY_ALIAS res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorMultU(BigUInt* CINTERNAL_RESTRICT res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorDivU(BigUInt* CINTERNAL_RESTRICT remn, BigUInt* CINTERNAL_RESTRICT res, const BigUInt& ls, const BigUInt& rs);
    static inline void    OperatorAnyIntLiteralUinline(BigUInt* res, char* pStr, size_t strLen,int base);
    static void    OperatorBtwAnd(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void    OperatorBtwOr(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void    OperatorBtwXor(BigUInt* res, const BigUInt& ls, const BigUInt& rs);
	static void    OperatorRightShift(BigUInt* res, const BigUInt& ls, uint64_t shiftCount);
	static void    OperatorLeftShift(BigUInt* res, const BigUInt& ls, uint64_t shiftCount);
    static void    OperatorAnyIntLiteralU(BigUInt* res, const ::std::string& a_n, int base);
    static cpputils::BigUInt<NUM_QWORDS_DEGR> OperatorBuiLiteral(const ::std::string& a_n);
	
public:
	uint64_t* buff();
	const uint64_t* buff()const;

protected:
    static bool InitGlobalVars();
	
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
    CINTERNAL_CONSTEXPR_FLOAT_CONTR BigInt(const float& val);
    CINTERNAL_CONSTEXPR_FLOAT_CONTR BigInt(const double& val);
    CINTERNAL_CONSTEXPR_FLOAT_CONTR BigInt(const long double& val);
    template <typename NumType>  // any type, that is possible to convert to int64_t, except double
    CINTERNAL_CONSTEXPR_CONS BigInt(const NumType& val);
    //template <uint64_t NUM_QWORDS_DEGR_OTHER>
    CINTERNAL_CONSTEXPR_CONS BigInt(const BigInt<NUM_QWORDS_DEGR_OTHER>& cM);
    template <uint64_t NUM_QWORDS_DEGR_OTHER2>
    CINTERNAL_CONSTEXPR_CONS BigInt(const BigUInt<NUM_QWORDS_DEGR_OTHER2>& cM);
		
	// because of this bug (or feature, but more looks like bug) https://github.com/grpc/grpc/issues/19570
	// we have these 2 operator=
	// the point is, that will be nice if derived class BigInt inherits these operators from BigUInt
    const BigInt& operator=(const BigUInt<NUM_QWORDS_DEGR>& val);
    const BigInt& operator=(const BigInt& val);
	
    operator float()const;
    operator double()const;
    operator long double()const;
    operator bool()const;
    template <typename NumType>  // any type, that is possible to convert to int64_t, except double and bool
	operator NumType()const;
	BigInt  operator-()const;

    const BigInt& operator++();
    const BigInt& operator--();

    const BigInt& operator+=(const BigInt& rS);
    const BigInt& operator-=(const BigInt& rS);
    const BigInt& operator*=(const BigInt& rS);
    const BigInt& operator/=(const BigInt& rS);

	bool operator<(const BigInt& rS)const;
	bool operator>(const BigInt& rS)const;
	bool operator<=(const BigInt& rS)const;
	bool operator>=(const BigInt& rS)const;

    inline void AlertSign();
    inline uint64_t isMinus()const;

    template <typename CharType>
    inline void toStreamS( ::std::basic_ostream<CharType>* a_pStream )const;

public:
    static inline void    OperatorMultS(BigInt* CINTERNAL_RESTRICT res, const BigInt& ls, const BigInt& rs);
    static inline void    OperatorDivS(BigInt* CINTERNAL_RESTRICT remn, BigInt* CINTERNAL_RESTRICT res, const BigInt& ls, const BigInt& rs);
    static inline void    OperatorAnyIntLiteralSinline(BigInt* res, char* pStr, size_t strLen, int base);
    static void    OperatorAnyIntLiteralS(BigInt* res, const ::std::string& a_n, int base);
    static ::cpputils::BigInt<NUM_QWORDS_DEGR> OperatorBiLiteral(const ::std::string& a_n);

private:
    template <typename CharType>
    ::std::basic_string< CharType > to_stringU( ::std::ios_base::fmtflags = ::std::ios_base::dec )const CINTERNAL_DELETE
    static inline void    OperatorMultU(BigUInt<NUM_QWORDS_DEGR>* CINTERNAL_RESTRICT , const BigUInt<NUM_QWORDS_DEGR>& , const BigUInt<NUM_QWORDS_DEGR>& ) CINTERNAL_DELETE
    static inline void    OperatorDivU(BigUInt<NUM_QWORDS_DEGR>* CINTERNAL_RESTRICT , BigUInt<NUM_QWORDS_DEGR>* CINTERNAL_RESTRICT , const BigUInt<NUM_QWORDS_DEGR>& , const BigUInt<NUM_QWORDS_DEGR>& ) CINTERNAL_DELETE
    static inline void    OperatorAnyIntLiteralUinline(BigUInt<NUM_QWORDS_DEGR>* res, ::std::string& a_n, int base) CINTERNAL_DELETE
    static void    OperatorAnyIntLiteralU(BigUInt<NUM_QWORDS_DEGR>* res, const ::std::string& a_n, int base) CINTERNAL_DELETE
    template <typename CharType>
    inline void toStreamU( ::std::basic_ostream<CharType>* a_pStream )const CINTERNAL_DELETE
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
