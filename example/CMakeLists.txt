cmake_minimum_required(VERSION 3.12...3.26)

project(parameter-example LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parameter-example main.cpp)
add_executable(parameter-client client.cpp)

add_subdirectory(./../lib param-parser)
target_link_libraries(parameter-example param-parser)
target_link_libraries(parameter-client param-parser)
include_directories(${LIB_INCLUDE_DIR})
set_target_properties(param-parser PROPERTIES LINKER_LANGUAGE CXX)
