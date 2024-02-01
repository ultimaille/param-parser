cmake_minimum_required(VERSION 3.12...3.26)

project(param-parser-lib LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(example)

# option(BUILD_EXAMPLE "BUILD_EXAMPLE" OFF)
# if (BUILD_EXAMPLE)
#     add_subdirectory(example)
# endif(BUILD_EXAMPLE)