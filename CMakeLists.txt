cmake_minimum_required(VERSION 3.21)
project(NETSIM)

set(CMAKE_CXX_STANDARD 17)

add_executable(NETSIM main.cpp)

include_directories(
        include
)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        include/package.hpp include/types.hpp include/storage_types.hpp)

add_executable(netsim ${SOURCE_FILES} main.cpp)