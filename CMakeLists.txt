cmake_minimum_required(VERSION 3.30)
project(OOPArcade)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# Add your new files to this list
add_executable(OOPArcade
    main.cpp
    BoardGame_Classes.h
    XO_Classes.cpp
    XO_Classes.h
    Numerical_TTT_Classes.cpp
    Numerical_TTT_Classes.h
    FiveByFiveTTT_Classes.cpp
    FiveByFiveTTT_Classes.h
)
