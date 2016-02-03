// *****************************************************************************
// 
// reveal/version.hpp
//
// Strongly type version with enough space to hold 65000 versions
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_VERSION_HPP_
#define REVEAL_VERSION_HPP_

namespace reveal {

// -----------------------------------------------------------------------------
//
enum version_t
{
	_first_ver = 0,
	_last_ver = 0xFFFF
};

inline version_t ver(unsigned short v)
{
	return version_t(v);
}

}

#endif // REVEAL_VERSION_HPP_
