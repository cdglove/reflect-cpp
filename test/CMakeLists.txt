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

add_executable(
	test.primary 
	gtest_main.cpp
	simple_binary_reader_writer.cpp
	print_names.cpp
	json.cpp
	operators.cpp
)

target_link_libraries(test.primary PUBLIC reveal-cpp gtest)
add_test(test.primary test.primary)
set_property(TARGET test.primary APPEND PROPERTY COMPILE_DEFINITIONS "_SCL_SECURE_NO_WARNINGS")