// *****************************************************************************
// 
// test/test_primitive_types.hpp
//
// Common primitive type for reflect-cpp tests.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REVEAL_TEST_PRIMITIVETYPES_HPP_
#define REVEAL_TEST_PRIMITIVETYPES_HPP_

#include <reveal/primitives.hpp>

// -----------------------------------------------------------------------------
//
struct primitives
{
	char char_;
	unsigned uchar_;
	signed char schar_;
	short short_;
	unsigned short ushort_;
	int int_;
	unsigned int uint_;
	long long_;
	unsigned long ulong_;
	long long llong_;
	unsigned long long ullong_;	
	float float_;
	double double_;
};

template<typename Visitor> constexpr inline
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<primitives>)
{
	return v
		.member("char_",	&primitives::char_)
		.member("uchar_",	&primitives::uchar_)
		.member("schar_",	&primitives::schar_)
		.member("short_",	&primitives::short_)
		.member("ushort_",	&primitives::ushort_)		
		.member("int_",		&primitives::int_)
		.member("uint_",	&primitives::uint_)
		.member("long_",	&primitives::long_)
		.member("ulong_",	&primitives::ulong_)
		.member("llong_",	&primitives::llong_)
		.member("ullong_",	&primitives::ullong_)
		.member("float_",	&primitives::float_)
		.member("double_",	&primitives::double_)
	 ;
}

#endif // REVEAL_TEST_PRIMITIVETYPES_HPP_