// *****************************************************************************
// 
// reveal/test/binary_reader_writer.cpp
//
// Tests the functionality of the binary reader and writer.
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
#include <cassert>

#include "reveal/reflect_type.hpp"
#include "reveal/serialize/simple_binary_writer.hpp"
#include "reveal/serialize/simple_binary_reader.hpp"
#include "test_primitive_types.hpp"
#include "test_container_types.hpp"
#include "test_user_types.hpp"

TEST(SimpleBinary, ReadWritePrimitives)
{
	primitives v = make_primitives_values();
	reveal::serialize::simple_binary_writer writer;
	std::stringstream str;
	writer(v, str);
	v = make_primitives_0s();
	reveal::serialize::simple_binary_reader binary_reader;
	binary_reader(v, str);
	EXPECT_EQ(make_primitives_values(), v);
}

TEST(SimpleBinary, ReadWriteStdContainers)
{
	std_containers c = make_containers_values();
	reveal::serialize::simple_binary_writer writer;
	std::stringstream str;
	writer(c, str);
	c = make_containers_empty();
	reveal::serialize::simple_binary_reader binary_reader;
	binary_reader(c, str);
	EXPECT_EQ(make_containers_values(), c);
}

TEST(SimpleBinary, ReadWritePod)
{
	user::pod p;
	p.data = 1;
	reveal::serialize::simple_binary_writer writer;
	std::stringstream str;
	writer(p, str);
	p.data = 0;
	reveal::serialize::simple_binary_reader binary_reader;
	binary_reader(p, str);
	EXPECT_EQ(p.data, 1);
}