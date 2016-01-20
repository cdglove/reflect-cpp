# ******************************************************************************
# 
# CMakeLists.txt
#
# Master CMake build script for reflect-cpp
#
# Copyright Chris Glover 2016
#
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#
# *****************************************************************************

cmake_minimum_required(VERSION 3.2)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project (reflect-cpp)

###############################################################################
#
# Options
#
###############################################################################
option( REFLECT_BUILD_TESTS "Build the reflect-cpp project tests." ON)
option( REFLECT_BUILD_DOCS  "Allow build the reflect-cppREFLECT project docs." ON)

###############################################################################
#
# determine install path for CMake config files
#
###############################################################################
include(GNUInstallDirs)
if(WIN32 AND NOT CYGWIN)
	set(DEF_INSTALL_CMAKE_DIR CMake)
else()
	set(DEF_INSTALL_CMAKE_DIR lib/cmake/reflect-cpp)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative cmake install path absolute (needed later on)
if(NOT IS_ABSOLUTE "${INSTALL_CMAKE_DIR}")
	set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}")
endif()

###############################################################################
#
# Configure CMake
#
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)

###############################################################################
#
# If using IWUY, we generate from fake cpp files to compile.  Their only`
# job is to include the corresponding header file.
#
###############################################################################
if(CHECK_INCLUDES_VIA_IWYU)
  file(GLOB_RECURSE PROJECT_HEADERS_RELATIVE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.hpp)
  foreach(f IN ITEMS ${PROJECT_HEADERS_RELATIVE})
    string(REPLACE ".hpp" ".cpp" s ${f})
    file(WRITE "${PROJECT_BINARY_DIR}/gen/${s}" "#include \"${f}\"")
  endforeach(f)
  file(GLOB_RECURSE PROJECT_GENERATED_SOURCES ${PROJECT_BINARY_DIR}/gen/*.cpp)
endif()

###############################################################################
#
# Find our project files
#
###############################################################################
file(GLOB_RECURSE PROJECT_HEADERS include/*.hpp)
add_library(reflect-cpp INTERFACE)
target_sources(reflect-cpp INTERFACE ${PROJECT_HEADERS})
target_include_directories(reflect-cpp INTERFACE "include/")

if(REFLECT_BUILD_TESTS)
  enable_testing()
	add_subdirectory(test)
endif()

# no docs at the moment
# if(REFLECT_BUILD_DOCS)
# 	add_subdirectory(doc)
# endif()

###############################################################################
#
# Enable IWYU
#
###############################################################################
if(CHECK_INCLUDES_VIA_IWYU)
  find_program(IWYU_PATH NAMES include-what-you-use iwyu)
  if(IWYU_PATH)
    set(IWYU_PATH_AND_OPTIONS ${IWYU_PATH}
      -Xiwyu --mapping_file=${IWYU_MAPFILE_DIR}gcc.stl.headers.imp
      -Xiwyu --mapping_file=${IWYU_MAPFILE_DIR}boost-all.imp
      -Xiwyu --mapping_file=${IWYU_MAPFILE_DIR}boost-all-private.imp
    )
    set_property(TARGET reflect-cpp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH_AND_OPTIONS})
  endif()
endif()

###############################################################################
#
# Export Targets
#
# (so reflect-cpp can be easily used by other CMake projects)
# [see http://www.cmake.org/Wiki/CMake/Tutorials/How_to_create_a_ProjectConfig.cmake_file]
#
###############################################################################

# Add all targets to the build-tree export set
export(TARGETS reflect-cpp
	FILE "${PROJECT_BINARY_DIR}/reflectCppTargets.cmake")
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE reflect-cpp)
# Create the reflectCppConfig.cmake and reflectCppConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
# ... for the build tree
configure_file(reflectCppConfig.cmake.in
	"${PROJECT_BINARY_DIR}/reflectCppConfig.cmake" @ONLY)
# ... for the install tree
configure_file(reflectCppConfig.cmake.in
	"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/reflectCppConfig.cmake" @ONLY)
# ... for both
configure_file(reflectCppConfig.cmake.in
    "${PROJECT_BINARY_DIR}/reflectCppConfigVersion.cmake" @ONLY)
# Install the reflectCppConfig.cmake
install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/reflectCppConfig.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev)
# Install the export set for use with the install-tree
# install(EXPORT reflectCppConfigTargets
#     DESTINATION "${INSTALL_CMAKE_DIR}"
#     COMPONENT dev)



	