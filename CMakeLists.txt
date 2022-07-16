cmake_minimum_required(VERSION 3.23)
project(raytracer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -Wall -W")

add_subdirectory(include/rmath)

# The test files.
add_subdirectory(tests)

include_directories(AFTER include)

add_executable(sample apps/sample.c)

target_link_libraries(sample PRIVATE rmath)