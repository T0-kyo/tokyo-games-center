#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "../GameManager/Game.h"
#include "../DEFENITIONS.h"
#include <memory>

namespace Tokyo{

    class HomeState : public State {
        public:
        HomeState( GameDataRef data, bool isMute );
        ~HomeState();

        void Init();
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

        private:
        GameDataRef _data;
        bool _isMute = false;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Text> _yes;
        std::unique_ptr<sf::Text> _no;
        std::unique_ptr<sf::Text> _quest;

        std::unique_ptr<sf::Sound> _option;
    };
}