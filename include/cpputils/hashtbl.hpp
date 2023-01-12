//
// file:			hashtbl.hpp
// path:			include/cpputils/hashtbl.hpp
// created on:		2017 Jul 21
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP


#include <cpputils/export_symbols.h>
#include <cpputils/functional.hpp>
#include <stdint.h>
#include <stddef.h>
#include <string>
#include "hashtbl.def.hpp"


namespace cpputils { namespace hashtbl {


template <typename KeyType,typename HashItemType, typename HashItemPrivateType, typename HashType, size_t templateDefaultSize>
class BaseBase
{
public:
    typedef __p::__i::HashItem<HashItemType>    HashItemTypeAdv;
public:
	HashItemTypeAdv*	FindEntry(const KeyType& key,size_t* corespondingHash=CINTERNAL_NULL)const;
	HashItemTypeAdv*	FindEntryWithKnownHash(const KeyType& key,size_t knownHash)const;
    bool		RemoveEntry01(const KeyType& key);
	void		RemoveEntry(const HashItemTypeAdv* a_data);
	size_t		size()const;
	void		clear() CINTERNAL_NOEXCEPT;
	void		pop_back() ;
	void		pop_front() ;
	
protected:	
	BaseBase(size_t tableSize= templateDefaultSize);
	BaseBase(const BaseBase& cM);
	BaseBase(BaseBase* mM) CINTERNAL_NOEXCEPT;
#ifdef CINTERNAL_CPP_11_DEFINED
	BaseBase(BaseBase&& cM) CINTERNAL_NOEXCEPT;
#endif
	virtual ~BaseBase();

	const BaseBase& operator=(const BaseBase& cM);
	const BaseBase& ReplaceWithOther(BaseBase* cM) CINTERNAL_NOEXCEPT;
#ifdef CINTERNAL_CPP_11_DEFINED
	const BaseBase& operator=(BaseBase&& cM) CINTERNAL_NOEXCEPT;
#endif
	
	HashItemTypeAdv*		AddEntryEvenIfExistsRaw(const HashItemType& a_item);
    HashItemTypeAdv*		AddEntryIfNotExistRaw(const HashItemType& a_item);
	HashItemTypeAdv*		AddEntryWithKnownHashRaw(const HashItemType& a_item, size_t a_hash);
    HashItemTypeAdv*		AddEntryWithKnownHashRaw(const HashItemTypeAdv& a_item);
	
	HashItemTypeAdv*		firstItem()const;

private:
	HashItemTypeAdv**			m_pTable;
	/*const*/ size_t	m_unRoundedTableSizeMin1;
	HashItemTypeAdv			*m_pFirstItem,*m_pLastItem;
	size_t				m_unSize;
};

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

template <typename KeyType,typename DataType,typename Hash=FHash<KeyType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE>
class Base : public BaseBase< KeyType,__p::__i::HashItemBase<KeyType,DataType>,__p::__i::HashItemFull<KeyType,DataType>,Hash,templateDefaultSize  >
{
public:
    typedef __p::__i::HashItem<__p::__i::HashItemBase<KeyType,DataType> >    HashItemTypeAdv;
public:
	class  iterator;
	class  const_iterator;
	
public:
	Base(size_t tableSize= templateDefaultSize);
	Base(const Base& cM);
	Base(Base* cM) CINTERNAL_NOEXCEPT;
#ifdef CINTERNAL_CPP_11_DEFINED
	Base(Base&& cM) CINTERNAL_NOEXCEPT;
#endif
	virtual ~Base() CINTERNAL_OVERRIDE ;
	
	const Base& operator=(const Base& cM);
	const Base& ReplaceWithOther(Base* cM) CINTERNAL_NOEXCEPT;
#ifdef CINTERNAL_CPP_11_DEFINED
	const Base& operator=(Base&& cM) CINTERNAL_NOEXCEPT;

    iterator		AddEntryIfNotExistMv(const KeyType& key, DataType&& data);
    iterator		AddOrReplaceEntryMv(const KeyType& key, DataType&& data);
    iterator		AddEntryWithKnownHashMv(const KeyType& key,DataType&& data, size_t a_hashVal);
#endif
	
    bool            RemoveEntry02(const KeyType& key,DataType* a_pData);
	iterator		AddEntryEvenIfExists(const KeyType& key, const DataType& data);
    iterator		AddEntryIfNotExist(const KeyType& key, const DataType& data);
	iterator		AddOrReplaceEntry(const KeyType& key, const DataType& data);
	iterator		AddEntryWithKnownHash(const KeyType& key,const DataType& a_data, size_t a_hashVal);
	iterator		FindEntryM(const KeyType& key,size_t* corespondingHash=CINTERNAL_NULL,
							   typename FuncF<KeyType,DataType>::Find a_fnc=&FuncF<KeyType,DataType>::DefaultFind, void*clbkData=CINTERNAL_NULL)const;
	
