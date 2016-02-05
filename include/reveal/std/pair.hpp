// *****************************************************************************
// 
// reveal/std/map.hpp
//
// Reflection of std::pair
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_STD_PAIR_HPP_
#define REVEAL_STD_PAIR_HPP_

#include <utility>
#include "reveal/version.hpp"
#include "reveal/tag.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal {

template<typename Visitor, typename T1, typename T2>
constexpr decltype(auto) reflect(Visitor& v, version_t, tag<std::pair<T1, T2>>)
{
	return v
		.member("first", &std::pair<T1, T2>::first)
		.member("second", &std::pair<T1, T2>::second)
	;
}

}

#endif // REVEAL_STD_PAIR_HPP_