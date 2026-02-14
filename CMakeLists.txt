cmake_minimum_required(VERSION 3.10)

project(GamesAssignment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FIX: Add the ROOT directory to the include path.
# This allows includes like "BoardGameFramework/File.h" to work.
include_directories(
    "${PROJECT_SOURCE_DIR}"
    "C:/SFML-3.0/include"
)

add_executable(Game
    main.cpp
    GameCenter/NumericalTTT/NumericalTTT_Board.cpp
    GameCenter/NumericalTTT/NumericalTTT_UI.cpp
    GameCenter/SUS/SUS_Board.cpp
    GameCenter/SUS/SUS_UI.cpp
    GameCenter/PyramidTTT/PyramidTTT_Board.cpp
    GameCenter/PyramidTTT/PyramidTTT_UI.cpp
    GameCenter/WordTTT/WordTTT_Board.cpp
    GameCenter/WordTTT/WordTTT_UI.cpp
    GameCenter/MisereTTT/MisereTTT_Board.cpp
    GameCenter/MisereTTT/MisereTTT_UI.cpp
    GameCenter/ObstaclesTTT/ObstaclesTTT_Board.cpp
    GameCenter/ObstaclesTTT/ObstaclesTTT_UI.cpp
    GameCenter/DiamondTTT/DiamondTTT_Board.cpp
    GameCenter/DiamondTTT/DiamondTTT_UI.cpp
    GameCenter/5x5_TTT/5x5_TTT_Board.cpp
    GameCenter/5x5_TTT/5x5_TTT_UI.cpp
    GameCenter/4x4_TTT/4x4_TTT_Board.cpp
    GameCenter/4x4_TTT/4x4_TTT_UI.cpp
    GameCenter/FourInARow/FourInARow_Board.cpp
    GameCenter/FourInARow/FourInARow_UI.cpp
    GameCenter/Infinity_TTT/Infinity_Board.cpp
    GameCenter/Infinity_TTT/Infinity_UI.cpp
    GameCenter/MemoryTTT/MemoryTTT_Board.cpp
    GameCenter/MemoryTTT/MemoryTTT_UI.cpp
    GameCenter/UltimateTTT/Ultimate_Board.cpp
    GameCenter/UltimateTTT/Ultimate_UI.cpp
    GameManager/StateMachine.cpp
    GameManager/AssetManager.cpp
    GameManager/InputManager.cpp
    GameManager/Game.cpp
    GameManager/SplashState.cpp
    GameManager/MainState.cpp
    GameManager/MainMenuState.cpp
)

#link-SFML
target_link_libraries(Game
    "C:/SFML-3.0/lib/libsfml-graphics.a"
    "C:/SFML-3.0/lib/libsfml-window.a"
    "C:/SFML-3.0/lib/libsfml-system.a"
    "C:/SFML-3.0/lib/libsfml-audio.a"
)