//
// file:			hashtbl.hpp
// path:			include/cpputils/hashtbl.hpp
// created on:		2017 Jul 21
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP


#include <cpputils_internal_header.h>
#include <cpputils/functional.hpp>
#include <stdint.h>
#include <stddef.h>
#include <string>

#define DEFAULT_TABLE_SIZE	256

namespace cpputils { namespace hashtbl {

template <typename KeyType, typename DataType=int>
class FuncsT
{
public:
	typedef ::cpputils::function< FUNC_ARGS(size_t,const KeyType& key) >   Hash;
	typedef ::cpputils::function< FUNC_ARGS(bool,void* clbkData,const KeyType& key, const DataType& data) > Find;
	typedef ::cpputils::function< FUNC_ARGS(bool,void* clbkData,const KeyType& key) > FindVoid;
};


template <typename KeyType, typename DataType=int>
class Funcs 
{
public:
	static size_t	DefaultHash(const KeyType& key);
	static bool		DefaultFind(void* clbkData,const KeyType& key, const DataType& data);
	static bool		DefaultFindVoid(void* clbkData, const KeyType& key);
};


struct VoidPtrKey{
	const void*	key;
	size_t		keyLen;
	
	VoidPtrKey(const void* key, size_t keyLen,bool shouldDelete=true);
	VoidPtrKey(const VoidPtrKey& cM);
	VoidPtrKey(VoidPtrKey& cM, int shouldMove, bool shouldDelete = true) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	VoidPtrKey(VoidPtrKey&& cM,bool shouldDelete=true) noexcept;
#endif
	~VoidPtrKey();
	bool operator==(const VoidPtrKey& aM)const;
private:
	const bool m_shouldDFree;
};

template <typename DataType>
class Funcs<VoidPtrKey,DataType>
{
public:
	static size_t	DefaultHash(const VoidPtrKey& key);
	static bool		DefaultFind(void* clbkData,const VoidPtrKey& key, const DataType& data);
	static bool		DefaultFindVoid(void* clbkData, const VoidPtrKey& key);
};

template <typename CharType, typename DataType>
class Funcs< ::std::basic_string<CharType>, DataType >
{
public:
	static size_t	DefaultHash(const ::std::basic_string<CharType>& key);
	static bool		DefaultFind(void* clbkData,const ::std::basic_string<CharType>& key, const DataType& data);
	static bool		DefaultFindVoid(void* clbkData, const ::std::basic_string<CharType>& key);
};


template <typename KeyType,typename DataType>
class Base
{
public:
	struct HashItem;
	class  iterator;
	class  const_iterator;
public:
	
	Base(size_t tableSize= DEFAULT_TABLE_SIZE, typename FuncsT<KeyType,DataType>::Hash a_funcHash=&Funcs<KeyType,DataType>::DefaultHash);
	Base(typename FuncsT<KeyType, DataType>::Hash a_funcHash);
	Base(const Base& cM);
	Base(Base& cM, int shouldMove) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	Base(Base&& cM) noexcept;
#endif
	virtual ~Base();

	Base& operator=(const Base& cM);
	Base& ReplaceWithOther(Base& cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	Base& operator=(Base&& cM) noexcept;
#endif

	iterator		AddEntryEvenIfExists(const KeyType& key, const DataType& data);
    iterator		AddEntry(const KeyType& key, const DataType& data);
	iterator		AddOrReplaceEntry(const KeyType& key, const DataType& data);
	iterator		AddEntryWithKnownHash(const KeyType& key,const DataType& a_data, size_t a_hashVal);
	iterator		FindEntry(const KeyType& key,size_t* corespondingHash=CPPUTILS_NULL,
							  typename FuncsT<KeyType,DataType>::Find a_fnc=&Funcs<KeyType,DataType>::DefaultFind, void*clbkData=CPPUTILS_NULL)const;
    bool			RemoveEntry(const KeyType& key);
	void			RemoveEntry(const const_iterator entry);
	
	DataType&		operator[]( const KeyType& key );
	
	size_t			size()const;
	iterator		begin();
	iterator		end();
	const_iterator	begin()const;
	const_iterator	end()const;

protected:
	/*const*/ typename FuncsT<KeyType,DataType>::Hash	m_funcHash;
	HashItem**			m_pTable;
	/*const*/ size_t	m_unRoundedTableSizeMin1;
	HashItem*			m_pFirstItem;
	size_t				m_unSize;
	
public:
	struct HashItem {
		friend class Base;
	protected:
        HashItem(const KeyType& key, const DataType& data);
		virtual ~HashItem();
	public:
		//const KeyType key; DataType data;
		const KeyType first; DataType second;
	};
	
	class iterator{
	public:
		iterator();
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		HashItem* operator->()const;
		operator HashItem*()const;
		
	private:
		friend class Base;
		iterator(HashItem* a_pItem);
		HashItem* m_pItem;
	}static const s_endIter;
	
	class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const_iterator& operator++();
		const_iterator  operator++(int);
		const_iterator& operator--();
		const_iterator  operator--(int);
		const HashItem* operator->()const;
		operator const HashItem* ()const;
		
	private:
		friend class Base;
		const_iterator(const HashItem* a_pItem);
		HashItem* m_pItem;
	}static const s_endConstIter;
};


template <typename KeyType>
class Base<KeyType,void>
{
public:
	struct HashItem;
	class  iterator;
public:
	
