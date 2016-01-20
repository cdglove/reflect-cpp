// *****************************************************************************
// 
// reflect/reflect_type.hpp
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

#include "reflect/reflect.hpp"

namespace reflect {

// -----------------------------------------------------------------------------
// Reflect type. Called by visitors to issue a call to reflection.
template<typename T, typename Visitor>
void reflect_type(Visitor& visitor, version_t version)
{
	reflect(visitor, version, tag<T>());
}

// -----------------------------------------------------------------------------
// 
class default_visitor
{
public:

	template<typename Child, typename Parent>
	void member(char const*, Child Parent::*)
	{}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun, InsertFun)
	{}

	void primitive()
	{}
};

// -----------------------------------------------------------------------------
// 
template<typename T, typename Visitor>
class reflector
{
public:

	template<typename... Ps>
	void operator()(Ps&... p)
	{
		Visitor visit(p...);
		reflect_type<T>(visit, reflect::_first_ver);
	}
};

}

#endif // REFLECT_REFLECTTYPE_HPP_