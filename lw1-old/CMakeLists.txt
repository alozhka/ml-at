cmake_minimum_required(VERSION 3.9)
project(timber-cutter)

set(CMAKE_CXX_STANDARD 26)


add_executable(tests tests.cpp)
add_executable(timber-cutter timber-cutter.cpp)