	DataType&		operator[](const KeyType& a_key);
	
	iterator		begin();
	iterator		end();
	const_iterator	begin()const;
	const_iterator	end()const;
	
public:	
	class iterator{
	public:
		iterator();
		iterator( HashItemTypeAdv* a_pItem);
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		HashItemTypeAdv* operator->()const;
		operator HashItemTypeAdv*()const;
        iterator next()const;
        iterator previous()const;
		
	private:
		friend class Base;
		HashItemTypeAdv* m_pItem;
	}static const s_endIter;
	
	class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const_iterator(const HashItemTypeAdv* a_pItem);
		const_iterator& operator++();
		const_iterator  operator++(int);
		const_iterator& operator--();
		const_iterator  operator--(int);
		const HashItemTypeAdv* operator->()const;
		operator const HashItemTypeAdv* ()const;
        const_iterator next()const;
        const_iterator previous()const;
		
	private:
		friend class Base;
		HashItemTypeAdv* m_pItem;
	}static const s_endConstIter;
};


/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

//template <typename KeyType>
//class Base<KeyType,void>;

template <typename KeyType,typename Hash,size_t templateDefaultSize>
class Base<KeyType,void,Hash,templateDefaultSize> : public BaseBase< KeyType,__p::__i::HashItemBase<KeyType,void>,__p::__i::HashItemFull<KeyType,void>,Hash, templateDefaultSize  >
{
public:
    typedef __p::__i::HashItem<__p::__i::HashItemBase<KeyType,void> >    HashItemTypeAdv;
public:
	class  iterator;
	class  const_iterator;
	
public:
	Base(size_t tableSize= templateDefaultSize);
	Base(const Base& cM);
	Base(Base* cM) CINTERNAL_NOEXCEPT;
#ifdef CINTERNAL_CPP_11_DEFINED
	Base(Base&& cM) CINTERNAL_NOEXCEPT;
#endif
	virtual ~Base() CINTERNAL_OVERRIDE ;
	
	const Base& operator=(const Base& cM);
	const Base& ReplaceWithOther(Base* cM) CINTERNAL_NOEXCEPT;
#ifdef CINTERNAL_CPP_11_DEFINED
	const Base& operator=(Base&& cM) CINTERNAL_NOEXCEPT;
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
		iterator( HashItemTypeAdv* a_pItem);
		iterator& operator++();
		iterator  operator++(int);
		iterator& operator--();
		iterator  operator--(int);
		HashItemTypeAdv* operator->()const;
		operator HashItemTypeAdv*()const;
        iterator next()const;
        iterator previous()const;
		
	private:
		friend class Base;
		HashItemTypeAdv* m_pItem;
	}static const s_endIter;
	
	class const_iterator{
	public:
		const_iterator();
		const_iterator(const iterator& iter);
		const_iterator(const HashItemTypeAdv* a_pItem);
		const_iterator& operator++();
		const_iterator  operator++(int);
		const_iterator& operator--();
		const_iterator  operator--(int);
		const HashItemTypeAdv* operator->()const;
		operator const HashItemTypeAdv* ()const;
        const_iterator next()const;
        const_iterator previous()const;
		
	private:
		friend class Base;
		HashItemTypeAdv* m_pItem;
	}static const s_endConstIter;
};



#ifdef CINTERNAL_CPP_11_DEFINED
//#if 0

// template <typename KeyType,typename DataType,typename Hash=FHash<KeyType>>
template <typename KeyType, typename Hash=FHash<KeyType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
using Set = Base<KeyType,void, Hash,templateDefaultSize>;


template <typename DataType,typename Hash=FHashVoidPtr,size_t templateDefaultSize=DEFAULT_TABLE_SIZE>
using VoidPtrHash = Base<VoidPtrKey,DataType,Hash,templateDefaultSize>;
template <typename Hash=FHashVoidPtr, size_t templateDefaultSize=DEFAULT_TABLE_SIZE>
using VoidPtrSetBase = Set<VoidPtrKey,Hash,templateDefaultSize>;
template <size_t templateDefaultSize>
using VoidPtrSet = VoidPtrSetBase<FHashVoidPtr,templateDefaultSize>;


template <typename CharType,typename DataType,typename Hash=FHashStr<CharType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
using StrHash = Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize >;
template <typename CharType, typename Hash=FHashStr<CharType>, size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
using StrSet = Set< ::std::basic_string<CharType>,Hash,templateDefaultSize>;


