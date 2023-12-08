cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Core Gui OpenGLWidgets)

set(PROJECT_SOURCES
    main.cc
    views/mainwindow.h
    views/mainwindow.cc
    views/mainwindow.ui
    views/maze_canvas.h
    views/maze_canvas.cc
    views/cave_canvas.h
    views/cave_canvas.cc
    controllers/controller_singleton.cc
    controllers/controller_singleton.h
    models/maze_generator.h
    models/maze_generator.cc
    models/maze_parser.h
    models/maze_parser.cc
    models/maze.h
    models/maze.cc
    models/model.cc
    models/model.h
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)
