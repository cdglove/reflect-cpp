// *****************************************************************************
// 
// reflect/test/binary_reader_writer.cpp
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
#include <sstream>
#include <cassert>

#include "reflect/reflect_type.hpp"
#include "reflect/serialize/simple_binary_writer.hpp"
#include "reflect/serialize/simple_binary_reader.hpp"
#include "test_user_types.hpp"

int main()
{
	ns::Parent1 obj;

	obj.f_.a_ = 1;
	obj.f_.b_ = 2;
	obj.s_.c_.push_back(3);
	obj.s_.c_.push_back(4);
	obj.s_.d_ = 5;
	
	std::stringstream archive;

	reflect::serialize::detail::simple_binary_writer_impl<
		ns::Parent1,
		std::stringstream
	> binary_writer(obj, archive);

	reflect::reflect_type<ns::Parent1>(binary_writer, reflect::_first_ver);

	obj.f_.a_ = 0;
	obj.f_.b_ = 0;
	obj.s_.c_.clear();
	obj.s_.d_ = 0;

	reflect::serialize::simple_binary_reader<
		std::stringstream
	> binary_reader(archive);

	binary_reader(obj);

	assert(obj.f_.a_ == 1);
	assert(obj.f_.b_ == 2);
	assert(obj.s_.c_[0] == 3);
	assert(obj.s_.c_[1] == 4);
	assert(obj.s_.d_ == 5);
	
	return 0;
}