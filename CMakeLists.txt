cmake_minimum_required(VERSION 2.8)

project(pathtracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -O3")

file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

add_executable(pathtracer ${SOURCES})

# for pngwriter
include_directories(/usr/include/freetype2 /usr/local/include)
target_link_libraries(pathtracer png PNGwriter z freetype)
