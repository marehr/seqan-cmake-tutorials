cmake_minimum_required(VERSION 3.0)

project (build_all CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTEST_DEFINITION=1")

add_subdirectory(test_hello_world)
add_subdirectory(test_factorial)

add_subdirectory(lib_factorial)
add_subdirectory(test_factorial_shared)

add_subdirectory(seqan_app)
add_subdirectory(seqan_app2)
