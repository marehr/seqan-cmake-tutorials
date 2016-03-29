## 04 Linking libraries?

### Let us write our own shared library

```console
mkdir ~/tutorials/lib_factorial
cd ~/tutorials/lib_factorial
```

```c++
// ~/tutorials/lib_factorial/factorial.cpp

#include "factorial.h"
#include <stdlib.h>

size_t factorial(size_t n)
{
    size_t fac = 1;

    for(size_t i = 1; i < n; ++i)
    {
        fac *= i;
    }

    return fac;
}
```

```c++
// ~/tutorials/lib_factorial/factorial.h

#ifndef LIB_HEADER_FACTORIAL_H
#define LIB_HEADER_FACTORIAL_H

#include <stdlib.h>

/**
 * calculate n!
 */
size_t factorial(size_t n);

#endif // #ifndef LIB_HEADER_FACTORIAL_H
```

```cmake
# ~/tutorials/lib_factorial/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(factorial_lib CXX)

# build shared library
add_library(factorial_lib SHARED factorial.cpp factorial.h)
```

Notice the change, it is now a library.

### Append the shared library to the top-level CMakeLists.txt

```cmake
# ~/tutorials/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(test_hello_world)
add_subdirectory(test_factorial)

add_subdirectory(lib_factorial)
```

### Build the Library

```console
cd ~/tutorials/build
make
```

```terminal
[ 33%] Built target hello
[ 66%] Built target factorial
Scanning dependencies of target factorial_lib
[100%] Building CXX object lib_factorial/CMakeFiles/factorial_lib.dir/factorial.cpp.o
Linking CXX shared library ../lib/libfactorial_lib.so
[100%] Built target factorial_lib
```

Where is the library?

```console
ls ~/tutorials/lib/
```

```terminal
libfactorial_lib.so
```

### Create program which uses the shared library

```console
mkdir ~/tutorials/test_factorial_shared
cd ~/tutorials/test_factorial_shared
```

```c++
// ~/tutorials/test_factorial_shared/factorial_main.cpp

#include <factorial.h>
#include <iostream>

int main()
{
    size_t n = 6;
    std::cout << factorial(n) << " = factorial(" << n << ")" << std::endl;

    return 0;
}
```

```cmake
# ~/tutorials/test_factorial_shared/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(factorial_shared CXX)

# add the executable
add_executable(factorial_shared factorial_main.cpp)

# add shared library
target_link_libraries(factorial_shared factorial_lib)
```

### Add the project to the top-level CMakeLists.txt

```cmake
# ~/tutorials/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(test_hello_world)
add_subdirectory(test_factorial)

add_subdirectory(lib_factorial)
add_subdirectory(test_factorial_shared)
```

### Build the project

```console
cd ~/tutorials/build
make
```

```terminal
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/build
[ 25%] Built target hello
[ 50%] Built target factorial
[ 75%] Built target factorial_lib
Scanning dependencies of target factorial_shared
[100%] Building CXX object test_factorial_shared/CMakeFiles/factorial_shared.dir/factorial_main.cpp.o
/home/marehr/tutorials/test_factorial_shared/factorial_main.cpp:1:23: fatal error: factorial.h: No such file or directory
 #include <factorial.h>
                       ^
compilation terminated.
make[2]: *** [test_factorial_shared/CMakeFiles/factorial_shared.dir/factorial_main.cpp.o] Error 1
make[1]: *** [test_factorial_shared/CMakeFiles/factorial_shared.dir/all] Error 2
make: *** [all] Error 2
zsh: exit 2     make
```

Oh we forgot to announce the header files.

### Copy header file into a include folder

Our program which should use the shared library must know the function
signatures. Thus, we need to copy the header files into an include folder.

For that change the CMakeLists.txt

```cmake
# ~/tutorials/lib_factorial/CMakeLists.txt

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
```

This basically creates `~/tutorials/build/include/factorial_lib/` and copies the
`factorial.h` file into that folder.

### Include header files in test_factorial_shared

```cmake
# ~/tutorials/test_factorial_shared/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(factorial_shared CXX)

# header files of shared library
include_directories(${CMAKE_BINARY_DIR}/include/factorial_lib)

# add the executable
add_executable(factorial_shared factorial_main.cpp)

# add shared library
target_link_libraries(factorial_shared factorial_lib)
```

### Now build everything!

```console
cd ~/tutorials/build
make VERBOSE=1
```

```terminal
Linking CXX shared library ../lib/libfactorial_lib.so
cd /home/marehr/tutorials/build/lib_factorial && /usr/bin/cmake -E cmake_link_script CMakeFiles/factorial_lib.dir/link.txt --verbose=1
/usr/bin/c++  -fPIC   -shared -Wl,-soname,libfactorial_lib.so -o ../lib/libfactorial_lib.so CMakeFiles/factorial_lib.dir/factorial.cpp.o

Moving header files to include/factorial_lib/

[...]

[100%] Building CXX object test_factorial_shared/CMakeFiles/factorial_shared.dir/factorial_main.cpp.o

cd /home/marehr/tutorials/build/test_factorial_shared && /usr/bin/c++    -I/home/marehr/tutorials/build/include/factorial_lib    -o CMakeFiles/factorial_shared.dir/factorial_main.cpp.o -c /home/marehr/tutorials/test_factorial_shared/factorial_main.cpp

Linking CXX executable ../bin/factorial_shared

[...]

/usr/bin/c++      CMakeFiles/factorial_shared.dir/factorial_main.cpp.o  -o ../bin/factorial_shared -rdynamic ../lib/libfactorial_lib.so -Wl,-rpath,/home/marehr/tutorials/build/lib
```

### Execute it

```console
bin/factorial_shared
```

```terminal
120 = factorial(6)
```

Is it shared?

```console
ldd bin/factorial_shared
```

```terminal
linux-vdso.so.1 =>  (0x00007ffc8d1be000)
libfactorial_lib.so => /home/marehr/tutorials/build/lib/libfactorial_lib.so (0x00007fba5ee8c000)
libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fba5eb7f000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fba5e7ba000)
libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fba5e4b4000)
/lib64/ld-linux-x86-64.so.2 (0x00007fba5f08e000)
libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fba5e29d000)
```
