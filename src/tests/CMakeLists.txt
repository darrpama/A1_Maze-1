cmake_minimum_required(VERSION 3.5)

project(MazeTests VERSION 0.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DGTEST_LANGUAGE_CXX17)

option(COVERAGE OFF)
if (COVERAGE)
    add_compile_options(-fprofile-arcs -ftest-coverage -fno-elide-constructors)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

if (APPLE)
    set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
endif()   

add_compile_options(-Wall -Werror -Wextra)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(${PROJECT_NAME}_SOURCES
    run_all_tests.cc
    cave_test.cc
    maze_saver_test.cc
    maze_parser_test.cc
    maze_resolver_test.cc
    maze_generator_test.cc
)

add_subdirectory(../models ${CMAKE_CURRENT_BINARY_DIR}/models)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
    MazeModels
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    pthread
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_test(tests ${PROJECT_NAME})
