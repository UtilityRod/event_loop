project(event_loop)
cmake_minimum_required(VERSION 3.13.0)

add_library(eloop_lib)
add_executable(eloop_test)

add_subdirectory(deps)
add_subdirectory(src)

target_link_libraries(eloop_lib dstruct_static pthread)
target_link_libraries(eloop_test eloop_lib)