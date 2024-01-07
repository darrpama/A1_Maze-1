cmake_minimum_required(VERSION 3.5)

project(MazeController VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(../models ${CMAKE_CURRENT_BINARY_DIR}/models)

set(${PROJECT_NAME}_SOURCES 
    controller_singleton.cc
    controller_singleton.h
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
    MazeModels
)
