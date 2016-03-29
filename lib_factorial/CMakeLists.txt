cmake_minimum_required(VERSION 3.0)
project(factorial_lib CXX)

# build shared library
add_library(factorial_lib SHARED factorial.cpp factorial.h)

# copy header files
add_custom_command(TARGET factorial_lib POST_BUILD
  COMMENT "Moving header files to include/factorial_lib/"
  COMMAND ${CMAKE_COMMAND} ARGS -E
    make_directory ${CMAKE_BINARY_DIR}/include/factorial_lib/
  COMMAND ${CMAKE_COMMAND} ARGS -E
    copy ${CMAKE_CURRENT_SOURCE_DIR}/factorial.h
         ${CMAKE_BINARY_DIR}/include/factorial_lib/factorial.h)


