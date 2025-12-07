cmake_minimum_required(VERSION 3.10)
project(OOPArcade)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOPArcade
    main.cpp
    XO_Classes.cpp
    Numerical_TTT_Classes.cpp
    Misere_TTT_Classes.cpp
    SUS.cpp
    Word_TTT.cpp
    4x4_TTT_Classes.cpp
    Obstacle6x6_TTT.cpp
    Timed_TTT_Classes.cpp
    Four_in_a_row.cpp
    Diamond_TTT_Classes.cpp
    FiveByFiveTTT_Classes.cpp
    Pyramid_TTT_Classes.cpp
    Memory_TTT_Classes.cpp
    Ultimate_TTT_Classes.cpp
)
