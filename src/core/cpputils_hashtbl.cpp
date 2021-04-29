//
// file:			cpputils_hashtbl.cpp
// path:			src/core/cpputils_hashtbl.cpp
// created on:		2021 Mar 05
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/hashtbl.hpp>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

namespace __private { namespace __implementation {

CPPUTILS_EXPORT const void* GenerateDataBasedOnData(const void* a_data, size_t a_dataSize);

}}  // namespace __private { namespace __implementation {

/* The mixing step */
#define mix2(a,b,c) \
{ \
  a=a-b;  a=a-c;  a=a^(c>>13); \
  b=b-c;  b=b-a;  b=b^(a<<8);  \
  c=c-a;  c=c-b;  c=c^(b>>13); \
  a=a-b;  a=a-c;  a=a^(c>>12); \
  b=b-c;  b=b-a;  b=b^(a<<16); \
  c=c-a;  c=c-b;  c=c^(b>>5);  \
  a=a-b;  a=a-c;  a=a^(c>>3);  \
  b=b-c;  b=b-a;  b=b^(a<<10); \
  c=c-a;  c=c-b;  c=c^(b>>15); \
}


namespace cpputils { namespace hashtbl {

size_t FHashVoidPtr::operator()(const VoidPtrKey& a_key)const
{
	return __private::__implementation::hash1_(a_key.key,a_key.keyLen);
}

/*///////////////////////////////////////////////////////////////////////////*/

VoidPtrKey::VoidPtrKey(const void* a_key, size_t a_keyLen,bool a_shouldDelete)
	:
	  key(a_shouldDelete?__private::__implementation::GenerateDataBasedOnData(a_key,a_keyLen):a_key),
	  keyLen(a_keyLen),
	  m_shouldDFree(a_shouldDelete)
{
}

VoidPtrKey::VoidPtrKey(const VoidPtrKey& a_cM)
	:
	  key(__private::__implementation::GenerateDataBasedOnData(a_cM.key,a_cM.keyLen)),
	  keyLen(a_cM.keyLen),
	  m_shouldDFree(true)
{
}

VoidPtrKey::VoidPtrKey(VoidPtrKey& a_cM, int, bool a_shouldDelete) CPPUTILS_NOEXCEPT
	:
	key(a_shouldDelete ? __private::__implementation::GenerateDataBasedOnData(a_cM.key, a_cM.keyLen) : a_cM.key),
	keyLen(a_cM.keyLen),
	m_shouldDFree(a_shouldDelete)
{
}

#ifdef CPPUTILS_CPP_11_DEFINED
VoidPtrKey::VoidPtrKey(VoidPtrKey&& a_cM,bool a_shouldDelete) CPPUTILS_NOEXCEPT
	:
	  VoidPtrKey(a_cM,1, a_shouldDelete)
{
}
#endif

VoidPtrKey::~VoidPtrKey()
{
	if(m_shouldDFree){
		free(const_cast<void*>(this->key));
	}
}

bool VoidPtrKey::operator==(const VoidPtrKey &a_aM) const
{
	return (this->keyLen ==a_aM.keyLen) && (memcmp(this->key,a_aM.key,this->keyLen)==0);
}

}}  // namespace cpputils { namespace hashtbl {



namespace __private { namespace __implementation {


CPPUTILS_EXPORT const void* GenerateDataBasedOnData(const void* a_data, size_t a_dataSize)
{
	void* pReturnData = malloc(a_dataSize);
	if(pReturnData){
		memcpy(pReturnData,a_data,a_dataSize);
	}
	
	return pReturnData;
}


CPPUTILS_EXPORT size_t FindTableSizeFromIitialArg(size_t a_tInitSize)
{
	size_t i(0);
	size_t tRet(a_tInitSize);

	if (!a_tInitSize) { return 1;} // list will be implemented
	
	for (; tRet; tRet = (a_tInitSize >> ++i))
		;
	tRet = static_cast<size_t>(1) << static_cast<size_t>(i - 1);
	if (tRet != a_tInitSize) { tRet <<= 1; }

	return tRet;
}


CPPUTILS_EXPORT size_t hash1_( const void* a_pKey, size_t a_unKeySize )
{
	uint32_t unKeySize = static_cast<uint32_t>(a_unKeySize);
    CPPUTILS_REGISTER const uint8_t *k = static_cast<const uint8_t *>(a_pKey);
    CPPUTILS_REGISTER uint32_t a,b,c;  /* the internal state */
	
	uint32_t          len;    /* how many key bytes still need mixing */
	
	/* Set up the internal state */
	len = unKeySize;
	a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
	c = 13;         /* variable initialization of internal state */
	
	/*---------------------------------------- handle most of the key */
	while (len >= 12)
	{
        a=a+(k[0]+(static_cast<uint32_t>(k[1])<<8)+(static_cast<uint32_t>(k[2])<<16) +(static_cast<uint32_t>(k[3])<<24));
        b=b+(k[4]+(static_cast<uint32_t>(k[5])<<8)+(static_cast<uint32_t>(k[6])<<16) +(static_cast<uint32_t>(k[7])<<24));
        c=c+(k[8]+(static_cast<uint32_t>(k[9])<<8)+(static_cast<uint32_t>(k[10])<<16)+(static_cast<uint32_t>(k[11])<<24));
		mix2(a,b,c);
		k = k+12; len = len-12;
	}
	
	
	/*------------------------------------- handle the last 11 bytes */
	c = c+unKeySize;
	
	switch(len)              /* all the case statements fall through */
	{
    case 11: c=c+(static_cast<uint32_t>(k[10])<<24); CPPUTILS_FALLTHROUGH 
    case 10: c=c+(static_cast<uint32_t>(k[9])<<16); CPPUTILS_FALLTHROUGH
    case 9 : c=c+(static_cast<uint32_t>(k[8])<<8); CPPUTILS_FALLTHROUGH
		
		/* the first byte of c is reserved for the length */
    case 8 : b=b+(static_cast<uint32_t>(k[7])<<24); CPPUTILS_FALLTHROUGH
    case 7 : b=b+(static_cast<uint32_t>(k[6])<<16); CPPUTILS_FALLTHROUGH
    case 6 : b=b+(static_cast<uint32_t>(k[5])<<8); CPPUTILS_FALLTHROUGH
    case 5 : b=b+k[4]; CPPUTILS_FALLTHROUGH
    case 4 : a=a+(static_cast<uint32_t>(k[3])<<24); CPPUTILS_FALLTHROUGH
    case 3 : a=a+(static_cast<uint32_t>(k[2])<<16); CPPUTILS_FALLTHROUGH
    case 2 : a=a+(static_cast<uint32_t>(k[1])<<8); CPPUTILS_FALLTHROUGH
    case 1 : a=a+k[0];
		/* case 0: nothing left to add */
	}
	mix2(a,b,c);
	/*-------------------------------------------- report the result */
	
	return static_cast<size_t>(c);
}


}}  // namespace __private { namespace __implementation {
