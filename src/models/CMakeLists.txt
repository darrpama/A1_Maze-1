cmake_minimum_required(VERSION 3.5)

project(MazeModels VERSION 0.1 LANGUAGES CXX)
option(COVERAGE OFF)

set(LIBGCOV "")
if (COVERAGE)
    set(LIBGCOV "gcov")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(${PROJECT_NAME}_SOURCES 
    type.h
    utils.h

    maze/maze.cc
    maze/maze.h
    maze/maze_saver.cc
    maze/maze_saver.h
    maze/maze_parser.cc
    maze/maze_parser.h
    maze/maze_generator.cc
    maze/maze_generator.h

    cave/cave.cc
    cave/cave.h
)

add_library(${PROJECT_NAME} STATIC
    ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${LIBGCOV}
)
