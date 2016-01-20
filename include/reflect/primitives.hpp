// *****************************************************************************
// 
// reflect/primitives.hpp
//
// Reflection of primitive types.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REFLECT_PRIMITIVES_HPP_
#define REFLECT_PRIMITIVES_HPP_

#include "reflect/version.hpp"

namespace reflect {

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<char>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<unsigned char>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<signed char>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<short>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<unsigned short>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<int>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<unsigned int>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<long>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<unsigned long>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<long long>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<unsigned long long>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<float>)
{
	v.primitive();
}

template<typename Visitor>
void reflect(Visitor& v, version_t, tag<double>)
{
	v.primitive();
}

}
#endif // REFLECT_REFLECT_HPP_