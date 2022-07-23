cmake_minimum_required(VERSION 3.23)

add_executable(ray_test rays_test.c)
add_executable(spheres_test spheres_test.c)
add_executable(intersections_test intersections_test.c)


include_directories(AFTER ../../include)

target_link_libraries(ray_test PRIVATE raytracer)
target_link_libraries(spheres_test PRIVATE raytracer)
target_link_libraries(intersections_test PRIVATE raytracer m)
