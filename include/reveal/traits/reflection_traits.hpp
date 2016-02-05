// *****************************************************************************
// 
// reveal/traits/reflection_traits.hpp
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
//
template<typename T>
class reflection_traits
{
public:

	constexpr bool is_container() const
	{
		return reflect_type<T>(is_container_visitor(), _first_ver);
	}

	constexpr bool is_string() const
	{
		return reflect_type<T>(is_container_visitor(), _first_ver);
	}

	constexpr bool is_pod() const
	{
		return reflect_type<T>(is_pod_visitor(), _first_ver);
	}

	constexpr bool is_primitive() const
	{
		return reflect_type<T>(is_primitive_visitor(), _first_ver);
	}

private:

	struct false_visitor
	{
		template<typename Child, typename Parent>
		constexpr bool member(char const*, Child Parent::*) const
		{ return false; }

		template<typename SizeFun, typename InsertFun>
		constexpr bool container(SizeFun, InsertFun) const
		{ return false; }

		template<typename SizeFun, typename InsertFun>
		constexpr bool string(SizeFun, InsertFun) const
		{ return false; }

		constexpr bool pod() const
		{ return false; }

		constexpr bool primitive() const
		{ return false; }
	};

	struct is_container_visitor : false_visitor
	{
		constexpr bool container() const
		{
			return true;
		}
	};

	struct is_string_visitor : false_visitor
	{
		constexpr bool string() const
		{
			return true;
		}
	};

	struct is_pod_visitor : false_visitor
	{
		constexpr bool pod() const
		{
			return true;
		}
	};

	struct is_primitive_visitor : false_visitor
	{
		constexpr bool primitive() const
		{
			return true;
		}
	};
};

}

#endif // REVEAL_REFLECTIONTYPE_HPP_