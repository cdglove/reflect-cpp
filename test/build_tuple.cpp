// *****************************************************************************
// 
// reveal/test/build_tuple.cpp
//
// Tests to see if we can build a tuple from the reflected data.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#include <iostream>

#include "reveal/reflect_type.hpp"
#include "reveal/serialize/build_tuple.hpp"
#include "test_user_types.hpp"

struct s1
{
	int i;
	float f;
};

template<typename Visitor>
auto reflect(Visitor& v, reveal::version_t, reveal::tag<s1>)
{
	return v
		.member("i", &s1::i)
		.member("f", &s1::f)
	;
}

int main()
{
	s1 s;
	s.i = 1;
	s.f = 10.f;

	std::tuple<> t;
	reveal::serialize::build_tuple<s1, std::tuple<>> builder(s, t);
	auto tup = reveal::reflect_type<s1>(builder, reveal::_first_ver);
	return 0;
}