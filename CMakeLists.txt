cmake_minimum_required(VERSION 3.26)
project(array C)

set(CMAKE_C_STANDARD 11)

add_executable(array main.c
        libs/algorithms/array/array.c
        libs/algorithms/array/array.h
        libs/algorithms/algorithms.c
        libs/algorithms/algorithms.h
)

add_subdirectory(libs)
target_link_libraries(array data_structures)
target_link_libraries(array algorithms)