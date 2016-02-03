// *****************************************************************************
// 
// reveal/std/string.hpp
//
// Reflection of std::string
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_STD_STRING_HPP_
#define REVEAL_STD_STRING_HPP_

#include <string>
#include "reveal/version.hpp"
#include "reveal/tag.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal {

template<typename Visitor, typename T, typename Traits, typename Allocator>
decltype(auto) reflect(Visitor& v, version_t, tag<std::basic_string<T, Traits, Allocator>>)
{
	return v.string(
		[](std::basic_string<T, Traits, Allocator> const& s) { return s.length(); },
		[](std::basic_string<T, Traits, Allocator>& s, T&& i) { return s.push_back(std::forward<T>(i)); }
	);
}

}

#endif // REVEAL_STD_STRING_HPP_
