// *****************************************************************************
// 
// test/test_user_types.hpp
//
// Common user types for reflect-cpp tests.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REVEAL_TEST_USERTYPES_HPP_
#define REVEAL_TEST_USERTYPES_HPP_

#include <vector>
#include "reveal/std/vector.hpp"
#include "reveal/primitives.hpp"
#include "test_primitive_types.hpp"

namespace ns
{
	struct Child1
	{
		int a_;
		float b_;
	};

	template<typename Visitor>
	decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<Child1>)
	{
		return v
			.member("a_", &Child1::a_)
			.member("b_", &Child1::b_)
		;
	}

	struct Child2
	{
		std::vector<double> c_;
		unsigned int d_;
	};

	template<typename Visitor>
	decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<Child2>)
	{
		return v
			.member("c_", &Child2::c_)
			.member("d_", &Child2::d_)
		;
	}

	struct Parent1
	{
		Child1 f_;
		Child2 s_;
	};

	template<typename Visitor>
	decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<Parent1>)
	{
		return v
			.member("f_", &Parent1::f_)
			.member("s_", &Parent1::s_)
		;
	}
}

// -----------------------------------------------------------------------------
//
struct compound_struct
{
	compound_struct()
		: p(make_primitives_values())
		, v(-1.f)
	{}

	primitives p;
	double v;
};

inline bool operator==(compound_struct const& a, compound_struct const& b)
{
	return a.p == b.p &&
		   a.v == b.v
	;
}

inline std::ostream& operator<<(std::ostream& out, compound_struct const& v)
{
	out << v.p << ", " << v.v;
	return out;
}

template<typename Visitor> constexpr inline
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<compound_struct>)
{
	return v
		.member("p", &compound_struct::p)
	 	.member("v", &compound_struct::v)
	 ;
}

// -----------------------------------------------------------------------------
//
struct pod
{
	int data;
};

template<typename Visitor> constexpr inline 
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<pod>)
{
	return v.pod();
}

#endif // REVEAL_TEST_USERTYPES_HPP_