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
    };
}