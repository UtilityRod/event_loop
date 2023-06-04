project(event_loop)
cmake_minimum_required(VERSION 3.13.0)

add_library(eloop_static STATIC EXCLUDE_FROM_ALL)
add_subdirectory(deps)
target_include_directories(eloop_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(eloop_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/eloop.c)
target_link_libraries(eloop_static dstruct_static pthread)

# add_executable(eloop_test)
# target_link_libraries(eloop_test eloop_lib)