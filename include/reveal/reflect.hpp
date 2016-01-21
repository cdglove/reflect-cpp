// *****************************************************************************
// 
// reveal/reflect.hpp
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

#include "reveal/version.hpp"
#include "reveal/tag.hpp"

// -----------------------------------------------------------------------------
// 
namespace reveal {

template<typename T>
struct make_lazy { static const bool value = false; };

// -----------------------------------------------------------------------------
// If you're getting a compiler error here, it is likely because the reflect
// function for type T is missing. Make sure it's implemented and correctly 
// included.
template<typename Visitor, typename T>
void reflect(Visitor& v, version_t, tag<T>)
{
	// cglovert-todo: Consider that instead of static assert, we could
	// call T::reflect(v), which would allow users to specify their reflect
	// functions as members if they wanted.
	static_assert(make_lazy<T>::value, "Failed to find 'reflect' function for type T");
}

}

#endif // REFLECT_REFLECT_HPP_