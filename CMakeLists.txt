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
set(CMAKE_C_STANDARD 99)

# Set project version
set(PROJECT_VERSION "0.0.1-alpha")

# Add git hash
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include(AddGitHash)
add_git_hash()

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
include_directories(${CURSES_INCLUDE_DIR})

# PAM (Pluggable Authentication Modules)
find_package(PAM REQUIRED)

# spdlog
find_package(spdlog REQUIRED)

# XCB
find_package(XCB REQUIRED)

#### COMPILE ####
#---------------#

# Manage version
add_compile_definitions(__VERSION_STR="${PROJECT_VERSION}")

# Add source subdir
add_subdirectory(src)


#### GENERATE DOCUMENTATION ####
#------------------------------#

### Attribution for generating documentation:
### https://vicrucann.github.io/tutorials/quick-cmake-doxygen

## first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


#### INSTALL ####
#---------------#


#### TESTING ####
#---------------#
enable_testing()
add_subdirectory(tests)

#### PACKAGE ####
#---------------#
