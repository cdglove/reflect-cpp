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
#ifndef REFLECT_REFLECTTYPE_HPP_
#define REFLECT_REFLECTTYPE_HPP_

#include "reveal/reflect.hpp"

namespace reveal {

// -----------------------------------------------------------------------------
// Reflect type. Called by visitors to issue a call to reflection.
template<typename T, typename Visitor>
decltype(auto) reflect_type(Visitor& visitor, version_t version)
{
	return reflect(visitor, version, tag<T>());
}

template<typename T, typename Visitor>
decltype(auto) reflect_type(Visitor& visitor)
{
	return reflect(visitor, reveal::_first_ver, tag<T>());
}

// -----------------------------------------------------------------------------
// 
class default_visitor
{
public:

	template<typename Child, typename Parent>
	default_visitor& member(char const*, Child Parent::*)
	{ return *this; }

	template<typename SizeFun, typename InsertFun>
	default_visitor& container(SizeFun, InsertFun)
	{ return *this; }

	template<typename SizeFun, typename InsertFun>
	default_visitor& string(SizeFun s, InsertFun i)
	{ return container(s, i); }

	default_visitor& primitive()
	{ return *this; }
};

}

#endif // REFLECT_REFLECTTYPE_HPP_