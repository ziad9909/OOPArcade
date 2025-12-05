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
    SUS.h
    SUS.cpp
    Word_TTT.h
    Word_TTT.cpp
    4x4_TTT_Classes.h
    4x4_TTT_Classes.cpp
    Obstacle6x6_TTT.h 
    Obstacle6x6_TTT.cpp
    Timed_TTT_Classes.h
    Timed_TTT_Classes.cpp
    Four_in_a_row.cpp
    Diamond_TTT_Classes.h 
    Diamond_TTT_Classes.cpp
    FiveByFiveTTT_Classes.h
    FiveByFiveTTT_Classes.cpp
    Pyramid_TTT_Classes.h
    Pyramid_TTT_Classes.cpp
    Memory_TTT_Classes.h
    Memory_TTT_Classes.cpp
)
