cmake_minimum_required(VERSION 3.23)

add_library(raytracer STATIC tuple.c canvas.c color.c
    raytracer_utils.c)
target_link_libraries(raytracer PRIVATE m)