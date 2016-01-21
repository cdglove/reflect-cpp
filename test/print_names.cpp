// *****************************************************************************
// 
// reflect/test/print_names.cpp
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

#include "reflect/reflect_type.hpp"
#include "reflect/serialize/print_names.hpp"
#include "test_user_types.hpp"

int main()
{
	reflect::serialize::print_names name_printer(std::cout);
	reflect::reflect_type<ns::Parent1>(name_printer, reflect::_first_ver);
	return 0;
}