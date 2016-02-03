// *****************************************************************************
// 
// reveal/primitives.hpp
//
//  reflection of primitive types.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_PRIMITIVES_HPP_
#define REVEAL_PRIMITIVES_HPP_

#include "reveal/version.hpp"

namespace reveal {

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<char>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<unsigned char>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<signed char>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<short>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<unsigned short>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<int>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<unsigned int>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<long>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<unsigned long>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<long long>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<unsigned long long>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<float>)
{
	return v.primitive();
}

template<typename Visitor>
inline decltype(auto) reflect(Visitor& v, version_t, tag<double>)
{
	return v.primitive();
}

}
#endif //  reflect_ reflect_HPP_