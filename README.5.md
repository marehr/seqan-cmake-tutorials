## 05 How to include SeqAn.

### Download SeqAn and setup project

```console
cd ~/tutorials
git clone --depth 1 https://github.com/seqan/seqan
```

Note: `--depth 1` truncates the history

```terminal
Cloning into 'seqan'...
remote: Counting objects: 4388, done.
remote: Compressing objects: 100% (3570/3570), done.
remote: Total 4388 (delta 1207), reused 2227 (delta 654), pack-reused 0
Receiving objects: 100% (4388/4388), 96.60 MiB | 3.39 MiB/s, done.
Resolving deltas: 100% (1207/1207), done.
Checking connectivity... done.
```

```console
mkdir ~/tutorials/seqan_app
cd ~/tutorials/seqan_app
```

### A SeqAn app...

(just copied from a tutorial)

```c++
// ~/tutorials/seqan_app/seqan_app.cpp
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
# ~/tutorials/seqan_app/CMakeLists.txt

cmake_minimum_required(VERSION 3.1)
project(seqan_app)

# point to the headers
# Note: ${CMAKE_CURRENT_SOURCE_DIR}/../ is ~/tutorials/
# Note: SeqAn include file are in ~/tutorials/seqan/include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../[- fill in include path -])

# add the executable
add_executable(seqan_app seqan_app.cpp)

# require c++11
set_property(TARGET seqan_app PROPERTY CXX_STANDARD 11)
set_property(TARGET seqan_app PROPERTY CXX_STANDARD_REQUIRED ON)

# You don't have cmake 3.1? Comment out the above. And comment in the below.
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
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
```

### Build and execute the project

```console
cd ~/tutorials/build
make
```

```terminal
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/build
[ 20%] Built target hello
[ 40%] Built target factorial
[ 60%] Built target factorial_lib
[ 80%] Built target factorial_shared
Scanning dependencies of target seqan_app
[100%] Building CXX object seqan_app/CMakeFiles/seqan_app.dir/seqan_app.cpp.o
Linking CXX executable ../bin/seqan_app
[100%] Built target seqan_app
```

Error? Did you change the include path?

Execute the binary

```console
bin/seqan_app
```

```terminal
Score: -2
      0     .
        CD-FG-HC
        || || ||
        CDEFGAHC
```
