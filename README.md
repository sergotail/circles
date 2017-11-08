Circles
=========
Testing assignment for DSSL

Uses Qt5 and GoogleTest

Requirements
------------
Minimum CMake required: 3.1.0

Minimum GCC version: GNU 4.8.5

Qt 5.9.2 used in development, other versions had not been tested

Build & Install
---------------
```bash
export CMAKE_PREFIX_PATH="path/to/qt5"
```

(e.g. export CMAKE_PREFIX_PATH="/opt/Qt/5.9.2/gcc_64") 

Another option is to set CMAKE_PREFIX_PATH variable in top-level CMakeLists.txt file

After setting CMAKE_PREFIX_PATH variable, run:

        $ mkdir build && cd build && cmake .. && make


Run
---
From build dir, run ./src/circles N, where N is a number of cirles randomly placed on the scene (e.g. ./src/circles 15)

Max N is 1000, default N is 50

Different settings available in utils.h, in class CircleUtils.

Run tests
---------
From build dir, run ./test/test_circles

