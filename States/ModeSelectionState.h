#pragma once

#include "../DEFENITIONS.h"
#include "State.h"
#include "../GameManager/Game.h"
#include <memory>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace Tokyo {

    class ModeSelectionState : public State {
        public:

        ModeSelectionState ( GameDataRef data, GameID gameID );

        void Init();
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

        private:

        GameID _gameID;
        GameDataRef _data;
        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Text> _choice1;
        std::unique_ptr<sf::Text> _choice2;
        std::unique_ptr<sf::Sprite> _backButton;
    };
}