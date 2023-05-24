target_sources(eloop_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/eloop.c)
target_sources(eloop_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_link_libraries(eloop_test PRIVATE eloop_lib)