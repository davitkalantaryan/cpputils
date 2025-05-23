//
// file:			hashtbl.def.hpp
// path:			include/cpputils/hashtbl.impl.hpp
// created on:		2021 Mar 26
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_DEF_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_DEF_HPP

#include <cpputils/export_symbols.h>
#include <cpputils/functional.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <string>
#include <cinternal/undisable_compiler_warnings.h>

#define DEFAULT_TABLE_SIZE	256

#ifdef _MSC_VER
#pragma warning (disable:4820)  //  '4' bytes padding added after data ...
#if (_MSC_VER>1929)
#pragma warning (disable:5267)  // copy constructor for '__p::__i::HashItemBase<KeyType,void>' is deprecated because it has a user-provided destructor
#endif
#endif

namespace cpputils { namespace hashtbl {

template <typename KeyType,typename DataType,typename Hash, size_t templateDefaultSize> 
class Base;

template <typename KeyType,typename HashItemType, typename HashItemPrivateType, typename Hash, size_t templateDefaultSize>
class BaseBase;

template <typename KeyType, typename DataType>
class FuncF 
{
public:
	typedef ::cpputils::function< CPPUTILS_FUNC_ARGS(bool,void* clbkData,const KeyType& key, const DataType& data) > Find;
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
	VoidPtrKey& operator=(const VoidPtrKey&) = delete;
#endif
	~VoidPtrKey();
	bool operator==(const VoidPtrKey& aM)const;
private:
	const bool	m_shouldDFree;
public:
	char		reserved01[7];
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
struct HashItemBase {
	template <typename KeyType1, typename DataType1,typename Hash,size_t templateDefaultSize>
	friend class ::cpputils::hashtbl::Base;
protected:
    HashItemBase(const KeyType& key, const DataType& data);
#ifdef CPPUTILS_CPP_11_DEFINED
    HashItemBase(const KeyType& key, DataType&& data);
#endif
	virtual ~HashItemBase();
public:
	const KeyType first; DataType second;
};

template <typename KeyType>
struct HashItemBase<KeyType,void>{
	template <typename KeyType1, typename DataType1, typename Hash,size_t templateDefaultSize>
	friend class ::cpputils::hashtbl::Base;
protected:
	HashItemBase(const KeyType& key);
	virtual ~HashItemBase();
public:
	const KeyType first;
};


template <typename TypeHashItem>
struct HashItem : public TypeHashItem{
	template <typename KeyType1, typename DataType1,typename Hash,size_t templateDefaultSize>
	friend class ::cpputils::hashtbl::Base;
    template <typename KeyType1,typename HashItemType, typename HashItemPrivateType, typename Hash, size_t templateDefaultSize>
    friend class ::cpputils::hashtbl::BaseBase;
protected:
    HashItem(const TypeHashItem& a_item, size_t a_hash);
	virtual ~HashItem() CPPUTILS_OVERRIDE;
public:
    const size_t  hash;
};


template <typename KeyType,typename DataType>
struct HashItemFull : public HashItem<HashItemBase<KeyType,DataType> > {
public:
	HashItemFull(const KeyType& key, const DataType& data);
	HashItemFull(const HashItem<HashItemBase<KeyType,DataType> >& item);
	~HashItemFull();
public:
	HashItemFull	*prev, *next;
	HashItemFull	*prevInTheList, *nextInTheList;
};


template <typename KeyType>
struct HashItemFull<KeyType,void> : public HashItem<HashItemBase<KeyType,void> > {
public:
	HashItemFull(const KeyType& key);
	HashItemFull(const HashItem<HashItemBase<KeyType,void> >& item);
	~HashItemFull();
public:
	HashItemFull	*prev, *next;
	HashItemFull	*prevInTheList, *nextInTheList;
};


}}  // namespace __p { namespace __i { 


#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_DEF_HPP
