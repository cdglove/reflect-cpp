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
#include "test_user_types.hpp"

TEST(BinaryIO, Read_Write)
{
	ns::Parent1 obj;

	obj.f_.a_ = 1;
	obj.f_.b_ = 2;
	obj.s_.c_.push_back(3);
	obj.s_.c_.push_back(4);
	obj.s_.d_ = 5;
	
	std::stringstream archive;

	reveal::serialize::simple_binary_writer<
		std::stringstream
	> binary_writer(archive);

	binary_writer(obj);

	obj.f_.a_ = 0;
	obj.f_.b_ = 0;
	obj.s_.c_.clear();
	obj.s_.d_ = 0;

	reveal::serialize::simple_binary_reader<
		std::stringstream
	> binary_reader(archive);

	binary_reader(obj);

	EXPECT_EQ(obj.f_.a_, 1);
	EXPECT_EQ(obj.f_.b_, 2);
	EXPECT_EQ(obj.s_.c_[0], 3);
	EXPECT_EQ(obj.s_.c_[1], 4);
	EXPECT_EQ(obj.s_.d_, 5);
}
