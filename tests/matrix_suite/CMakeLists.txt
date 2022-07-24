cmake_minimum_required(VERSION 3.23)

add_executable(matrix_test matrix_test.c)
add_executable(matrix_transform_test matrix_transform_test.c)

include_directories(AFTER ../../include)

target_link_libraries(matrix_test PRIVATE raytracer m)
target_link_libraries(matrix_transform_test PRIVATE raytracer m)

add_test(Matrix_Test matrix_test)
add_test(Matrix_Transform_Test matrix_transform_test)