# ******************************************************************************
# 
# test/CMakeLists.txt
#
# Tests CMake build script for reveal-cpp
#
# Copyright Chris Glover 2016
#
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#
# *****************************************************************************

cmake_minimum_required(VERSION 3.2)

function(create_test test_name test_source test_defines)
	add_executable(${test_name} ${test_source})
	target_link_libraries(${test_name} PUBLIC reveal-cpp )
	add_test(${test_name} ${test_name})
	set_property(TARGET ${test_name} APPEND PROPERTY COMPILE_DEFINITIONS ${test_defines})	
	if(MSVC)
		set_property(TARGET ${test_name} APPEND PROPERTY COMPILE_DEFINITIONS "_SCL_SECURE_NO_WARNINGS")
		add_definitions( "/wd4459" )
	endif()
endfunction(create_test)

create_test(test.print_names print_names.cpp "")
create_test(test.simple_binary simple_binary_reader_writer.cpp "")
create_test(test.build_tuple build_tuple.cpp "")