//
// file:			hashbase.hpp
// path:			include/cpputils/hash/hashbase.hpp
// created on:		2022 Jan 28
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP


#include <cpputils_internal_header.h>
#include <cpputils/hash/items.hpp>
#include <cpputils/functional.hpp>
#include <string>
#include <functional>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


namespace cpputils { namespace hash {

template <typename Input,size_t templateDefaultSize,TypeMalloc mallocFn, TypeCalloc callocFn, TypeFree freeFn>
class ApiData : public BaseForAlloc<mallocFn,freeFn>
{
public:
    typedef it::InputPrivate<Input,mallocFn,freeFn> InputPrivate;
        
public:
    virtual ~ApiData();
        
protected:
    void ConstructAfterRoundedTableSizeMin1IsKnownB();
    void InitAllToZeroB();
    void ReplaceWithOtherB(ApiData*) CPPUTILS_NOEXCEPT;
    void AddEntryWithAlreadyCreatedItemB(InputPrivate* a_pItem, size_t a_hash);
    void RemoveEntryRawB(InputPrivate* a_pItem, size_t a_hash);
    
protected:
    InputPrivate**  m_pTable;
	size_t          m_unRoundedTableSizeMin1;
	size_t          m_unSize;
};

template <typename Key,typename InputT, typename Hash, size_t templateDefaultSize,
          TypeMalloc mallocFn, TypeCalloc callocFn, TypeRealloc reallocFn, TypeFree freeFn, typename ApiType>
class HashBase : public ApiType
{    
public:
    typedef ApiData<InputT,templateDefaultSize,mallocFn,callocFn,freeFn>  ApiDataAdv;
    static_assert( ::std::is_base_of<ApiDataAdv,ApiType>(), "ApiType shoulb be child of ApiData" );
    typedef it::InputPrivate<InputT,mallocFn,freeFn> InputPrivate;
    typedef typename ApiType::iterator Output;
    typedef typename ApiType::const_iterator COutput;
    typedef InputT  Input;
    
public:
    HashBase(size_t a_unBacketsCount=templateDefaultSize);
    HashBase(const HashBase& cM);
	HashBase(HashBase&& cM) CPPUTILS_NOEXCEPT;
	virtual ~HashBase() override;
    
    HashBase&      operator=(const HashBase& cM);
	HashBase&      operator=(HashBase&& cM) CPPUTILS_NOEXCEPT;
        
    size_t   size()const;
	void     clear() CPPUTILS_NOEXCEPT;
    
    Output   AddEntryWithKnownHashMv(Input&& a_item, size_t a_hash);
    Output   AddEntryWithKnownHashC(const Input& a_item, size_t a_hash);
    Output   AddEntryEvenIfExistsMv(Input&& a_item);
    Output   AddEntryEvenIfExistsC(const Input& a_item);
    Output   AddEntryIfNotExistMv(Input&& a_item);
    Output   AddEntryIfNotExistC(const Input& a_item);
    Output   findEntry( const Key& key, size_t* a_pHash=CPPUTILS_NULL )const;
    bool     erase(const Key& a_key);
    
protected:
    Input*   findEntryRaw( const Key& key, size_t* a_pHash )const;
        
    //friend ApiType;
};




}}  //  namespace cpputils { namespace hash {

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_IMPL_HPP
#include "hashbase.impl.hpp"
#endif

#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASH_HASHBASE_HPP
