cmake_minimum_required(VERSION 3.30)
project(OOPArcade)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOPArcade
    BoardGame_Classes.h
    XO_Classes.cpp
    XO_Classes.h
    XO_Demo.cpp)
