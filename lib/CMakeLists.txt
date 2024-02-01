cmake_minimum_required(VERSION 3.12...3.26)

project(param-parser LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# if(TARGET param-parser)
# message("param-parser is already defined")
# else()

# include_directories(${LIB_INCLUDE_DIR})
# add_library(param-parser SHARED param_parser.h)

# endif()

add_library(param-parser SHARED param_parser.h)