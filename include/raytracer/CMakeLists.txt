cmake_minimum_required(VERSION 3.23)

add_library(raytracer STATIC tuple.c canvas.c color.c
    raytracer_utils.c matrix.c matrix_transformations.c
    ray.c intersections.c sphere.c)
target_link_libraries(raytracer PRIVATE m)