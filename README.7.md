## 07 Compiler Change?

So that's nice but that is with multiple compilers?

### Create multiple build folders

```console
mkdir ~/tutorials/builds/
mkdir ~/tutorials/builds/gcc
mkdir ~/tutorials/builds/clang
```

### What where the parameters again?

#### gcc
```console
cd ~/tutorials/builds/gcc
touch cm.sh
chmod +x cm.sh
```

I usually create a little shell script to remember what parameters I used to
generate the makefiles.

```shell
#!/usr/bin/env bash
# ~/tutorials/builds/gcc/cm.sh

rm -r CMake*
cmake -DCMAKE_CXX_COMPILER=$(which g++) ../..
```

generate make files

```console
./cm.sh
```

```terminal
rm: cannot remove ‘CMake*’: No such file or directory
-- The CXX compiler identification is GNU 4.8.5
-- Check for working CXX compiler: /usr/bin/g++
-- Check for working CXX compiler: /usr/bin/g++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Warning (dev) at seqan/util/cmake/FindSeqAn.cmake:145 (message):
  GCC version (4.8.5) should be at least 4.9! Anything below is untested.
Call Stack (most recent call first):
  seqan_app2/CMakeLists.txt:22 (find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Looking for C++ include execinfo.h
-- Looking for C++ include execinfo.h - found
--   Determined version is 2.1.1
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/builds/gcc
```

building with gcc

```console
make VERBOSE=1
```

```terminal
[...]
/usr/bin/g++      CMakeFiles/hello.dir/hello.cpp.o  -o ../bin/hello -rdynamic
[...]
```

executing...

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

#### clang
```console
cd ~/tutorials/builds/clang
touch cm.sh
chmod +x cm.sh
```

```shell
#!/usr/bin/env bash
# ~/tutorials/builds/clang/cm.sh

rm -r CMake*
cmake -DCMAKE_CXX_COMPILER=$(which clang++) ../..
```

generate make files

```console
./cm.sh
```

```terminal
rm: cannot remove ‘CMake*’: No such file or directory
-- The CXX compiler identification is Clang 3.6.0
-- Check for working CXX compiler: /usr/bin/clang++-3.6
-- Check for working CXX compiler: /usr/bin/clang++-3.6 -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Looking for C++ include execinfo.h
-- Looking for C++ include execinfo.h - found
--   Determined version is 2.1.1
-- Configuring done
-- Generating done
-- Build files have been written to: /home/marehr/tutorials/builds/clang
```

building with gcc

```console
make VERBOSE=1
```

```terminal
[...]
/usr/bin/clang++-3.6      CMakeFiles/hello.dir/hello.cpp.o  -o ../bin/hello -rdynamic
[...]
```

executing...

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

----------

[prev](README.6.md)
