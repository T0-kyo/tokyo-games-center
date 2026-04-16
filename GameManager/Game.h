#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"

using namespace std;

namespace Tokyo {

    // Struct that holds all the data for games,
    // so there is only one object of each manager that can manage any game instead of making one object for each game.
    struct GameData {
        StateMachine machine;
        InputManager input;
        AssetManager assets;
        sf::RenderWindow window;

        sf::Clock _delay;   // Clock to delay input when switching States

        int _score1;
        int _score2;
    };

    // smart pointer that will be passed to states so they can access the data in the game and use it to manage the game,
    // Instead of making multiple objects of the GameData for each state.
    typedef std::shared_ptr<GameData> GameDataRef;

    // The main game class that will be used to run the game and manage the states.
    class Game {

        private:
        const float dt = 1.0f / 60.0f;   // Delta time for fixed time step
        sf::Clock _clock;   // Clock to track time for fixed time step
        GameDataRef _data = make_shared<GameData>();   // Shared pointer to the game data that will be passed to states
        void Run();   // Function that will run the game loop and manage the states, it will be called in the constructor of the game class.

        public:
        Game( unsigned int width, unsigned int height, string title );   // Constructor that will initialize the game data and create the window, it will also call the Run function to start the game loop.
    };
}