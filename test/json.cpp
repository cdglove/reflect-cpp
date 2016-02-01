// *****************************************************************************
// 
// reveal/test/json.cpp
//
// Tests JSON serializer 
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#include "gtest/gtest.h"

#include <sstream>

#include "reveal/reflect_type.hpp"
#include "reveal/serialize/json_writer.hpp"
#include "reveal/serialize/json_reader.hpp"
#include "reveal/std/string.hpp"
#include "reveal/std/vector.hpp"
#include "reveal/std/map.hpp"

class Json : public ::testing::Test
{
public:
	std::stringstream struct_str;
};

// -----------------------------------------------------------------------------
//
struct values
{
	int integer;
	float real;
	std::string string;
};

template<typename Visitor>
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<values>)
{
	return v
		.member("integer", &values::integer)
	 	.member("real", &values::real)
	 	.member("string", &values::string)
	 ;
}

struct nested_values
{
	float f;
	values v;
	int i;
};

// -----------------------------------------------------------------------------
//
template<typename Visitor>
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<nested_values>)
{
	return v
		.member("f", &nested_values::f)
	 	.member("v", &nested_values::v)
	 	.member("i", &nested_values::i)
	 ;
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, WriteStruct)
{
	values v;
	v.integer = 10;
	v.real = 5.f;
	v.string = "Hello World!";
	
	reveal::serialize::json_writer writer;
	writer(v, struct_str);
	EXPECT_EQ(struct_str.str(), "{\n  \"integer\": 10,\n  \"real\": 5,\n  \"string\": \"Hello World!\"\n}");
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, ReadStruct)
{
	values v;
	reveal::serialize::json_reader reader;
	reader(v, struct_str);
	EXPECT_EQ(v.integer, 10);
	EXPECT_EQ(v.real, 5.f);
	EXPECT_EQ(v.string, "Hello World!");
}

TEST(Json, WriteNestedStruct)
{
	nested_values nv;
	nv.f = 1.f;
	nv.v.integer = 10;
	nv.v.real = 5.f;
	nv.v.string = "Hello World!";
	nv.i = 2;
	
	std::stringstream str;
	reveal::serialize::json_writer writer;
	writer(nv, str);
	EXPECT_EQ(str.str(), "{\n  \"f\": 1,\n  \"v\": {\n    \"integer\": 10,\n    \"real\": 5,\n    \"string\": \"Hello World!\"\n  },\n  \"i\": 2\n}");
}

struct container
{
	std::vector<int> v;
	std::map<int, float> m;
};

template<typename Visitor>
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<container>)
{
	return v
		.member("v", &container::v)
		.member("m", &container::m)
	;
}

TEST(Json, WriteContainer)
{
	container c;
	c.v.push_back(0);
	c.v.push_back(1);

	c.m.insert(std::make_pair(1, 10.f));
	c.m.insert(std::make_pair(2, 20.f));
	std::stringstream str;
	reveal::serialize::json_writer writer;
	writer(c, str);
	EXPECT_EQ(str.str(), "{\n  \"v\": [0, 1],\n  \"m\": [{\n    \"first\": 1,\n    \"second\": 10\n  }, {\n    \"first\": 2,\n    \"second\": 20\n  }]\n}");
}
