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

	char const* struct_json = "{\n  \"integer\": 10,\n  \"real\": 5,\n  \"string\": \"Hello World!\"\n}";
	char const* nested_struct_json = "{\n  \"f\": 1,\n  \"v\": {\n    \"integer\": 10,\n    \"real\": 5,\n    \"string\": \"Hello World!\"\n  },\n  \"i\": 2\n}";
	char const* container_json = "{\n  \"v\": [0, 1],\n  \"m\": [{\n    \"first\": 1,\n    \"second\": 10\n  }, {\n    \"first\": 2,\n    \"second\": 20\n  }]\n}";
	char const* pod_json = "\"iRMAAA\"";
};

// -----------------------------------------------------------------------------
//
TEST_F(Json, WritePrimitives)
{
	primitives v;
	
	reveal::serialize::json_writer writer;
	std::stringstream str;
	writer(v, str);
}

TEST_F(Json, ReadPrimitives)
{
	primitives v;
	reveal::serialize::json_reader reader;
	std::stringstream str(struct_json);
	reader(v, str);
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, WriteStdContainers)
{
	std_containers c;
	std::stringstream str;
    reveal::serialize::json_writer writer;
	writer(c, str);
}

TEST_F(Json, ReadStdContainers)
{
	std_containers c;
	reveal::serialize::json_reader reader;
	std::stringstream str(container_json);
	reader(c, str);
}

// -----------------------------------------------------------------------------
//
TEST_F(Json, WriteNestedStruct)
{
	compound_struct nv;
	std::stringstream str;
	reveal::serialize::json_writer writer;
	writer(nv, str);
}

TEST_F(Json, ReadNestedStruct)
{
	compound_struct nv;
	std::stringstream str(nested_struct_json);
	reveal::serialize::json_reader reader;
	reader(nv, str);
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