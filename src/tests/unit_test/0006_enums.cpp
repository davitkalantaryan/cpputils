//
// file:			0006_enums.cpp
// created on:		2021 Apr 11
//

#include <cinternal/unit_test.h>
#include <cpputils/named_types.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <iostream>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_NAMED_ENUM_TP(Enum1, int, Field1, Field2);
CPPUTILS_NAMED_ENUM(Enum2, Field1, Field2);

CPPUTILS_NAMED_ENUM_TP(Enum3, int, Field1, Field2);
CPPUTILS_NAMED_ENUM_TP(Enum4, int, Field1, Field2);

CPPUTILS_NAMED_ENUM_TP(Enum5, int, Field1, Field2);
CPPUTILS_NAMED_ENUM_TP(Enum6, long, Field1, Field2);

CPPUTILS_NAMED_ENUM_TP(Enum7, int, Field1, Field2);
CPPUTILS_NAMED_ENUM_TP(Enum8, int, Field1, Field2);

//
CPPUTILS_NAMED_ENUM_TP(Color, char, Red, Blue);
CPPUTILS_NAMED_ENUM_TP(Auto, char, Wolkswagen, Renault, Bmw, Mers);

class TestClass{
public:
    CPPUTILS_NAMED_ENUM(Red, Green, Blue);
    CPPUTILS_NAMED_ENUM(Auto,Wolkswagen, Renault, Bmw, Mers);
};


TEST(f_0006_enums, t0000_enum01)
{
	Color aColor = Color::Red;
	
	// this switch is just to show, that this new enum you can use from switch
	switch(aColor){
	case Color::Blue:
		std::cout << "We have Blue\n";
		break;
	default:
		break;
	}
	
	// remember! CPPUTILS_ENUM01(Color,char,Red=1,Blue); will not work, enum should not contain =integerValue
	
	// now let's switch to demonstration of other features
	
	
	ASSERT_EQ(aColor,Color::Red);
	ASSERT_STREQ(aColor.toString(),"Red");
	
	aColor = Color::Blue;
	ASSERT_EQ(aColor,Color::Blue);
	ASSERT_STREQ(aColor.toString(),"Blue");
	
	// and now we demonstrate main advantage in comparision with
	// https://github.com/aantron/better-enums.  
	// Advantage is, that we are able to declare enum inside function and inside class.  
	// this is not possible in the case of better enum, because with defination of BETTER_ENUM, 
	// namespace also declared
	
    CPPUTILS_NAMED_ENUM(Animal,Dog,Cat,Elephant) ;
	Animal aAnimal;
	
	aAnimal = Animal::Dog;
	ASSERT_EQ(aAnimal,Animal::Dog);
	ASSERT_STREQ(aAnimal.toString(),"Dog");
	
	aAnimal = Animal::Cat;
	ASSERT_EQ(aAnimal,Animal::Cat);
	ASSERT_STREQ(aAnimal.toString(),"Cat");
	
	aAnimal = Animal::Elephant;
	ASSERT_EQ(aAnimal,Animal::Elephant);
	ASSERT_STREQ(aAnimal.toString(),"Elephant");
	
}


TEST(f_0006_enums, t0001_enum_raw)
{
	TestClass::Auto aAuto;

	aAuto = TestClass::Auto::Bmw;
	ASSERT_EQ(aAuto,TestClass::Auto::Bmw);
	ASSERT_STREQ(aAuto.toString(),"Bmw");
}
