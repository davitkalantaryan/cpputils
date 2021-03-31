//
// file:			0000_initial.cpp
// created on:		2021 Feb 02
//

#include "gtest/gtest.h"
#include <common/sharedptr.hpp>

class MyTestClass
{
public:
	MyTestClass(bool*);
	~MyTestClass();
	
private:
	bool* m_pbIsDeleted;
};

static void ReferenceChangeClbk(void*,MyTestClass*,size_t a_prevRefs,size_t a_refs);
static size_t s_expectedPrevRef;
static size_t s_expectedRef;
static bool s_bIsExiting = false;


TEST(f_0004_sharedptr, t0000_first)
{
	bool bIsDeleted = false;
	
#ifdef CPPUTILS_STD_FUNCTION_IS_USED
	
	{
		s_expectedPrevRef = 0;
		s_expectedRef = 1;
		
		common::SharedPtr< MyTestClass > ptr01( new MyTestClass(&bIsDeleted),[](void* a1,MyTestClass* a2,size_t a_prevRefs,size_t a_refs){
			ReferenceChangeClbk(a1,a2,a_prevRefs,a_refs);
		});
		ASSERT_EQ(ptr01.getReferences(),1);
		
		s_expectedPrevRef = 1;
		s_expectedRef = 0;
	}
	
	ASSERT_TRUE(bIsDeleted);
	
#endif
	
	s_expectedPrevRef = 0;
	s_expectedRef = 1;
	common::SharedPtr< MyTestClass > ptr02( new MyTestClass(&bIsDeleted),&ReferenceChangeClbk);
	ASSERT_EQ(ptr02.getReferences(),1);
	
	s_expectedPrevRef = 1;
	s_expectedRef = 2;
	common::SharedPtr< MyTestClass > ptr03(ptr02);
	ASSERT_EQ(ptr02.getReferences(),ptr03.getReferences());
	ASSERT_EQ(ptr02.getReferences(),2);
	
	s_expectedPrevRef = 2;
	s_expectedRef = 3;
	common::SharedPtr< MyTestClass > ptr04;
	ptr04 = ptr03;
	ASSERT_EQ(ptr02.getReferences(),ptr03.getReferences());
	ASSERT_EQ(ptr02.getReferences(),ptr04.getReferences());
	ASSERT_EQ(ptr02.getReferences(),3);
	
	s_bIsExiting = true;
	
}


void ReferenceChangeClbk(void*,MyTestClass*,size_t a_prevRefs,size_t a_refs)
{
	if(s_bIsExiting){
		ASSERT_TRUE(a_refs<a_prevRefs);
	}
	else{
		ASSERT_EQ(a_prevRefs,s_expectedPrevRef);
		ASSERT_EQ(a_refs,s_expectedRef);
	}
}


MyTestClass::MyTestClass(bool* a_pbIsDeleted)
	:
	  m_pbIsDeleted(a_pbIsDeleted)
{
	*m_pbIsDeleted = false;
}

MyTestClass::~MyTestClass()
{
	*m_pbIsDeleted = true;
}
