cmake_minimum_required(VERSION 3.10)

project(GamesAssignment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FIX: Add the ROOT directory to the include path.
# This allows includes like "BoardGameFramework/File.h" to work.
include_directories(
    "${PROJECT_SOURCE_DIR}"
)

add_executable(Game
    main.cpp
    NumericalTTT/NumericalTTT_Board.cpp
    NumericalTTT/NumericalTTT_UI.cpp
    SUS/SUS_Board.cpp
    SUS/SUS_UI.cpp
    PyramidTTT/PyramidTTT_Board.cpp
    PyramidTTT/PyramidTTT_UI.cpp
    WordTTT/WordTTT_Board.cpp
    WordTTT/WordTTT_UI.cpp
    MisereTTT/MisereTTT_Board.cpp
    MisereTTT/MisereTTT_UI.cpp
    ObstaclesTTT/ObstaclesTTT_Board.cpp
    ObstaclesTTT/ObstaclesTTT_UI.cpp
    DiamondTTT/DiamondTTT_Board.cpp
    DiamondTTT/DiamondTTT_UI.cpp
    5x5_TTT/5x5_TTT_Board.cpp
    5x5_TTT/5x5_TTT_UI.cpp
    4x4_TTT/4x4_TTT_Board.cpp
    4x4_TTT/4x4_TTT_UI.cpp
    FourInARow/FourInARow_Board.cpp
    FourInARow/FourInARow_UI.cpp
    Infinity_TTT/Infinity_Board.cpp
    Infinity_TTT/Infinity_UI.cpp
    MemoryTTT/MemoryTTT_Board.cpp
    MemoryTTT/MemoryTTT_UI.cpp
    UltimateTTT/Ultimate_Board.cpp
    UltimateTTT/Ultimate_UI.cpp
)