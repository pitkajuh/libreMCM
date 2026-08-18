cmake_minimum_required(VERSION 3.15)
project(libreMCM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-openmp -03")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wpedantic -fsanitize=address,leak")
set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(main src/main.cpp ${SRC_FILES})
