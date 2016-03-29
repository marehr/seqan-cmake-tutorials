cmake_minimum_required(VERSION 3.1)
project(seqan_app2)

# Add the executable
add_executable (seqan_app2 seqan_app.cpp)

# Require C++11
target_compile_features(seqan_app2 PRIVATE cxx_constexpr)
set(CXX11_FOUND TRUE)

# Set paths for FindSeqAn.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../seqan/util/cmake")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../seqan/include")

# Use SeqAn module
find_package (OpenMP)
find_package (SeqAn REQUIRED)

# Was SeqAn included?
if (NOT (SEQAN_FOUND))
    message (FATAL_ERROR "SeqAn not found")
endif ()

# Add include directories set by find_package (SeqAn).
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add dependencies found by find_package (SeqAn).
target_link_libraries (seqan_app2 ${SEQAN_LIBRARIES})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

