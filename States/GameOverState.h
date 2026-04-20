#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "../GameManager/Game.h"
#include "../DEFENITIONS.h"
#include <memory>


namespace Tokyo {
    class GameOverState : public State {
        public:

        GameOverState(GameDataRef data, GameID gameID, Winner winner);

        void Init();
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

        private:
        GameDataRef _data;

        GameID _gameID;
        Winner _winner;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _playAgain;
        std::unique_ptr<sf::Sprite> _home;
        std::unique_ptr<sf::Sprite> _medal;
        std::unique_ptr<sf::Text> _announce;

        std::unique_ptr<sf::Sound> _gameover;
        std::unique_ptr<sf::Sound> _draw;
    };
}