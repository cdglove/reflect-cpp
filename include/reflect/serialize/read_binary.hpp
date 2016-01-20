// *****************************************************************************
// 
// reflect/serialize/read_binary.hpp
//
// Converts an flat binary stream into an instance
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REFLECT_SERIALIZE_READBINARY_HPP_
#define REFLECT_SERIALIZE_READBINARY_HPP_

#include "reflect/reflect_type.hpp"

namespace reflect { namespace serialize {

template<typename T, typename Stream>
class read_binary
{
public:
	read_binary(T& t, Stream& s)
		: instance_(t)
		, stream_(s)
	{}

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*member)
	{
	 	read_binary<Child, Stream> read_child(instance_.*member, stream_);
		reflect_type<value_type>(read_child, _first_ver);
	}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun size, InsertFun insert)
	{
		auto num_elements = size(instance_);
		stream_.read(reinterpret_cast<char*>(&num_elements), sizeof(num_elements));

		typedef std::decay_t<
			typename function_traits<InsertFun>::template argument<1>::type
		> value_type;

		for(auto&& i : instance_)
		{
			read_binary<value_type, Stream> read_child(i, stream_);
			reflect_type<value_type>(read_child, _first_ver);
		}
	}

	void primitive()
	{
		stream_.read(reinterpret_cast<char*>(&instance_), sizeof(instance_));
	}

private:

	T const& instance_;
	Stream& stream_;
};

#endif // REFLECT_SERIALIZE_READBINARY_HPP_