// *****************************************************************************
// 
// reveal/null_visitor.hpp
//
// Use the null_visitor if you only plan on overriding a subset of the visitor
// functions.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once
#ifndef REVEAL_NULLVISITOR_H_
#define REVEAL_NULLVISITOR_H_

// ----------------------------------------------------------------------------
//
namespace reveal { 

class null_visitor
{
public:

	template<typename Child, typename Parent>
	null_visitor& member(char const*, Child Parent::*)
	{ return *this; }

	template<typename SizeFun, typename InsertFun>
	null_visitor& container(SizeFun, InsertFun)
	{ return *this; }

	template<typename SizeFun, typename InsertFun>
	null_visitor& string(SizeFun s, InsertFun i)
	{ return *this; }

	null_visitor& pod()
	{ return *this; }

	null_visitor& primitive()
	{ return *this; }
};

}

#endif // REVEAL_NULLVISITOR_H_