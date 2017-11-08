cmake_minimum_required(VERSION 3.1.0)

project(${TEST_PROJECT})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(TEST_SOURCE_FILES main.cpp
		      testcircles.cpp)

# wrap manually for correct moc work
qt5_wrap_cpp(widget_SRC ${HDR_ROOT}/widget.h)
qt5_wrap_cpp(interactingcirclescene_SRC ${HDR_ROOT}/interactingcirclescene.h)

add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES} ${SOURCE_FILES} ${interactingcirclescene_SRC} ${widget_SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets gtest)
