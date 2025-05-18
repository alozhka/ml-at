cmake_minimum_required(VERSION 3.30)
project(lucky_ticket)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")

add_executable(lucky_ticket main.cpp)
