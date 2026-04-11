//
// file:			type_traits.hpp
// path:			include/cpputils/type_traits.hpp
// created on:		2026 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#pragma once

#include <cinternal/disable_compiler_warnings.h>
#include <type_traits>
#include <bitset>
#include <functional>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace types{


typedef ::std::integral_constant<bool, false>   false_type;
typedef ::std::integral_constant<bool, true>    true_type;
template< typename... >
using void_t = void;

template<typename T, typename = void>
struct has_std_hash : types::false_type {};

template<typename T>
struct has_std_hash<
    T,
    types::void_t<
        decltype(::std::declval<::std::hash<T> >()(::std::declval<const T&>()))
    >
> : types::true_type {
};


template<typename T, typename = void>
struct has_std_equal_to : types::false_type {};

template<typename T>
struct has_std_equal_to<
    T,
    types::void_t<
        decltype(::std::declval<::std::equal_to<T> >()(::std::declval<const T&>()))
    >
> : types::true_type {
};


template<typename T, typename = void>
struct has_operator_equal : types::false_type {};

template<typename T>
struct has_operator_equal<
    T,
    types::void_t<
        decltype(::std::declval<const T&>() == ::std::declval<const T&>())
    >
> : types::true_type {
};


}}  //  namespace cpputils { namespace types{
