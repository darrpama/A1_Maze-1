cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Core Gui OpenGLWidgets)

set(PROJECT_SOURCES
    ../main.cc
    mainwindow.h
    mainwindow.cc
    mainwindow.ui
    maze_canvas.h
    maze_canvas.cc
    cave_canvas.h
    cave_canvas.cc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_subdirectory(../controllers ${CMAKE_CURRENT_BINARY_DIR}/controllers)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    MazeController
)
