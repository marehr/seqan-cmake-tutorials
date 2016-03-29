## 02 Slightly more difficult example with cmake

```console
mkdir ~/tutorials/test_factorial
cd ~/tutorials/test_factorial
```

### create factorial_main.cpp and factorial.h

```c++
// ~/tutorials/test_factorial/factorial_main.cpp

#include "factorial.h"
#include <iostream>

int main()
{
    size_t n = 6;
    std::cout << factorial(n) << " = factorial(" << n << ")" << std::endl;

    return 0;
}

```

```c++
// ~/tutorials/test_factorial/factorial.h

#ifndef TEST_HEADER_FACTORIAL_H
#define TEST_HEADER_FACTORIAL_H

#include <stdlib.h>

/**
 * calculate n!
 */
size_t factorial(size_t n)
{
    size_t fac = 1;

    // fill in your code

    return fac;
}

#endif // #ifndef TEST_HEADER_FACTORIAL_H
```

### create CMakeLists.txt

```cmake
# ~/tutorials/test_factorial/CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(factorial)

# add the executable
add_executable(factorial [- fill in the source files -])
```

### build the source code

clean the build folder

```console
cd ~/tutorials/build
rm -r *
```
generate the makefiles

```console
cmake [- fill in the path -]
```

```terminal
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/build
```

build the source files

```console
make VERBOSE=1
```

```terminal
/usr/bin/cmake -H/home/marehr/tutorials/test_factorial -B/home/marehr/tutorials/build --check-build-system CMakeFiles/Makefile.cmake 0
/usr/bin/cmake -E cmake_progress_start /home/marehr/tutorials/build/CMakeFiles /home/marehr/tutorials/build/CMakeFiles/progress.marks
make -f CMakeFiles/Makefile2 all
make[1]: Entering directory `/home/marehr/tutorials/build'
make -f CMakeFiles/factorial.dir/build.make CMakeFiles/factorial.dir/depend
make[2]: Entering directory `/home/marehr/tutorials/build'
cd /home/marehr/tutorials/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/marehr/tutorials/test_factorial /home/marehr/tutorials/test_factorial /home/marehr/tutorials/build /home/marehr/tutorials/build /home/marehr/tutorials/build/CMakeFiles/factorial.dir/DependInfo.cmake --color=
Dependee "/home/marehr/tutorials/build/CMakeFiles/factorial.dir/DependInfo.cmake" is newer than depender "/home/marehr/tutorials/build/CMakeFiles/factorial.dir/depend.internal".
Dependee "/home/marehr/tutorials/build/CMakeFiles/CMakeDirectoryInformation.cmake" is newer than depender "/home/marehr/tutorials/build/CMakeFiles/factorial.dir/depend.internal".
Scanning dependencies of target factorial
make[2]: Leaving directory `/home/marehr/tutorials/build'
make -f CMakeFiles/factorial.dir/build.make CMakeFiles/factorial.dir/build
make[2]: Entering directory `/home/marehr/tutorials/build'
/usr/bin/cmake -E cmake_progress_report /home/marehr/tutorials/build/CMakeFiles 1
[100%] Building CXX object CMakeFiles/factorial.dir/factorial_main.cpp.o

/usr/bin/c++     -o CMakeFiles/factorial.dir/factorial_main.cpp.o -c /home/marehr/tutorials/test_factorial/factorial_main.cpp

Linking CXX executable factorial
/usr/bin/cmake -E cmake_link_script CMakeFiles/factorial.dir/link.txt --verbose=1

/usr/bin/c++      CMakeFiles/factorial.dir/factorial_main.cpp.o  -o factorial -rdynamic

make[2]: Leaving directory `/home/marehr/tutorials/build'
/usr/bin/cmake -E cmake_progress_report /home/marehr/tutorials/build/CMakeFiles  1
[100%] Built target factorial
make[1]: Leaving directory `/home/marehr/tutorials/build'
/usr/bin/cmake -E cmake_progress_start /home/marehr/tutorials/build/CMakeFiles 0
```

execute the binary

```console
./factorial
```

```terminal
120 = factorial(6)
```
