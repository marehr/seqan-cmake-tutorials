cmake_minimum_required(VERSION 3.1)
project(factorial CXX)

# add the executable
add_executable(factorial factorial_main.cpp factorial.h)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTEST_FLAG=1")

# require c++11
#set_property(TARGET seqan_app PROPERTY CXX_STANDARD 11)
#set_property(TARGET seqan_app PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_features(factorial PRIVATE cxx_constexpr)

