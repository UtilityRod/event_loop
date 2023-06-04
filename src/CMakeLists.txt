target_include_directories(eloop_static PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources(eloop_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/eloop.c)

# target_sources(eloop_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.c)