cmake_minimum_required(VERSION 3.10)
project(OOPArcade)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOPArcade
    main.cpp
    BoardGame_Classes.h
    XO_Classes.cpp
    XO_Classes.h
    Numerical_TTT_Classes.cpp
    Numerical_TTT_Classes.h
    Misere_TTT_Classes.cpp
    Misere_TTT_Classes.h
)
