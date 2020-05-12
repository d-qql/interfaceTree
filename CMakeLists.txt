cmake_minimum_required(VERSION 3.10)
project(interfaceTree)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_executable(interfaceTree main.cpp Container.h Template.h Template.cpp)