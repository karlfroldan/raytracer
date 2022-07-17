cmake_minimum_required(VERSION 3.23)


add_library(rmath STATIC tuple.c)
target_link_libraries(rmath PRIVATE m)