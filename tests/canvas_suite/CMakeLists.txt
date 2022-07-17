cmake_minimum_required(VERSION 3.23)

add_executable(colors_test colors_test.c)
add_executable(canvas_test canvas_test.c)

include_directories(AFTER ../../include)

target_link_libraries(colors_test PRIVATE raytracer)
target_link_libraries(canvas_test PRIVATE raytracer m)