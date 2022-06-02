 # ---------------------------------------------------------------------
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the Apache License version 2 as
 # published by the Free Software Foundation.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 # See the Apache License 2.0 for more details.
 #
 # You should have received a copy of the Apache License
 # along with this program.  If not, see
 # https://www.apache.org/licenses/LICENSE-2.0.
 #
 # Copyright (C) 2021 Ajeet Singh Yadav [ er.ajeetsinghyadav@gmail.com ]
 #
 # Author:    Ajeet Singh Yadav
 # Created:   JAN-2021
 #
 # Autodoc:   yes
 # ----------------------------------------------------------------------

# CMake version setting
cmake_minimum_required(VERSION 3.5)
if(${CMAKE_VERSION} VERSION_LESS 3.19)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.19)
endif()

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)


# Set project name and version
set(PROJECT_NAME supernova)
project(supernova
    VERSION 1.0.0.0
    DESCRIPTION "Robotics Simulation Software"
    LANGUAGES CXX
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C++17 standard, using new CMake variables.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS ${LOC_PATH})
    message(FATAL_ERROR "You cannot build in a source directory
        (or any directory with a CMakeLists.txt file).
        Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles."
    )
endif()

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

# Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET_ARCHITECTURE "x64")

# CMake helper module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Include cmake modules

# Register general cmake command
include(${CMAKE_MODULE_PATH}/Custom.cmake)
# Set policies
set_policy(CMP0054 NEW) # ENABLE CMP0054: Only interpret if() arguments as variables or keywords when unquoted.
set_policy(CMP0042 NEW) # ENABLE CMP0042: MACOSX_RPATH is enabled by default.
set_policy(CMP0063 NEW) # ENABLE CMP0063: Honor visibility properties for all target types.
set_policy(CMP0077 NEW) # ENABLE CMP0077: option() honors normal variables

include(${CMAKE_MODULE_PATH}/StandardProjectSettings.cmake)
include(${CMAKE_MODULE_PATH}/PreventInSourceBuilds.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_11)
message("---- compiler id: ${CMAKE_CXX_COMPILER_ID}----------")

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" ON)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Enable cache system
include(${CMAKE_MODULE_PATH}/CCache.cmake)

# Standard compiler warnings
include(${CMAKE_MODULE_PATH}/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(${CMAKE_MODULE_PATH}/Sanitizers.cmake)
enable_sanitizers(project_options)

# Enable doxygen
include(${CMAKE_MODULE_PATH}/Doxygen.cmake)
enable_doxygen()

# Enable static code analyazers tools options
include(${CMAKE_MODULE_PATH}/Cppcheck.cmake)
include(${CMAKE_MODULE_PATH}/ClangTidy.cmake)

# Include Qt
include(${CMAKE_MODULE_PATH}/FindQt.cmake)

# Enable the testing
option(ENABLE_TESTING "Enable testing and building the tests." ON)
if(ENABLE_TESTING)
    #include(CTest)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# Set source and header dirs
set(SUPERNOVA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/supernova/include)
set(SUPERNOVA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/supernova/src)
set(SN_SANDBOX_SOURCE_DIR ${PROJECT_SOURCE_DIR}/sandbox/src)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)

# Set project folders
set(SN_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(SUPERNOVA_DIR ${PROJECT_SOURCE_DIR}/supernova)
set(SN_ASSEST_DIR ${PROJECT_SOURCE_DIR}/supernova/assest)
set(SN_SANDBOX_DIR ${PROJECT_SOURCE_DIR}/sandbox)
set(SN_TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)
set(SN_TEST_DATA_DIR ${PROJECT_SOURCE_DIR}/testdata)
set(SN_BUILD_DIR ${PROJECT_BINARY_DIR})

# Configuration header
configure_file (
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/configuration.h.in"
    "${PROJECT_BINARY_DIR}/generated_headers/configuration.h"
)
include_directories(${PROJECT_BINARY_DIR})

#--------------------------------------------------------------------
# Sub directories
#--------------------------------------------------------------------
add_subdirectory(src/log)
