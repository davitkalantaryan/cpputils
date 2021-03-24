//
// file:			hashtbl.hpp
// path:			include/common/hashtbl.hpp
// created on:		2017 Jul 21
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef COMMON_HASHTBL_HPP
#define COMMON_HASHTBL_HPP


#include <cpputils_internal_header.h>
#if defined(CPPUTILS_CPP_11_DEFINED) && !defined(DO_NOT_USE_STD_FUNCTION)
#define STD_FUNCTION_IS_USED
#include <functional>
#else
#endif
#include <stdint.h>
#include <stddef.h>

#define DEFAULT_TABLE_SIZE	1024

namespace common { namespace hashtbl {

template <typename KeyType, typename DataType=void>
class FuncsT
{
public:
#ifdef STD_FUNCTION_IS_USED
	typedef std::function<size_t(const KeyType& key)> Hash;
	typedef std::function<bool(void* clbkData,const KeyType& key, const DataType& data)> Find;
#else
	typedef size_t (*Hash)(const KeyType& key);
	typedef bool (*Find)(void* clbkData,const KeyType& key, const DataType* data_ptr);
#endif
};

template <typename KeyType>
class FuncsT<KeyType,void>
{
public:
#ifdef STD_FUNCTION_IS_USED
	typedef std::function<size_t(const KeyType& key)> Hash;
	typedef std::function<bool(void* clbkData,const KeyType& key)> Find;
#else
	typedef size_t (*Hash)(const KeyType& key);
	typedef bool (*Find)(void* clbkData,const KeyType& key);
#endif
};


template <typename KeyType, typename DataType=void>
class Funcs 
{
public:
	static size_t	DefaultHash(const KeyType& key);
	static bool		DefaultFind(void* clbkData,const KeyType& key, const DataType& data);
};

template <typename KeyType>
class Funcs<KeyType,void>
{
public:
	static size_t	DefaultHash(const KeyType& key);
	static bool		DefaultFind(void* clbkData,const KeyType& key);
};

struct VoidPtrKey{
	const void*	key;
	size_t		keyLen;
	
	VoidPtrKey(const void* key, size_t keyLen,bool shouldDelete=true);
	VoidPtrKey(const VoidPtrKey& cM);
	VoidPtrKey(VoidPtrKey&& cM,bool shouldDelete=true);
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
	virtual ~Base();

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
	const typename FuncsT<KeyType,DataType>::Hash	m_funcHash;
	HashItem**		m_pTable;
	size_t			m_unRoundedTableSizeMin1;
	HashItem*		m_pFirstItem;
	size_t			m_unSize;
	
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
	virtual ~Base();

    iterator	AddEntry(const KeyType& key);
	iterator	AddEntryWithKnownHash(const KeyType& key,size_t a_hashVal);
	iterator	FindEntry(const KeyType& key,size_t* corespondingHash=CPPUTILS_NULL,
						  void*clbkData=CPPUTILS_NULL,typename FuncsT<KeyType>::Find a_fnc=&Funcs<KeyType>::DefaultFind);
    bool		RemoveEntry(const KeyType& key);
	void		RemoveEntry(iterator entry);
	
	size_t		size()const;

protected:
	const typename FuncsT<KeyType>::Hash	m_funcHash;
	HashItem**		m_pTable;
	size_t			m_unRoundedTableSizeMin1;
	HashItem*		m_pFirstItem;
	size_t			m_unSize;
	
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



template <typename DataType>
class HashTbl : public Base<VoidPtrKey,DataType>{};

template <typename KeyType>
class Map : public Base<KeyType,void>{};


}}  // namespace common { namespace hashtbl {


#ifndef COMMON_HASHTBL_IMPL_HPP
#include "hashtbl.impl.hpp"
#endif



#endif  // #ifndef COMMON_HASHTBL_HPP
