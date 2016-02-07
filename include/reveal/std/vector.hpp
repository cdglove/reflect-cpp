// *****************************************************************************
// 
// reveal/std/vector.hpp
//
// Reflection of std::vector<>
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_STD_VECTOR_HPP_
#define REVEAL_STD_VECTOR_HPP_

#include <vector>
#include "reveal/version.hpp"
#include "reveal/tag.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal {

template<typename Visitor, typename T, typename Allocator>
constexpr decltype(auto) reflect(Visitor& v, version_t, tag<std::vector<T, Allocator>>)
{
	return v.container(
		[](std::vector<T, Allocator> const& vec) { return vec.size(); },
		[](std::vector<T, Allocator>& vec, T&& i) { return vec.push_back(std::forward<T>(i)); }
	);
}

}

#endif // REVEAL_STD_VECTOR_HPP_
