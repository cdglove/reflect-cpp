// *****************************************************************************
//
// reveal/serialize/build_tuple.hpp
//
// Converts an object to a tuple of references.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REFLECT_SERIALIZE_BUILDTUPLE_HPP_
#define REFLECT_SERIALIZE_BUILDTUPLE_HPP_

#include <tuple>
#include "reveal/reflect_type.hpp"


// -----------------------------------------------------------------------------
//
namespace reveal { namespace serialize {

template<typename T, typename Tuple>
class build_tuple : public default_visitor
{
public:

	build_tuple(T& t, Tuple& tup)
		: instance_(t)
		, tup_(tup)
	{}

	template<typename Child, typename Parent>
	auto member(char const*, Child Parent::*member)
	{ 
		return reveal::reflect_type<Child>(*this, _first_ver);
	}

	//template<typename SizeFun, typename InsertFun>
	//auto container(SizeFun, InsertFun)
	//{
	//	typedef std::decay_t<
	//		typename function_traits<InsertFun>::template argument<1>::type
	//	> value_type;
	//}

	auto primitive()
	{
		auto new_tup = std::tuple_cat(tup_, std::tie(instance_)); 
		return build_tuple<T, decltype(new_tup)>(instance_, new_tup);
	}

private:

	T& instance_;
	Tuple& tup_;
};

}}
#endif // REFLECT_SERIALIZE_BUILDTUPLE_HPP_