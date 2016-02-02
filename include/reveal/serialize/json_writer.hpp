// *****************************************************************************
// 
// reveal/serialize/json_writer.hpp
//
// Uses reflection to write out json data.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REFLECT_SERIALIZE_JSONWRITER_HPP_
#define REFLECT_SERIALIZE_JSONWRITER_HPP_

#include "reveal/reflect_type.hpp"

// -----------------------------------------------------------------------------
//
namespace reveal { namespace serialize {

// -----------------------------------------------------------------------------
//
namespace detail
{
	template<typename T, typename Stream>
	class json_writer_impl : public default_visitor<json_writer_impl<T, Stream>>
	{
	public:
		json_writer_impl(T const& t, Stream& s, int indent)
			: instance_(t)
			, stream_(s)
			, indent_(indent)
			, first_member_written_(false)
		{
		}

		~json_writer_impl()
		{
			if(first_member_written_)
			{
				indent_ -= 1;
				stream_ << '\n';
				indent();
				stream_ << "}";
			}
		}

		json_writer_impl(json_writer_impl const&) = delete;
		json_writer_impl operator=(json_writer_impl) = delete;

		template<typename Child, typename Parent>
		json_writer_impl<T, Stream>& member(char const* name, Child Parent::*member)
		{
			if(!first_member_written_)
			{
				stream_ << "{\n";
				indent_ += 1;
			}
			else
			{
				stream_ << ",\n";
			}
			
			first_member_written_ = true;
		
			indent();

			stream_ << '"' << name << '"' << ": ";

	 		json_writer_impl<const Child, Stream> write_child(instance_.*member, stream_, indent_);
			reflect_type<const Child>(write_child, _first_ver);
			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		json_writer_impl<T, Stream>& container(SizeFun, InsertFun)
		{
			stream_ << '[';

			auto begin = std::begin(instance_);
			auto end = std::end(instance_);

			typedef std::decay_t<
				decltype(*begin)
			> value_type;

			if(begin != end)
			{
				json_writer_impl<value_type, Stream> write_child(*begin, stream_, indent_);
				reflect_type<value_type>(write_child, _first_ver);
				++begin;
			}

			while(begin != end)
			{
				stream_ << ", ";
				json_writer_impl<value_type, Stream> write_child(*begin, stream_, indent_);
				reflect_type<value_type>(write_child, _first_ver);
				++begin;
			}

			stream_ << ']';

			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		json_writer_impl<T, Stream>& string(SizeFun size, InsertFun insert)
		{
			stream_ << '"' << instance_ << '"';
			return *this;
		}

		json_writer_impl<T, Stream>& primitive()
		{
			stream_ << instance_;
			return *this;
		}

	private:

		void indent()
		{
			for(int i = 0; i < indent_; ++i)
				stream_ << "  ";
		}

		T const& instance_;
		Stream& stream_;
		int indent_;
		bool first_member_written_;
	};
}

// -----------------------------------------------------------------------------
//
class json_writer
{
public:

	template<typename T, typename Stream>
	void operator()(T const& t, Stream& s)
	{
		detail::json_writer_impl<T, Stream> writer(t, s, 0);
		reflect_type<T>(writer, _first_ver);
	}
};

}} // namespace reveal { namespace serialize {

#endif // REFLECT_SERIALIZE_JSONWRITER_HPP_