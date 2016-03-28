cmake_minimum_required(VERSION 3.0)
project(factorial_shared)


# header files of shared library
include_directories(${CMAKE_BINARY_DIR}/include/factorial_lib)

# add the executable
add_executable(factorial_shared factorial_main.cpp)

# add shared library
target_link_libraries(factorial_shared factorial_lib)

