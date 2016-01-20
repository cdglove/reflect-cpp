// *****************************************************************************
// 
// reflect/serialize/simple_binary_writer.hpp
//
// Converts an instance into a flat binary stream.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REFLECT_SERIALIZE_SIMPLEBINARYWRITER_HPP_
#define REFLECT_SERIALIZE_SIMPLEBINARYWRITER_HPP_

#include "reflect/reflect_type.hpp"

namespace reflect { namespace serialize {

template<typename T, typename Stream>
class simple_binary_writer
{
public:
	simple_binary_writer(T& t, Stream& s)
		: instance_(t)
		, stream_(s)
	{}

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*member)
	{
	 	simple_binary_writer<Child, Stream> write_child(instance_.*member, stream_);
		reflect_type<value_type>(write_child, _first_ver);
	}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun size, InsertFun insert)
	{
		auto num_elements = size(instance_);
		stream_.write(reinterpret_cast<char const*>(&num_elements), sizeof(num_elements));

		typedef std::decay_t<
			typename function_traits<InsertFun>::template argument<1>::type
		> value_type;

		for(auto&& i : instance_)
		{
			simple_binary_writer<value_type, Stream> write_child(i, stream_);
			reflect_type<value_type>(write_child, _first_ver);
		}
	}

	void primitive()
	{
		stream_.write(reinterpret_cast<char const*>(&instance_), sizeof(instance_));
	}

private:

	T const& instance_;
	Stream& stream_;
};

#endif // REFLECT_SERIALIZE_SIMPLEBINARYWRITER_HPP_