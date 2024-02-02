
add_executable(parameter-example main.cpp)
target_link_libraries(parameter-example param-parser)

# Parameter client only works on UNIX platform for now,
# It's just an example of consuming an executable that implement param_parser.h, not very important
if (UNIX)
    add_executable(parameter-client client.cpp)
    target_link_libraries(parameter-client param-parser)
endif (UNIX)
