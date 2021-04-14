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
#include "hashtbl.def.hpp"


namespace cpputils { namespace hashtbl {


template <typename KeyType,typename HashItem, typename HashItemPrivate, typename Hash>
class BaseBase
{
public:
	HashItem*	FindEntry(const KeyType& key,size_t* corespondingHash=CPPUTILS_NULL)const;
	bool		RemoveEntry(const KeyType& key);
	void		RemoveEntry(const HashItem* a_data);
	size_t		size()const;
	
protected:	
	BaseBase(size_t tableSize= DEFAULT_TABLE_SIZE);
	BaseBase(const BaseBase& cM);
	BaseBase(BaseBase* mM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	BaseBase(BaseBase&& cM) noexcept;
#endif
	virtual ~BaseBase();

	const BaseBase& operator=(const BaseBase& cM);
	const BaseBase& ReplaceWithOther(BaseBase* cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	const BaseBase& operator=(BaseBase&& cM) noexcept;
#endif
	
	HashItem*		AddEntryEvenIfExistsRaw(const HashItem& a_item);
    HashItem*		AddEntryIfNotExistRaw(const HashItem& a_item);
	HashItem*		AddEntryWithKnownHashRaw(const HashItem& a_item, size_t a_hashVal);
	
	HashItem*		firstItem()const;

private:
	HashItem**			m_pTable;
	/*const*/ size_t	m_unRoundedTableSizeMin1;
	HashItem*			m_pFirstItem;
	size_t				m_unSize;
	
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash=FHash<KeyType>>
class Base : public BaseBase< KeyType,__p::__i::HashItem<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash  >
{
public:
	class  iterator;
	class  const_iterator;
	
public:
	Base(size_t tableSize= DEFAULT_TABLE_SIZE);
	Base(const Base& cM);
	Base(Base* cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	Base(Base&& cM) noexcept;
#endif
	virtual ~Base() CPPUTILS_OVERRIDE ;
	
	const Base& operator=(const Base& cM);
	const Base& ReplaceWithOther(Base* cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	const Base& operator=(Base&& cM) noexcept;
#endif
	
	iterator		AddEntryEvenIfExists(const KeyType& key, const DataType& data);
    iterator		AddEntryIfNotExist(const KeyType& key, const DataType& data);
	iterator		AddOrReplaceEntry(const KeyType& key, const DataType& data);
	iterator		AddEntryWithKnownHash(const KeyType& key,const DataType& a_data, size_t a_hashVal);
	iterator		FindEntryM(const KeyType& key,size_t* corespondingHash=CPPUTILS_NULL,
							   typename FuncF<KeyType,DataType>::Find a_fnc=&FuncF<KeyType,DataType>::DefaultFind, void*clbkData=CPPUTILS_NULL)const;
	
	DataType&		operator[](const KeyType& a_key);
	
	iterator		begin();
	iterator		end();
	const_iterator	begin()const;
	const_iterator	end()const;
	
public:	
	class iterator{
	public:
		iterator();
		iterator( __p::__i::HashItem<KeyType,DataType>* a_pItem);
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		__p::__i::HashItem<KeyType,DataType>* operator->()const;
		operator __p::__i::HashItem<KeyType,DataType>*()const;
		
	private:
		friend class Base;
		__p::__i::HashItem<KeyType,DataType>* m_pItem;
	}static const s_endIter;
	
	class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const_iterator(const __p::__i::HashItem<KeyType,DataType>* a_pItem);
		const_iterator& operator++();
		const_iterator  operator++(int);
		const_iterator& operator--();
		const_iterator  operator--(int);
		const __p::__i::HashItem<KeyType,DataType>* operator->()const;
		operator const __p::__i::HashItem<KeyType,DataType>* ()const;
		
	private:
		friend class Base;
		__p::__i::HashItem<KeyType,DataType>* m_pItem;
	}static const s_endConstIter;
};


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

//template <typename KeyType>
//class Base<KeyType,void>;

template <typename KeyType,typename Hash>
class Base<KeyType,void,Hash> : public BaseBase< KeyType,__p::__i::HashItem<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash  >
{
public:
	class  iterator;
	class  const_iterator;
	
public:
	Base(size_t tableSize= DEFAULT_TABLE_SIZE);
	Base(const Base& cM);
	Base(Base* cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	Base(Base&& cM) noexcept;
#endif
	virtual ~Base() CPPUTILS_OVERRIDE ;
	
	const Base& operator=(const Base& cM);
	const Base& ReplaceWithOther(Base* cM) noexcept;
#ifdef CPPUTILS_CPP_11_DEFINED
	const Base& operator=(Base&& cM) noexcept;
#endif
	
	iterator		AddEntryEvenIfExists(const KeyType& key);
    iterator		AddEntryIfNotExist(const KeyType& key);
	iterator		AddEntryWithKnownHash(const KeyType& key, size_t a_hashVal);
	
	iterator		begin();
	iterator		end();
	const_iterator	begin()const;
	const_iterator	end()const;
	
public:	
	class iterator{
	public:
		iterator();
		iterator( __p::__i::HashItem<KeyType,void>* a_pItem);
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		__p::__i::HashItem<KeyType,void>* operator->()const;
		operator __p::__i::HashItem<KeyType,void>*()const;
		
	private:
		friend class Base;
		__p::__i::HashItem<KeyType,void>* m_pItem;
	}static const s_endIter;
	
	class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const_iterator(const __p::__i::HashItem<KeyType,void>* a_pItem);
		const_iterator& operator++();
		const_iterator  operator++(int);
		const_iterator& operator--();
		const_iterator  operator--(int);
		const __p::__i::HashItem<KeyType,void>* operator->()const;
		operator const __p::__i::HashItem<KeyType,void>* ()const;
		
	private:
		friend class Base;
		__p::__i::HashItem<KeyType,void>* m_pItem;
	}static const s_endConstIter;
};



#ifdef CPPUTILS_CPP_11_DEFINED
//#if 0

// template <typename KeyType,typename DataType,typename Hash=FHash<KeyType>>
template <typename KeyType, typename Hash=FHash<KeyType> >
using Set = Base<KeyType,void, Hash>;


template <typename DataType,typename Hash=FHashVoidPtr>
using VoidPtrHash = Base<VoidPtrKey,DataType,Hash>;
template <typename Hash=FHashVoidPtr>
using VoidPtrSetBase = Set<VoidPtrKey,Hash>;
using VoidPtrSet = VoidPtrSetBase<FHashVoidPtr>;


template <typename CharType,typename DataType,typename Hash=FHashStr<CharType> >
using StrHash = Base< ::std::basic_string<CharType>,DataType,Hash >;
template <typename CharType, typename Hash=FHashStr<CharType> >
using StrSet = Set< ::std::basic_string<CharType>,Hash>;


template <typename IntType,typename DataType,typename Hash=FHashInt<IntType> >
using IntHash = Base< IntType,DataType,Hash >;
template <typename IntType, typename Hash=FHashInt<IntType> >
using IntSet = Set< IntType,Hash>;


#else


template <typename KeyType, typename Hash=FHash<KeyType> >
class Set : public Base<KeyType,void,Hash>{
public:
	Set(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Base<KeyType,void,Hash>(a_tableSize){}
	Set(const Set& a_cM) : Base<KeyType,void,Hash>(a_cM){}
	Set(Set* a_cM) noexcept : Base<KeyType,void,Hash>(a_cM){}
	virtual ~Set() CPPUTILS_OVERRIDE {}
	
	const Set& operator=(const Set& a_cM) { Base<KeyType,void,Hash>::operator=(a_cM); return *this; }
	const Set& ReplaceWithOther(Set* a_cM) noexcept { Base<KeyType,void,Hash>::ReplaceWithOther(a_cM); return *this; }
};


template <typename DataType,typename Hash=FHashVoidPtr>
class VoidPtrHash : public Base<VoidPtrKey,DataType,Hash> {
public:
	VoidPtrHash(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Base<VoidPtrKey,DataType,Hash>(a_tableSize){}
	VoidPtrHash(const VoidPtrHash& a_cM) : Base<VoidPtrKey,DataType,Hash>(a_cM){}
	VoidPtrHash(VoidPtrHash* a_cM) noexcept : Base<VoidPtrKey,DataType,Hash>(&a_cM){}
	virtual ~VoidPtrHash() CPPUTILS_OVERRIDE {}
	
	const VoidPtrHash& operator=(const VoidPtrHash& a_cM) { return Base<VoidPtrKey,DataType,Hash>::operator=(a_cM); }
	const VoidPtrHash& ReplaceWithOther(VoidPtrHash* a_cM) noexcept { return Base<VoidPtrKey,DataType,Hash>::ReplaceWithOther(a_cM); }
};

template <typename Hash=FHashVoidPtr>
class VoidPtrSetBase : public Set<VoidPtrKey,Hash> {	
public:
	VoidPtrSetBase(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Set<VoidPtrKey,Hash>(a_tableSize){}
	VoidPtrSetBase(const VoidPtrSetBase& a_cM) : Set<VoidPtrKey,Hash>(a_cM){}
	VoidPtrSetBase(VoidPtrSetBase* a_cM) noexcept : Set<VoidPtrKey,Hash>(a_cM){}
	virtual ~VoidPtrSetBase() CPPUTILS_OVERRIDE {}
	
	const VoidPtrSetBase& operator=(const VoidPtrSetBase& a_cM) { Set<VoidPtrKey,Hash>::operator=(a_cM); return *this; }
	const VoidPtrSetBase& ReplaceWithOther(VoidPtrSetBase* a_cM) noexcept { Set<VoidPtrKey,Hash>::ReplaceWithOther(a_cM);return *this; }
};

class VoidPtrSet : public VoidPtrSetBase<FHashVoidPtr> {	
public:
	VoidPtrSet(size_t a_tableSize= DEFAULT_TABLE_SIZE) : VoidPtrSetBase<FHashVoidPtr>(a_tableSize){}
	VoidPtrSet(const VoidPtrSet& a_cM) : VoidPtrSetBase<FHashVoidPtr>(a_cM){}
	VoidPtrSet(VoidPtrSet* a_cM) noexcept : VoidPtrSetBase<FHashVoidPtr>(a_cM){}
	virtual ~VoidPtrSet() CPPUTILS_OVERRIDE {}
	
	const VoidPtrSet& operator=(const VoidPtrSet& a_cM) { VoidPtrSetBase<FHashVoidPtr>::operator=(a_cM); return *this; }
	const VoidPtrSet& ReplaceWithOther(VoidPtrSet* a_cM) noexcept { VoidPtrSetBase<FHashVoidPtr>::ReplaceWithOther(a_cM);return *this; }
};



template <typename CharType,typename DataType,typename Hash=FHashStr<CharType> >
class StrHash : public Base< ::std::basic_string<CharType>,DataType,Hash> {
public:
	StrHash(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Base< ::std::basic_string<CharType>,DataType,Hash>(a_tableSize){}
	StrHash(const StrHash& a_cM) : Base< ::std::basic_string<CharType>,DataType,Hash>(a_cM){}
	StrHash(StrHash* a_cM) noexcept : Base< ::std::basic_string<CharType>,DataType,Hash>(&a_cM){}
	virtual ~StrHash() CPPUTILS_OVERRIDE {}
	
	StrHash& operator=(const StrHash& a_cM) { return Base< ::std::basic_string<CharType>,DataType,Hash>::operator=(a_cM); }
	StrHash& ReplaceWithOther(StrHash& a_cM) noexcept { return Base< ::std::basic_string<CharType>,DataType,Hash>::ReplaceWithOther(a_cM); }
};

template <typename CharType, typename Hash=FHashStr<CharType> >
class StrSet : public Set< ::std::basic_string<CharType>,Hash> {
public:
	StrSet(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Set< ::std::basic_string<CharType>,Hash>(a_tableSize){}
	StrSet(const StrSet& a_cM) : Set< ::std::basic_string<CharType>,Hash>(a_cM){}
	StrSet(StrSet* a_cM) noexcept : Set< ::std::basic_string<CharType>,Hash>(&a_cM){}
	virtual ~StrSet() CPPUTILS_OVERRIDE {}
	
	StrSet& operator=(const StrSet& a_cM) { return Set< ::std::basic_string<CharType>,Hash>::operator=(a_cM); }
	StrSet& ReplaceWithOther(StrSet& a_cM) noexcept { return Set< ::std::basic_string<CharType>,Hash>::ReplaceWithOther(a_cM); }
};


template <typename IntType,typename DataType,typename Hash=FHashInt<IntType> >
class IntHash : public Base< IntType,DataType,Hash> {
public:
	IntHash(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Base< IntType,DataType,Hash>(a_tableSize){}
	IntHash(const IntHash& a_cM) : Base< IntType,DataType,Hash>(a_cM){}
	IntHash(IntHash* a_cM) noexcept : Base< IntType,DataType,Hash>(&a_cM){}
	virtual ~IntHash() CPPUTILS_OVERRIDE {}
	
	IntHash& operator=(const IntHash& a_cM) { return Base< IntType,DataType,Hash>::operator=(a_cM); }
	IntHash& ReplaceWithOther(IntHash& a_cM) noexcept { return Base< IntType,DataType,Hash>::ReplaceWithOther(a_cM); }
};

template <typename IntType, typename Hash=FHashInt<IntType> >
class IntSet : public Set<IntType,Hash> {
public:
	IntSet(size_t a_tableSize= DEFAULT_TABLE_SIZE) : Set<IntType,Hash>(a_tableSize){}
	IntSet(const IntSet& a_cM) : Set<IntType,Hash>(a_cM){}
	IntSet(IntSet* a_cM) noexcept : Set<IntType,Hash>(&a_cM){}
	virtual ~IntSet() CPPUTILS_OVERRIDE {}
	
	IntSet& operator=(const IntSet& a_cM) { return Set<IntType,Hash>::operator=(a_cM); }
	IntSet& ReplaceWithOther(IntSet& a_cM) noexcept { return Set<IntType,Hash>::ReplaceWithOther(a_cM); }
};



#endif  // #ifdef CPPUTILS_CPP_11_DEFINED


}}  // namespace cpputils { namespace hashtbl {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP
#include "hashtbl.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP
