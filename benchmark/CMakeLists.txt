# ******************************************************************************
# 
# benchmark/CMakeLists.txt
#
# Benchmark CMake build script for reveal-cpp
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
	benchmark.serialization 
	gbenchmark_main.cpp
	serialization.cpp
)

target_link_libraries(benchmark.serialization  PUBLIC reveal-cpp benchmark)
add_test(benchmark.serialization benchmark.serialization)