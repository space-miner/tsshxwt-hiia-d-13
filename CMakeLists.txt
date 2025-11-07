project (bwt)
cmake_minimum_required (VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file (GLOB_RECURSE SOURCES "src/*.cpp")

add_executable (xd ${SOURCES})