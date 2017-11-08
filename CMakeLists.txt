cmake_minimum_required(VERSION 3.1.0)

project(circles)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_THREAD_PREFER_PTHREAD)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)

#set(CMAKE_PREFIX_PATH /opt/Qt5.9.2/5.9.2/gcc_64)

# Use native optimizations
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_OPT_ARCH_NATIVE_SUPPORTED)
if (COMPILER_OPT_ARCH_NATIVE_SUPPORTED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
endif()

find_package(Qt5 REQUIRED Widgets)

set(SRC_ROOT "${PROJECT_SOURCE_DIR}/src")
set(HDR_ROOT "${PROJECT_SOURCE_DIR}/include")
set(TST_ROOT "${PROJECT_SOURCE_DIR}/test")
set(THIRD_PARTY_ROOT "${PROJECT_SOURCE_DIR}/third-party")

set(SOURCE_FILES ${SRC_ROOT}/circle.cpp
		 ${SRC_ROOT}/interactingcircle.cpp
		 ${SRC_ROOT}/graphicscircleitem.cpp
		 ${SRC_ROOT}/interactingcirclelist.cpp)

set(interactingcirclescene_SRC ${SRC_ROOT}/interactingcirclescene.cpp)
set(widget_SRC ${SRC_ROOT}/widget.cpp)

include_directories(${HDR_ROOT})

add_subdirectory(${SRC_ROOT})


# GoogleTest
set(BUILD_GTEST ON CACHE BOOL "Builds the googletest subproject")
set(BUILD_GMOCK ON CACHE BOOL "Builds the googlemock subproject")
set(gtest_disable_pthreads ON CACHE BOOL "Disable uses of pthreads in gtest.")
add_subdirectory(${THIRD_PARTY_ROOT}/googletest-release-1.8.0)

# Tests
set(TEST_PROJECT test_${PROJECT_NAME})
add_test(NAME ${TEST_PROJECT} COMMAND ${TEST_PROJECT})
add_subdirectory(${TST_ROOT})
enable_testing()
