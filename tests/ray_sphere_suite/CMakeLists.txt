cmake_minimum_required(VERSION 3.23)

add_executable(ray_test rays_test.c)
add_executable(spheres_test spheres_test.c)
# add_executable(tuple_arithmetic_test tuple_arithmetic_test.c)


include_directories(AFTER ../../include)

target_link_libraries(ray_test PRIVATE raytracer)
target_link_libraries(spheres_test PRIVATE raytracer)
# target_link_libraries(tuple_arithmetic_test PRIVATE raytracer m)
