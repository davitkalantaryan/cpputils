//
// repo:            cpputils
// file:			orderedcalls.hpp
// path:			include/cpputils/orderedcalls.hpp
// created on:		2024 Oct 29
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#pragma once

#ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_HPP
#define CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_HPP

#include <cpputils/export_symbols.h>
#include <functional>
#include <vector>
#include <stddef.h>


namespace cpputils { namespace orderedcalls{


template <typename CalleeType>
class OrderedCalls_p;
template <typename MutexType>
class Guard_p;


template <typename CalleeType>
class OrderedCalls
{
public:
    typedef ::std::function<void (CalleeType* CPPUTILS_ARG_NN)> TypeStart;
    typedef ::std::function<void (CalleeType* CPPUTILS_ARG_NN)> TypeStop;
    
    struct GenericCallee{
        CalleeType*     callee_p;
        TypeStart       starter;
        TypeStop        stopper;
    };
    
    class Item
    {
        friend class OrderedCalls;
    public:
        void lock();
        void unlock();
        OrderedCalls* const         m_parent_p;
        const size_t                m_index;
        const CalleeType* const     m_mutex_p;
    protected:
        ~Item();
        Item(OrderedCalls* a_parent_p, size_t a_index, const CalleeType* a_mutex_p);
        Item(const Item&)=delete;
        Item(Item&&)=delete;
        Item& operator=(const Item&)=delete;
        Item& operator=(Item&&)=delete;
    };
    
public:
    virtual ~OrderedCalls();
	OrderedCalls(const ::std::vector<GenericCallee>& a_callees);
    OrderedCalls(const OrderedCalls&) = delete;
    OrderedCalls& operator=(const OrderedCalls&) = delete;

    // I keep names lock/unlock name to demonstrate that the main use case is multiple mutexes
	void lock(size_t a_index);
	void unlock(size_t a_index);
    size_t size()const;
    Item* getSingleMutex(size_t a_index)const;

protected:
	OrderedCalls_p<CalleeType>* const   m_orderedCalls_p;    
};


template <typename MutexType>
class Guard
{
public:
    struct defer_lock_t { explicit defer_lock_t() = default; };
    struct symetric_unlock_t { explicit symetric_unlock_t() = default; };
    static constexpr defer_lock_t defer_lock {};
    static constexpr symetric_unlock_t symetric_unlock {};
public:
    ~Guard();    
    template<typename... Targs>
	Guard(MutexType* CPPUTILS_ARG_NN a_callees_p, Targs... a_args);
    Guard( const defer_lock_t& a_def, MutexType* CPPUTILS_ARG_NN a_callees_p);
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;

    template<typename... Targs>
    void lock(Targs... a_args);
    template<typename... Targs>
    void unlock(Targs... a_args);
    void unlock(const symetric_unlock_t&);

private:
    Guard_p<MutexType>* const  m_lockGuard_p;
};

}}  //  namespace cpputils { namespace orderedcalls{


#ifndef CPPUTILS_INCLUDE_CPPUTILS_IMPL_ORDEREDCALLS_IMPL_HPP
#include <cpputils/impl/cpputils_orderedcalls.impl.hpp>
#endif


#endif  //  #ifndef CPPUTILS_INCLUDE_CPPUTILS_ORDEREDCALLS_HPP
