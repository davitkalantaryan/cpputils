//
// file:			hashtbl.def.hpp
// path:			include/cpputils/hashtbl.impl.hpp
// created on:		2021 Mar 26
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_DEF_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_DEF_HPP

#include <cpputils_internal_header.h>
#include <cpputils/functional.hpp>
#include <stddef.h>
#include <string>

#define DEFAULT_TABLE_SIZE	256

namespace cpputils { namespace hashtbl {

template <typename KeyType,typename DataType,typename Hash, size_t templateDefaultSize> 
class Base;

template <typename KeyType, typename DataType>
class FuncF 
{
public:
	typedef ::cpputils::function< FUNC_ARGS(bool,void* clbkData,const KeyType& key, const DataType& data) > Find;
	static bool		DefaultFind(void* clbkData,const KeyType& key, const DataType& data);
};


struct VoidPtrKey{
	const void*	key;
	size_t		keyLen;
	
	VoidPtrKey(const void* key, size_t keyLen,bool shouldDelete=true);
	VoidPtrKey(const VoidPtrKey& cM);
	VoidPtrKey(VoidPtrKey& cM, int shouldMove, bool shouldDelete = true) CPPUTILS_NOEXCEPT;
#ifdef CPPUTILS_CPP_11_DEFINED
	VoidPtrKey(VoidPtrKey&& cM,bool shouldDelete=true) CPPUTILS_NOEXCEPT;
#endif
	~VoidPtrKey();
	bool operator==(const VoidPtrKey& aM)const;
private:
	const bool m_shouldDFree;
};

template <typename KeyType>
class FHash 
{
public:
	size_t	operator()(const KeyType& key)const;
};

class FHashVoidPtr
{
public:
	size_t	operator()(const VoidPtrKey& key)const;
};

template <typename CharType>
class FHashStr
{
public:
	size_t	operator()(const ::std::basic_string<CharType>& key)const;
};

template <typename IntType>
class FHashInt
{
public:
	size_t	operator()(const IntType& key)const;
};


}} // namespace cpputils { namespace hashtbl {


namespace __p { namespace __i { 

template <typename KeyType,typename DataType>
struct HashItem {
	template <typename KeyType1, typename DataType1,typename Hash,size_t templateDefaultSize>
	friend class ::cpputils::hashtbl::Base;
protected:
	HashItem(const KeyType& key, const DataType& data);
	virtual ~HashItem();
public:
	const KeyType first; DataType second;
};


template <typename KeyType,typename DataType>
struct HashItemFull : public HashItem<KeyType,DataType> {
public:
	HashItemFull(const KeyType& key, const DataType& data);
	HashItemFull(const HashItem<KeyType,DataType>& item);
	~HashItemFull();
	const HashItemFull& operator=(const HashItem<KeyType,DataType>& item);
public:
	HashItemFull	*prev, *next;
	HashItemFull	*prevInTheList, *nextInTheList;
	size_t			hashValue;
};


template <typename KeyType>
struct HashItem<KeyType,void>{
	template <typename KeyType1, typename DataType1, typename Hash,size_t templateDefaultSize>
	friend class ::cpputils::hashtbl::Base;
protected:
	HashItem(const KeyType& key);
	virtual ~HashItem();
public:
	const KeyType first;
};

template <typename KeyType>
struct HashItemFull<KeyType,void> : public HashItem<KeyType,void> {
public:
	HashItemFull(const KeyType& key);
	HashItemFull(const HashItem<KeyType,void>& item);
	~HashItemFull();
public:
	HashItemFull	*prev, *next;
	HashItemFull	*prevInTheList, *nextInTheList;
	size_t			hashValue;
};


}}  // namespace __p { namespace __i { 


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_DEF_HPP
