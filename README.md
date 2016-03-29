# seqan cmake tutorial

## preliminaries

check if you have cmake installed by
```console
cmake --version
```
will deliver
```terminal
cmake version 3.0.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## setup tutorial

```console
mkdir ~/tutorials
cd ~/tutorials
```

## 01 Hello world with cmake

```console
mkdir ~/tutorials/test_hello_world
cd ~/tutorials/test_hello_world
```

### create hello.cpp

```c++
// ~/tutorials/test_hello_world/hello.cpp
#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
    return 0;
}
```

try to compile and run it

```console
g++ ~/tutorials/test_hello_world/hello.cpp
./a.out
```

```terminal
Hello World
```

### How to automate the build process?

We could use Makefiles.

```makefile
#~/tutorials/test_hello_world/Makefile

all:
	mkdir build
	g++ hello.cpp -o build/hello

clean:
	rm -r build
```

(notice that the indention must be tabs) and use it

```console
make
```

```terminal
mkdir build
g++ hello.cpp -o build/hello
```

but Makefiles are kinda hard to maintain and to program. (also platform specific)

### Using cmake as an abstraction layer

Creating a minimal cmake file.

```cmake
# ~/tutorials/test_hello_world/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(hello CXX)

# add the executable
add_executable(hello hello.cpp)
```

Now, we need a build folder to build the library.

```console
mkdir ~/tutorials/build
cd ~/tutorials/build
```

And now let us build the hello world program.

```console
cmake ../test_hello_world
```

```terminal
-- The CXX compiler identification is GNU 4.8.5
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

This only generated the Makefile, we will build it right now.

```console
make
```

```terminal
Scanning dependencies of target hello
[100%] Building CXX object CMakeFiles/hello.dir/hello.cpp.o
Linking CXX executable hello
[100%] Built target hello
```

Where to find the executable?

```console
ls ~/tutorials/build
```

```terminal
[...] hello [...]
```

executing the file

```console
./hello
```

```terminal
Hello World
```
