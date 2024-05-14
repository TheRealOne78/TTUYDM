# Set CMAKE minimum version
cmake_minimum_required(VERSION 3.25)


#### PROJECT ####
#---------------#

# Set project name
project(ttuydm
  LANGUAGES C CXX)

# Set C++ standard to 2011
## Due to:
### * std::future
### * std::async
set(CMAKE_CXX_STANDARD 11)

# Set project version
set(PROJECT_VERSION "0.0.1-alpha")

# Set default build type
set(default_build_type "Release")

# If default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type: '${default_build_type}'")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the build type" FORCE)
endif()

# Set release options in the CMake cache
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# Export compile_commands.json by default
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#### DEPENDENCIES CHECK ####
#--------------------------#

# Import modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# ncurses
find_package(Curses REQUIRED)

# PAM (Pluggable Authentication Modules)
find_package(PAM REQUIRED)

# spdlog
find_package(spdlog REQUIRED)

# XCB
find_package(XCB REQUIRED)

#### COMPILE ####
#---------------#

# Manage version
add_compile_definitions(VERSION_STR="${PROJECT_VERSION}")

# Add source subdir
add_subdirectory(src)


#### GENERATE DOCUMENTATION ####
#------------------------------#


#### INSTALL ####
#---------------#


#### TESTING ####
#---------------#


#### PACKAGE ####
#---------------#
