cmake_minimum_required(VERSION 3.15)
# find_package(OpenMP REQUIRED)

project(libreMCM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
# set (CMAKE_CXX_FLAGS "-g -Wall -Wpedantic -fsanitize=address,leak")
set (CMAKE_CXX_FLAGS "-g -fopenmp -O2 -Wall -Wpedantic -fsanitize=address,leak")
# set (CMAKE_CXX_FLAGS "-g -Wall -Wpedantic -fsanitize=address,leak")
# set (CMAKE_CXX_FLAGS "-Wall -Wpedantic -fsanitize=address,leak")

# set (CMAKE_CXX_FLAGS "-g -Wall -Werror -Wpedantic")
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(main src/main.cpp ${SRC_FILES})
