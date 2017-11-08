set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_MAIN ${SRC_ROOT}/main.cpp)

# wrap manually for correct moc work
qt5_wrap_cpp(widget_SRC ${HDR_ROOT}/widget.h)
qt5_wrap_cpp(interactingcirclescene_SRC ${HDR_ROOT}/interactingcirclescene.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SOURCE_MAIN} ${interactingcirclescene_SRC} ${widget_SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
