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
#ifndef REVEAL_SERIALIZE_BUILDTUPLE_HPP_
#define REVEAL_SERIALIZE_BUILDTUPLE_HPP_

#include <tuple>
#include "reveal/reflect_type.hpp"


// -----------------------------------------------------------------------------
//
namespace reveal { namespace serialize {

// -----------------------------------------------------------------------------
//
template<typename T, typename Tuple>
class build_tuple
{
public:

	build_tuple(T& instance, Tuple tuple)
		: instance_(instance)
		, tuple_(tuple)
	{}

	template<typename Child, typename Parent>
	auto member(char const*, Child Parent::*member)
	{
		//auto children = std::tuple_cat(tuple_, std::tie(instance_.*member));
		build_tuple<Child, std::tuple<>> build_child(s, std::tuple<>());
		return reveal::reflect_type<Child>(build_child, _first_ver);
		//return build_tuple<Parent, decltype(children)>(instance_, children);
		//auto new_tup = 
		//return build_tuple<Parent, std::tuple<>>(instance_.*member, std::tuple<>());
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
		*this;
	}

	Tuple result()
	{
		return tuple_;
	}

private:

	T& instance_;
	Tuple tuple_;
};

}}
#endif // REVEAL_SERIALIZE_BUILDTUPLE_HPP_
