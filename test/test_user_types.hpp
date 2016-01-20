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

#include <vector>
#include "reflect/std/vector.hpp"
#include "reflect/primitives.hpp"

namespace ns
{
	struct Child1
	{
		int a_;
		float b_;
	};

	template<typename Visitor>
	void reflect(Visitor& v, reflect::version_t, reflect::tag<Child1>)
	{
		v.member("a_", &Child1::a_);
		v.member("b_", &Child1::b_);
	}

	struct Child2
	{
		std::vector<double> c_;
		unsigned int d_;
	};

	template<typename Visitor>
	void reflect(Visitor& v, reflect::version_t, reflect::tag<Child2>)
	{
		v.member("c_", &Child2::c_);
		v.member("d_", &Child2::d_);
	}

	struct Parent1
	{
		Child1 f_;
		Child2 s_;
	};

	template<typename Visitor>
	void reflect(Visitor& v, reflect::version_t, reflect::tag<Parent1>)
	{
		v.member("f_", &Parent1::f_);
		v.member("s_", &Parent1::s_);
	}
}