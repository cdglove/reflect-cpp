// *****************************************************************************
// 
// reveal/test/operators.cpp
//
// Demonstrates using reflection to implement common operators.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#include "gtest/gtest.h"

#include "reveal/reflect_type.hpp"
#include <cstring>

// -----------------------------------------------------------------------------
//
template<typename T>
struct equality_visitor
{
	equality_visitor(bool& eq, T const& lhs, T const& rhs)
		: eq_(eq)
		, lhs_(lhs)
		, rhs_(rhs)
	{}

	template<typename Child, typename Parent>
	equality_visitor<T>& member(char const*, Child Parent::*member)
	{ 
		if(eq_)
			eq_ = (lhs_.*member == rhs_.*member);
		return *this;
	}

	template<typename SizeFun, typename InsertFun>
	equality_visitor<T>& container(SizeFun, InsertFun)
	{
		if(eq_)
		{
			auto begin1 = std::begin(lhs_);
			auto end1 = std::end(lhs_);
			eq_ = std::equal(
				std::begin(lhs_),
				std::end(lhs_)
				std::begin(rhs_),
				std::end(rhs_)
			);
		}
	}

	template<typename SizeFun, typename InsertFun>
	equality_visitor<T>& string(SizeFun s, InsertFun i)
	{ 
		if(eq_)
			eq_ = (lhs_ == rhs_);
		return *this;
	}

	equality_visitor<T>& pod()
	{
		if(eq_)
			eq_ = std::memcmp(&lhs_, &rhs_, sizeof(T)) == 0;
		return *this;
	}

	equality_visitor<T>& primitive()
	{
		if(eq_)
			eq_ = lhs_ == rhs_;
		return *this;
	}

private:

	T const& lhs_;
	T const& rhs_;
	bool& eq_;
};

template<typename T>
bool is_equal(T const& a, T const& b)
{
	bool ret_code = false;
	equality_visitor<T> visit(ret_code, a, b);
	reveal::reflect_type<T>(visit);
	return ret_code;
}

// -----------------------------------------------------------------------------
//
namespace {
struct primitives
{
	char 				char_;
	unsigned 			uchar_;
	signed char 		schar_;
	short 				short_;
	unsigned short 		ushort_;
	int 				int_;
	unsigned int 		uint_;
	long 				long_;
	unsigned long 		ulong_;
	long long 			llong_;
	unsigned long long 	ullong_;
	float 				float_;
	double 				double_;
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

inline bool operator==(primitives const& a, primitives const& b)
{
	return is_equal(a, b);
}


// -----------------------------------------------------------------------------
//
struct compound_struct
{
	compound_struct()
	{
		std::memset(this, 0, sizeof(*this));
	}

	primitives p;
	double v;
};

template<typename Visitor> constexpr inline
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<compound_struct>)
{
	return v
		.member("p", &compound_struct::p)
	 	.member("v", &compound_struct::v)
	 ;
}

bool operator==(compound_struct const& a, compound_struct const& b)
{
	return is_equal(a, b);
}

}

TEST(Operators, Equality)
{
	compound_struct a, b;
	
	EXPECT_EQ(a, b);
	a.v = a.v - 1;
	EXPECT_FALSE(a == b);
}