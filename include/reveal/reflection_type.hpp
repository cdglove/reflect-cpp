// *****************************************************************************
// 
// reveal/reflection_type.hpp
//
// Detects what serialization function a type is going to call.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_REFLECTIONTYPE_HPP_
#define REVEAL_REFLECTIONTYPE_HPP_

#include "reveal/reflect_type.hpp"

namespace reveal {

// -----------------------------------------------------------------------------

class reflection_type : default_visitor<reflection_type>
{
public:

	reflection_type()
		: flags_(F_NONE)
	{}

	template<typename Child, typename Parent>
	reflection_type& member(char const*, Child Parent::*)
	{
		flags_ |= F_MEMBER;
		return *this;
	}

	template<typename SizeFun, typename InsertFun>
	reflection_type& container(SizeFun, InsertFun)
	{
		flags_ |= F_CONTAINER;
		return *this;
	}

	template<typename SizeFun, typename InsertFun>
	reflection_type& string(SizeFun s, InsertFun i)
	{ 
		flags_ |= F_STRING;
		return *this;
	}

	reflection_type& primitive()
	{
		flags_ |= F_POD;
		return *this;
	}

	bool is_member()
	{
		return flags_ == F_MEMBER;
	}

	bool is_container()
	{
		return flags_ == F_CONTAINER;
	}

	bool isstring()
	{
		return flags_ == F_STRING;
	}

	bool is_pod()
	{
		return flags_ == F_POD;
	}

private:

	enum type_flag
	{
		F_NONE			= 0,
		F_MEMBER		= 1,
		F_CONTAINER		= 1 << 1,
		F_STRING		= 1 << 2,
		F_POD			= 1 << 3,
	};

	unsigned int flags_;
};

}

#endif // REVEAL_REFLECTIONTYPE_HPP_