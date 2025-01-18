//
// repo:			cpputils
// file:			main_any_quick_test.cpp
// path:			src/tests/main_any_quick_test.cpp
// created on:		2023 Feb 27
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cpputils/named_types.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_NAMED_ENUM_TP(Enum1,int, fld1, fld2);

int main(void)
{

    Enum1 aEnm = Enum1::fld1;

    ::std::cout << aEnm.toString() << ::std::endl;
	
	return 0;
}
