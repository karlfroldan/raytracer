cmake_minimum_required(VERSION 3.23)
project(raytracer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -Wall -W")

add_subdirectory(include/raytracer)



include_directories(AFTER include)

add_executable(projectile apps/projectile/main.c)
add_executable(clock apps/clock/main.c)
add_executable(silhouette apps/silhouette/main.c)

target_link_libraries(projectile PRIVATE raytracer m)
target_link_libraries(clock PRIVATE raytracer m)
target_link_libraries(silhouette PRIVATE raytracer m)

enable_testing()

# The test files.
add_subdirectory(tests)

