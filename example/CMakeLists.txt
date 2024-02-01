cmake_minimum_required(VERSION 3.12...3.26)

project(parameter-example LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parameter-example main.cpp)
target_link_libraries(parameter-example param-parser)

# Parameter client only works on UNIX platform for now,
# It's just an example of consuming an executable that implement param_parser.h, not very important
if (UNIX)
    add_executable(parameter-client client.cpp)
    target_link_libraries(parameter-client param-parser)
endif (UNIX)

include_directories(${LIB_INCLUDE_DIR})
set_target_properties(param-parser PROPERTIES LINKER_LANGUAGE CXX)
