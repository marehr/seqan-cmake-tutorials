cmake_minimum_required(VERSION 3.1)
project(seqan_app CXX)

# point to the headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../seqan/include)

# add the executable
add_executable(seqan_app seqan_app.cpp)

# require c++14
set_property(TARGET seqan_app PROPERTY CXX_STANDARD 14)
set_property(TARGET seqan_app PROPERTY CXX_STANDARD_REQUIRED ON)
