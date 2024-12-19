//
// file:			cpputils_hashtbl.cpp
// path:			src/core/cpputils_hashtbl.cpp
// created on:		2021 Mar 05
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef cinternal_hash1_raw_mem_inline_needed
#define cinternal_hash1_raw_mem_inline_needed
#endif

#include <cpputils/hashtbl.hpp>
#include <cinternal/hash_functions.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

namespace __private { namespace __implementation {

CPPUTILS_EXPORT const void* GenerateDataBasedOnData(const void* a_data, size_t a_dataSize);

}}  // namespace __private { namespace __implementation {

namespace cpputils { namespace hashtbl {

size_t FHashVoidPtr::operator()(const VoidPtrKey& a_key)const
{
	return ::cinternal_hash1_raw_mem_inline(a_key.key,a_key.keyLen);
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



}}  // namespace __private { namespace __implementation {
