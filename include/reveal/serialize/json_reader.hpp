// *****************************************************************************
// 
// reveal/serialize/json_reader.hpp
//
// Uses reflection to read in json data.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REFLECT_SERIALIZE_JSONREADER_HPP_
#define REFLECT_SERIALIZE_JSONREADER_HPP_

#include "reveal/reflect_type.hpp"
#include "reveal/traits/function_traits.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// -----------------------------------------------------------------------------
//
namespace reveal { namespace serialize {

// -----------------------------------------------------------------------------
//
namespace detail
{
	template<typename T>
	class json_reader_impl  : public default_visitor<json_reader_impl<T>>
	{
	public:
		json_reader_impl(T& t, boost::property_tree::ptree& node)
			: instance_(t)
			, node_(node)
		{}

		template<typename Child, typename Parent>
		json_reader_impl<T>& member(char const* name, Child Parent::*member)
		{
			boost::optional<boost::property_tree::ptree&> child = node_.get_child_optional(name);
			if(child)
			{
	 			json_reader_impl<Child> read_child(instance_.*member, *child);
				reflect_type<Child>(read_child, _first_ver);
			}
			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		json_reader_impl<T>& container(SizeFun size, InsertFun insert)
		{
			typedef std::decay_t<
				typename function_traits<InsertFun>::template argument<1>::type
			> value_type;

			for(auto&& element : node_)
			{
				// cglover-todo: remove the requirement for default constructibility.
				value_type value;
				json_reader_impl<value_type> read_child(value, element.second);
				reflect_type<value_type>(read_child, _first_ver);
				insert(instance_, std::move(value));
			}

			return *this;
		}

		template<typename SizeFun, typename InsertFun>
		json_reader_impl<T>& string(SizeFun, InsertFun)
		{
			return primitive();
		}

		json_reader_impl<T>& primitive()
		{
			boost::optional<T> value = node_.get_value_optional<T>();
			if(value)
			{
				instance_ = *value;
			}
			return *this;
		}

	private:

		T& instance_;
		boost::property_tree::ptree& node_;
	};
	}

// -----------------------------------------------------------------------------
//
class json_reader
{
public:

	template<typename T, typename Stream>
	void operator()(T& t, Stream& s)
	{
		boost::property_tree::ptree tree;
		boost::property_tree::read_json(s, tree);
		detail::json_reader_impl<T> reader(t, tree);
		reflect_type<T>(reader, _first_ver);
	}
};

}} // namespace reveal { namespace serialize {
	
#endif // REFLECT_SERIALIZE_JSONREADER_HPP_