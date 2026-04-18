#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "../GameManager/Game.h"
#include <memory>
#include "../DEFENITIONS.h"


namespace Tokyo {
    class MainState : public State {

        public:
        MainState ( GameDataRef data );

        void Init();
        void HandleInput();
        void Update ( float dt );
        void Draw ( float dt );

        private:
        GameDataRef _data;
        bool _isStartClicked = false;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Text> _startButton;
        std::unique_ptr<sf::Sprite> _clearBg;
    };
}