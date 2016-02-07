// *****************************************************************************
// 
// reveal/test/print_names.cpp
//
// Uses reflection to print the names of all of the mamber variables of a type
// hierarchy.
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
#include "reveal/serialize/print_names.hpp"
#include "test_user_types.hpp"

TEST(Visitor, PrintNames)
{
	std::stringstream str;
	reveal::serialize::print_names name_printer(str);
	reveal::reflect_type<user::compound_struct>(name_printer);
}