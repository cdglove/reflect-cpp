// *****************************************************************************
// 
// reflect/reflect.hpp
//
// Everything necessary to implement a refelct function for your type.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REFLECT_REFLECT_HPP_
#define REFLECT_REFLECT_HPP_

#include "reflect/version.hpp"
#include "reflect/tag.hpp"

// -----------------------------------------------------------------------------
// 
namespace reflect {

template<typename T>
struct make_lazy { static const bool value = false; };

// -----------------------------------------------------------------------------
// If you're getting a compiler error here, it is likely because the reflect
// function for type T is missing. Make sure it's implemented and correctly 
// included.
template<typename Visitor, typename T>
void reflect(Visitor& v, version_t, tag<T>)
{
	static_assert(make_lazy<T>::value, "Failed to find 'reflect' function for type T");
}

}

#endif // REFLECT_REFLECT_HPP_