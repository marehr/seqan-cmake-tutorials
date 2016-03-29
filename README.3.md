## 03 Multiple targets

That's cool, but we had to clean the build directory. Can we build all at once?

### create top-level CMakeLists.txt

```cmake
# ~/tutorials/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

add_subdirectory(test_hello_world)
add_subdirectory(test_factorial)
```

### build all targets

clean build folder

```console
cd ~/tutoials/build
```

generate makefiles

```console
cmake ..
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

make binaries

```console
make
```

```terminal
Scanning dependencies of target hello
[ 50%] Building CXX object test_hello_world/CMakeFiles/hello.dir/hello.cpp.o
Linking CXX executable hello
[ 50%] Built target hello
Scanning dependencies of target factorial
[100%] Building CXX object test_factorial/CMakeFiles/factorial.dir/factorial_main.cpp.o
Linking CXX executable factorial
[100%] Built target factorial
```

building all binaries takes to long? you can also cherry-pick.

```console
make factorial
```

```terminal
[100%] Built target factorial
```

### Where are the binaries?

```console
cd ~/tutorials/build/
ls ~/tutorials/build/
```

```terminal
CMakeCache.txt  CMakeFiles  cmake_install.cmake  Makefile  test_factorial  test_hello_world
```

They are in their respective folder.

```console
test_factorial/factorial
test_hello_world/hello
```

```terminal
120 = factorial(6)
Hello World
```

### Change binaries folder.

One folder would be nicer. So change the top-level CMakeLists.txt

```cmake
# ~/tutorials/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(test_hello_world)
add_subdirectory(test_factorial)
```

rebuild the sources

```console
cd ~/tutorials/build
make
```

```terminal
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/build
Linking CXX executable ../bin/hello
[ 50%] Built target hello
Linking CXX executable ../bin/factorial
[100%] Built target factorial
```

The source are now in `~/tutorials/build/bin`.

```console
ls ~/tutorials/build/bin
```

```terminal
factorial  hello
```

Executing the binaries

```console
bin/factorial
bin/hello
```

```terminal
120 = factorial(6)
Hello World
```
