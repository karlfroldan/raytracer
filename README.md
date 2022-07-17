# Raytracer in C

Some important shell files include
1. `make` - run [cmake](https://cmake.org) and build the programs and test suite using ninja.
2. `runtests` - run all tests. Note that this project does not make use of `ctest` so all test filenames must conform to *_test.

### Dependencies:
1. cmake 2.23
2. ninja.
3. POSIX compliant C compiler (I'm using [clang](https://llvm.org)).