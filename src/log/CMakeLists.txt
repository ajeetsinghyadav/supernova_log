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
# Created:   May-2021
#
# Autodoc:   yes
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# CMake version setting
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
if(${CMAKE_VERSION} VERSION_LESS 3.19)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.19)
endif()

project(SupernovaLog)

# ----------------------------------------------------------------------
# Set headers
# ----------------------------------------------------------------------
set(SUPERNOVA_LOG_HEADERS
	src/logging_attributes.h
    src/text_color.h
    src/log_message_sink.h
    src/logger.h
)

# ----------------------------------------------------------------------
# Set sources
# ----------------------------------------------------------------------
set (SUPERNOVA_LOG_SOURCES
	src/logging_attributes.cpp
    src/text_color.cpp
    src/log_message_sink.cpp
    src/logger.cpp
)

# ----------------------------------------------------------------------
# Define the library & create an alias
# ----------------------------------------------------------------------
add_library(${PROJECT_NAME} ${SUPERNOVA_LOGHEADERS}  ${SUPERNOVA_LOG_SOURCES})
add_library(Supernova::Log ALIAS ${PROJECT_NAME})

# ----------------------------------------------------------------------
# Set include directories
# ----------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

# ----------------------------------------------------------------------
# Subdirectories & linking
# ----------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    project_options
    project_warnings
)