template <typename IntType,typename DataType,typename Hash=FHashInt<IntType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
using IntHash = Base< IntType,DataType,Hash,templateDefaultSize >;
template <typename IntType, size_t templateDefaultSize=DEFAULT_TABLE_SIZE, typename Hash=FHashInt<IntType> >
using IntSet = Set< IntType,Hash,templateDefaultSize>;


#else


template <typename KeyType, typename Hash=FHash<KeyType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
class Set : public Base<KeyType,void,Hash,templateDefaultSize>{
public:
	Set(size_t a_tableSize= templateDefaultSize) : Base<KeyType,void,Hash,templateDefaultSize>(a_tableSize){}
	Set(const Set& a_cM) : Base<KeyType,void,Hash,templateDefaultSize>(a_cM){}
	Set(Set* a_cM) CINTERNAL_NOEXCEPT : Base<KeyType,void,Hash,templateDefaultSize>(a_cM){}
	virtual ~Set() CINTERNAL_OVERRIDE {}
	
	const Set& operator=(const Set& a_cM) { Base<KeyType,void,Hash,templateDefaultSize>::operator=(a_cM); return *this; }
	const Set& ReplaceWithOther(Set* a_cM) CINTERNAL_NOEXCEPT { Base<KeyType,void,Hash,templateDefaultSize>::ReplaceWithOther(a_cM); return *this; }
};


template <typename DataType,typename Hash=FHashVoidPtr,size_t templateDefaultSize=DEFAULT_TABLE_SIZE>
class VoidPtrHash : public Base<VoidPtrKey,DataType,Hash,templateDefaultSize> {
public:
	VoidPtrHash(size_t a_tableSize= templateDefaultSize) : Base<VoidPtrKey,DataType,Hash,templateDefaultSize>(a_tableSize){}
	VoidPtrHash(const VoidPtrHash& a_cM) : Base<VoidPtrKey,DataType,Hash,templateDefaultSize>(a_cM){}
	VoidPtrHash(VoidPtrHash* a_cM) CINTERNAL_NOEXCEPT : Base<VoidPtrKey,DataType,Hash,templateDefaultSize>(&a_cM){}
	virtual ~VoidPtrHash() CINTERNAL_OVERRIDE {}
	
	const VoidPtrHash& operator=(const VoidPtrHash& a_cM) { return Base<VoidPtrKey,DataType,Hash,templateDefaultSize>::operator=(a_cM); }
	const VoidPtrHash& ReplaceWithOther(VoidPtrHash* a_cM) CINTERNAL_NOEXCEPT { return Base<VoidPtrKey,DataType,Hash,templateDefaultSize>::ReplaceWithOther(a_cM); }
};

template <typename Hash=FHashVoidPtr,size_t templateDefaultSize=DEFAULT_TABLE_SIZE>
class VoidPtrSetBase : public Set<VoidPtrKey,Hash,templateDefaultSize> {	
public:
	VoidPtrSetBase(size_t a_tableSize= templateDefaultSize) : Set<VoidPtrKey,Hash,templateDefaultSize>(a_tableSize){}
	VoidPtrSetBase(const VoidPtrSetBase& a_cM) : Set<VoidPtrKey,Hash,templateDefaultSize>(a_cM){}
	VoidPtrSetBase(VoidPtrSetBase* a_cM) CINTERNAL_NOEXCEPT : Set<VoidPtrKey,Hash,templateDefaultSize>(a_cM){}
	virtual ~VoidPtrSetBase() CINTERNAL_OVERRIDE {}
	
	const VoidPtrSetBase& operator=(const VoidPtrSetBase& a_cM) { Set<VoidPtrKey,Hash,templateDefaultSize>::operator=(a_cM); return *this; }
	const VoidPtrSetBase& ReplaceWithOther(VoidPtrSetBase* a_cM) CINTERNAL_NOEXCEPT { Set<VoidPtrKey,Hash,templateDefaultSize>::ReplaceWithOther(a_cM);return *this; }
};

template <size_t templateDefaultSize=DEFAULT_TABLE_SIZE>
class VoidPtrSet : public VoidPtrSetBase<FHashVoidPtr,templateDefaultSize> {	
public:
	VoidPtrSet(size_t a_tableSize= templateDefaultSize) : VoidPtrSetBase<FHashVoidPtr,templateDefaultSize>(a_tableSize){}
	VoidPtrSet(const VoidPtrSet& a_cM) : VoidPtrSetBase<FHashVoidPtr,templateDefaultSize>(a_cM){}
	VoidPtrSet(VoidPtrSet* a_cM) CINTERNAL_NOEXCEPT : VoidPtrSetBase<FHashVoidPtr,templateDefaultSize>(a_cM){}
	virtual ~VoidPtrSet() CINTERNAL_OVERRIDE {}
	
