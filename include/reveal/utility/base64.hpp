// *****************************************************************************
// 
// reveal/utility/base64.hpp
//
// Base64 encode / decode routines.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REVEAL_UTILITY_BASE64_HPP_
#define REVEAL_UTILITY_BASE64_HPP_

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <iterator>

// -----------------------------------------------------------------------------
//
namespace reveal { namespace utility { 

// -----------------------------------------------------------------------------
//
template<typename InputIterator, typename OutputIterator>
void base64_encode(InputIterator first, InputIterator last, OutputIterator out)
{
	//typedef typename std::iterator_traits<
	//	OutputIterator
	//>::value_type CharType;

	typedef char CharType;

	using namespace boost::archive::iterators;

	typedef 
	  insert_linebreaks<
        base64_from_binary<
          transform_width<
            InputIterator,
			6,
			sizeof(CharType) * 8
		  >
        >,
		76
      > 
      translate_out;

	std::copy(
        translate_out(first),
        translate_out(last),
        out
    );
}

template<typename InputIterator, typename OutputIterator>
void base64_decode(InputIterator first, InputIterator last, OutputIterator out)
{
	typedef typename std::iterator_traits<
		InputIterator
	>::value_type CharType;

	using namespace boost::archive::iterators;

	typedef 
        transform_width<
			binary_from_base64<
				remove_whitespace<
                   InputIterator
                >
            >,
            sizeof(CharType) * 8,
            6
        > 
		translate_in;

	std::copy(
        translate_in(first),
        translate_in(last),
        out
    );
}

}} 

#endif // REVEAL_UTILITY_BASE64_HPP_