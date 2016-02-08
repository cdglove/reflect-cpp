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
#include "test_primitive_types.hpp"

// -----------------------------------------------------------------------------
//
namespace user {

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

}

#endif // REVEAL_TEST_USERTYPES_HPP_