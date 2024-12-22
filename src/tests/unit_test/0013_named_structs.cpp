//
// file:			0006_enums.cpp
// created on:		2021 Apr 11
//

#include <cinternal/unit_test.h>
#include <cpputils/named_types.hpp>



CPPUTILS_NAMED_STRUCT(
    Struct1,
    (int,field1),
    (int,field2)
);


TEST(f_0013_named_structs, t0001)
{
    const char* strFieldName;
    Struct1 aStr;
    aStr.field1 = 1;
    aStr.field2 = 2;

    ASSERT_EQ(aStr.field1,1);
    ASSERT_EQ(aStr.field2, 2);
    strFieldName = CPPUTILS_NAMED_STRUCT_FIELD_NAME(Struct1, &aStr, &(aStr.field1));
    ASSERT_STREQ(strFieldName, "field1");
    strFieldName = CPPUTILS_NAMED_STRUCT_FIELD_NAME(Struct1, &aStr, &(aStr.field2));
    ASSERT_STREQ(strFieldName, "field2");
}
