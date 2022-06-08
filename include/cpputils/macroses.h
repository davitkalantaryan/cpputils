//
// file:			macroses.h
// path:			include/cpputils/macroses.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_MACROSES_H
#define CPPUTILS_INCLUDE_CPPUTILS_MACROSES_H

#include <cpputils/internal_header.h>

#define CPPUTILS_ID(_x)							_x
#define CPPUTILS_MACRO_APPLY_IMPL(_macro, ...)	CPPUTILS_ID(_macro(__VA_ARGS__))
#define CPPUTILS_CAT_IMPL(_a, _b)				_a ## _b
#define CPPUTILS_CAT(_a, _b)					CPPUTILS_CAT_IMPL(_a, _b)
#define CPPUTILS_MACRO_NAME(_name,_arg)			#_arg


#define CPPUTILS_MACRO_A1(_macro,_nm,_x)			_macro(_nm,_x)
#define CPPUTILS_MACRO_A2(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A1 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A3(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A2 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A4(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A3 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A5(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A4 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A6(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A5 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A7(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A6 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A8(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A7 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A9(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A8 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A10(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A9 (_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A11(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A10(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A12(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A11(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A13(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A12(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A14(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A13(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A15(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A14(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A16(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A15(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A17(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A16(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A18(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A17(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A19(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A18(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A20(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A19(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A21(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A20(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A22(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A21(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A23(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A22(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A24(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A23(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A25(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A24(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A26(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A25(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A27(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A26(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A28(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A27(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A29(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A28(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A30(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A29(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A31(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A30(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A32(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A31(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A33(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A32(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A34(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A33(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A35(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A34(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A36(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A35(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A37(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A36(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A38(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A37(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A39(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A38(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A40(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A39(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A41(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A40(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A42(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A41(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A43(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A42(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A44(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A43(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A45(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A44(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A46(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A45(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A47(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A46(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A48(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A47(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A49(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A48(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A50(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A49(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A51(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A50(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A52(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A51(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A53(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A52(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A54(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A53(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A55(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A54(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A56(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A55(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A57(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A56(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A58(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A57(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A59(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A58(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A60(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A59(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A61(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A60(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A62(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A61(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A63(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A62(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A64(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A63(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A65(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A64(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A66(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A65(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A67(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A66(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A68(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A67(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A69(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A68(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A70(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A69(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A71(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A70(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A72(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A71(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A73(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A72(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A74(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A73(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A75(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A74(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A76(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A75(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A77(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A76(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A78(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A77(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A79(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A78(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A80(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A79(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A81(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A80(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A82(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A81(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A83(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A82(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A84(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A83(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A85(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A84(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A86(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A85(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A87(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A86(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A88(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A87(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A89(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A88(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A90(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A89(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A91(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A90(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A92(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A91(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A93(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A92(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A94(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A93(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A95(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A94(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A96(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A95(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A97(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A96(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A98(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A97(_macro,_nm,__VA_ARGS__))
#define CPPUTILS_MACRO_A99(_macro,_nm,_x,...)		_macro(_nm,_x) , CPPUTILS_ID(CPPUTILS_MACRO_A98(_macro,_nm,__VA_ARGS__))

#define CPPUTILS_MACRO_COUNT(_count)			CPPUTILS_MACRO_A ## _count


#define CPPUTILS_NARGS_IMPL(_1,   _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9		\
		,_10, _11, _12, _13, _14, _15, _16, _17, _18, _19					\
		,_20, _21, _22, _23, _24, _25, _26, _27, _28, _29					\
		,_30, _31, _32, _33, _34, _35, _36, _37, _38, _39					\
		,_40, _41, _42, _43, _44, _45, _46, _47, _48, _49					\
		,_50, _51, _52, _53, _54, _55, _56, _57, _58, _59					\
		,_60, _61, _62, _63, _64, _65, _66, _67, _68, _69					\
		,_70, _71, _72, _73, _74, _75, _76, _77, _78, _79					\
		,_80, _81, _82, _83, _84, _85, _86, _87, _88, _89					\
		,_90, _91, _92, _93, _94, _95, _96, _97, _98, _99, N, ...			\
	) N


#define CPPUTILS_NARGS(...) CPPUTILS_ID( CPPUTILS_NARGS_IMPL(__VA_ARGS__,	\
		99, 98, 97, 96, 95, 94, 93, 92, 91, 90,								\
		89, 88, 87, 86, 85, 84, 83, 82, 81, 80,								\
		79, 78, 77, 76, 75, 74, 73, 72, 71, 70,								\
		69, 68, 67, 66, 65, 64, 63, 62, 61, 60,								\
		59, 58, 57, 56, 55, 54, 53, 52, 51, 50,								\
		49, 48, 47, 46, 45, 44, 43, 42, 41, 40,								\
		39, 38, 37, 36, 35, 34, 33, 32, 31, 30,								\
		29, 28, 27, 26, 25, 24, 23, 22, 21, 20,								\
		19, 18, 17, 16, 15, 14, 13, 12, 11, 10,								\
		9, 8, 7, 6, 5, 4, 3, 2, 1											\
	))


#define CPPUTILS_MACRO_APPY(_macro,_nm, ...) \
    CPPUTILS_ID( \
        CPPUTILS_MACRO_APPLY_IMPL( \
            CPPUTILS_MACRO_COUNT, \
            CPPUTILS_NARGS(__VA_ARGS__)) \
			(_macro,_nm, __VA_ARGS__))


#define CPPUTILS_NAMES(...)			CPPUTILS_MACRO_APPY(CPPUTILS_MACRO_NAME,dummy,__VA_ARGS__)




#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_MACROSES_H
