cmake_minimum_required(VERSION 3.5)

project(MazeProject VERSION 0.1 LANGUAGES CXX)

option(INSTALL OFF)
option(TESTING OFF)
option(COVERAGE OFF)

if (INSTALL)
    add_subdirectory(views)
endif()

if (TESTING AND (NOT COVERAGE))
    add_subdirectory(tests)
endif()

if (COVERAGE)
    set(COVERAGE ON)
    add_subdirectory(tests)
endif()
