# ******************************************************************************
# 
# CMakeLists.txt
#
# Master CMake build script for reveal-cpp
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
project (reveal-cpp)

###############################################################################
#
# Options
#
###############################################################################
option( REFLECT_BUILD_TESTS "Build the reveal-cpp project tests." ON)
option( REFLECT_BUILD_DOCS  "Allow build the reveal-cppREFLECT project docs." ON)

###############################################################################
#
# determine install path for CMake config files
#
###############################################################################
include(GNUInstallDirs)
if(WIN32 AND NOT CYGWIN)
	set(DEF_INSTALL_CMAKE_DIR CMake)
else()
	set(DEF_INSTALL_CMAKE_DIR lib/cmake/reveal-cpp)
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
# Configure packages
#
###############################################################################
include(contrib/cmaketools/external_git.cmake)

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
add_library(reveal-cpp INTERFACE)
target_sources(reveal-cpp INTERFACE ${PROJECT_HEADERS})
target_include_directories(reveal-cpp INTERFACE "include/")

###############################################################################
#
# See if w'ere testing.
#
###############################################################################
if(REFLECT_BUILD_TESTS)
  enable_testing()

  #############################################################################
  #
  # Add google test
  #
  #############################################################################
  include(contrib/cmaketools/DownloadProject.cmake)
  download_project(
    PROJ                googletest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG             master
  )

  # Prevent GoogleTest from overriding our compiler/linker options
  # when building with Visual Studio
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

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
    set_property(TARGET reveal-cpp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH_AND_OPTIONS})
  endif()
endif()

###############################################################################
#
# Export Targets
#
# (so reveal-cpp can be easily used by other CMake projects)
# [see http://www.cmake.org/Wiki/CMake/Tutorials/How_to_create_a_ProjectConfig.cmake_file]
#
###############################################################################

# Add all targets to the build-tree export set
export(TARGETS reveal-cpp
	FILE "${PROJECT_BINARY_DIR}/revealCppTargets.cmake")
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE reveal-cpp)
# Create the revealCppConfig.cmake and revealCppConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
# ... for the build tree
configure_file(revealCppConfig.cmake.in
	"${PROJECT_BINARY_DIR}/revealCppConfig.cmake" @ONLY)
# ... for the install tree
configure_file(revealCppConfig.cmake.in
	"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/revealCppConfig.cmake" @ONLY)
# ... for both
configure_file(revealCppConfig.cmake.in
    "${PROJECT_BINARY_DIR}/revealCppConfigVersion.cmake" @ONLY)
# Install the revealCppConfig.cmake
install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/revealCppConfig.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev)
# Install the export set for use with the install-tree
# install(EXPORT revealCppConfigTargets
#     DESTINATION "${INSTALL_CMAKE_DIR}"
#     COMPONENT dev)



	