	const VoidPtrSet& operator=(const VoidPtrSet& a_cM) { VoidPtrSetBase<FHashVoidPtr,templateDefaultSize>::operator=(a_cM); return *this; }
	const VoidPtrSet& ReplaceWithOther(VoidPtrSet* a_cM) CINTERNAL_NOEXCEPT { VoidPtrSetBase<FHashVoidPtr,templateDefaultSize>::ReplaceWithOther(a_cM);return *this; }
};



template <typename CharType,typename DataType,typename Hash=FHashStr<CharType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
class StrHash : public Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize> {
public:
	StrHash(size_t a_tableSize= templateDefaultSize) : Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize>(a_tableSize){}
	StrHash(const StrHash& a_cM) : Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize>(a_cM){}
	StrHash(StrHash* a_cM) CINTERNAL_NOEXCEPT : Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize>(&a_cM){}
	virtual ~StrHash() CINTERNAL_OVERRIDE {}
	
	StrHash& operator=(const StrHash& a_cM) { return Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize>::operator=(a_cM); }
	StrHash& ReplaceWithOther(StrHash& a_cM) CINTERNAL_NOEXCEPT { return Base< ::std::basic_string<CharType>,DataType,Hash,templateDefaultSize>::ReplaceWithOther(a_cM); }
};

template <typename CharType, typename Hash=FHashStr<CharType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
class StrSet : public Set< ::std::basic_string<CharType>,Hash,templateDefaultSize> {
public:
	StrSet(size_t a_tableSize= templateDefaultSize) : Set< ::std::basic_string<CharType>,Hash,templateDefaultSize>(a_tableSize){}
	StrSet(const StrSet& a_cM) : Set< ::std::basic_string<CharType>,Hash,templateDefaultSize>(a_cM){}
	StrSet(StrSet* a_cM) CINTERNAL_NOEXCEPT : Set< ::std::basic_string<CharType>,Hash,templateDefaultSize>(&a_cM){}
	virtual ~StrSet() CINTERNAL_OVERRIDE {}
	
	StrSet& operator=(const StrSet& a_cM) { return Set< ::std::basic_string<CharType>,Hash,templateDefaultSize>::operator=(a_cM); }
	StrSet& ReplaceWithOther(StrSet& a_cM) CINTERNAL_NOEXCEPT { return Set< ::std::basic_string<CharType>,Hash,templateDefaultSize>::ReplaceWithOther(a_cM); }
};


template <typename IntType,typename DataType,typename Hash=FHashInt<IntType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
class IntHash : public Base< IntType,DataType,Hash,templateDefaultSize> {
public:
	IntHash(size_t a_tableSize= templateDefaultSize) : Base< IntType,DataType,Hash,templateDefaultSize>(a_tableSize){}
	IntHash(const IntHash& a_cM) : Base< IntType,DataType,Hash,templateDefaultSize>(a_cM){}
	IntHash(IntHash* a_cM) CINTERNAL_NOEXCEPT : Base< IntType,DataType,Hash,templateDefaultSize>(&a_cM){}
	virtual ~IntHash() CINTERNAL_OVERRIDE {}
	
	IntHash& operator=(const IntHash& a_cM) { return Base< IntType,DataType,Hash,templateDefaultSize>::operator=(a_cM); }
	IntHash& ReplaceWithOther(IntHash& a_cM) CINTERNAL_NOEXCEPT { return Base< IntType,DataType,Hash,templateDefaultSize>::ReplaceWithOther(a_cM); }
};

template <typename IntType, typename Hash=FHashInt<IntType>,size_t templateDefaultSize=DEFAULT_TABLE_SIZE >
class IntSet : public Set<IntType,Hash,templateDefaultSize> {
public:
	IntSet(size_t a_tableSize= templateDefaultSize) : Set<IntType,Hash,templateDefaultSize>(a_tableSize){}
	IntSet(const IntSet& a_cM) : Set<IntType,Hash,templateDefaultSize>(a_cM){}
	IntSet(IntSet* a_cM) CINTERNAL_NOEXCEPT : Set<IntType,Hash,templateDefaultSize>(&a_cM){}
	virtual ~IntSet() CINTERNAL_OVERRIDE {}
	
	IntSet& operator=(const IntSet& a_cM) { return Set<IntType,Hash,templateDefaultSize>::operator=(a_cM); }
	IntSet& ReplaceWithOther(IntSet& a_cM) CINTERNAL_NOEXCEPT { return Set<IntType,Hash,templateDefaultSize>::ReplaceWithOther(a_cM); }
};



#endif  // #ifdef CINTERNAL_CPP_11_DEFINED


}}  // namespace cpputils { namespace hashtbl {


#ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_IMPL_HPP
#include "hashtbl.impl.hpp"
#endif



#endif  // #ifndef CPPUTILS_INCLUDE_CPPUTILS_HASHTBL_HPP
