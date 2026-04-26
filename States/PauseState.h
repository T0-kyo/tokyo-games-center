#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "../GameManager/Game.h"
#include "../DEFENITIONS.h"
#include <memory>

namespace Tokyo{

    class PauseState : public State {
        public:
        PauseState( GameDataRef data, GameID gameId, bool isMute);
        ~PauseState();

        void Init();
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

        private:
        GameDataRef _data;
        GameID _gameId;
        bool _isMute = false;
        sf::Clock _clock;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _resume;
        std::unique_ptr<sf::Sprite> _home;
        std::unique_ptr<sf::Sprite> _book;
        std::unique_ptr<sf::Sprite> _rules;

        std::unique_ptr<sf::Sound> _bookSound;
        std::unique_ptr<sf::Sound> _option;

        bool isRules = false;
    };
}