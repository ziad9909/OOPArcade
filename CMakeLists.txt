cmake_minimum_required(VERSION 3.30)
project(OOPArcade)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOPArcade
<<<<<<< Updated upstream
    main.cpp                 # This is your renamed XO_Demo.cpp
    BoardGame_Classes.h
    XO_Classes.cpp
    XO_Classes.h
    Numerical_TTT_Classes.cpp  # Your new .cpp file
    Numerical_TTT_Classes.h    # Your new .h file
)
=======
    main.cpp
    XO_Classes.cpp
    Numerical_TTT_Classes.cpp
    FiveByFiveTTT_Classes.cpp
    Misere_TTT_Classes.cpp
)


>>>>>>> Stashed changes
