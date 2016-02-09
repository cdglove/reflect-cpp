// *****************************************************************************
// 
// reveal/serialize/simple_binary_writer.hpp
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
#ifndef REVEAL_SERIALIZE_SIMPLEBINARYWRITER_HPP_
#define REVEAL_SERIALIZE_SIMPLEBINARYWRITER_HPP_

#include "reveal/reflect_type.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal { namespace serialize {

// -----------------------------------------------------------------------------
//
namespace detail
{
	template<typename T, typename Stream>
	class simple_binary_writer_impl
	{
	public:
		simple_binary_writer_impl(T const& t, Stream& s)
			: instance_(t)
			, stream_(s)
		{}

		template<typename Child, typename Parent>
		simple_binary_writer_impl<T, Stream>& member(char const* name, Child Parent::*member)
		{
	 		simple_binary_writer_impl<Child, Stream> write_child(instance_.*member, stream_);
			reflect_type<Child>(write_child, _first_ver);
			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		simple_binary_writer_impl<T, Stream>& container(SizeFun size, InsertFun insert)
		{
			auto num_elements = size(instance_);
			stream_.write(reinterpret_cast<char const*>(&num_elements), sizeof(num_elements));

			for(auto&& i : instance_)
			{
				typedef std::decay_t<decltype(i)> value_type;
				simple_binary_writer_impl<value_type, Stream> write_child(i, stream_);
				reflect_type<value_type>(write_child, _first_ver);
			}

			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		simple_binary_writer_impl<T, Stream>& string(SizeFun size, InsertFun insert)
		{
			return container(size, insert);
		}

		simple_binary_writer_impl<T, Stream>& pod()
		{
			stream_.write(reinterpret_cast<char const*>(&instance_), sizeof(instance_));
			return *this;
		}

		simple_binary_writer_impl<T, Stream>& primitive()
		{
			return pod();
		}

	private:

		T const& instance_;
		Stream& stream_;
	};
}

// -----------------------------------------------------------------------------
//
class simple_binary_writer
{
public:
	template<typename T, typename Stream>
	void operator()(T const& t, Stream& s)
	{
		detail::simple_binary_writer_impl<T, Stream> writer(t, s);
		reflect_type<T>(writer, _first_ver);
	}
};

}} // namespace reveal { namespace serialize {

#endif // REVEAL_SERIALIZE_SIMPLEBINARYWRITER_HPP_