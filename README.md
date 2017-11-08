# Circles
=========
Testing assignment for DSSL
Uses Qt5 and GoogleTest
Minimum CMake required: 3.1.0
Minimum GCC version: GNU 4.8.5

REQUIREMENTS
------------
Minimum CMake required: 3.1.0

Minimum GCC version: GNU 4.8.5

## Build & Install
------------------
export CMAKE_PREFIX_PATH="path/to/qt5" (e.g. export CMAKE_PREFIX_PATH="/opt/Qt/5.9.2/gcc_64") or set CMAKE_PREFIX_PATH variable in top-level CMakeLists.txt file

        $ mkdir build && cd build && cmake .. && make


## Run
From build dir, run ./src/circles N, where N is a number of cirles randomly placed on the scene (e.g. ./src/circles 15)

Max N is 500, default N is 50

## Run tests
From build dir, run ./test/test_cicles

