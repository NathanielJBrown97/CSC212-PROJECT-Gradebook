cmake_minimum_required(VERSION 3.25)
project(211Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(211Project
        gradebook.cpp
        gradebook.h
        main.cpp)
