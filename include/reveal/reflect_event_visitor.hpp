// *****************************************************************************
// 
// reveal/reflect_event_visitor.hpp
//
// Visitor that transforms reflection visits to higher level events.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_REFLECTEVENTVISITOR_H_
#define REVEAL_REFLECTEVENTVISITOR_H_

// ----------------------------------------------------------------------------
//
namespace reveal { 

template <typename Handler>
class reflect_event_visitor
{
public:

	template<typename Child, typename Parent>
	decltype(auto) member(char const* name, Child Parent::*member)
	{ 
		return static_cast<Handler*>(this)->on_member(name, member); 
	}

	template<typename SizeFun, typename InsertFun>
	decltype(auto) container(SizeFun size, InsertFun insert)
	{ 
		return static_cast<Handler*>(this)->on_container(size, insert); 
	}

	template<typename SizeFun, typename InsertFun>
	decltype(auto) string(SizeFun size, InsertFun insert)
	{
		return static_cast<Handler*>(this)->on_string(size, insert); 
	}

	decltype(auto) pod()
	{
		return static_cast<Handler*>(this)->on_pod(); 
	}

	decltype(auto) primitive()
	{ 
		return static_cast<Handler*>(this)->on_primitive(); 
	}

private:

};

}

#endif // REVEAL_REFLECTEVENTVISITOR_H_