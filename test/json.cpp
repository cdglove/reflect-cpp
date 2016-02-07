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
#include "test_primitive_types.hpp"
#include "test_container_types.hpp"
#include "test_user_types.hpp"

// -----------------------------------------------------------------------------
//
class Json : public ::testing::Test
{
public:

	char const* primitives_json = 
					"{\n"
					"  \"char_\": 1,\n"
					"  \"uchar_\": 2,\n"
					"  \"schar_\": 3,\n"
					"  \"short_\": 4,\n"
					"  \"ushort_\": 5,\n"
					"  \"int_\": 6,\n"
					"  \"uint_\": 7,\n"
					"  \"long_\": 8,\n"
					"  \"ulong_\": 9,\n"
					"  \"llong_\": 10,\n"
					"  \"ullong_\": 11,\n"
					"  \"float_\": 12,\n"
					"  \"double_\": 13\n"
					"}";
					
	char const* containers_json = 
					"{\n"
					"  \"pair_\": {\n"
					"    \"first\": 1,\n"
					"    \"second\": 2\n"
					"  },\n"
					"  \"vector_\": [10, 20],\n"
					"  \"map_\": [{\n"
					"    \"first\": 100,\n"
					"    \"second\": 200\n"
					"  }, {\n"
					"    \"first\": 300,\n"
					"    \"second\": 400\n"
					"  }],\n"
					"  \"string_\": \"Hello World!\"\n"
					"}";
					
	char const* nested_struct_json = 
					"{\n"
					"  \"p\": {\n"
					"    \"char_\": 1,\n"
					"    \"uchar_\": 2,\n"
					"    \"schar_\": 3,\n"
					"    \"short_\": 4,\n"
					"    \"ushort_\": 5,\n"
					"    \"int_\": 6,\n"
					"    \"uint_\": 7,\n"
					"    \"long_\": 8,\n"
					"    \"ulong_\": 9,\n"
					"    \"llong_\": 10,\n"
					"    \"ullong_\": 11,\n"
					"    \"float_\": 12,\n"
					"    \"double_\": 13\n"
					"  },\n"
					"  \"v\": -1\n"
					"}";
					
	char const* pod_json = "\"iRMAAA\"";
};

// -----------------------------------------------------------------------------
//
TEST_F(Json, WritePrimitives)
{
	primitives v = make_primitives_values();
	reveal::serialize::json_writer writer;
	std::stringstream str;
	writer(v, str);
	EXPECT_EQ(primitives_json, str.str());
}

TEST_F(Json, ReadPrimitives)
{
	primitives v = make_primitives_0s();
	reveal::serialize::json_reader reader;
	std::stringstream str(primitives_json);
	reader(v, str);
	EXPECT_EQ(make_primitives_values(), v);
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, WriteStdContainers)
{
	std_containers c = make_containers_values();
	std::stringstream str;
    reveal::serialize::json_writer writer;
	writer(c, str);

	EXPECT_EQ(containers_json, str.str());
}

TEST_F(Json, ReadStdContainers)
{
	std_containers c = make_containers_empty();
	reveal::serialize::json_reader reader;
	std::stringstream str(containers_json);
	reader(c, str);
	EXPECT_EQ(make_containers_values(), c);
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, WriteNestedStruct)
{
	compound_struct cs;
	std::stringstream str;
	reveal::serialize::json_writer writer;
	writer(cs, str);
	EXPECT_EQ(nested_struct_json, str.str());
}

TEST_F(Json, ReadNestedStruct)
{
	compound_struct cs;
	cs.p = make_primitives_0s();
	cs.v = 0.f;

	std::stringstream str(nested_struct_json);
	reveal::serialize::json_reader reader;
	reader(cs, str);
	ASSERT_EQ(compound_struct(), cs);
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, WritePod)
{
	pod p;
	p.data = 5001;
	std::stringstream str;
    reveal::serialize::json_writer writer;
	writer(p, str);
	EXPECT_EQ(str.str(), pod_json);
}

TEST_F(Json, ReadPod)
{
	pod p;
	std::stringstream str(pod_json);
	reveal::serialize::json_reader reader;
	reader(p, str);
	EXPECT_EQ(5001, p.data);
}