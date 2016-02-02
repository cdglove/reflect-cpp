// *****************************************************************************
// 
// reveal/serialize/simple_binary_reader.hpp
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
#ifndef REFLECT_SERIALIZE_SIMPLEBINARYREADER_HPP_
#define REFLECT_SERIALIZE_SIMPLEBINARYREADER_HPP_

#include "reveal/reflect_type.hpp"
#include "reveal/traits/function_traits.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal { namespace serialize {

// -----------------------------------------------------------------------------
//
namespace detail
{
	template<typename T, typename Stream>
	class simple_binary_reader_impl  : public default_visitor<simple_binary_reader_impl<T, Stream>>
	{
	public:
		simple_binary_reader_impl(T& t, Stream& s)
			: instance_(t)
			, stream_(s)
		{}

		template<typename Child, typename Parent>
		simple_binary_reader_impl<T, Stream>& member(char const* name, Child Parent::*member)
		{
	 		simple_binary_reader_impl<Child, Stream> read_child(instance_.*member, stream_);
			reflect_type<Child>(read_child, _first_ver);
			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		simple_binary_reader_impl<T, Stream>& container(SizeFun size, InsertFun insert)
		{
			auto num_elements = size(instance_);
			stream_.read(reinterpret_cast<char*>(&num_elements), sizeof(num_elements));

			typedef std::decay_t<
				typename function_traits<InsertFun>::template argument<1>::type
			> value_type;

			for(std::size_t i = 0; i < num_elements; ++i)
			{
				//cglover-todo: remove the requirement for default constructibility.
				value_type value;
				simple_binary_reader_impl<value_type, Stream> read_child(value, stream_);
				reflect_type<value_type>(read_child, _first_ver);
				insert(instance_, std::move(value));
			}

			return *this;
		}

		simple_binary_reader_impl<T, Stream>& primitive()
		{
			stream_.read(reinterpret_cast<char*>(&instance_), sizeof(instance_));
			return *this;
		}

	private:

		T& instance_;
		Stream& stream_;
	};
	}

// -----------------------------------------------------------------------------
//
class simple_binary_reader
{
public:

	template<typename T, typename Stream>
	void operator()(T& t, Stream& s)
	{
		detail::simple_binary_reader_impl<T, Stream> reader(t, s);
		reflect_type<T>(reader, _first_ver);
	}
};

}} // namespace reveal { namespace serialize {
	
#endif // REFLECT_SERIALIZE_SIMPLEBINARYREADER_HPP_