	Base(size_t tableSize= DEFAULT_TABLE_SIZE, typename FuncsT<KeyType>::Hash a_funcHash=&Funcs<KeyType>::DefaultHash);
	Base(typename FuncsT<KeyType>::Hash a_funcHash);
	Base(const Base& cM);
	Base(Base& cM, int shouldMove) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	Base(Base&& cM) noexcept;
#endif
	virtual ~Base();

	Base& operator=(const Base& cM);
	Base& ReplaceWithOther(Base& cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	Base& operator=(Base&& cM) noexcept;
#endif

    iterator	AddEntry(const KeyType& key);
	iterator	AddEntryEvenIfExists(const KeyType& a_key);
	iterator	AddEntryWithKnownHash(const KeyType& key,size_t a_hashVal);
	iterator	FindEntry(const KeyType& key,size_t* corespondingHash=CPPUTILS_NULL,
						  void*clbkData=CPPUTILS_NULL,typename FuncsT<KeyType>::FindVoid a_fnc=&Funcs<KeyType>::DefaultFindVoid);
    bool		RemoveEntry(const KeyType& key);
	void		RemoveEntry(iterator entry);
	
	size_t		size()const;

protected:
	/*const*/ typename FuncsT<KeyType>::Hash	m_funcHash;
	HashItem**			m_pTable;
	/*const*/ size_t	m_unRoundedTableSizeMin1;
	HashItem*			m_pFirstItem;
	size_t				m_unSize;
	
public:
	struct HashItem {
		friend class Base;
	protected:
        HashItem(const KeyType& key);
		virtual ~HashItem();
	public:
		const KeyType first;
	};
	
	class iterator{
	public:
		iterator();
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		HashItem* operator->()const;
		operator HashItem*()const;
		
	private:
		friend class Base;
		iterator(HashItem* a_pItem);
		HashItem* m_pItem;
	}static const s_endIter;
	
	class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const_iterator& operator++();
		const_iterator  operator++(int);
		const_iterator& operator--();
		const_iterator  operator--(int);
		const HashItem* operator->()const;
		operator const HashItem*()const;
		
	private:
		friend class Base;
		const_iterator(const HashItem* a_pItem);
		HashItem* m_pItem;
	}static const s_endConstIter;
};


#ifdef CPPUTILS_CPP_11_DEFINED

template <typename DataType>
using HashTbl = Base<VoidPtrKey,DataType>;

template <typename KeyType>
using Set = Base<KeyType,void>;

using SetHash = Base<VoidPtrKey, void>;


template <typename CharType,typename DataType>
using StrHash = Base< ::std::basic_string<CharType>,DataType>;

template <typename CharType>
using StrSet = Base< ::std::basic_string<CharType>,void>;


#else

template <typename DataType>
class HashTbl : public Base<VoidPtrKey,DataType>{};

template <typename KeyType>
class Set : public Base<KeyType,void>{};

class SetHash : public Base<VoidPtrKey, void> {};

#endif


}}  // namespace cpputils { namespace hashtbl {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP
#include "hashtbl.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP
