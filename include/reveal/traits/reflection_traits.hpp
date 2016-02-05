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
		return reflect_type<T>(is_container_visitor(), _first_ver).result();
	}

	constexpr bool is_string() const
	{
		return reflect_type<T>(is_string_visitor(), _first_ver).result();
	}

	constexpr bool is_pod() const
	{
		return reflect_type<T>(is_pod_visitor(), _first_ver).result();
	}

	constexpr bool is_primitive() const
	{
		return reflect_type<T>(is_primitive_visitor(), _first_ver).result();
	}

private:

	struct false_type
	{
		constexpr bool result() const
		{
			return false;
		}
	};

	struct true_type
	{
		constexpr bool result() const
		{
			return true;
		}
	};

	struct false_visitor : false_type
	{
		template<typename Child, typename Parent>
		constexpr false_visitor member(char const*, Child Parent::*) const
		{ 
			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		constexpr false_type container(SizeFun, InsertFun) const
		{ 
			return false_type();
		}

		template<typename SizeFun, typename InsertFun>
		constexpr false_type string(SizeFun, InsertFun) const
		{ 
			return false_type();
		}

		constexpr false_type pod() const
		{ 
			return false_type();
		}

		constexpr false_type primitive() const
		{ 
			return false_type();
		}
	};

	struct is_container_visitor : false_visitor
	{
		constexpr true_type container() const
		{
			return true_type();
		}
	};

	struct is_string_visitor : false_visitor
	{
		constexpr true_type string() const
		{
			return true_type();
		}
	};

	struct is_pod_visitor : false_visitor
	{
		constexpr true_type pod() const
		{
			return true_type();
		}
	};

	struct is_primitive_visitor : false_visitor
	{
		constexpr true_type primitive() const
		{
			return true_type();
		}
	};
};

}

#endif // REVEAL_REFLECTIONTYPE_HPP_