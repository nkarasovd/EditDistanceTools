cmake_minimum_required(VERSION 3.4...3.18)
project(edit_distance_tools)

add_subdirectory(pybind11)
pybind11_add_module(edit_distance_tools src/main.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(edit_distance_tools
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
