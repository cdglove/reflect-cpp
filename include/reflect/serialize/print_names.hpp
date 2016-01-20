// *****************************************************************************
// 
// reflect/serialize/print_names.hpp
//
// Prints the member varialble names of a type hierarchy
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REFLECT_SERIALIZE_PRINTNAMES_HPP_
#define REFLECT_SERIALIZE_PRINTNAMES_HPP_

#include <ostream>
#include <iterator>
#include <algorithm>
#include "reflect/reflect_type.hpp"

namespace reflect { namespace serialize {

class print_names : public default_visitor
{
public:

	print_names(std::ostream& out)
		: out_(out)
		, indent_(0)
	{}

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*)
	{
		++indent_;
		std::generate_n(
			std::ostream_iterator<char>(out_),
			indent_,
			[]() { return '-'; }
		);

		out_ << ' ' << name << std::endl;

		reflect::reflect_type<Child>(*this, _first_ver);
		
		--indent_;
	}

private:

	std::ostream& out_;
	int indent_;
};

}}

#endif // REFLECT_SERIALIZE_PRINTNAMES_HPP_