cmake_minimum_required(VERSION 3.15)

project(libreMCM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
file(GLOB_RECURSE SRC_FILES src/*/*.cpp)
add_executable(main src/main.cpp ${SRC_FILES})
