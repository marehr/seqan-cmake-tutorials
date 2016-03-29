## 06 How to include SeqAn (more complex)

### setup project

```console
mkdir ~/tutorials/seqan_app2
cd ~/tutorials/seqan_app2
```

### A SeqAn app...

(just copied from a tutorial)

```c++
// ~/tutorials/seqan_app2/seqan_app.cpp
#include <iostream>
#include <seqan/align.h>

using namespace seqan;

int main()
{
    typedef String<char> TSequence;                 // sequence type
    typedef Align<TSequence, ArrayGaps> TAlign;     // align type

    TSequence seq1 = "CDFGHC";
    TSequence seq2 = "CDEFGAHC";

    TAlign align;
    resize(rows(align), 2);
    assignSource(row(align, 0), seq1);
    assignSource(row(align, 1), seq2);

    int score = globalAlignment(align, Score<int, Simple>(0, -1, -1));
    std::cout << "Score: " << score << std::endl;
    std::cout << align << std::endl;

    return 0;
}
```

```cmake
cmake_minimum_required(VERSION 3.1)
project(seqan_app2)

# Add the executable
add_executable (seqan_app2 seqan_app.cpp)

# Require C++11
target_compile_features(seqan_app2 PRIVATE cxx_constexpr)

# You don't have cmake 3.1? Comment out the above. And comment in the below.
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CXX11_FOUND TRUE)

# Set paths for FindSeqAn.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../seqan/util/cmake")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../seqan/include")

# Use SeqAn module
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
```

### Add project to top-level CMakeLists.txt

```cmake
# ~/tutorials/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

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
```

### Build and execute the project

```console
cd ~/tutorials/build
make
```

```terminal
CMake Warning (dev) at seqan/util/cmake/FindSeqAn.cmake:145 (message):
  GCC version (4.8.5) should be at least 4.9! Anything below is untested.
Call Stack (most recent call first):
  seqan_app2/CMakeLists.txt:20 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Looking for C++ include execinfo.h
-- Looking for C++ include execinfo.h - found
--   Determined version is 2.1.1
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/build
[ 16%] Built target hello
[ 33%] Built target factorial
[ 50%] Built target factorial_lib
[ 66%] Built target factorial_shared
[ 83%] Built target seqan_app
Scanning dependencies of target seqan_app2
[100%] Building CXX object seqan_app2/CMakeFiles/seqan_app2.dir/seqan_app.cpp.o
Linking CXX executable ../bin/seqan_app2
[100%] Built target seqan_app2
```

Execute the binary

```console
bin/seqan_app2
```

```terminal
Score: -2
      0     .
        CD-FG-HC
        || || ||
        CDEFGAHC
```
