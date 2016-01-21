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
#include <iostream>

#include "reveal/reflect_type.hpp"
#include "reveal/serialize/print_names.hpp"
#include "test_user_types.hpp"

int main()
{
	ns::Parent1 obj;
	
	reveal::reflector<
		reveal::serialize::print_names
	> name_printer;

	name_printer(reveal::tag<ns::Parent1>(), std::cout);
	
	return 0;
}