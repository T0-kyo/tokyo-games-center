#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include <memory>

namespace Tokyo {

    class SplashState : public State {

        public:
        SplashState( GameDataRef data );

        void Init();
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

        private:
        GameDataRef _data;
        sf::Clock _clock;
        std::unique_ptr<sf::Sprite> _background;
    };
}