// *****************************************************************************
// 
// reflect/serialize/simple_binary_reader.hpp
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

#include "reflect/reflect_type.hpp"
#include "reflect/traits/function_traits.hpp"

// -----------------------------------------------------------------------------
//
namespace reflect { namespace serialize {

// -----------------------------------------------------------------------------
//
namespace detail
{
	template<typename T, typename Stream>
	class simple_binary_reader_impl
	{
	public:
		simple_binary_reader_impl(T& t, Stream& s)
			: instance_(t)
			, stream_(s)
		{}

		template<typename Child, typename Parent>
		void member(char const* name, Child Parent::*member)
		{
	 		simple_binary_reader_impl<Child, Stream> read_child(instance_.*member, stream_);
			reflect_type<Child>(read_child, _first_ver);
		}

		template<typename SizeFun, typename InsertFun>
		void container(SizeFun size, InsertFun insert)
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
		}

		void primitive()
		{
			stream_.read(reinterpret_cast<char*>(&instance_), sizeof(instance_));
		}

	private:

		T& instance_;
		Stream& stream_;
	};
	}

// -----------------------------------------------------------------------------
//
template<typename Stream>
class simple_binary_reader
{
public:

	simple_binary_reader(Stream& stream)
		: stream_(stream)
	{}

	template<typename T>
	void operator()(T& t)
	{
		detail::simple_binary_reader_impl<T, Stream> reader(t, stream_);
		reflect_type<T>(reader, _first_ver);
	}

private:

	Stream& stream_;
};

}} // namespace reflect { namespace serialize {
	
#endif // REFLECT_SERIALIZE_SIMPLEBINARYREADER_HPP_