// *****************************************************************************
// 
// reflect/std/vector.hpp
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
#ifndef REFLECT_STD_VECTOR_HPP_
#define REFLECT_STD_VECTOR_HPP_

#include <vector>
#include "reflect/version.hpp"
#include "reflect/tag.hpp"

// -----------------------------------------------------------------------------
//
namespace reflect {

template<typename Visitor, typename T, typename Allocator>
void reflect(Visitor& v, version_t, tag<std::vector<T, Allocator>>)
{
	v.container(
		[](std::vector<T, Allocator> const& vec) { return vec.size(); },
		[](std::vector<T, Allocator>& vec, T&& i) { return vec.push_back(std::forward<T>(i)); }
	);
}

}

#endif // REFLECT_STD_VECTOR_HPP_