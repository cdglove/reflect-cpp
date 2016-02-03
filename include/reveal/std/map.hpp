// *****************************************************************************
// 
// reveal/std/map.hpp
//
// Reflection of std::map
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_STD_MAP_HPP_
#define REVEAL_STD_MAP_HPP_

#include <map>
#include "reveal/std/pair.hpp"
#include "reveal/version.hpp"
#include "reveal/tag.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal {

template<typename Visitor, typename Key, typename T, typename Compare, typename Allocator>
decltype(auto) reflect(Visitor& v, version_t, tag<std::map<Key, T, Compare, Allocator>>)
{
	return v.container(
		[](std::map<Key, T, Compare, Allocator> const& s) { return s.size(); },
		[](std::map<Key, T, Compare, Allocator>& s, std::pair<Key, T>&& i) { return s.insert(std::forward<std::pair<Key, T>>(i)); }
	);
}

}

#endif // REVEAL_STD_MAP_HPP_