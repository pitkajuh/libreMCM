cmake_minimum_required(VERSION 3.15)
project(libreMCM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++20 -g -O0 -Wall -Wextra -Wpedantic -Wshadow -fsanitize=address,undefined -fno-omit-frame-pointer ")
set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(main src/main.cpp ${SRC_FILES})
