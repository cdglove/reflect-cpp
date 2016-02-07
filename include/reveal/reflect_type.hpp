// *****************************************************************************
// 
// reveal/reflect_type.hpp
//
// Basic reflection framework for constructing parsers, generators and
// serializers from reflected type information.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_REFLECTTYPE_HPP_
#define REVEAL_REFLECTTYPE_HPP_

#include "reveal/reflect.hpp"

namespace reveal {

// -----------------------------------------------------------------------------
// Reflect type. Called by visitors to issue a call to reflection.
template<typename T, typename Visitor>
constexpr decltype(auto) reflect_type(Visitor& visitor, version_t version)
{
	return reflect(visitor, version, tag<std::decay_t<T>>());
}

template<typename T, typename Visitor>
constexpr decltype(auto) reflect_type(Visitor& visitor)
{
	return reflect(visitor, reveal::_first_ver, tag<std::decay_t<T>>());
}

// -----------------------------------------------------------------------------
// 
template<typename Derived>
class default_visitor
{
public:

	template<typename Child, typename Parent>
	Derived& member(char const*, Child Parent::*)
	{ return *static_cast<Derived*>(this); }

	template<typename SizeFun, typename InsertFun>
	Derived& container(SizeFun, InsertFun)
	{ return *static_cast<Derived*>(this); }

	template<typename SizeFun, typename InsertFun>
	Derived& string(SizeFun s, InsertFun i)
	{ return static_cast<Derived*>(this)->container(s, i); }

	Derived& pod()
	{ return *static_cast<Derived*>(this); }

	Derived& primitive()
	{ return *static_cast<Derived*>(this); }
};

}

#endif // REVEAL_REFLECTTYPE_HPP_