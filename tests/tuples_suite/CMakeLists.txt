cmake_minimum_required(VERSION 3.23)

add_executable(point_test point_test.c)
add_executable(vector_test vector_test.c)

include_directories(AFTER ../../include)

target_link_libraries(point_test PRIVATE rmath)
target_link_libraries(vector_test PRIVATE rmath)