project(event_loop)
cmake_minimum_required(VERSION 3.13.0)

add_library(eloop_lib)
target_include_directories(eloop_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(eloop_test)

add_subdirectory(src)