cmake_minimum_required(VERSION 3.23)

add_executable(point_test point_test.c)
add_executable(vector_test vector_test.c)
add_executable(tuple_arithmetic_test tuple_arithmetic_test.c)


include_directories(AFTER ../../include)

target_link_libraries(point_test PRIVATE raytracer)
target_link_libraries(vector_test PRIVATE raytracer)
target_link_libraries(tuple_arithmetic_test PRIVATE raytracer m)

# add_test(NAME point_test)
# add_test(NAME vector_test)
# add_test(NAME tuple_arithmetic_test)

add_test(Point_Test point_test)
add_test(Vector_Test vector_test)
add_test(Tuple_Arithmetic_Test tuple_arithmetic_test)