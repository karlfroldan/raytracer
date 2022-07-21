cmake_minimum_required(VERSION 3.23)

add_executable(matrix_test matrix_test.c)

include_directories(AFTER ../../include)

target_link_libraries(matrix_test PRIVATE raytracer m)