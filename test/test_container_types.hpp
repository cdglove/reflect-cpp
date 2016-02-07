// *****************************************************************************
// 
// test/test_container_types.hpp
//
// Common container types for reflect-cpp tests.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REVEAL_TEST_CONTAINERTYPES_HPP_
#define REVEAL_TEST_CONTAINERTYPES_HPP_

#include <reveal/std/vector.hpp>
#include <reveal/std/map.hpp>
#include <reveal/std/string.hpp>
#include <reveal/std/pair.hpp>

// -----------------------------------------------------------------------------
//
struct std_containers
{
	std::pair<int, float>	pair_;
	std::vector<int>		vector_;
	std::map<int, int>		map_;
	std::string				string_;
};

inline bool operator==(std_containers const& a, std_containers const& b)
{
	return 
		a.pair_		== b.pair_ &&
		a.vector_	== b.vector_ &&
		a.map_		== b.map_ &&
		a.string_	== b.string_ 
	;
}

template<typename Visitor> inline constexpr 
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<std_containers>)
{
	return v
		.member("pair_", &std_containers::pair_)
		.member("vector_", &std_containers::vector_)
		.member("map_", &std_containers::map_)
		.member("string_", &std_containers::string_)
	;
}

inline std_containers make_containers_empty()
{
	return std_containers();
}

inline std_containers make_containers_values()
{
	std_containers ret;
	
	ret.pair_ = std::make_pair(1, 2.f);
	
	ret.vector_.push_back(10);
	ret.vector_.push_back(20);

	ret.map_.insert(std::make_pair(100, 200));
	ret.map_.insert(std::make_pair(300, 400));

	ret.string_ = "Hello World!";

	return ret;
}

#endif // REVEAL_TEST_CONTAINERTYPES_HPP_