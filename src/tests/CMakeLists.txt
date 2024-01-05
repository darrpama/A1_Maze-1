cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

project(MazeTests VERSION 0.1 LANGUAGES CXX)
option(COVERAGE OFF)

if (COVERAGE)
    add_compile_options(--coverage -fno-elide-constructors)
endif()

if (APPLE)
    add_link_options("-Wl,-no_compact_unwind")
    # set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
endif()
    
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
enable_testing()
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
