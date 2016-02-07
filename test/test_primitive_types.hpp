// *****************************************************************************
// 
// test/test_primitive_types.hpp
//
// Common primitive type for reflect-cpp tests.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#pragma once 
#ifndef REVEAL_TEST_PRIMITIVETYPES_HPP_
#define REVEAL_TEST_PRIMITIVETYPES_HPP_

#include <reveal/primitives.hpp>

// -----------------------------------------------------------------------------
//
struct primitives
{
	char 				char_;
	unsigned 			uchar_;
	signed char 		schar_;
	short 				short_;
	unsigned short 		ushort_;
	int 				int_;
	unsigned int 		uint_;
	long 				long_;
	unsigned long 		ulong_;
	long long 			llong_;
	unsigned long long 	ullong_;
	float 				float_;
	double 				double_;
};

inline bool operator==(primitives const& a, primitives const& b)
{
	return   
		a.char_			== b.char_	  &&	
		a.uchar_		== b.uchar_	  &&		
		a.schar_		== b.schar_	  &&		
		a.short_		== b.short_	  &&		
		a.ushort_		== b.ushort_  &&			
		a.int_			== b.int_	  &&	
		a.uint_			== b.uint_	  &&	
		a.long_			== b.long_	  &&	
		a.ulong_		== b.ulong_	  &&		
		a.llong_		== b.llong_	  &&			
		a.ullong_		== b.ullong_  &&			
		a.float_		== b.float_	  &&		
		a.double_		== b.double_
	;	
}

inline std::ostream& operator<<(std::ostream& out, primitives const& p)
{
	return out  
		<< p.char_	 << ", "
		<< p.uchar_	 << ", "
		<< p.schar_	 << ", "
		<< p.short_	 << ", "
		<< p.ushort_ << ", "	
		<< p.int_	 << ", "
		<< p.uint_	 << ", "
		<< p.long_	 << ", "
		<< p.ulong_	 << ", "
		<< p.llong_	 << ", "
		<< p.ullong_ << ", "	
		<< p.float_	 << ", "
		<< p.double_
	;	
}

// We don't use a contructor because we want the time to remain POD
inline primitives make_primitives_0s()
{
	primitives ret;
	std::memset(&ret, 0, sizeof(ret));
	return ret;
}

inline primitives make_primitives_values()
{
	primitives ret;
	ret.char_		 = '1';
	ret.uchar_		 = 2;
	ret.schar_		 = 3;
	ret.short_		 = 4;
	ret.ushort_		 = 5;
	ret.int_		 = 6;
	ret.uint_		 = 7;
	ret.long_		 = 8;
	ret.ulong_		 = 9;
	ret.llong_		 = 10;
	ret.ullong_		 = 11;
	ret.float_		 = 12;
	ret.double_		 = 13;
	return ret;
}

template<typename Visitor> constexpr inline
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<primitives>)
{
	return v
		.member("char_",	&primitives::char_)
		.member("uchar_",	&primitives::uchar_)
		.member("schar_",	&primitives::schar_)
		.member("short_",	&primitives::short_)
		.member("ushort_",	&primitives::ushort_)		
		.member("int_",		&primitives::int_)
		.member("uint_",	&primitives::uint_)
		.member("long_",	&primitives::long_)
		.member("ulong_",	&primitives::ulong_)
		.member("llong_",	&primitives::llong_)
		.member("ullong_",	&primitives::ullong_)
		.member("float_",	&primitives::float_)
		.member("double_",	&primitives::double_)
	 ;
}

#endif // REVEAL_TEST_PRIMITIVETYPES_HPP_